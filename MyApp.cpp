#include "MyApp.h"
#include "MyFrame.h"
#include <wx/event.h>

bool MyApp::OnInit() {
     MyFrame *frame = new MyFrame();
  frame->Show(true);
  return true;
}

void MyFrame::OnExit(wxCommandEvent &event) { Close(true); }

void MyFrame::OnAbout(wxCommandEvent &event) {
  wxMessageBox(wxT("Пример"),wxT( "Приложение для управления Discord"),
               wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent &event) {
  wxLogMessage(wxT("Привет "));
}

void MyFrame::OnComboBoxSelect(wxCommandEvent &event) {
    int selection = comboBox->GetSelection();
    if (selection != wxNOT_FOUND && selection < my_channels.size()) {
      channel_id = my_channels[selection].id;
      std::cout << "Выбран канал: " << my_channels[selection].chanelName
                << " (ID: " << channel_id << ")" << std::endl;
    }
}

void MyFrame::UpdateTheme()
{
    // Обновляем все цвета
    wxColour bgCol = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW);
    wxColour fgCol = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
    
    SetBackgroundColour(bgCol);
    SetForegroundColour(fgCol);
    
    // Рекурсивно обновляем все дочерние элементы
    wxWindowList& children = GetChildren();
    for (wxWindow* child : children) {
        child->SetBackgroundColour(bgCol);
        child->SetForegroundColour(fgCol);
        child->Refresh();
    }
    
    Refresh();
}
