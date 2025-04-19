#include "MyApp.h"
#include "MyFrame.h"

bool MyApp::OnInit() {
  MyFrame *frame = new MyFrame();
  frame->Show(true);
  return true;
}

void MyFrame::OnExit(wxCommandEvent &event) { Close(true); }

void MyFrame::OnAbout(wxCommandEvent &event) {
  wxMessageBox("This is a wxWidgets Hello World example", "About Hello World",
               wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent &event) {
  wxLogMessage("Hello world from wxWidgets!");
}
