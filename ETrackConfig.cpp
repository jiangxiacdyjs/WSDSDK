// ETrackConfig.cpp: implementation of the CETrackConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ETrackConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CETrackConfig::CETrackConfig()
{
	m_nTrack = 0;
	m_arrPreset.RemoveAll();
}

CETrackConfig::~CETrackConfig()
{

}
