
// Assignment1View.h: интерфейс класса CAssignment1View
//

#pragma once

#include "vector";

#include "CustomEllipse.h"
using namespace std;

class CAssignment1View : public CView
{
protected: // создать только из сериализации
	CAssignment1View() noexcept;
	DECLARE_DYNCREATE(CAssignment1View)

// Атрибуты
public:
	CAssignment1Doc* GetDocument() const;

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
	virtual ~CAssignment1View();
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
	void drawRandomEllipse(int count = 10);
	void drawEllipse(CPoint point, int radius= 50);
	vector<CustomEllipse> vEllipse;
	bool checkCircleIntersectOrTouch(CustomEllipse ellipse);
};

#ifndef _DEBUG  // версия отладки в Assignment1View.cpp
inline CAssignment1Doc* CAssignment1View::GetDocument() const
   { return reinterpret_cast<CAssignment1Doc*>(m_pDocument); }
#endif

