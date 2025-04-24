#include "MyFrame.h"
#include <wx/event.h>

// Удаление сообщений в канале
// Можно сразу несколько а можно по одному
void MyFrame::discord_remover() {
  // Обработчик команды !channels
  bot->on_message_create([this](const dpp::message_create_t &event) {
    if (event.msg.content == "!channels") {
      dpp::guild *guild = dpp::find_guild(event.msg.guild_id);

      if (!guild) {
        bot->message_create(dpp::message(
            event.msg.channel_id, "Не могу получить информацию о сервере"));
        return;
      }

      my_channels.clear(); // Очищаем текущий список каналов
      comboBox->Clear();   // Очищаем wxComboBox

      std::string channel_list = "**Каналы на сервере:**\n";

      for (const auto &channel_id : guild->channels) {
        dpp::channel *channel = dpp::find_channel(channel_id);
        if (channel) {
          my_channels.push_back({channel->name, channel->id});
          channel_list +=
              "#" + channel->name + " (" + std::to_string(channel->id) + ")\n";
          comboBox->Append(wxString::FromUTF8(
              channel->name.c_str())); // добавление с поддержкой русского языка
        }
      }

      bot->message_create(dpp::message(event.msg.channel_id, channel_list));

      // Устанавливаем первый канал как текущий, если есть
      if (!my_channels.empty()) {
        channel_id = my_channels[0].id;
        comboBox->SetSelection(0);
      }
    }
  });
}

void MyFrame::GetIdList(wxCommandEvent &event) {
  wxTextEntryDialog dialog(this, wxT("Введите ID сeрвера:"),
                           wxT("Установить Channel ID"),
                           std::to_string(server_id));
  if (dialog.ShowModal() == wxID_OK) {
    wxString input = dialog.GetValue();
    try {
      // Преобразуем введенное значение в dpp::snowflake (uint64_t)
      server_id = std::stoull(input.ToStdString());
      std::cout << "Установлен id сервера: " << channel_id << std::endl;

      // Проверяем, есть ли канал в списке, и обновляем выбор в comboBox
      for (size_t i = 0; i < my_channels.size(); ++i) {
        if (my_channels[i].id == channel_id) {
          comboBox->SetSelection(i);
          break;
        }
      }
    } catch (const std::exception &e) {
      wxMessageBox(wxT("Некорректный ID сервера! Введите числовое значение."),
                   wxT("Для получения списка каналов введите в любом из "
                       "каналов (!channels)"),
                   wxOK | wxICON_ERROR);
      std::cout << "Ошибка преобразования channel_id: " << e.what()
                << std::endl;
    }
  }

  if (true) {
    dpp::guild *guild = dpp::find_guild(server_id);
    my_channels.clear(); // Очищаем текущий список каналов
    comboBox->Clear();   // Очищаем wxComboBox

    std::string channel_list = "**Каналы на сервере:**\n";

    for (const auto &channel_id : guild->channels) {
      dpp::channel *channel = dpp::find_channel(channel_id);
      if (channel) {
        my_channels.push_back({channel->name, channel->id});
        channel_list +=
            "#" + channel->name + " (" + std::to_string(channel->id) + ")\n";
        comboBox->Append(wxString::FromUTF8(
            channel->name.c_str())); // добавление с поддержкой русского языка
      }
    }

    // Устанавливаем первый канал как текущий, если есть
    if (!my_channels.empty()) {
      channel_id = my_channels[0].id;
      comboBox->SetSelection(0);
    }
  }
}

void MyFrame::DeleteMessage(wxCommandEvent &event) {
  std::cout << "Нажата кнопка 'Удалить сообщение'" << std::endl;
  
  // Получаем начальную и конечную дату/время из пикеров
        wxDateTime start = m_startPicker->GetDateTime();
        wxDateTime end = m_endPicker->GetDateTime();

        // Преобразуем даты в формат времени Unix (в секундах)
        time_t startTime = start.GetTicks();
        time_t endTime = end.GetTicks();

        // Проверяем, что начальная дата раньше конечной
        if (startTime >= endTime) {
            wxMessageBox(wxT("Начальная дата должна быть раньше конечной!"),
                         wxT("Ошибка"), wxOK | wxICON_ERROR);
            return;
        }

        // Запрашиваем до 100 сообщений из указанного канала
        bot->messages_get(
            channel_id, 0, 0, 0, 100,
            [&, endTime,startTime](const dpp::confirmation_callback_t &callback) {
                // Проверяем, произошла ли ошибка при получении сообщений
                if (callback.is_error()) {
                    // Логируем ошибку в консоль бота
                    bot->log(dpp::ll_error, "Не удалось получить сообщения: " +
                                                callback.get_error().message);
                    // Показываем пользователю сообщение об ошибке
                    wxMessageBox(wxT("Ошибка при получении сообщений: ") +
                                     callback.get_error().message,
                                 wxT("Ошибка"), wxOK | wxICON_ERROR);
                    return;
                }

                // Получаем карту сообщений из ответа
                dpp::message_map messages =
                    std::get<dpp::message_map>(callback.value);
                int deletedCount = 0; // Счетчик удаленных сообщений

                // Перебираем все сообщения
                for (auto &[id, msg] : messages) {
                    // Проверяем, попадает ли время отправки сообщения в заданный диапазон
                    if (msg.sent >= startTime && msg.sent <= endTime) {
                        // Удаляем сообщение
                        bot->message_delete(id, channel_id);
                        deletedCount++;
                        // Задержка 300 мс для избежания ограничений API (rate limit)
                        std::this_thread::sleep_for(std::chrono::milliseconds(300));
                    }
                }

                // Формируем сообщение об успехе с количеством удаленных сообщений
                wxString msg = wxString::Format(
                    wxT("Удалено %d сообщений в заданном диапазоне."), deletedCount);
                // Показываем пользователю результат
                wxMessageBox(msg, wxT("Успех"), wxOK | wxICON_INFORMATION);
            });
}

/* Заготовка
 void MyFrame::GetBotToken(wxCommandEvent &event)
{
        // Цикл до корректного ввода
     while (true)
     {
         wxTextEntryDialog dialog(nullptr,
                                  wxT("Введите строку ровно из 72 символов:"),
                                  wxT("Ввод строки"));

         if (dialog.ShowModal() == wxID_OK)
         {
             input = dialog.GetValue();

             if (input.Length() == 72)
             {
                 token = std::string(input.mb_str()); // сохранить в
                 std::string break; // корректный ввод
             }
             else
             {
                 wxMessageBox(wxT("Строка должна содержать ровно 72
                 символа."), wxT("Ошибка"), wxOK | wxICON_ERROR);
             }
         }
         else
         {
             //return false; // пользователь нажал Cancel — выход из
             приложения
         }
     }


 }
 */


