/**-----------------------------------------------------------
Autor       : Neumair Günther
Class       : Zeitung
Date        : 06.11.2010
LastChange  : 06.11.2010
Description : Runtime Logging device for wxWidgets
Add news ONLY via add_news_save
-------------------------------------------------------------*/

#include "news.h"
#include <wx/colour.h>
#include <wx/gdicmn.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <iostream>
#include <sstream>

#define LOGFILE "Log.txt"



pthread_mutex_t *os_mutex =0;
t_News * Zeitung = 0;
t_News::~t_News()
{
    os.close();
}


t_News::t_News(wxWindow* parent, int id): wxPanel(parent,id)
{
    wxBoxSizer *Mainsizer = new wxBoxSizer( wxHORIZONTAL);
    Header = new wxStaticText(this,wxID_ANY,wxT("Nachrichten"), wxDefaultPosition, wxDefaultSize,0);
    text = new wxTextCtrl(this, -1, _(""), wxDefaultPosition,wxSize(300,250), wxNO_BORDER | wxTE_MULTILINE);
    Mainsizer->Add(Header,0, wxALL,0);
    Mainsizer->Add(text,0, wxALL,0);
    os.open("Log.txt");
    Zeitung = this;

    os_mutex = new pthread_mutex_t;
    pthread_mutex_init(os_mutex,0);

}


std::ofstream &t_News::get_log_stream()
{
    return os;
}

void t_News::add_news(std::string const & value, int r , int g , int b)
{


    wxString tmp(value.c_str(), wxConvUTF8);
    text->SetForegroundColour( wxColour( r,g,b ) );
    text->AppendText(tmp);
    text->AppendText(wxT("\n"));

    if(os)
    {
        os << value;
        os << std::endl;
        os.flush();
    }

}

