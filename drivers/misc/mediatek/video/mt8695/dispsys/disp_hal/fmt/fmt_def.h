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
 * $Author: chuanfei.wang $
 * $Date: 2016/05/25 $
 * $RCSfile: fmt_hal.h,v $
 *
 * @file drv_hw.h
 *
 */

#ifndef _FMT_DEF_H_
#define _FMT_DEF_H_

/* ----------------------------------------------------------------------------- */
/* Include files */
/* ----------------------------------------------------------------------------- */
#include <linux/types.h>
#include <linux/printk.h>

#include "fmt_hw.h"

#define FMT_OK 0
#define FMT_PARAR_ERR -1
#define FMT_SET_ERR -2
#define FMT_GET_ERR -3
#define FMT_STATE_ERR -4
#define FMT_ALLOC_FAIL -5

#define DISP_FMT_MAIN 0
#define DISP_FMT_SUB 1
#define VDOUT_FMT (DISP_FMT_SUB + 1)
#define VDOUT_FMT_SUB (VDOUT_FMT + 1)

#define FMT_HW_PLANE_1    0
#define FMT_HW_PLANE_2    1
#define FMT_HW_PLANE_3    2

/* Resolution */
#define FMT_480I_WIDTH		720
#define FMT_480I_HEIGHT	480
#define FMT_480P_WIDTH		720
#define FMT_480P_HEIGHT	480
#define FMT_576I_WIDTH		720
#define FMT_576I_HEIGHT	576
#define FMT_576P_WIDTH		720
#define FMT_576P_HEIGHT	576
#define FMT_720P_WIDTH		1280
#define FMT_720P_HEIGHT	720
#define FMT_1080I_WIDTH	1920
#define FMT_1080I_HEIGHT	1080
#define FMT_1080P_WIDTH	1920
#define FMT_1080P_HEIGHT	1080
#define FMT_2160P_WIDTH  3840
#define FMT_2160P_HEIGHT	2160
#define FMT_2161P_WIDTH  4096
#define FMT_2161P_HEIGHT	2160



#define FMT_768P_WIDTH		1366
#define FMT_768P_HEIGHT	768
#define FMT_540P_WIDTH		1920
#define FMT_540P_HEIGHT	540
#define FMT_768I_WIDTH		1366
#define FMT_768I_HEIGHT	768
#define FMT_1536I_WIDTH	1366
#define FMT_1536I_HEIGHT	1536
#define FMT_720I_WIDTH		1280
#define FMT_720I_HEIGHT	720
#define FMT_1440I_WIDTH	1280
#define FMT_1440I_HEIGHT	1440

#define FMT_PANEL_AUO_B089AW01_WIDTH  1024
#define FMT_PANEL_AUO_B089AW01_HEIGHT  600

#define FMT_640_480_WIDTH	640
#define FMT_640_480_HEIGHT	480

enum FMT_TV_TYPE {
	FMT_TV_TYPE_NTSC = 0,
	FMT_TV_TYPE_PAL_M,
	FMT_TV_TYPE_PAL_N,
	FMT_TV_TYPE_PAL,
	FMT_TV_TYPE_PAL_1080P_24,
	FMT_TV_TYPE_PAL_1080P_25,
	FMT_TV_TYPE_PAL_1080P_30,
	FMT_TV_TYPE_NTSC_1080P_23_9,
	FMT_TV_TYPE_NTSC_1080P_29_9,
	FMT_TV_TYPE_720P3D,
	FMT_TV_TYPE_1080i3D
};


enum FMT_OUTPUT_FREQ_T {
	FMT_OUTPUT_FREQ_60 = 60,
	FMT_OUTPUT_FREQ_50 = 50,
	FMT_OUTPUT_FREQ_30 = 30,
	FMT_OUTPUT_FREQ_25 = 25,
	FMT_OUTPUT_FREQ_24 = 24,
	FMT_OUTPUT_FREQ_23_976 = 23,
	FMT_OUTPUT_FREQ_29_97 = 29,
};

enum FMT_3D_TYPE_T {
	FMT_3D_NO = 0,
	FMT_3D_FP,
	FMT_3D_SBS,
	FMT_3D_TAB,
	FMT_3D_SBSF,
	FMT_3D_MAX
};

enum FMT_LOG_LEVEL {
	FMT_LL_ERROR,
	FMT_LL_WARNING,
	FMT_LL_INFO,
	FMT_LL_DEBUG,
	FMT_LL_VERBOSE
};

enum FMT_STATUS {
	FMT_STA_UNUSED,
	FMT_STA_USED
};

enum DISP_FMT {
	DISP_FMT1 = 0,
	DISP_FMT2 = 1,
	DISP_FMT_CNT = 2
};

struct vdout_fmt_t {
	enum FMT_STATUS status;
	bool reset_in_vsync;
	bool shadow_en;
	bool shadow_trigger;
	uint64_t *reg_mode;
	uintptr_t hw_fmt_base;
	union vdout_fmt_union_t *sw_fmt_base;
};

struct disp_fmt_t {
	enum FMT_STATUS status;
	bool reset_in_vsync;
	bool shadow_en;
	bool shadow_trigger;
	bool is_sec;
	uint64_t *reg_mode;
	uintptr_t hw_fmt_base;
	union disp_fmt_union_t *sw_fmt_base;
};

struct fmt_context {
	uintptr_t vdout_fmt_reg_base;
	uintptr_t disp_fmt_reg_base[DISP_FMT_CNT];	/*fmt1, fmt2 */
	uintptr_t io_reg_base;

	struct vdout_fmt_t vdout_fmt;
	struct vdout_fmt_t sub_vdout_fmt;
	struct disp_fmt_t main_disp_fmt;
	struct disp_fmt_t sub_disp_fmt;

	struct mutex lock;
	bool inited;
	uint32_t fmt_log_level;
	HDMI_VIDEO_RESOLUTION res;
};


extern struct fmt_context fmt;

#define FMT_LOG(level, format...) \
do { \
	if (level <= fmt.fmt_log_level) \
		pr_err("[FMT] "format); \
} while (0)

#define FMT_LOG_E(format...) FMT_LOG(FMT_LL_ERROR, "error: "format)
#define FMT_LOG_W(format...) FMT_LOG(FMT_LL_WARNING, format)
#define FMT_LOG_I(format...) FMT_LOG(FMT_LL_INFO, format)
#define FMT_LOG_D(format...) FMT_LOG(FMT_LL_DEBUG, format)
#define FMT_LOG_V(format...) FMT_LOG(FMT_LL_VERBOSE, format)

#define FMT_FUNC()  FMT_LOG_D("%s LINE:%d\n", __func__, __LINE__)

#define CHECK_STATE_RET_VOID(state) \
do { \
	if (state == FMT_STA_UNUSED) { \
		FMT_LOG_E("%s state error\n", __func__); \
	} \
} while (0)

#define CHECK_STATE_RET_INT(state) \
do { \
	if (state == FMT_STA_UNUSED) { \
		FMT_LOG_E("%s state error\n", __func__); \
	} \
} while (0)


#endif
