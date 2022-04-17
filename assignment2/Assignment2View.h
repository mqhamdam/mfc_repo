
// Assignment2View.h: интерфейс класса CAssignment2View
//

#pragma once
#include <vector>
#include <iostream>
#include "MyCircle.h"


using namespace std;


class CAssignment2View : public CView
{
protected: // создать только из сериализации
	CAssignment2View() noexcept;
	DECLARE_DYNCREATE(CAssignment2View)

// Атрибуты
public:
	CAssignment2Doc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CAssignment2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	// ~ vector of My circle 
	vector<MyCircle> vMyCircles;
	COLORREF cRGB[3] = { RGB(0, 0, 255), RGB(0, 255, 0), RGB(255, 0, 0) };
	bool isCircleIntersectOrTouch(MyCircle c);
	void onCollision(MyCircle* c1, MyCircle* c2,int i1,int i2);
	bool setTimer = false;
};

#ifndef _DEBUG  // версия отладки в Assignment2View.cpp
inline CAssignment2Doc* CAssignment2View::GetDocument() const
   { return reinterpret_cast<CAssignment2Doc*>(m_pDocument); }
#endif

