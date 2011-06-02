/**-----------------------------------------------------------
Autor       : Neumair Günther
Class       : Zeitung
Date        : 06.11.2010
LastChange  : 29.01.2011
Description : Runtime Logging device for wxWidgets
Add news ONLY via add_news_save
-------------------------------------------------------------*/

#ifndef NEWS_H
#define NEWS_H

#include <wx/stattext.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/window.h>
#include <wx/wx.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <string>
#include <pthread.h>

////PREDEFINED COLOURS////////
#define N_Warning  255, 200, 0
#define N_Error    255, 0  , 0
#define N_Info     0  , 255, 0
#define N_Log      0  , 0  , 0
//////////////////////////////

extern pthread_mutex_t *os_mutex;

class t_News : public wxPanel
{

public:

    t_News(wxWindow* parent, int id);
    virtual ~t_News();
    void add_news (std::string const & value, int r, int g, int b);
    std::ofstream &get_log_stream(); ///get stream in order to log directly into file

private:

    wxTextCtrl * text;
    wxStaticText *Header;

    std::ofstream os;

};

extern t_News *Zeitung;


///Only use add_news_save in order to avoid problems if news is not instantiated
/// ********** THREAD SAVE *****************************************************
static void add_news_save(std::string const & value, int r, int g, int b)
{
    pthread_mutex_lock(os_mutex);

    if (Zeitung)
    {
        Zeitung->add_news(value, r,g,b);
    }

    pthread_mutex_unlock(os_mutex);
}


#endif // NEWS_H


