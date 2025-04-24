#pragma once

#include <dpp/dpp.h>        // Библиотека D++ для взаимодействия с Discord API
#include <wx/datectrl.h>    // Для выбора даты в wxWidgets
#include <wx/timectrl.h>    // Для выбора времени в wxWidgets
#include <wx/wx.h>
// Класс для выбора даты и времени
class DateTimePicker : public wxPanel {
public:
    // Конструктор: создает панель с выбором даты и времени
    DateTimePicker(wxWindow *parent, const wxString &dateLabel = wxT("Дата:"),
                   const wxString &timeLabel = wxT("Время:"),
                   bool showTime = true)
        : wxPanel(parent, wxID_ANY) {
        // Создаем горизонтальный сайзер для компоновки элементов
        wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

        // Метка и элемент для выбора даты
        m_dateText = new wxStaticText(this, wxID_ANY, dateLabel);
        m_datePicker = new wxDatePickerCtrl(this, wxID_ANY);

        // Добавляем метку и выбор даты в сайзер
        sizer->Add(m_dateText, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
        sizer->Add(m_datePicker, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);

        // Если showTime=true, добавляем выбор времени
        if (showTime) {
            m_timeText = new wxStaticText(this, wxID_ANY, timeLabel);
            m_timePicker = new wxTimePickerCtrl(this, wxID_ANY);

            // Добавляем метку и выбор времени в сайзер
            sizer->Add(m_timeText, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
            sizer->Add(m_timePicker, 0, wxALIGN_CENTER_VERTICAL);
        } else {
            // Если время не нужно, устанавливаем указатели в nullptr
            m_timeText = nullptr;
            m_timePicker = nullptr;
        }

        // Устанавливаем сайзер для панели
        SetSizer(sizer);
    }

    // Устанавливает дату и время в элементы выбора
    void SetDateTime(const wxDateTime &dt) {
        m_datePicker->SetValue(dt);
        if (m_timePicker) {
            m_timePicker->SetValue(dt);
        }
    }

    // Возвращает выбранную дату и время
    wxDateTime GetDateTime() const {
        wxDateTime dt = m_datePicker->GetValue();
        if (m_timePicker) {
            // Получаем время из timePicker и устанавливаем его в dt
            wxDateTime::Tm tm = m_timePicker->GetValue().GetTm();
            dt.SetHour(tm.hour);
            dt.SetMinute(tm.min);
            dt.SetSecond(tm.sec);
        } else {
            // Если время не выбрано, устанавливаем 00:00:00
            dt.SetHour(0);
            dt.SetMinute(0);
            dt.SetSecond(0);
        }
        return dt;
    }

    // Устанавливает только дату
    void SetDate(const wxDateTime &date) { m_datePicker->SetValue(date); }

    // Устанавливает только время
    void SetTime(const wxDateTime &time) {
        if (m_timePicker) {
            m_timePicker->SetValue(time);
        }
    }

private:
    // Указатели на элементы интерфейса
    wxDatePickerCtrl *m_datePicker; // Выбор даты
    wxTimePickerCtrl *m_timePicker; // Выбор времени
    wxStaticText *m_dateText;       // Метка для даты
    wxStaticText *m_timeText;       // Метка для времени
};

