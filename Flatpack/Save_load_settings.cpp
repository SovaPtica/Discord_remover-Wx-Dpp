#include"MyFrame.h"

void MyFrame::SaveSettings()
{
    wxConfig config("MyAppName");
   
    config.Write("Token", wxString(token));
    
    config.Write("Server_id", wxString::FromUTF8(server_id.str()));
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
}

