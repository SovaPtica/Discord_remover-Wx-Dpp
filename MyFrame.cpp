#include "MyFrame.h"

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Discor control", wxDefaultPosition,
              wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER)//отсключена возможность изменения размеров окна 
{
  LoadSettings();
  // Цикл до корректного ввода
  while (token.empty()) {
    wxTextEntryDialog dialog(nullptr,
                             wxT("Введите строку ровно из 72 символов:"),
                             wxT("Ввод строки"));

    if (dialog.ShowModal() == wxID_OK) {
      input = dialog.GetValue();
      std::cout << input << std::endl;

      if (input.Length() == 72) {
        token = std::string(input.mb_str()); // сохранить в std::string
        break;                               // корректный ввод
      } else {
        wxMessageBox(wxT("Строка должна содержать ровно 72 символа."),
                     wxT("Ошибка"), wxOK | wxICON_ERROR);
      }
    } else {
      // return false; // пользователь нажал Cancel — выход из приложения
    }
  }
  try {
    // Создаем кластер с токеном и необходимыми интентами
    bot = new dpp::cluster(token,
                           dpp::i_default_intents | dpp::i_message_content);

    // Обработчик события готовности - если токен валидный, этот обработчик
    // будет вызван
    bot->on_ready([&](const dpp::ready_t &event) {
      std::cout << "Бот успешно подключен как " << bot->me.username << "#"
                << bot->me.discriminator << " (ID: " << bot->me.id << ")"
                << std::endl;

      // После проверки токена можно завершить программу
      // или продолжить выполнение основной логики бота
      //  bot->shutdown();
    });

    // Обработчик ошибок - будет вызван, если возникнет проблема с токеном
    bot->on_log([](const dpp::log_t &event) {
      if (event.severity == dpp::ll_error) {
        std::cerr << "Ошибка: " << event.message << std::endl;

        // Проверяем, связана ли ошибка с токеном
        if (event.message.find("token") != std::string::npos ||
            event.message.find("authentication") != std::string::npos) {
          std::cerr << "Возможно, предоставлен неверный токен бота!"
                    << std::endl;
          exit(1);
        }
      }
    });

    // Запуск с блокировкой - ожидаем ответа от Discord API
    std::cout << "Проверка токена..." << std::endl;
    //   bot->start(dpp::st_wait);

    std::cout << "Токен успешно проверен!" << std::endl;
    // return 0;
    // Запускаем бота в отдельном потоке
    std::thread bot_thread([this]() {
      std::cout << "Запуск бота в отдельном потоке..." << std::endl;
      bot->start(dpp::st_wait);
    });
    bot_thread.detach();

  } catch (const std::exception &e) {
    std::cerr << "Произошла ошибка: " << e.what() << std::endl;
    //   return 1;
  }

  discord_remover();
  drowning_interface();
  drowning_wx_menu();

  CreateStatusBar();
  SetStatusText(wxT("Добро пожаловать"));

  Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
  Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
  
}

MyFrame::~MyFrame() { SaveSettings(); }
