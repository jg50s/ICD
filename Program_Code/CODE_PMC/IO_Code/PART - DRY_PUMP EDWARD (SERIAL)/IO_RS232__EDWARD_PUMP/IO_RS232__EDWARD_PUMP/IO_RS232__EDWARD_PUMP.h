// IO_RS232__EDWARD_PUMP.h : IO_RS232__EDWARD_PUMP DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CIO_RS232__EDWARD_PUMPApp
// �� Ŭ������ ������ ������ IO_RS232__EDWARD_PUMP.cpp�� �����Ͻʽÿ�.
//

class CIO_RS232__EDWARD_PUMPApp : public CWinApp
{
public:
	CIO_RS232__EDWARD_PUMPApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
