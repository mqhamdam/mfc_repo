
// Assignment1View.cpp: реализация класса CAssignment1View
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Assignment1.h"
#endif

#include "Assignment1Doc.h"
#include "Assignment1View.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "iostream"
#include "time.h"
#include "stdlib.h"
using namespace std;

// CAssignment1View

IMPLEMENT_DYNCREATE(CAssignment1View, CView)

BEGIN_MESSAGE_MAP(CAssignment1View, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
//	ON_WM_SIZE()
END_MESSAGE_MAP()

// Создание или уничтожение CAssignment1View

CAssignment1View::CAssignment1View() noexcept
{
	// TODO: добавьте код создания
	srand((unsigned)time(NULL));
}

CAssignment1View::~CAssignment1View() 

{
}

BOOL CAssignment1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CAssignment1View

void CAssignment1View::OnDraw(CDC* /*pDC*/)
{
	CAssignment1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
	CClientDC dc(this);
	dc.TextOutW(50, 50, L"2019117366 MUQIMOV HAMDAM");
	for (int i = 0; i < vEllipse.size(); i++) {
		CustomEllipse obj = vEllipse[i];
		int x1 = obj.point.x + obj.radius;
		int x2 = obj.point.x - obj.radius;
		int y1 = obj.point.y + obj.radius;
		int y2 = obj.point.y - obj.radius;
		dc.Ellipse(x1, y1, x2, y2);
	}
	
}


// Печать CAssignment1View

BOOL CAssignment1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CAssignment1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CAssignment1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CAssignment1View

#ifdef _DEBUG
void CAssignment1View::AssertValid() const
{
	CView::AssertValid();
}

void CAssignment1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAssignment1Doc* CAssignment1View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAssignment1Doc)));
	return (CAssignment1Doc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CAssignment1View


void CAssignment1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	if (nChar & VK_SPACE) {
		drawRandomEllipse(10);
	}

	
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CAssignment1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	drawEllipse(point);

	CView::OnLButtonDown(nFlags, point);
}

/** 
 * Randomly draw Ellipses with random radius on board 
 * @param count (number of ellipses to draw) is optional and by default is 10	
 * @return void
 */
void CAssignment1View::drawRandomEllipse(int count)
{
	// TODO: Добавьте сюда код реализации.
	int i = 0; // iterator
	int s = 0, f = 0; // success, fail
	CRect rect;
	GetClientRect(rect);

	while (i++ < count) {
		int radius = rand() % 50 + 10;
		int rx = rand() % rect.Width();
		int ry = rand() & rect.Height();
		CPoint pt = CPoint(rx, ry);
		if (checkCircleIntersectOrTouch(CustomEllipse(pt, radius)) == false) {
			drawEllipse(pt, radius);
			s++; // success count
		}
		else {
			f++; // fail count
		}
	}
	CString str;
	str.Format(L"Circles Spawned!\nSuccess: %d\nFailed:%d", s, f);
	AfxMessageBox(str);
}



/*
	Draws ellipse in gived position(point) and with gived radius
*/
void CAssignment1View::drawEllipse(CPoint point, int radius)
{
	// TODO: Добавьте сюда код реализации.
	CustomEllipse obj = CustomEllipse(point,radius);
	if (checkCircleIntersectOrTouch(obj)
		== false) {

	vEllipse.push_back(obj);
	Invalidate();
	}
	else {
		AfxMessageBox(L"Can not put there Ellipse, it intersects or touches other ellipses, try to click another place");
	}
}


/*
	@param Ellipse is required to check if this ellipse intersects or touches other ellipses
	@return false ok / true fail
*/
bool CAssignment1View::checkCircleIntersectOrTouch(CustomEllipse ellipse)
{
	// TODO: Добавьте сюда код реализации.
	bool doesTouchOrIntersect = false;
	CustomEllipse o1 = ellipse;
	for (int i = 0; i < vEllipse.size(); i++) {
		CustomEllipse o2 = vEllipse[i];
		int distSq = (o1.point.x - o2.point.x) * (o1.point.x - o2.point.x) +
			(o1.point.y - o2.point.y) * (o1.point.y - o2.point.y);
		int radSumSq = (o1.radius + o2.radius) * (o1.radius + o2.radius);

		if (distSq == radSumSq) {

			doesTouchOrIntersect = true;
			break;
		} else if (distSq > radSumSq) {
			continue;
		} else {
			doesTouchOrIntersect = true;
			break;
		}
	}
	return doesTouchOrIntersect;
}
