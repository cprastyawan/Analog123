
// Analog123.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAnalog123App:
// See Analog123.cpp for the implementation of this class
//

class CAnalog123App : public CWinApp
{
public:
	CAnalog123App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CAnalog123App theApp;
