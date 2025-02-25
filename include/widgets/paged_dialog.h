/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2017-2021 KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef PAGED_DIALOG_H
#define PAGED_DIALOG_H

#include <dialog_shim.h>


class WX_INFOBAR;
class wxTreebook;

class PAGED_DIALOG : public DIALOG_SHIM
{
public:
    PAGED_DIALOG( wxWindow* aParent, const wxString& aTitle, bool aShowReset,
                  const wxString& aAuxiliaryAction = wxEmptyString );
    ~PAGED_DIALOG() override;

    wxTreebook* GetTreebook() { return m_treebook; }

    void SetInitialPage( const wxString& aPage, const wxString& aParentPage = wxEmptyString );

    void SetModified() { m_modified = true; }

    void SetError( const wxString& aMessage, const wxString& aPageName, int aCtrlId, int aRow = -1,
                   int aCol = -1 );

    void SetError( const wxString& aMessage, wxWindow* aPage, wxWindow* aCtrl, int aRow = -1,
                   int aCol = -1 );

protected:
    void finishInitialization();

    bool TransferDataToWindow() override;
    bool TransferDataFromWindow() override;

    void OnClose( wxCloseEvent& event );
    void OnCancel( wxCommandEvent& event );
    virtual void OnAuxiliaryAction( wxCommandEvent& event ) { event.Skip(); }
    void OnResetButton( wxCommandEvent& aEvent );
    virtual void OnPageChanged( wxBookCtrlEvent& event );
    virtual void OnPageChanging( wxBookCtrlEvent& aEvent );

    wxTreebook* m_treebook;
    wxButton*   m_auxiliaryButton;
    wxButton*   m_resetButton;
    wxButton*   m_cancelButton;
    WX_INFOBAR* m_infoBar;

private:
    wxString    m_title;

    bool        m_dirty;

    wxBoxSizer* m_buttonsSizer;
};


#endif //PAGED_DIALOG_H
