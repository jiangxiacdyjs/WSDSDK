// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__CDB3B85A_2CA6_48F0_A7CE_FBE24A979835__INCLUDED_)
#define AFX_STDAFX_H__CDB3B85A_2CA6_48F0_A7CE_FBE24A979835__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions

// 引入库头文件
#include <vector>
#include <map>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#include "NS_NET.h"
#include "NS_PLAYER.h"
#include "NS_MP4.h"
#include "NS_DECODER.h"

extern CString g_strChannel;
extern unsigned int g_u32DevHandle;

enum enumStringId
{
	STR_SUCCESS = 0,
	STR_FAIL,
	STR_SET_VM_FAIL,
	STR_FILE_NAME,
	STR_PARTITION,
	STR_SPACE_TOTAL,
	STR_SPACE_LEFT,
	STR_PRESET_ID,
	STR_PRESET_NAME,
	STR_USER_NAME,
	STR_USER_GROUP,
	STR_GROUP_ADMIN,
	STR_GROUP_OPER,
	STR_GROUP_GUEST,
	STR_ERR_CONNECT,
	STR_ERR_PASSWORD,
	STR_ERR_DISCONN,
	STR_ALARM_MD,
	STR_ALARM_IN,
	STR_ALARM_VL,
	STR_ERR_NON_CONN,
	STR_3D,
	STR_TRACK_ID,
	STR_TRACK_PRESET,
	STR_TRACK_INTERVAL,
	STR_DEV_REC_STATUS_IDLE,
	STR_DEV_REC_STATUS_MANUAL,
	STR_DEV_REC_STATUS_ALARM,
	STR_DEV_REC_STATUS_MD,
	STR_DEV_REC_STATUS_SCHE,
	STR_DEV_REC_STATUS_SNAP,
	STR_TIME_ZONE_1,
	STR_TIME_ZONE_2,
	STR_TIME_ZONE_3,
	STR_TIME_ZONE_4,
	STR_TIME_ZONE_5,
	STR_TIME_ZONE_6,
	STR_TIME_ZONE_7,
	STR_TIME_ZONE_8,
	STR_TIME_ZONE_9,
	STR_TIME_ZONE_10,
	STR_TIME_ZONE_11,
	STR_TIME_ZONE_12,
	STR_TIME_ZONE_13,
	STR_TIME_ZONE_14,
	STR_TIME_ZONE_15,
	STR_TIME_ZONE_16,
	STR_TIME_ZONE_17,
	STR_TIME_ZONE_18,
	STR_TIME_ZONE_19,
	STR_TIME_ZONE_20,
	STR_TIME_ZONE_21,
	STR_TIME_ZONE_22,
	STR_TIME_ZONE_23,
	STR_TIME_ZONE_24,
	STR_TIME_ZONE_25,
	STR_TIME_ZONE_26,
	STR_TIME_ZONE_27,
	STR_TIME_ZONE_28,
	STR_TIME_ZONE_29,
	STR_TIME_ZONE_30,
	STR_TIME_ZONE_31,
	STR_TIME_ZONE_32,
	STR_TIME_ZONE_33,
	STR_TIME_ZONE_34,
	STR_TIME_ZONE_35,
};

typedef struct  
{
	enumStringId id;
	const char * strings[2];
}ui_string_t;

extern ui_string_t uistrings[];

extern int g_nLangID;

#endif // !defined(AFX_STDAFX_H__CDB3B85A_2CA6_48F0_A7CE_FBE24A979835__INCLUDED_)
