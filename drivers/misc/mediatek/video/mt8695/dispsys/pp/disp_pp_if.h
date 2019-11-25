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
 * $Date: 2016/09/25 $
 * $RCSfile: disp_pp_if.h $
 *
 * @file disp_pp_if.h
 *
 */


#ifndef _DISP_PP_H_
#define _DISP_PP_H_

#include "disp_type.h"
#include "disp_hw_mgr.h"
#include "disp_info.h"

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef NULL
#define NULL0
#endif

#define PP_OK (0)
#define PP_FAIL (-1)
#define OSR_OK (0)

#define SV_ON (1)
#define SV_OFF (0)

#define PP_DRV_NAME "disp_drv_pp"

#define pp_is_video_3d(ucFmt) ((ucFmt == HDMI_VIDEO_1920x1080p3d_23Hz) || (ucFmt == HDMI_VIDEO_1920x1080p3d_24Hz) || \
			(ucFmt == HDMI_VIDEO_1280x720p3d_60Hz) || (ucFmt == HDMI_VIDEO_1280x720p3d_50Hz) || \
			(ucFmt == HDMI_VIDEO_1920x1080i3d_60Hz) || (ucFmt == HDMI_VIDEO_1920x1080i3d_50Hz))

#define pp_is_video_hd(ucFmt) ((ucFmt == HDMI_VIDEO_1280x720p_60Hz) || (ucFmt == HDMI_VIDEO_1280x720p_50Hz) ||\
			(ucFmt == HDMI_VIDEO_1920x1080i_60Hz) || (ucFmt == HDMI_VIDEO_1920x1080i_50Hz) ||\
			(ucFmt == HDMI_VIDEO_1920x1080p_30Hz) || (ucFmt == HDMI_VIDEO_1920x1080p_25Hz) ||\
			(ucFmt == HDMI_VIDEO_1920x1080p_24Hz) || (ucFmt == HDMI_VIDEO_1920x1080p_23Hz) ||\
			(ucFmt == HDMI_VIDEO_1920x1080p_29Hz) || (ucFmt == HDMI_VIDEO_1920x1080p_60Hz) ||\
			(ucFmt == HDMI_VIDEO_1920x1080p_50Hz) || (ucFmt == HDMI_VIDEO_1280x720p3d_60Hz) ||\
			(ucFmt == HDMI_VIDEO_1280x720p3d_50Hz) || (ucFmt == HDMI_VIDEO_1920x1080i3d_60Hz) ||\
			(ucFmt == HDMI_VIDEO_1920x1080i3d_50Hz) || (ucFmt == HDMI_VIDEO_1920x1080p3d_24Hz) ||\
			(ucFmt == HDMI_VIDEO_1920x1080p3d_23Hz) || (ucFmt == HDMI_VIDEO_3840x2160P_23_976HZ) ||\
			(ucFmt == HDMI_VIDEO_3840x2160P_24HZ) || (ucFmt == HDMI_VIDEO_3840x2160P_25HZ) ||\
			(ucFmt == HDMI_VIDEO_3840x2160P_29_97HZ) || (ucFmt == HDMI_VIDEO_3840x2160P_30HZ) ||\
			(ucFmt == HDMI_VIDEO_4096x2160P_24HZ) || (ucFmt == HDMI_VIDEO_3840x2160P_60HZ) ||\
			(ucFmt == HDMI_VIDEO_3840x2160P_50HZ) || (ucFmt == HDMI_VIDEO_4096x2160P_60HZ) ||\
			(ucFmt == HDMI_VIDEO_4096x2160P_50HZ))


#define pp_is_video_60hz(ucFmt) ((ucFmt == HDMI_VIDEO_720x480i_60Hz) || (ucFmt == HDMI_VIDEO_720x480p_60Hz) ||\
			(ucFmt == HDMI_VIDEO_1280x720p_60Hz) || (ucFmt == HDMI_VIDEO_1920x1080i_60Hz) ||\
			(ucFmt == HDMI_VIDEO_1920x1080p_60Hz) || (ucFmt == HDMI_VIDEO_1280x720p3d_60Hz) ||\
			(ucFmt == HDMI_VIDEO_1920x1080i3d_60Hz) || (ucFmt == HDMI_VIDEO_3840x2160P_60HZ) ||\
			(ucFmt == HDMI_VIDEO_4096x2160P_60HZ))


#define pp_is_video_50hz(ucFmt) ((ucFmt == HDMI_VIDEO_720x576i_50Hz) || (ucFmt == HDMI_VIDEO_1280x720p_50Hz) ||\
			(ucFmt == HDMI_VIDEO_1280x720p3d_50Hz) || (ucFmt == HDMI_VIDEO_1920x1080i_50Hz) ||\
			(ucFmt == HDMI_VIDEO_1920x1080i3d_50Hz) || (ucFmt == HDMI_VIDEO_1920x1080p_50Hz) ||\
			(ucFmt == HDMI_VIDEO_3840x2160P_50HZ) || (ucFmt == HDMI_VIDEO_4096x2160P_50HZ))


#define pp_is_video_24hz(ucFmt) ((ucFmt == HDMI_VIDEO_1920x1080p_24Hz) || (ucFmt == HDMI_VIDEO_1920x1080p3d_24Hz) ||\
			(ucFmt == HDMI_VIDEO_3840x2160P_24HZ) || (ucFmt == HDMI_VIDEO_4096x2160P_24HZ))

enum POST_UI_ITEM_ENUM {
	POST_VIDEO_CONTRAST = 0,
	POST_VIDEO_BRIGHTNESS,
	POST_VIDEO_HUE,
	POST_VIDEO_SATURATION,
	POST_VIDEO_SHARPNESS,
	POST_VIDEO_CDS,
	POST_VIDEO_CTI,
	POST_VIDEO_ADAPTIVE_LUMA_ONOFF,
	POST_VIDEO_SCE_ONOFF,

	POST_VIDEO_COLOR_RED_Y,
	POST_VIDEO_COLOR_RED_S,
	POST_VIDEO_COLOR_RED_H,
	POST_VIDEO_COLOR_GREEN_Y,
	POST_VIDEO_COLOR_GREEN_S,
	POST_VIDEO_COLOR_GREEN_H,
	POST_VIDEO_COLOR_BLUE_Y,
	POST_VIDEO_COLOR_BLUE_S,
	POST_VIDEO_COLOR_BLUE_H,
	POST_VIDEO_COLOR_YELLOW_Y,
	POST_VIDEO_COLOR_YELLOW_S,
	POST_VIDEO_COLOR_YELLOW_H,
	POST_VIDEO_COLOR_CYAN_Y,
	POST_VIDEO_COLOR_CYAN_S,
	POST_VIDEO_COLOR_CYAN_H,
	POST_VIDEO_COLOR_MAGENTA_Y,
	POST_VIDEO_COLOR_MAGENTA_S,
	POST_VIDEO_COLOR_MAGENTA_H,

};

enum POST_VIDEO_MODE_ENUM {
	POST_VIDEO_MODE_STD = 0,
	POST_VIDEO_MODE_VIVID,
	POST_VIDEO_MODE_CINEMA,
	POST_VIDEO_MODE_CUSTOMER,
	POST_VIDEO_MODE_OTHER,

};

struct POST_SHN_CTRL_PARA {
	uint16_t b_limitAllPos;
	uint16_t b_limitAllNeg;
	bool fgShnEn;

};

enum POST_SHN_BAND_ENUM {


	SHN_BAND_H1 = 1,
	SHN_BAND_H2 = 2,
	SHN_BAND_V1 = 3,
	SHN_BAND_V2 = 4,
	SHN_BAND_X1 = 5,
	SHN_BAND_X2 = 6,
	SHN_BAND_LTI1 = 7,
	SHN_BAND_LTI2 = 8,
	SHN_BAND_H1_1 = 9,
	SHN_BAND_H2_1 = 10,

};

struct POST_SHN_BAND_PARA {
	enum POST_SHN_BAND_ENUM eShnBand;
	uint8_t b_gain;
	uint8_t bCoring;
	uint8_t b_limitPos;
	uint8_t b_limitNeg;
	uint8_t bClipEn;
	uint8_t bClipThPos;
	uint8_t bClipThNeg;
	uint8_t bSoftCore_gain;
};

struct POST_SHN_PRE_BAND1_PARA {	/*addforpresharpness */
/*enum POST_SHN_BAND_ENUM eShnBand;  */
	uint8_t bCoringB1;
	uint8_t b_limitNegB1;
	uint8_t b_limitPosB1;
	uint8_t b_gainB1;

/*uint8_t bSharpEnB1;  */
	uint8_t bShrinkSelB1;
	uint8_t bClipSelB1;
	uint8_t bClipEnB1;
	uint8_t bClipNegB1;
	uint8_t bClipPosB1;

/*uint8_t bBypassSharp;  */
	uint8_t bFilterSelB1;
	uint8_t bShift;
/*uint8_t bPrecB1;  */
	uint8_t b_limitNeg;
	uint8_t b_limitPos;
};

struct POST_CTI_CTRL_PARA {
	uint8_t bECTIVwgt;
	uint8_t bECTIUwgt;
	uint8_t bECTIFlpfSel;
	bool fgECTIFlpfEn;
	bool fgCtiEn;
};


enum POST_BLUR_MODE_ENUM {
	FF1_FR1_MODE = 0,
	FF2_FR2_MODE,
	FF3_FR3_MODE,
	PLAY_MODE,
	STOP_MODE,
};

enum POST_BLUR_FRAM_RATE_ENUM {
	FRAM_RATE_60HZ = 1,
	FRAM_RATE_50HZ,
	FRAM_RATE_24HZ,
};

/***********************************************************************/
/*ExportAPI*/
/***********************************************************************/

/***PostTASK***/

void pp_vsync_tick(void);
int32_t disp_pp_vdieo_proc(enum POST_UI_ITEM_ENUM proc_item,
			   int16_t ui_min, int16_t ui_max, int16_t ui_dft, int16_t ui_cur);


void disp_pp_set_mode(uint8_t b_on_off);
void disp_pp_chg_input_cs(enum DISP_VIDEO_TYPE e_cs);
void disp_pp_request_vdp_src_region(uint32_t src_width, uint32_t output_width);


void dis_pp_set_sfs_curve_for_gain(uint32_t mode, uint32_t syncounter, uint32_t y_b, uint32_t y_tar,
				   uint32_t y_d, uint32_t cbcr_b, uint32_t cbcr_tar,
				   uint32_t cbcr_d);
void disp_pp_set_sfs_curve(uint32_t mode, uint32_t frame, uint32_t syncounter, uint32_t y_b,
			   uint32_t y_tar, uint32_t y_d, uint32_t cbcr_b, uint32_t cbcr_tar,
			   uint32_t cbcr_d);


#endif				/*#define _DRV_POST_POST_H_ */
