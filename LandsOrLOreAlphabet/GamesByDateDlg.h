
// LandsOrLOreAlphabetDlg.h : header file
//

#pragma once

#include <memory>
#include <string>

#include "Settings.h"

class IStrategy;

// CLandsOrLOreAlphabetDlg dialog
class CLandsOrLOreAlphabetDlg : public CDialogEx
{
// Construction
public:
	CLandsOrLOreAlphabetDlg(CWnd* pParent = nullptr);	// standard constructor
	~CLandsOrLOreAlphabetDlg() override;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LANDSORLOREALPHABET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	void SelectGame(Game game);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPathButton();
	afx_msg void OnEnKillfocusPathEdit();
	afx_msg void OnCbnSelchangeGameCombo();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	std::wstring m_CurrentPath;
	void UpdateFromPath(const std::wstring& aPath);

	CEdit m_Path;
	CListBox m_SaveList;
	CComboBox m_GameCombo;

	Settings m_settings;
	std::unique_ptr<IStrategy> m_Strategy;
public:
	afx_msg void OnBnClickedRefreshbutton();
	afx_msg void OnEnChangePathEdit();
};
