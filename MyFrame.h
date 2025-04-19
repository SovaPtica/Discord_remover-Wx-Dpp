#pragma once
#include <wx/wx.h>

class MyFrame : public wxFrame
{
      void OnHello(wxCommandEvent& event);
      void OnExit (wxCommandEvent& event);
      void OnAbout(wxCommandEvent& ecent);

   public:
      MyFrame();
};

enum 
{
   ID_Hello =1
};
