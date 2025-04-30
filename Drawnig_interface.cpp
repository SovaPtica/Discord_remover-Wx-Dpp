#include "MyFrame.h"
#include <wx/event.h>
#include <wx/memory.h>

void MyFrame::drowning_interface() {
  comboBox = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                            wxDefaultSize, 0, nullptr, wxCB_READONLY);
  wxButton *button_remove =
      new wxButton(this, wxID_ANY, wxT("Удалить"), wxDefaultPosition);
  wxButton *button_get_channels =
     new wxButton(this, wxID_ANY,wxT(""),wxDefaultPosition);

  // Создаем вертикальный сайзер для компоновки элементов
  wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

  wxStaticText *static_text = new wxStaticText(this, wxID_ANY, wxT("Временной промежуток \n  удаления сообщений "));
  // Создаем два экземпляра DateTimePicker для выбора начальной и конечной даты/времени
  m_startPicker =
      new DateTimePicker(this, wxT("Начальная дата:\t"), wxT("Время:"));
  m_endPicker =
      new DateTimePicker(this, wxT("Конечная дата:\t"), wxT("Время:"));

  // Добавляем элементы интерфейса в основной сайзер
  mainSizer->Add(static_text, 1,wxALL|wxALIGN_CENTER_HORIZONTAL);
  mainSizer->Add(m_startPicker, 1, wxALL, 3); // Начальная дата/время
  mainSizer->Add(m_endPicker, 1, wxALL, 3);   // Конечная дата/время

  //Сетка отрисовки 
  wxBoxSizer *gridSizer =  new wxBoxSizer( wxVERTICAL);
  gridSizer->Add(comboBox, 1,wxEXPAND|wxALL, 3);
  gridSizer->AddStretchSpacer();
  gridSizer->Add(button_remove, 1, wxALIGN_CENTER|wxALL, 3);
  gridSizer->Add(button_get_channels, 1, wxALIGN_CENTER|wxALL, 3);

  wxBoxSizer *horizontSizer =  new wxBoxSizer( wxHORIZONTAL);
  horizontSizer->Add(gridSizer, 0, wxEXPAND|wxALL,1);
  horizontSizer->Add(mainSizer,0 ,wxEXPAND|wxALL,1);

  SetSizer(horizontSizer);
  SetSizerAndFit(horizontSizer);
  GetSizer()->SetSizeHints(this); // Автоподгонка + запрет уменьшения
                                          
        // Устанавливаем значения по умолчанию: текущая дата и следующая
  wxDateTime now = wxDateTime::Now();
  m_startPicker->SetDateTime(now);
  m_endPicker->SetDateTime(now.Add(wxDateSpan::Days(1)));

  button_remove->Bind(wxEVT_BUTTON, &MyFrame::DeleteMessage, this);
  comboBox->Bind(wxEVT_COMBOBOX, &MyFrame::OnComboBoxSelect, this);
  
}

