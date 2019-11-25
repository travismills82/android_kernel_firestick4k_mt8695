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
 * $RCSfile: p2i_hal.h,v $
 *
 * @file p2i_hal.h
 *
 */


#ifndef _P2I_HAL_H_
#define _P2I_HAL_H_
#include "disp_type.h"
#include "disp_hw_mgr.h"


#ifndef FALSE
#define FALSE   0
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef NULL
#define NULL    0
#endif




/* P2I and CST mode */
#define P2I_ONLY  0
#define CST_ONLY  1
#define P2I_AND_CST  2

/*#define P2I_SYS_BASE 0xf0003700*/

/* #define vWriteP2I(dAddr, dVal)  WriteREG32(((uint64_t)(P2I_SYS_BASE+dAddr)), dVal) */
/* #define dReadP2I(dAddr)        ReadREG32(((uint64_t)(P2I_SYS_BASE+dAddr))) */
/* #define vWriteP2IMsk(dAddr, dVal, dMsk) vWriteP2I((dAddr), (dReadP2I(dAddr) & (~(dMsk))) | ((dVal) & (dMsk))) */

#define P2I_ERR(fmt, arg...)  pr_err("[P2I] error:"fmt, ##arg)
#define P2I_WARN(fmt, arg...)  pr_warn("[P2I]:"fmt, ##arg)
#define P2I_INFO(fmt, arg...)  pr_info("[P2I]:"fmt, ##arg)
#define P2I_LOG(fmt, arg...)  pr_debug("[P2I]:"fmt, ##arg)
#define P2I_DEBUG(fmt, arg...) pr_debug("[P2I]:"fmt, ##arg)

#define P2I_FUNC() pr_debug("[P2I] func: %s, line: %d\n", __func__, __LINE__)


/* API */
int p2i_hal_init(void);
void p2i_hal_set_cstmode(unsigned char mode);
void p2i_hal_enable_cst(bool is_on);
void p2i_hal_set_time(HDMI_VIDEO_RESOLUTION res);
void p2i_hal_turnoff_cst(bool turn_off);
void p2i_hal_enable_clk(bool on);
void p2i_hal_set_rwnotsametime(bool is_on);
uint32_t p2i_hal_get_tv_field(void);
void pi2_hal_reset(void);
#endif
