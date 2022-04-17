
// Assignment2.h: основной файл заголовка для приложения Assignment2
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CAssignment2App:
// Сведения о реализации этого класса: Assignment2.cpp
//

class CAssignment2App : public CWinApp
{
public:
	CAssignment2App() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAssignment2App theApp;
