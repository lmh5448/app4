// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를 
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된 
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해 
// 추가적으로 제공되는 내용입니다.  
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.  
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "app4.h"

#include "MainFrm.h"
#include"app4Doc.h"
#include"app4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
ON_COMMAND(ID_COMBO3, &CMainFrame::OnCombo3)
ON_UPDATE_COMMAND_UI(ID_COMBO3, &CMainFrame::OnUpdateCombo3)
ON_COMMAND(ID_COMBO4, &CMainFrame::OnCombo4)
ON_UPDATE_COMMAND_UI(ID_COMBO4, &CMainFrame::OnUpdateCombo4)
ON_COMMAND(ID_BUTTON7, &CMainFrame::OnButton7)
ON_COMMAND(ID_BUTTON8, &CMainFrame::OnButton8)
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_WINDOWS_7);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	CMFCRibbonComboBox* pComboBox = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(ID_COMBO3));
	pComboBox->AddItem(CA2W("1"));
	pComboBox->AddItem(CA2W("2.5"));
	pComboBox->AddItem(CA2W("1/2.5"));
	pComboBox->OnSelectItem(0);

	pComboBox = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(ID_COMBO4));
	pComboBox->AddItem(CA2W("1"));
	pComboBox->AddItem(CA2W("2"));
	pComboBox->AddItem(CA2W("3"));
	pComboBox->AddItem(CA2W("4"));
	pComboBox->AddItem(CA2W("5"));
	pComboBox->OnSelectItem(4);


	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// Visual Studio 2005 스타일 도킹 창 동작을 활성화합니다.
	CDockingManager::SetDockingMode(DT_SMART);
	// Visual Studio 2005 스타일 도킹 창 자동 숨김 동작을 활성화합니다.
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	// 보관된 값에 따라 비주얼 관리자 및 스타일을 설정합니다.
	OnApplicationLook(theApp.m_nAppLook);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


void CMainFrame::OnCombo3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCRibbonComboBox* pComboBox = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(ID_COMBO3));
	int nCurSel = pComboBox->GetCurSel();
	Capp4Doc* pDoc = (Capp4Doc*)GetActiveDocument();
	Capp4View* pView = (Capp4View*)GetActiveView();
	if (nCurSel == 0) {
		pDoc->m_gamma = 1;
	}else if (nCurSel == 1) {
		pDoc->m_gamma = 2.5;
		pView->OnFilterGamma(pDoc->m_gamma);
	}
	else if (nCurSel == 2) {
		pDoc->m_gamma = 1/2.5;
		pView->OnFilterGamma(pDoc->m_gamma);
	}
}


void CMainFrame::OnUpdateCombo3(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CMFCRibbonComboBox* pComboBox = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(ID_COMBO3));
	int nCurSel = pComboBox->GetCurSel();
	pCmdUI->SetCheck(nCurSel);
}


void CMainFrame::OnCombo4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCRibbonComboBox* pComboBox = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(ID_COMBO4));
	int nCurSel = pComboBox->GetCurSel();
	Capp4Doc* pDoc = (Capp4Doc*)GetActiveDocument();
	if (nCurSel == 0) {
		pDoc->m_thickness = 1;
	}
	else if (nCurSel == 1) {
		pDoc->m_thickness = 2;
	}
	else if (nCurSel == 2) {
		pDoc->m_thickness = 3;
	}
	else if (nCurSel == 3) {
		pDoc->m_thickness = 4;
	}
	else if (nCurSel == 4) {
		pDoc->m_thickness = 5;
	}
}


void CMainFrame::OnUpdateCombo4(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CMFCRibbonComboBox* pComboBox = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(ID_COMBO4));
	int nCurSel = pComboBox->GetCurSel();
	pCmdUI->SetCheck(nCurSel);
}


void CMainFrame::OnButton7()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetActiveDocument();
	CMFCRibbonColorButton* pColorButton = DYNAMIC_DOWNCAST(CMFCRibbonColorButton, m_wndRibbonBar.FindByID(ID_BUTTON7));
	COLORREF color = pColorButton->GetColor();
	pDoc->m_color_r = GetRValue(color);
	pDoc->m_color_g = GetGValue(color);
	pDoc->m_color_b = GetBValue(color);
}

void CMainFrame::OnButton8()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetActiveDocument();
	CMFCRibbonColorButton* pColorButton = DYNAMIC_DOWNCAST(CMFCRibbonColorButton, m_wndRibbonBar.FindByID(ID_BUTTON8));
	COLORREF color = pColorButton->GetColor();
	pDoc->m_brush_color_r = GetRValue(color);
	pDoc->m_brush_color_g = GetGValue(color);
	pDoc->m_brush_color_b = GetBValue(color);
}

