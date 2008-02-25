/*
 * Copyright (C) 2006-2008 Christian Kindahl, christian dot kindahl at gmail dot com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "stdafx.h"
#include "CopyImageDlg.h"
#include "StringTable.h"
#include "Settings.h"
#include "LangUtil.h"
#include "WaitDlg.h"
#include "SCSI.h"

CCopyImageDlg::CCopyImageDlg() : CPropertySheetImpl<CCopyImageDlg>(lngGetString(COPYIMAGE_TITLE),0,NULL),
	m_ReadPage(true,true)
{
	m_bCentered = false;
	m_uiSourceDeviceIndex = 0;

	m_psh.dwFlags |= PSH_NOAPPLYNOW;
	m_psh.dwFlags |= PSH_HASHELP;

	AddPage(m_GeneralPage);
	AddPage(m_ReadPage);
}

CCopyImageDlg::~CCopyImageDlg()
{
}

LRESULT CCopyImageDlg::OnShowWindow(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	// Center the window, once.
	if (wParam == TRUE && !m_bCentered)
	{
		CenterWindow();
		m_bCentered = true;
	}

	bHandled = FALSE;
	return 0;
}

LRESULT CCopyImageDlg::OnSetDeviceIndex(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	m_uiSourceDeviceIndex = (unsigned int)lParam;

	bHandled = TRUE;
	return 0;
}

LRESULT CCopyImageDlg::OnGetDeviceIndex(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	bHandled = TRUE;
	return m_uiSourceDeviceIndex;
}

LRESULT CCopyImageDlg::OnCheckMediaBroadcast(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled)
{
	if (m_GeneralPage.IsWindow())
		::SendMessage(m_GeneralPage,WM_CHECKMEDIA,wParam,lParam);
	if (m_ReadPage.IsWindow())
		::SendMessage(m_ReadPage,WM_CHECKMEDIA,wParam,lParam);

	bHandled = TRUE;
	return 0;
}

TCHAR *CCopyImageDlg::GetFileName()
{
	return m_GeneralPage.GetFileName();
}