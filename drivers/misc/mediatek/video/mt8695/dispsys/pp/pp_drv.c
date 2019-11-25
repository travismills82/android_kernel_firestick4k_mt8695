/*----------------------------------------------------------------------------*
 * Copyright Statement:                                                       *
 *                                                                            *
 *   This software/firmware and related documentation ("MediaTek Software")   *
 * are protected under international and related jurisdictions'copyright laws *
 * as unpublished works. The information contained herein is confidential and *
 * proprietary to MediaTek Inc. Without the prior written permission of       *
 * MediaTek Inc., any reproduction, modification, use or disclosure of        *
 * MediaTek Software, and information contained herein, in whole or in part,  *
 * shall be strictly prohibited.                                              *
 * MediaTek Inc. Copyright (C) 2010. All rights reserved.                     *
 *                                                                            *
 *   BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND     *
 * AGREES TO THE FOLLOWING:                                                   *
 *                                                                            *
 *   1)Any and all intellectual property rights (including without            *
 * limitation, patent, copyright, and trade secrets) in and to this           *
 * Software/firmware and related documentation ("MediaTek Software") shall    *
 * remain the exclusive property of MediaTek Inc. Any and all intellectual    *
 * property rights (including without limitation, patent, copyright, and      *
 * trade secrets) in and to any modifications and derivatives to MediaTek     *
 * Software, whoever made, shall also remain the exclusive property of        *
 * MediaTek Inc.  Nothing herein shall be construed as any transfer of any    *
 * title to any intellectual property right in MediaTek Software to Receiver. *
 *                                                                            *
 *   2)This MediaTek Software Receiver received from MediaTek Inc. and/or its *
 * representatives is provided to Receiver on an "AS IS" basis only.          *
 * MediaTek Inc. expressly disclaims all warranties, expressed or implied,    *
 * including but not limited to any implied warranties of merchantability,    *
 * non-infringement and fitness for a particular purpose and any warranties   *
 * arising out of course of performance, course of dealing or usage of trade. *
 * MediaTek Inc. does not provide any warranty whatsoever with respect to the *
 * software of any third party which may be used by, incorporated in, or      *
 * supplied with the MediaTek Software, and Receiver agrees to look only to   *
 * such third parties for any warranty claim relating thereto.  Receiver      *
 * expressly acknowledges that it is Receiver's sole responsibility to obtain *
 * from any third party all proper licenses contained in or delivered with    *
 * MediaTek Software.  MediaTek is not responsible for any MediaTek Software  *
 * releases made to Receiver's specifications or to conform to a particular   *
 * standard or open forum.                                                    *
 *                                                                            *
 *   3)Receiver further acknowledge that Receiver may, either presently       *
 * and/or in the future, instruct MediaTek Inc. to assist it in the           *
 * development and the implementation, in accordance with Receiver's designs, *
 * of certain software relating to Receiver's product(s) (the "Services").   *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MediaTek Inc. with respect  *
 * to the Services provided, and the Services are provided on an "AS IS"      *
 * basis. Receiver further acknowledges that the Services may contain errors  *
 * that testing is important and it is solely responsible for fully testing   *
 * the Services and/or derivatives thereof before they are used, sublicensed  *
 * or distributed. Should there be any third party action brought against     *
 * MediaTek Inc. arising out of or relating to the Services, Receiver agree   *
 * to fully indemnify and hold MediaTek Inc. harmless.  If the parties        *
 * mutually agree to enter into or continue a business relationship or other  *
 * arrangement, the terms and conditions set forth herein shall remain        *
 * effective and, unless explicitly stated otherwise, shall prevail in the    *
 * event of a conflict in the terms in any agreements entered into between    *
 * the parties.                                                               *
 *                                                                            *
 *   4)Receiver's sole and exclusive remedy and MediaTek Inc.'s entire and    *
 * cumulative liability with respect to MediaTek Software released hereunder  *
 * will be, at MediaTek Inc.'s sole discretion, to replace or revise the      *
 * MediaTek Software at issue.                                                *
 *                                                                            *
 *   5)The transaction contemplated hereunder shall be construed in           *
 * accordance with the laws of Singapore, excluding its conflict of laws      *
 * principles.  Any disputes, controversies or claims arising thereof and     *
 * related thereto shall be settled via arbitration in Singapore, under the   *
 * then current rules of the International Chamber of Commerce (ICC).  The    *
 * arbitration shall be conducted in English. The awards of the arbitration   *
 * shall be final and binding upon both parties and shall be entered and      *
 * enforceable in any court of competent jurisdiction.                        *
 *
 * $Author: guiwu.guo $
 * $Date: 2016/10/28 $
 * $RCSfile: pp_drv.c,v $
 *
 * @file pp_drv.c
 *
 */

#include <linux/kthread.h>
#include <linux/mutex.h>
#include "pp_drv.h"
#include "pp_drv.h"
#include "pp_hw.h"
#include "pp_hal.h"

uint32_t pp_debug_level;


/******************************************************************************
*Local variable
******************************************************************************/
static uint8_t _pp_vsync_initiated;
static uint8_t _pp_vsync_destroy;

static struct task_struct *h_pp_kthread;
struct mutex _pp_vsync_lock;

void pp_enable(bool enable)
{
	if (enable) {
		vRegWt4BMsk(io_reg_base + 0x300, (0x07 << 24), (0x07 << 24));
		vRegWt4BMsk(io_reg_base + 0x310, (0x07 << 24), (0x07 << 24));
	}

	else {			/*sequence should be reverse. */
		vRegWt4BMsk(io_reg_base + 0x310, (0x00 << 24), (0x07 << 24));
		vRegWt4BMsk(io_reg_base + 0x300, (0x00 << 24), (0x07 << 24));
	}
}

int pp_suspend(void *param)
{
	PP_INFO("PostP Suspend\n");
	pp_enable(false);
	/*pp_hal_sharp_enable(SV_OFF);*/
	return 0;
}

int pp_resume(void *param)
{
	PP_INFO("PostP Resume\n");
	pp_enable(true);
	/*pp_hal_sharp_enable(SV_ON);*/
	return 0;
}


/******************************************************************************
*Function: pp_vsync_tick
*Description: main routine for PostTask
*Parameter: None
*Return: None
******************************************************************************/
void pp_vsync_tick(void)
{
	if (_pp_vsync_initiated == SV_ON) {
		/*pp_set_luma_curve();  //update last calculation*/
		/*mutex unlock*/
		mutex_unlock(&_pp_vsync_lock);
	}
}


/******************************************************************************
*Function: vPostTaskMain
*Description: main routine for Posttask
*Parameter: None
*Return: None
******************************************************************************/
static int pp_mainloop(void *pvArg)
{
	pp_auto_con_init();
	while (_pp_vsync_destroy == 0) {

		/*mutex lock*/
		mutex_lock(&_pp_vsync_lock);
		pp_auto_contrast();

		/*pp_hal_auto_sat();  */
		if (kthread_should_stop())
			break;
	}
	return 0;
}


/******************************************************************************
*Function: pp_drv_init
*Description: initial
*Parameter: None
*Return: PP_OK PP_FAIL
******************************************************************************/
int32_t pp_drv_init(void)
{
	if (_pp_vsync_initiated == SV_OFF) {

		/*initial some post settings */
		pp_hal_yc_proc_init();
		h_pp_kthread = kthread_create(pp_mainloop, NULL, "postproc_kthread");
		/* wake_up_process(h_pp_kthread); */

		mutex_init(&_pp_vsync_lock);
		_pp_vsync_initiated = SV_ON;
	}
	return PP_OK;
}


/******************************************************************************
*Function: pp_drv_uninit
*Description: Un-initial
*Parameter: None
*Return: None
******************************************************************************/
int32_t pp_drv_uninit(void)
{
	if (_pp_vsync_initiated == SV_ON) {

		/*destroy thread*/
		_pp_vsync_destroy = 1;
		pp_vsync_tick();
		_pp_vsync_initiated = SV_OFF;
	}
	return PP_OK;
}
