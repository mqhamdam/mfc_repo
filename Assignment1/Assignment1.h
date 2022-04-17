
// Assignment1.h: основной файл заголовка для приложения Assignment1
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CAssignment1App:
// Сведения о реализации этого класса: Assignment1.cpp
//

class CAssignment1App : public CWinApp
{
public:
	CAssignment1App() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAssignment1App theApp;
