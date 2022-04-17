
// Assignment2View.cpp: реализация класса CAssignment2View
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Assignment2.h"
#endif

#include "Assignment2Doc.h"
#include "Assignment2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <time.h>
#include <stdlib.h>
// CAssignment2View

IMPLEMENT_DYNCREATE(CAssignment2View, CView)

BEGIN_MESSAGE_MAP(CAssignment2View, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// Создание или уничтожение CAssignment2View

CAssignment2View::CAssignment2View() noexcept
{
	// TODO: добавьте код создания
	srand(unsigned(time(NULL)));
}

CAssignment2View::~CAssignment2View()
{
}

BOOL CAssignment2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CAssignment2View

void CAssignment2View::OnDraw(CDC* /*pDC*/)
{
	CAssignment2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
	CClientDC dc(this);
	CBrush brush, * oldBrush;
	CRect rc;
	GetClientRect(&rc);
	 for (int i = 0; i < vMyCircles.size(); i++) {
		for (int j = i + 1; j < vMyCircles.size(); j++) {
			 double dx = vMyCircles[i].point.x - vMyCircles[j].point.x;
			 double dy = vMyCircles[i].point.y - vMyCircles[j].point.y;
			 double dr = vMyCircles[i].radius + vMyCircles[j].radius;
			if (dx * dx + dy * dy <= dr * dr) {
				onCollision(&vMyCircles[i],&vMyCircles[j],i,j);
				/* CPoint tmp = vMyCircles[i].dxy;
				vMyCircles[i].dxy = vMyCircles[j].dxy;
				vMyCircles[j].dxy = tmp;*/
			}
		}
	} 

	for (int i = 0; i < vMyCircles.size(); i++) {
		if (vMyCircles[i].point.x < 10 || vMyCircles[i].point.x > rc.right - 10) {
			vMyCircles[i].point.x = max(min(vMyCircles[i].point.x, rc.right - 10), 10);
			vMyCircles[i].dxy.x = -vMyCircles[i].dxy.x;
		}
		if (vMyCircles[i].point.y < 10 || vMyCircles[i].point.y > rc.bottom - 10) {
			vMyCircles[i].point.y = max(min(vMyCircles[i].point.y, rc.bottom - 10), 10);
			vMyCircles[i].dxy.y = -vMyCircles[i].dxy.y;
		}
	}

	for (int i = 0; i< vMyCircles.size(); i++) {
		CPoint p = vMyCircles[i].point; // get points
		int r = vMyCircles[i].radius; // get radius
		COLORREF c = vMyCircles[i].color;

		brush.CreateSolidBrush(c);
		oldBrush = dc.SelectObject(&brush);
		


		dc.Ellipse(p.x - r, p.y - r, p.x + r, p.y + r);
		dc.SelectObject(oldBrush);
		brush.DeleteObject();
	}

	CString str = L"2019117366 무키모프 함담";
	dc.TextOutW(100, 100,str);

	
	
}


// Печать CAssignment2View

BOOL CAssignment2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CAssignment2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CAssignment2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CAssignment2View

#ifdef _DEBUG
void CAssignment2View::AssertValid() const
{
	CView::AssertValid();
}

void CAssignment2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAssignment2Doc* CAssignment2View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAssignment2Doc)));
	return (CAssignment2Doc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CAssignment2View


void CAssignment2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (nChar == VK_SPACE) {
		if (setTimer) {
			KillTimer(0);
		}
		else {
		SetTimer(1, 50, NULL);
		}
		setTimer = !setTimer;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CAssignment2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CRect rc;
	GetClientRect(&rc);
	if (vMyCircles.size() >= 250) {
		CString str;
		str.Format(L"There are %d circles, cannot spawn more circles",vMyCircles.size());
		AfxMessageBox(str);
	} else
	for (int i = 0; i < 100; ) {
		int x = rc.right;
		int y = rc.bottom;

		int r = rand() % 70 + 3;
		CPoint p = CPoint(rand() % (x-r), rand() % (y-r));
		

		CPoint dxy = CPoint(rand() % 7 - 3, rand() % 7 - 3);

		int c = cRGB[ rand() % 3];
		MyCircle circle = MyCircle(r, dxy, c, p);
		if (isCircleIntersectOrTouch(circle) == false) {
		vMyCircles.push_back(MyCircle(r, dxy, c, p));
			i++;
		}

	}
		Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void CAssignment2View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	for (int i = 0; i < vMyCircles.size(); i++) {
		MyCircle c = vMyCircles[i];
		vMyCircles[i].point.x += vMyCircles[i].dxy.x;
		vMyCircles[i].point.y += vMyCircles[i].dxy.y;
	}
	Invalidate();
	CView::OnTimer(nIDEvent);
}


bool CAssignment2View::isCircleIntersectOrTouch(MyCircle c)
{
	// TODO: Добавьте сюда код реализации.
	bool doesTouchOrIntersect = false;
	MyCircle o1 = c;
	for (int i = 0; i < vMyCircles.size(); i++) {
		MyCircle o2 = vMyCircles[i];
		int distSq = (o1.point.x - o2.point.x) * (o1.point.x - o2.point.x) +
			(o1.point.y - o2.point.y) * (o1.point.y - o2.point.y);
		int radSumSq = (o1.radius + o2.radius) * (o1.radius + o2.radius);

		if (distSq == radSumSq) {

			doesTouchOrIntersect = true;
			break;
		}
		else if (distSq > radSumSq) {
			continue;
		}
		else {
			doesTouchOrIntersect = true;
			break;
		}
	}
	return doesTouchOrIntersect;
}


void CAssignment2View::onCollision(MyCircle* c1, MyCircle* c2,int i1,int i2)
{
	// TODO: Добавьте сюда код реализации.
	// if color same
	if (c1->color == c2->color) {
		// if radius greater
	 if (c1->radius > 50) {
		 vMyCircles.erase(vMyCircles.begin() + i1);
	}
	else if (c2->radius > 50) {
		 vMyCircles.erase(vMyCircles.begin() + i2);
	}
	else if (c1->radius > c2->radius) {	
		vMyCircles.erase(vMyCircles.begin()+i2);
	}	
	else if (c1->radius < c2->radius) { 
		vMyCircles.erase(vMyCircles.begin()+i1);
	}
	else if (c1->radius == c2->radius) {
		 // sorry i didn't understand what to do.
		 swap(c1->dxy, c2->dxy);
		 /* CPoint tmp = c1->dxy;
		 c1->dxy = c2->dxy;
		 c2->dxy = tmp;*/
		}
	}
	else {
		if (c1->radius < 5) {
			vMyCircles.erase(vMyCircles.begin() + i1);
		}
		else if (c2->radius < 5) {
			vMyCircles.erase(vMyCircles.begin() + i2);
		}
		else {
			c1->radius -= 1;
			c2->radius -= 1;
			swap(c1->dxy, c2->dxy);
			/* CPoint tmp = c1->dxy;
			c1->dxy = c2->dxy;
			c2->dxy = tmp;*/
		}
	}
}
