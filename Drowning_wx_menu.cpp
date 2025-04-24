#include "MyFrame.h"
#include <wx/event.h>

void MyFrame::drowning_wx_menu()
{
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(ID_Hello, wxT("&Привет...\tCtrl-H"),
                   wxT("Привет эта программа для управления каналами discora"));
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);

  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT,wxT("О приложении"));

  wxMenu *get_channel_list = new wxMenu;
  get_channel_list->Append(ID_getChannelList, wxT("Получить список каналов"));
  get_channel_list->Append(ID_getBotToken, wxT("Заготовка"));


  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, wxT("&Файл"));
  menuBar->Append(menuHelp, wxT("&ПОмощь"));
  menuBar->Append(get_channel_list, wxT("Бот"));

  SetMenuBar(menuBar);

  Bind(wxEVT_MENU, &MyFrame::GetIdList, this , ID_getChannelList);
 //заготовка Bind(wxEVT_MENU, &MyFrame::GetBotToken, this , ID_getBotToken);

}
