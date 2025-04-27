#include"MyFrame.h"

void MyFrame::SaveSettings()
{
    wxConfig config("MyAppName");
   
    config.Write("Token", wxString(token));
    
    config.Write("Server_id", wxString::FromUTF8(server_id.str()));
//    // Очищаем предыдущие записи
//    config.DeleteGroup("/Channels");
//
//    // Сохраняем количество каналов
//    config.Write("/Channels/Count", static_cast<long>(my_channels.size()));
//
//    // Сохраняем каждый канал
//    for (size_t i = 0; i < my_channels.size(); ++i)
//    {
//        wxString group = wxString::Format("/Channels/Channel%zu", i);
//        // Преобразуем std::string в wxString, явно указывая UTF-8
//        wxString name = wxString::FromUTF8(my_channels[i].chanelName.c_str());
//        config.Write(group + "/Name", name);
//        // Преобразуем std::string в wxString явно
//   //     config.Write(group + "/Name", wxString(my_channels[i].chanelName));
//        // Преобразуем dpp::snowflake в wxString вручную
//        config.Write(group + "/ID", wxString::Format("%" wxLongLongFmtSpec "u", static_cast<uint64_t>(my_channels[i].id)));
//    }
    config.Flush();
}

void MyFrame::LoadSettings()
{
  wxConfig config("MyAppName");

  wxString value;
  config.Read("Token", &value); 
     // Преобразование wxString → std::string
  token= value.ToStdString();

  config.Read("Server_id", &value);
  server_id = value.ToStdString();

 std::thread Server([&](){    
    std::this_thread::sleep_for(std::chrono::seconds(3));
    wxCommandEvent fakeEvent;
    GetIdList(fakeEvent);
  });
  
  Server.detach();
 //   // Очищаем текущий список каналов
 //   my_channels.clear();
 //   comboBox->Clear();

 //   // Читаем количество каналов
 //   long count = 0;
 //   config.Read("/Channels/Count", &count, 0L);

 //   // Загружаем каждый канал
 //   for (long i = 0; i < count; ++i)
 //   {
 //       wxString group = wxString::Format("/Channels/Channel%ld", i);
 //       ClientInfo info;

 //       // Читаем chanelName как wxString и преобразуем в std::string
 //       wxString name;
 //       config.Read(group + "/Name", &name, "");
 //       info.chanelName = name.ToStdString();

 //       // Читаем ID как wxString и преобразуем в dpp::snowflake
 //       wxString idStr;
 //       config.Read(group + "/ID", &idStr, "0");
 //       info.id = std::stoull(idStr.ToStdString());

 //       my_channels.push_back(info);
 //       comboBox->Append(name);
 //   }

 //   // Устанавливаем первый канал как текущий, если есть
 //   if (!my_channels.empty())
 //   {
 //       channel_id = my_channels[0].id;
 //       comboBox->SetSelection(0);
 //   }
}

