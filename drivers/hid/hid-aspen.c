/*
 * HID driver for Lab126 Bluetooth Keyboard
 * adapted from hid_magneto.c
 *
 * Copyright (C) 2014 Primax Electronics Ltd.
 *
 * Author:
 *	Brent Chang <brent.chang@primax.com.tw>
 *  Brothans Li <brothans.li@primax.com.tw>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#include <linux/device.h>
#include <linux/hid.h>
#include <linux/input/mt.h>
#include <linux/module.h>
#include <linux/delay.h>
#include "hid-ids.h"

#include <linux/kernel.h>
#include <linux/version.h>

/* Debug message */

#undef ASPEN_DEBUG
#ifdef ASPEN_DEBUG
	#define DEBUG_MSG(fmt, args...)	printk(fmt, ## args)
#else
	#define DEBUG_MSG(fmt, args...)
#endif

#undef ASPEN_TRACE
#ifdef ASPEN_TRACE
	#define TRACE_MSG(fmt, args...)	printk(fmt, ## args)
#else
	#define TRACE_MSG(fmt, args...)
#endif

/* Firmware version */
#define ASPEN_DRV_VERSION __DATE__

/* Report id */
#define REPORT_ID_KEYBOARD		0x01
#define REPORT_ID_MOUSE			0x07
#define REPORT_ID_TOUCHPAD      0x06
/* Handle Lab126 Keyboard shop key */
#define REPORT_ID_CONSUMER		0x0c
#define REPORT_ID_LAB126		0x09

#define CAPS_OFF	0
#define CAPS_ON		1

static int caps_status = CAPS_OFF;

/* CapsLock set feature report command */
static unsigned char buf_on[] = { 0x64, 0x02 };
static unsigned char buf_off[] = { 0x64, 0x00 };

/* Conditionally enable Multi Touch for development */
#define SUPPORT_MULTITOUCH      TRUE

/* Max multi-touch count */
#define MAX_MULTITOUCH_COUNT	2

/* Track Pad Constants */

#define TRACKPAD_MIN_X 0
#define TRACKPAD_MAX_X 590
#define TRACKPAD_MIN_Y -165
#define TRACKPAD_MAX_Y 165
#define TRACKPAD_RES_X 590
#define TRACKPAD_RES_Y 330

#define TOUCH_STATE_MASK  0xff
#define TOUCH_STATE_NONE  0x00

#define SHOP_KEY			0x86
#define BRIGHTNESSUP		0x87
#define BRIGHTNESSDOWN		0x88
#define TRACKPAD_LOCK		0x90
#define TRACKPAD_UNLOCK		0x91

/*
 * Device structure for matched devices
 * @quirks: Currently unused.
 * @input: Input device through which we report events.
 * @lastFingCount: Last finger count for multi-touch.
 * @DPadPressed: 4-direction D-pad status array
 * @lastDirection: Last direction of gesture (4-direction)
 * @DPadTransformed: Record if D-Pad long pressed action been transformed
 * @lastZoomStart: Record last received zoom event time
 */
struct aspen_device {
	unsigned long quirks;
	struct input_dev *input;
	int lastFingCount;
	char DPadPressed[4];
	int lastDirection;
	int DPadTransformed;
	unsigned long lastZoomStart;
	unsigned char initDone;
	struct timer_list dpad_timer;	/* brent */
	struct timer_list delay_timer;	/* brent */
};

/*
 * Timer callback function for first key event delay feature.
 * This is used to delay input events until evdev been created successfully.
 */
void aspen_delay_func(unsigned long data)
{
	struct aspen_device *aspen_dev = (struct aspen_device *) data;

	TRACE_MSG("%s: Ready to send input event\n", __func__);
	aspen_dev->initDone = 1;

	input_sync(aspen_dev->input);
}

#ifdef SUPPORT_MULTITOUCH
/*
 * The following payload data structure is what we expect to get from the Aspen side.
 * Note: The first byte before touchData[0] is the report ID (0x06 in this case)
 *
 *	touchData[0] = 0x02;					Contact Count
 *	touchData[1] = 0x01;					Tip switch
 *	touchData[2] = 0x11;					Finger ID
 *	touchData[3] = (xInc[0]&0xff00)>>8;		X1
 *	touchData[4] = (xInc[0]&0xff);			X1
 *	touchData[5] = (yInc[0]&0xff00)>>8;		Y1
 *	touchData[6] = (yInc[0]&0xff);			Y1
 *	touchData[7] = 0x01;					Tip switch
 *	touchData[8] = 0x12;					Finger ID
 *	touchData[9] = (xInc[1]&0xff00)>>8;		X2
 *	touchData[10]= (xInc[1]&0xff);			X2
 *	touchData[11]= (yInc[1]&0xff00)>>8;		Y2
 *	touchData[12]= (yInc[1]&0xff);			Y2
 *
*/
static void aspen_emit_touch(struct aspen_device *aspen_dev, int raw_id, u8 *tdata)
{
	struct input_dev *input = aspen_dev->input;
	int id, x, y, state, down, i = 0;

	id = raw_id;
	DEBUG_MSG("%s - %d %2x %2x %2x %2x\n", __func__, raw_id, tdata[i+2], tdata[i+3], tdata[i+4], tdata[i+5]);
	/* check to see if this is the very first touch, capture it into the previous array for the very first touch */

	x = (tdata[i+3] | (tdata[i+2]<<8));
	y = -(tdata[i+5] | (tdata[i+4]<<8));

	DEBUG_MSG("X = %d : Y = %d\n", x, y);

	state = tdata[i+1] ^ TOUCH_STATE_MASK;
	down = (state != TOUCH_STATE_NONE);

	DEBUG_MSG("rawid = %d : x=%d : y=%d down=%d tdada[i+1]=%2x\n", raw_id, x, y, down, tdata[i+1]);

	input_mt_slot(input, id);
    /* Generate the input events for this touch. */
	if (down) {
		input_mt_report_slot_state(input, MT_TOOL_FINGER, down);
		input_report_abs(input, ABS_MT_POSITION_X, x);
		input_report_abs(input, ABS_MT_POSITION_Y, y);
	} else {
		input_mt_report_slot_state(input, MT_TOOL_FINGER, false);
	}
}
#endif

/*
 *  Deal with input raw event
 *  REPORT_ID:		DESCRIPTION:
 *	0x01			Keyboard
 *	0x07			Mouse
 *	0x08			Touchpad
 *
 *	0x09			Lab126 Keyboard : handle Shop key
 */

static int aspen_raw_event(struct hid_device *hdev, struct hid_report *report,
	 u8 *data, int size)
{
	struct aspen_device *aspen_dev = hid_get_drvdata(hdev);
	int ret;

	char keyCode;
	/* int keyStatus; */
	int delay_count = 0;
	int i, clicks = 0;
	int npoints;

	struct input_dev *input = aspen_dev->input;

	DEBUG_MSG("%s: report id: %d, size: %d report data: ", __func__, report->id, size);
	for (i = 0; i < size; i++) {
		DEBUG_MSG("0x%02x ", data[i]);
	}
	DEBUG_MSG("\n");

	/* Add loop to delay input event while init not finished */
	while (!(hdev->claimed & HID_CLAIMED_INPUT) || !aspen_dev->initDone) {

		delay_count++;
		TRACE_MSG("%s: wait for initialization\n", __func__);
		msleep(500);
	}
	TRACE_MSG("%s: event delay time = %d ms\n", __func__, delay_count * 500);
	TRACE_MSG("%s: hdev->claimed = 0x%x, ready to send input event\n", __func__, hdev->claimed);

	switch (report->id) {

	case REPORT_ID_KEYBOARD:	/* Keyboard event: 0x01 */
		DEBUG_MSG("%s: Enter:: received REPORT_ID_KEYBOARD event\n", __func__);
		keyCode = data[3];
		switch (keyCode) {
		case 0x39:	/* Handle CapsLock key */
			DEBUG_MSG("%s: handle Lab126 KEY_CAPSLOCK:  keyCode = 0x%02x\n", __func__, keyCode);
			if (caps_status) {
				/* Current Caps status: On ==> changed to Off */
				DEBUG_MSG("%s: CapsLock status: On ---> Off\n", __func__);
				caps_status = CAPS_OFF;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 15, 0))
				ret = hid_hw_raw_request(hdev, buf_off[0], buf_off, sizeof(buf_off),
							HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
#else
				ret = hdev->hid_output_raw_report(hdev, buf_off, sizeof(buf_off), HID_FEATURE_REPORT);
#endif
			} else {
				/* Current Caps status: Off ==> changed to On */
				DEBUG_MSG("%s: CapsLock status: Off ---> On\n", __func__);
				caps_status = CAPS_ON;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 15, 0))
				ret = hid_hw_raw_request(hdev, buf_on[0], buf_on, sizeof(buf_on),
							HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
#else
				ret = hdev->hid_output_raw_report(hdev, buf_on, sizeof(buf_on), HID_FEATURE_REPORT);
#endif
			}

			if (ret < 0)
				DEBUG_MSG("%s: set HID_FEATURE_REPORT of CapsLock failed\n", __func__);

			/* pass event to system */
			break;
		}
		break;

	case REPORT_ID_CONSUMER:		/* Consumer event: 0x0c */
		DEBUG_MSG("%s: Enter:: received REPORT_ID_CONSUMER event\n", __func__);
		break;

	case REPORT_ID_MOUSE:		/* Mouse event: 0x07 */
		DEBUG_MSG("%s: Enter:: received REPORT_ID_MOUSE event\n", __func__);
		break;

	case REPORT_ID_TOUCHPAD:	/* Touchpad event: 0x06 */
		/* N*6 bytes of touch data. */
		if (size < 2 || ((size - 2) % 6) != 0)
			return 0;

		npoints = (size - 2) / 6;

/*		DEBUG_MSG("%s: Enter:: received REPORT_ID_TOUCHPAD event: size = %d , npoints = %d\n", __func__, size, npoints); */
		for (i = 0; i < npoints; i++)
			aspen_emit_touch(aspen_dev, i, data + 2 + i * 6);

		clicks = data[2] & 0x01;
		input_report_key(input, BTN_MOUSE, clicks & 1);

		input_mt_report_pointer_emulation(input, true);
		input_sync(input);
		return 1;

		break;

	case REPORT_ID_LAB126:		/* Lab126 Keyboard event: 0x09 */
		keyCode = data[1];
		DEBUG_MSG("%s: Enter:: received REPORT_ID_LAB126 event keyCode = %02x\n",
			__func__, keyCode);
		switch (keyCode) {
		case SHOP_KEY:
			DEBUG_MSG("%s: handle Lab126 Keyboard special case: (SHOP) keyCode = 0x%02x\n",
				__func__, keyCode);
			input_report_key(aspen_dev->input, KEY_SHOP, 1);
			input_sync(aspen_dev->input);
			input_report_key(aspen_dev->input, KEY_SHOP, 0);
			input_sync(aspen_dev->input);
			break;

		case BRIGHTNESSUP:
			DEBUG_MSG("%s: handle Lab126 Keyboard special case:  (BRIGHTNESSUP) keyCode = 0x%02x\n",
				__func__, keyCode);
			input_report_key(aspen_dev->input, KEY_BRIGHTNESSUP, 1);
			input_sync(aspen_dev->input);
/*
			input_report_key(aspen_dev->input, KEY_BRIGHTNESSUP, 0);
			input_sync(aspen_dev->input);
*/
			break;

		case BRIGHTNESSDOWN:
			DEBUG_MSG("%s: handle Lab126 Keyboard special case:  (BRIGHTNESSDOWN) keyCode = 0x%02x\n",
				__func__, keyCode);
			input_report_key(aspen_dev->input, KEY_BRIGHTNESSDOWN, 1);
			input_sync(aspen_dev->input);
/*
			input_report_key(aspen_dev->input, KEY_BRIGHTNESSDOWN, 0);
			input_sync(aspen_dev->input);
*/
			break;
		case TRACKPAD_LOCK:
			DEBUG_MSG("%s: handle Lab126 Keyboard special case:  (Lock screen) keyCode = 0x%02x\n",
				__func__, keyCode);
			input_report_key(aspen_dev->input, KEY_LAB126_TP_LOCK, 1);
			input_sync(aspen_dev->input);
			input_report_key(aspen_dev->input, KEY_LAB126_TP_LOCK, 0);
			input_sync(aspen_dev->input);
			break;

		case TRACKPAD_UNLOCK:
			DEBUG_MSG("%s: handle Lab126 Keyboard special case:  (UnLock screen) keyCode = 0x%02x\n",
				__func__, keyCode);
			input_report_key(aspen_dev->input, KEY_LAB126_TP_UNLOCK, 1);
			input_sync(aspen_dev->input);
			input_report_key(aspen_dev->input, KEY_LAB126_TP_UNLOCK, 0);
			input_sync(aspen_dev->input);

			break;

		case 0x00:
			DEBUG_MSG("%s: handle Lab126 Keyboard special case:  (KEYS RELEASED) keyCode = 0x%02x\n",
				__func__, keyCode);
			input_report_key(aspen_dev->input, KEY_BRIGHTNESSUP, 0);
			input_sync(aspen_dev->input);
			input_report_key(aspen_dev->input, KEY_BRIGHTNESSDOWN, 0);
			input_sync(aspen_dev->input);
			break;
		}
		TRACE_MSG("%s: returning 1 - handled report id\n", __func__);
		return 1;
		break;
	default:	/* Unknown report id */
		DEBUG_MSG("%s: unhandled report id %d\n", __func__, report->id);
		break;
	}

	TRACE_MSG("%s: returning 0 to pass event to linux input syssystem\n", __func__);
	return 0;	/* Pass event to linux input subsystem */

}


/*
 * Probe function for matched devices
 */
static int aspen_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	int ret;
	struct aspen_device *aspen;

	DEBUG_MSG("%s\n", __func__);

	aspen = kmalloc(sizeof(*aspen), GFP_KERNEL | __GFP_ZERO);
	if (aspen == NULL) {
		TRACE_MSG("%s: can't alloc aspen descriptor\n", __func__);
		return -ENOMEM;
	}

	aspen->quirks = id->driver_data;
	hid_set_drvdata(hdev, aspen);

	ret = hid_parse(hdev);
	if (ret) {
		TRACE_MSG("%s: parse failed\n", __func__);
		goto fail;
	}

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	/* ret = hid_hw_start(hdev, HID_CONNECT_HIDINPUT); */
	if (ret) {
		TRACE_MSG("%s: hw start failed\n", __func__);
		goto fail;
	}

	/* Initialize CapsLock status: Off */
	caps_status = CAPS_OFF;

#if 0
	/* Send CapsLock set feature report command */
	if (caps_status) {
		/* CapsLock status: On */
		DEBUG_MSG("%s: Initialize CapsLock status: On\n", __func__);
		ret = hdev->hid_output_raw_report(hdev, buf_on, sizeof(buf_on), HID_FEATURE_REPORT);
	} else {
		/* CapsLock status: Off */
		DEBUG_MSG("%s: Initialize CapsLock status: Off\n", __func__);
	}

	if (ret < 0) {
		DEBUG_MSG("%s: set HID_FEATURE_REPORT of CapsLock failed\n", __func__);
		goto fail;
	}
#endif


	TRACE_MSG("%s: Init ok, hdev->claimed = 0x%x\n", __func__, hdev->claimed);

	init_timer(&aspen->delay_timer);
	aspen->delay_timer.function = aspen_delay_func;
	aspen->delay_timer.expires = jiffies + 1*HZ;
	aspen->delay_timer.data = (unsigned long) aspen;
	add_timer(&aspen->delay_timer);

	return 0;

fail:
	kfree(aspen);
	return ret;
}


/*
 * Input settings and key mapping for matched devices
 *  USAGE_PAGE_ID:      DESCRIPTION:
 *		0x0001			Generic Desktop
 *		0x0006			Generic Device Control
 *		0x0007			Keyboard/Keypad
 *		0x0008			LED
 *		0x0009			BUTTON
 *		0x000c			Consumer
 *		0x000d			Digitizer
 */

static int aspen_input_mapping(struct hid_device *hdev,
		struct hid_input *hi, struct hid_field *field,
		struct hid_usage *usage, unsigned long **bit, int *max)
{
	struct input_dev *input = hi->input;
	struct aspen_device *aspen = hid_get_drvdata(hdev);

	if (!aspen->input)
		aspen->input = hi->input;


		DEBUG_MSG("%s: Usage page = 0x%x, Usage id = 0x%x\n", __func__,
				  (usage->hid & HID_USAGE_PAGE) >> 4, usage->hid & HID_USAGE);

	switch (usage->hid & HID_USAGE_PAGE) {
	case HID_UP_GENDESK:	/* 0x0001 */
		/* Define accepted event */
		set_bit(EV_REL, input->evbit);
		set_bit(EV_ABS, input->evbit);
		set_bit(EV_KEY, input->evbit);
		set_bit(EV_SYN, input->evbit);

		/* Handle Lab126 Keyboard shop key */
		set_bit(KEY_SHOP, input->keybit);
		set_bit(KEY_BRIGHTNESSUP, input->keybit);
		set_bit(KEY_BRIGHTNESSDOWN, input->keybit);
		set_bit(KEY_LAB126_TP_LOCK, input->keybit);
		set_bit(KEY_LAB126_TP_UNLOCK, input->keybit);
		break;

	case HID_UP_KEYBOARD:	/* 0x0007 */
		break;

	case HID_UP_LED:		/* 0x0008 */
		break;

	case HID_UP_BUTTON:		/* 0x0009 */
		break;

	case HID_UP_CONSUMER:	/* 0x000c */
		break;

	case HID_UP_DIGITIZER:	/* 0x000d */
		break;

	default:
		break;
	}


	/*
	 * Return a 1 means a matching mapping is found, otherwise need
     * HID driver to search mapping in hid-input.c
	 */
	return 0;
}

#ifdef SUPPORT_MULTITOUCH
static int aspen_setup_input(struct input_dev *input, struct hid_device *hdev)
{
	int error;

	clear_bit(BTN_RIGHT, input->keybit);
	clear_bit(BTN_MIDDLE, input->keybit);
	set_bit(BTN_MOUSE, input->keybit);

	set_bit(EV_KEY, input->evbit);
	set_bit(EV_ABS, input->evbit);
	set_bit(BTN_TOUCH, input->keybit);
	set_bit(BTN_TOOL_FINGER, input->keybit);

	error = input_mt_init_slots(input, 2, 0);
	if (error)
		return error;

	/* Note: Touch Y position from the device is inverted relative
	 * to how pointer motion is reported (and relative to how USB
	 * HID recommends the coordinates work).  This driver keeps
	 * the origin at the same position, and just uses the additive
	 * inverse of the reported Y.
	 */

	input_set_abs_params(input, ABS_X, TRACKPAD_MIN_X,
			     TRACKPAD_MAX_X, 0, 0);
	input_set_abs_params(input, ABS_Y, TRACKPAD_MIN_Y,
			     TRACKPAD_MAX_Y, 0, 0);
	input_set_abs_params(input, ABS_MT_POSITION_X,
			     TRACKPAD_MIN_X, TRACKPAD_MAX_X, 0, 0);
	input_set_abs_params(input, ABS_MT_POSITION_Y,
			     TRACKPAD_MIN_Y, TRACKPAD_MAX_Y, 0, 0);

	input_abs_set_res(input, ABS_X, TRACKPAD_RES_X);
	input_abs_set_res(input, ABS_Y, TRACKPAD_RES_Y);
	input_abs_set_res(input, ABS_MT_POSITION_X,
			  TRACKPAD_RES_X);
	input_abs_set_res(input, ABS_MT_POSITION_Y,
				  TRACKPAD_RES_Y);

	return 0;
}

static int aspen_input_configured(struct hid_device *hdev,
		struct hid_input *hi)

{
	struct aspen_device *aspen = hid_get_drvdata(hdev);

	int ret = aspen_setup_input(aspen->input, hdev);
	if (ret) {
		hid_err(hdev, "aspen setup input failed (%d)\n", ret);
		/* clean msc->input to notify probe() of the failure */
		aspen->input = NULL;
	}
	return ret;
}
#endif

/*
 * Remove function
 */
static void aspen_remove(struct hid_device *hdev)
{
	struct aspen_device *aspen = hid_get_drvdata(hdev);

	DEBUG_MSG("%s\n", __func__);
	hid_hw_stop(hdev);

	if (NULL != aspen)
		kfree(aspen);
}


/*
 * Device list that matches this driver
 */
static const struct hid_device_id aspen_devices[] = {
	{ HID_BLUETOOTH_DEVICE(BT_VENDOR_ID_LAB126, USB_DEVICE_ID_LAB126_ASPEN_KB_US) },
	{ HID_BLUETOOTH_DEVICE(BT_VENDOR_ID_LAB126, USB_DEVICE_ID_LAB126_ASPEN_KB_UK) },
	{ }	/* Terminating entry */
};
MODULE_DEVICE_TABLE(hid, aspen_devices);


/*
 * Special driver function structure for matched devices
 */
static struct hid_driver aspen_driver = {
	.name = "aspen_lab126_keyboard",
	.id_table = aspen_devices,
	.raw_event = aspen_raw_event,
	.probe = aspen_probe,
	.remove = aspen_remove,
	.input_mapping = aspen_input_mapping,
#ifdef SUPPORT_MULTITOUCH
	.input_configured = aspen_input_configured,
#endif
};


/*
 * Init function
 */
static int __init aspen_init(void)
{
	int ret = hid_register_driver(&aspen_driver);

	DEBUG_MSG("%s: hid_register_driver returned %d\n", __func__, ret);
	DEBUG_MSG("%s: aspen driver version = %s\n", __func__, ASPEN_DRV_VERSION);
	return ret;
}


/*
 * Exit function
 */
static void __exit aspen_exit(void)
{
	DEBUG_MSG("%s\n", __func__);
	hid_unregister_driver(&aspen_driver);
}


module_init(aspen_init);
module_exit(aspen_exit);

MODULE_AUTHOR("moragues@lab126.com");
MODULE_LICENSE("GPL");

/* End of file */
