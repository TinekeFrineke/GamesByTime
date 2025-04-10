// GameSavesDialog.cpp : implementation file
//

#include "pch.h"
#include "LandsOrLOreAlphabet.h"
#include "GameSavesDialog.h"
#include "afxdialogex.h"


// GameSavesDialog dialog

IMPLEMENT_DYNAMIC(GameSavesDialog, CDialogEx)

GameSavesDialog::GameSavesDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LANDSORLOREALPHABET_DIALOG, pParent)
{

}

GameSavesDialog::~GameSavesDialog()
{
}

void GameSavesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GameSavesDialog, CDialogEx)
END_MESSAGE_MAP()


// GameSavesDialog message handlers
