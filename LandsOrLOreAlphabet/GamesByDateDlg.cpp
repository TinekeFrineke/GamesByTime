
// GamesByDateDlg.cpp : implementation file
//

#include "pch.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <string>

#include "framework.h"
#include "GameDefinitions.h"
#include "IStrategy.h"
#include "GamesByDate.h"
#include "GamesByDateDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "StrategyFactory.h"
#include "StrategyUtilities.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace {

	std::wstring InifileName()
	{
		auto curpath(std::filesystem::current_path());
		auto file(curpath / _T("GamesByDate.ini"));
		return file.wstring();
	}
} // namespace

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLandsOrLOreAlphabetDlg dialog



CLandsOrLOreAlphabetDlg::CLandsOrLOreAlphabetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LANDSORLOREALPHABET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CLandsOrLOreAlphabetDlg::~CLandsOrLOreAlphabetDlg()
{
}

void CLandsOrLOreAlphabetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PATH_EDIT, m_Path);
	DDX_Control(pDX, IDC_SAVELIST, m_SaveList);
	DDX_Control(pDX, IDC_GAME_COMBO, m_GameCombo);
}

void CLandsOrLOreAlphabetDlg::SelectGame(Game game)
{
	m_GameCombo.SelectString(0, ToString(game).c_str());
	m_Strategy = StrategyFactory::CreateStrategy(game);
}

BEGIN_MESSAGE_MAP(CLandsOrLOreAlphabetDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PATH_BUTTON, &CLandsOrLOreAlphabetDlg::OnBnClickedPathButton)
	ON_EN_KILLFOCUS(IDC_PATH_EDIT, &CLandsOrLOreAlphabetDlg::OnEnKillfocusPathEdit)
	ON_CBN_SELCHANGE(IDC_GAME_COMBO, &CLandsOrLOreAlphabetDlg::OnCbnSelchangeGameCombo)
//	ON_WM_DESTROY()
ON_BN_CLICKED(IDC_REFRESHBUTTON1, &CLandsOrLOreAlphabetDlg::OnBnClickedRefreshbutton)
ON_EN_CHANGE(IDC_PATH_EDIT, &CLandsOrLOreAlphabetDlg::OnEnChangePathEdit)
END_MESSAGE_MAP()


// CLandsOrLOreAlphabetDlg message handlers

BOOL CLandsOrLOreAlphabetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	const auto games{ allGames() };
	for (auto game: games)
		m_GameCombo.AddString(game.second.c_str());

	SelectGame(m_settings.GetGame());

	// TODO: Add extra initialization here
	const std::wstring path{ m_settings.GetPath(m_settings.GetGame()) };
	m_Path.SetWindowText(path.c_str());
	UpdateFromPath(path);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLandsOrLOreAlphabetDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLandsOrLOreAlphabetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLandsOrLOreAlphabetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

std::pair<FILETIME, std::string> Interpret(const std::wstring& rPath, const WIN32_FIND_DATA& aData)
{
	const size_t length(rPath.length() + wcslen(aData.cFileName));
	char* path = new char[length + 1];
	sprintf_s(path, length + 1, "%S%S", rPath.c_str(), aData.cFileName);
	std::ifstream instr(path);
	delete[] path;
	std::string name;
	std::getline(instr, name);

	return std::pair<FILETIME, std::string>(aData.ftLastWriteTime, name);
}

void CLandsOrLOreAlphabetDlg::UpdateFromPath(const std::wstring& aPath)
{
	m_CurrentPath = aPath;
	if (m_CurrentPath.empty() || m_CurrentPath.back() != '\\')
		m_CurrentPath += '\\';

	auto files(m_Strategy->ListItemsInPath(aPath));

	m_SaveList.ResetContent();
	for (auto name = files.rbegin(); name != files.rend(); ++name)
	{
		if (!name->second.empty())
			m_SaveList.AddString(name->second.c_str());
	}
}

// timer, sorry about the jump
static void CALLBACK BFFTimer(HWND hc, UINT, UINT_PTR idEvent, DWORD)
{
	ATLASSERT(404 == idEvent);
	KillTimer(hc, idEvent);

	/*HTREEITEM*/LRESULT sel = SendMessage(hc, TVM_GETNEXTITEM, TVGN_CARET, 0L);
	if (sel != 0)
		PostMessage(hc, TVM_ENSUREVISIBLE, 0, sel);
	else
		ATLASSERT(0);
}

// locate the treeview in browse for folder dialog
static BOOL CALLBACK winenumfn(HWND hc, LPARAM lp)
{
	TCHAR buf[100];
	buf[0] = 0;
	GetClassName(hc, buf, ARRAYSIZE(buf));

	if (lstrcmpi(WC_TREEVIEW, buf) == 0) {
		*(HWND*)lp = hc;
		return 0; // found
	}

	return 1; // more
}

static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED)
	{
		static TCHAR path[MAX_PATH];
		wcscpy_s<MAX_PATH>(path, (const TCHAR*)lpData);
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, LPARAM(path));

		// find the tree and ensure selection is visible
		HWND hc = 0;
		EnumChildWindows(hwnd, winenumfn, (LPARAM)&hc);
		ATLASSERT(hc); // not found?
		if (hc) {
			// direct ensurevisible only works half of the time, so try a timer instead
			SetTimer(hc, 404, 250/*ms*/, BFFTimer);
		}
	}

	return 0;
}

std::optional<std::wstring> BrowseFolder(std::wstring saved_path)
{
	TCHAR path[MAX_PATH];

	const TCHAR* path_param = saved_path.c_str();
	TCHAR name[1024] = L"C:\\Games\\GOG\\Betrayal at Krondor\\GAMES";

	BROWSEINFO bi = { 0 };
	bi.lpszTitle = L"Browse for folder...";
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = (LPARAM)path_param;
	bi.pszDisplayName = name;//saved_path.c_str();

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != 0)
	{
		//get the name of the folder and put it in path
		SHGetPathFromIDList(pidl, path);

		//free memory used
		IMalloc* imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}

		return path;
	}

	return std::nullopt;
}
void CLandsOrLOreAlphabetDlg::OnBnClickedPathButton()
{
	const auto folder(BrowseFolder(m_settings.GetPath(m_settings.GetGame())));
	if (!folder)
		return;

	m_settings.SetPath(m_settings.GetGame(), *folder);
	m_Path.SetWindowTextW(folder->c_str());
	UpdateFromPath(*folder);
}

void CLandsOrLOreAlphabetDlg::OnEnKillfocusPathEdit()
{
	CString string;
	m_Path.GetWindowText(string);
	if (m_CurrentPath == string.GetBuffer() || string.IsEmpty())
	{
		return;
	}

	UpdateFromPath(string.GetBuffer());
	m_settings.SetPath(m_settings.GetGame(), m_CurrentPath);
}


void CLandsOrLOreAlphabetDlg::OnCbnSelchangeGameCombo()
{
	Game selected(static_cast<Game>(m_GameCombo.GetCurSel()));

	m_Strategy = StrategyFactory::CreateStrategy(selected);

	UpdateFromPath(m_CurrentPath);
	m_settings.SetGame(selected);
	m_settings.SetPath(selected, m_CurrentPath);
}


void CLandsOrLOreAlphabetDlg::OnBnClickedRefreshbutton()
{
	UpdateFromPath(m_CurrentPath);
}


void CLandsOrLOreAlphabetDlg::OnEnChangePathEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
