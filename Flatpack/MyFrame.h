#pragma once

#include <dpp/cluster.h>
#include <dpp/snowflake.h>
#include <vector>
#include <wx/event.h>
#include <wx/wx.h>
#include <wx/config.h>
#include <dpp/dpp.h>

#include "DateTimerPicker.h"

//структура для получения списка каналов на сервере
struct ClientInfo
{
  std::string chanelName;  
  dpp::snowflake id;  //id канала
};

class MyFrame : public wxFrame
{
      void OnHello(wxCommandEvent& event);
      void OnExit (wxCommandEvent& event);
      void OnAbout(wxCommandEvent& ecent);//о программе 
      void GetIdList(wxCommandEvent& event);//получить id  каналов сервера
      void OnComboBoxSelect(wxCommandEvent& event);//строка список для выбора сервера
      void DeleteMessage(wxCommandEvent& event);//удаление сообщений
      void SaveSettings();// Сохранение настроек программы 
      void LoadSettings();// загрузка настроек 
      void UpdateTheme();

      wxString input;// для ввода Токена в стартовом окне 
      std::string token;
      dpp::cluster *bot;
      wxComboBox *comboBox;  //для вывода списка каналов на сервере
      std::vector<ClientInfo> my_channels; //список каналов для добавления в вывод
      dpp::snowflake channel_id =0; //
      dpp::snowflake server_id =0;
      DateTimePicker *m_startPicker; // Пикер начальной даты/времени
      DateTimePicker *m_endPicker;   // Пикер конечной даты/времени

   public:
      MyFrame();
     ~MyFrame();
      void drowning_interface();
      void drowning_wx_menu();
      void discord_remover();
};

enum 
{
   ID_Hello =1,
   ID_getChannelList=2,
   ID_getBotToken=3
};
