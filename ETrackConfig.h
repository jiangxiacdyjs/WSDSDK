// ETrackConfig.h: interface for the CETrackConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ETRACKCONFIG_H__B17E33B5_3A0E_4DC7_8CD6_5EF3F9AE2666__INCLUDED_)
#define AFX_ETRACKCONFIG_H__B17E33B5_3A0E_4DC7_8CD6_5EF3F9AE2666__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxtempl.h"

typedef CArray<PRESET_INFO_S,PRESET_INFO_S&> CPresetArray;

class CETrackConfig  
{
public:
	CETrackConfig();
	CETrackConfig(const CETrackConfig& ETrack)
	{
		*this = ETrack;
	}

	virtual ~CETrackConfig();

	CETrackConfig& operator = (const CETrackConfig& ETrack)
	{
		m_nTrack = ETrack.m_nTrack;

		m_arrPreset.RemoveAll();
		for(int nIndex = 0 ; nIndex < ETrack.m_arrPreset.GetSize() ; nIndex ++)
		{
			m_arrPreset.Add(ETrack.m_arrPreset.GetAt(nIndex));
		}

		return *this;
	}

public:
	UINT			m_nTrack;						// 轨迹索引 1 --- 16
	CPresetArray	m_arrPreset;					// 预置位数组

};

#endif // !defined(AFX_ETRACKCONFIG_H__B17E33B5_3A0E_4DC7_8CD6_5EF3F9AE2666__INCLUDED_)
