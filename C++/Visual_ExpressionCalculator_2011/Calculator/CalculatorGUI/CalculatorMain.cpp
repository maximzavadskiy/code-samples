/***************************************************************
 * Name:      CalculatorMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2009-03-28
 * Copyright:  ()
 * License:
 **************************************************************/

#include "CalculatorMain.h"
#include "CalculatorController.h"
#include "Value.h"
#include "GUIBuildInfo.h"
#include "BuildInfoController.h"

#include <wx/url.h>
#include <wx/wfstream.h>
#include <wx/msgdlg.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include "my_fractionlib.h"
//(*InternalHeaders(CalculatorFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)
#ifdef WXMSW
#include <wx/intl.h>
#endif

using namespace Controllers;
//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(CalculatorFrame)
const long CalculatorFrame::ID_PANEL1 = wxNewId();
const long CalculatorFrame::ID_BUTTON17 = wxNewId();
const long CalculatorFrame::ID_BUTTON16 = wxNewId();
const long CalculatorFrame::ID_BUTTON15 = wxNewId();
const long CalculatorFrame::ID_BUTTON7 = wxNewId();
const long CalculatorFrame::ID_BUTTON14 = wxNewId();
const long CalculatorFrame::ID_BUTTON13 = wxNewId();
const long CalculatorFrame::ID_BUTTON12 = wxNewId();
const long CalculatorFrame::ID_BUTTON6 = wxNewId();
const long CalculatorFrame::ID_BUTTON11 = wxNewId();
const long CalculatorFrame::ID_BUTTON10 = wxNewId();
const long CalculatorFrame::ID_BUTTON9 = wxNewId();
const long CalculatorFrame::ID_BUTTON5 = wxNewId();
const long CalculatorFrame::ID_BUTTON3 = wxNewId();
const long CalculatorFrame::ID_BUTTON18 = wxNewId();
const long CalculatorFrame::ID_BUTTON8 = wxNewId();
const long CalculatorFrame::ID_BUTTON4 = wxNewId();
const long CalculatorFrame::ID_BUTTON2 = wxNewId();
const long CalculatorFrame::ID_BUTTON1 = wxNewId();
const long CalculatorFrame::ID_BUTTON19 = wxNewId();
const long CalculatorFrame::ID_BUTTON20 = wxNewId();
const long CalculatorFrame::ID_STATUSBAR1 = wxNewId();
const long CalculatorFrame::ID_MENUITEM1 = wxNewId();
const long CalculatorFrame::ID_MENUITEM4 = wxNewId();
const long CalculatorFrame::ID_MENUITEM5 = wxNewId();
const long CalculatorFrame::ID_MENUITEM6 = wxNewId();
const long CalculatorFrame::ID_MENUITEM7 = wxNewId();
const long CalculatorFrame::ID_MENUITEM8 = wxNewId();
const long CalculatorFrame::ID_MENUITEM9 = wxNewId();
const long CalculatorFrame::ID_MENUITEM10 = wxNewId();
const long CalculatorFrame::ID_MENUITEM2 = wxNewId();
const long CalculatorFrame::ID_MENUITEM3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(CalculatorFrame,wxFrame)
    //(*EventTable(CalculatorFrame)
    //*)
END_EVENT_TABLE()

wxPanel* CalculatorFrame::Panel=0;
TextCtrlItem* CalculatorFrame::ActiveCtrl=0;
ans CalculatorFrame::Answer;
CalculatorFrame* CalculatorFrame::curr_frame;

CalculatorFrame::CalculatorFrame(CalculatorController& calc_ctrl,wxWindow* parent,wxWindowID id):
calculator_controller(calc_ctrl)
{
    //(*Initialize(CalculatorFrame)
    wxMenu* Menu3;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem4;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxGridSizer* GridSizer1;
    wxBoxSizer* BoxSizer1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("Visual ExpressionCalculator"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(564,329));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUBAR));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_REDO")),wxART_FRAME_ICON));
    	SetIcon(FrameIcon);
    }
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(637,299), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetMaxSize(wxSize(5000,5000));
    Panel1->SetBackgroundColour(wxColour(255,255,255));
    BoxSizer1->Add(Panel1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    GridSizer1 = new wxGridSizer(4, 4, 0, 0);
    b1 = new wxButton(this, ID_BUTTON17, _("1"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON17"));
    GridSizer1->Add(b1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    b2 = new wxButton(this, ID_BUTTON16, _("2"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON16"));
    GridSizer1->Add(b2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    b3 = new wxButton(this, ID_BUTTON15, _("3"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON15"));
    GridSizer1->Add(b3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    bp = new wxButton(this, ID_BUTTON7, _("+"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    GridSizer1->Add(bp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    b4 = new wxButton(this, ID_BUTTON14, _("4"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON14"));
    GridSizer1->Add(b4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    b5 = new wxButton(this, ID_BUTTON13, _("5"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON13"));
    GridSizer1->Add(b5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    b6 = new wxButton(this, ID_BUTTON12, _("6"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON12"));
    GridSizer1->Add(b6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    bm = new wxButton(this, ID_BUTTON6, _("-"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    GridSizer1->Add(bm, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    b7 = new wxButton(this, ID_BUTTON11, _("7"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON11"));
    GridSizer1->Add(b7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    b8 = new wxButton(this, ID_BUTTON10, _("8"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON10"));
    GridSizer1->Add(b8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    b9 = new wxButton(this, ID_BUTTON9, _("9"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    GridSizer1->Add(b9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    bmul = new wxButton(this, ID_BUTTON5, _("*"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    GridSizer1->Add(bmul, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button3 = new wxButton(this, ID_BUTTON3, _("="), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    wxFont Button3Font(20,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button3->SetFont(Button3Font);
    GridSizer1->Add(Button3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    bdot = new wxButton(this, ID_BUTTON18, _("."), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON18"));
    wxFont bdotFont(14,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    bdot->SetFont(bdotFont);
    GridSizer1->Add(bdot, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    b0 = new wxButton(this, ID_BUTTON8, _("0"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    GridSizer1->Add(b0, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    bd = new wxButton(this, ID_BUTTON4, _("/"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    GridSizer1->Add(bd, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button2 = new wxButton(this, ID_BUTTON2, _("( )"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    wxFont Button2Font(14,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button2->SetFont(Button2Font);
    Button2->SetToolTip(_("добавить скобки(Ctrl-B)"));
    GridSizer1->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button1 = new wxButton(this, ID_BUTTON1, _("⅓"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    wxFont Button1Font(14,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button1->SetFont(Button1Font);
    Button1->SetToolTip(_("добавить дробь(Ctrl-F)"));
    GridSizer1->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    bce = new wxButton(this, ID_BUTTON19, _("CE"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON19"));
    bce->SetToolTip(_("стереть все(Ctrl-E)"));
    GridSizer1->Add(bce, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    bca = new wxButton(this, ID_BUTTON20, _("CA"), wxDefaultPosition, wxSize(54,34), 0, wxDefaultValidator, _T("ID_BUTTON20"));
    bca->SetToolTip(_("стереть ответ(Ctrl-A)"));
    GridSizer1->Add(bca, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(GridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND|wxSHAPED|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -10 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, ID_MENUITEM1, _("&Выход\tAlt+F4"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&Файл"));
    Menu4 = new wxMenu();
    MenuItem4 = new wxMenuItem(Menu4, ID_MENUITEM4, _("Копировать &выражение\tCtrl+Shift+C"), _("копировать выражение в виде строки"), wxITEM_NORMAL);
    Menu4->Append(MenuItem4);
    MenuItem5 = new wxMenuItem(Menu4, ID_MENUITEM5, _("Копировать &изображение выражения\tCtrl+I"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem5);
    MenuBar1->Append(Menu4, _("П&равка"));
    Menu5 = new wxMenu();
    MenuItem6 = new wxMenuItem(Menu5, ID_MENUITEM6, _("&автовыбор\tCtrl+Shift+A"), wxEmptyString, wxITEM_RADIO);
    Menu5->Append(MenuItem6);
    MenuItem7 = new wxMenuItem(Menu5, ID_MENUITEM7, _("&дробь\tCtrl+Shift+F"), wxEmptyString, wxITEM_RADIO);
    Menu5->Append(MenuItem7);
    MenuItem8 = new wxMenuItem(Menu5, ID_MENUITEM8, _("&смешанное число\tCtrl+Shift+M"), wxEmptyString, wxITEM_RADIO);
    Menu5->Append(MenuItem8);
    MenuItem9 = new wxMenuItem(Menu5, ID_MENUITEM9, _("д&есятичная дробь\tCtrl+Shift+D"), wxEmptyString, wxITEM_RADIO);
    Menu5->Append(MenuItem9);
    MenuBar1->Append(Menu5, _("Ф&ормат ответа"));
    Menu6 = new wxMenu();
    MenuItem10 = new wxMenuItem(Menu6, ID_MENUITEM10, _("О&бновить программу"), wxEmptyString, wxITEM_NORMAL);
    Menu6->Append(MenuItem10);
    MenuBar1->Append(Menu6, _("О&бновление"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, ID_MENUITEM2, _("&Справка по программе\tF1"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("По&мощь"));
    Menu3 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu3, ID_MENUITEM3, _("&О программе\tF2"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem3);
    MenuBar1->Append(Menu3, _("О &программе"));
    SetMenuBar(MenuBar1);
    BoxSizer1->SetSizeHints(this);
    Center();

    Connect(ID_BUTTON17,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::Onb1Click);
    Connect(ID_BUTTON16,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::Onb2Click);
    Connect(ID_BUTTON15,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::Onb3Click);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::OnbpClick);
    Connect(ID_BUTTON14,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::Onb4Click);
    Connect(ID_BUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::Onb5Click);
    Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::Onb6Click);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::OnbmClick);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::Onb7Click);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::Onb8Click);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::Onb9Click);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::OnbmulClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::calculate_expr);
    Connect(ID_BUTTON18,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::OnbdotClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::Onb0Click);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::OnbdClick);
    Connect(ID_BUTTON19,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::OnbceClick);
    Connect(ID_BUTTON20,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::OnbcaClick);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CalculatorFrame::OnQuit);
    Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CalculatorFrame::OnMenuItem4Selected);
    Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CalculatorFrame::OnMenuItem5Selected);
    Connect(ID_MENUITEM6,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CalculatorFrame::OnRadioBox1Select2);
    Connect(ID_MENUITEM7,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CalculatorFrame::OnRadioButton2Select);
    Connect(ID_MENUITEM8,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CalculatorFrame::OnRadioButton3Select);
    Connect(ID_MENUITEM9,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CalculatorFrame::OnRadioButton4Select);
    Connect(ID_MENUITEM10,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CalculatorFrame::OnMenuItem10Selected);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CalculatorFrame::OnMenuItem2Selected);
    Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&CalculatorFrame::OnMenuItem3Selected);
    //*)
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::OnButtonAddBracketItemClicked);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalculatorFrame::OnButtonAddFractionClicked);

    wxAcceleratorEntry entries[2];
    entries[0].Set(wxACCEL_CTRL,(int) 'Q',ID_BUTTON20);
    entries[1].Set(wxACCEL_CTRL,int('E'),ID_BUTTON19);

    wxAcceleratorTable accel(2, entries);
    this->SetAcceleratorTable(accel);



    Panel=Panel1;
    ActiveCtrl=NULL;
   curr_frame=this;
   curr_sel=_("автовыбор");
   My_fract_ctrl=  new FractCtrl(NULL,point(10,Panel->GetPosition().y+Panel->GetSize().GetHeight()/2));
   My_fract_ctrl->SetActive();

   StatusBar1->SetStatusText(_("Добро пожаловать в Visual ExpressionCalculator! F2 для просмотра возможностей."));
}
//-------------------------------------------------------------------
//---------------HELPER FUNCTIONS------------------------------------
//-------------------------------------------------------------------

void CalculatorFrame::AddSymb(const char* p)
{
    int ins=ActiveCtrl->textctrl->GetInsertionPoint();
    ActiveCtrl->textctrl->WriteText(wxString(p,wxConvUTF8));
    ActiveCtrl->textctrl->SetFocus();
    ActiveCtrl->textctrl->SetSelection(1,1);
    ActiveCtrl->textctrl->SetInsertionPoint(ins+1);
}

void CalculatorFrame::draw_fract(point pos,my_fraction f)
{
  wxString s;
  int num=f.getnumerator(),den=f.getdenominator();
  s.Printf(_("%d"),num);
  Answer.l=new wxStaticLine(Panel,wxNewId(),wxPoint(pos.x,pos.y));
  Answer.l->SetBackgroundColour(wxColour(0,0,0));
  #ifdef __WXMSW__
      Answer.l->SetForegroundColour(*wxBLACK/*wxColour(0,0,0)*/);
  #endif

  #ifdef __WXMSW__
    Answer.num=new wxTextCtrl(Panel, wxNewId(), s,wxPoint(pos.x+2,pos.y-Panel->GetCharHeight()-8) , wxDefaultSize, wxTE_READONLY|wxNO_BORDER);
  #endif
  #ifdef __UNIX__
    Answer.num=new wxTextCtrl(Panel, wxNewId(), s,wxPoint(pos.x+2,pos.y-Panel->GetCharHeight()-4) , wxDefaultSize, wxTE_READONLY|wxNO_BORDER);
  #endif
  int w,h;
  Answer.num->GetTextExtent(Answer.num->GetLineText(0),&w,&h);
  Answer.num->SetSize(wxSize(w+4,h));
  s=_("");
  s.Printf(_("%d"),den);
  #ifdef __WXMSW__
     Answer.den=new wxTextCtrl(Panel, wxNewId(), s,wxPoint(pos.x+16,pos.y+9) , wxDefaultSize, wxTE_READONLY|wxNO_BORDER);
  #endif
  #ifdef __UNIX__
     Answer.den=new wxTextCtrl(Panel, wxNewId(), s,wxPoint(pos.x,pos.y+6) , wxDefaultSize, wxTE_READONLY|wxNO_BORDER);
  #endif
  Answer.den->GetTextExtent(Answer.den->GetLineText(0),&w,&h);
  Answer.den->SetSize(wxSize(w+4,h));
   int ma=std::max(Answer.den->GetSize().GetWidth(),Answer.num->GetSize().GetWidth());

  #ifdef __WXMSW__
    Answer.l->SetSize(ma*9/5,2);
  #endif
  #ifdef __UNIX__
    Answer.l->SetSize(ma*7/5,0);
  #endif
    #ifdef __WXMSW__
       Answer.num->Move(wxPoint(pos.x+3+ma*7/10-Answer.num->GetSize().GetWidth()/2,Answer.num->GetPosition().y));
   Answer.den->Move(wxPoint(pos.x+3+ma*7/10-Answer.den->GetSize().GetWidth()/2,Answer.den->GetPosition().y));
  #endif
  #ifdef __UNIX__
       Answer.num->Move(wxPoint(pos.x+ma*7/10-Answer.num->GetSize().GetWidth()/2,Answer.num->GetPosition().y));
   Answer.den->Move(wxPoint(pos.x+ma*7/10-Answer.den->GetSize().GetWidth()/2,Answer.den->GetPosition().y));
  #endif
}
 point CalculatorFrame::draw_doub(point pos,long double num)
 {
          std::ostringstream os;
         //std::cout<<std::fixed<<num;
        os<<std::fixed<<num;
        wxString s(os.str().c_str(),wxConvUTF8);
        Answer.n=new wxTextCtrl(Panel, wxNewId(), s,wxPoint(pos.x,pos.y-Panel->GetCharHeight()/2) , wxDefaultSize, wxTE_READONLY|wxNO_BORDER);
        int w,h;
        Answer.n->GetTextExtent(Answer.n->GetLineText(0),&w,&h);
        Answer.n->SetSize(wxSize(w+4,h));
        pos.x+=Answer.n->GetSize().GetWidth();
        return pos;
 }

 point CalculatorFrame::draw_num(point pos,long long num)
 {
          std::ostringstream os;
        os<<num;
        wxString s(os.str().c_str(),wxConvUTF8);
        Answer.n=new wxTextCtrl(Panel, wxNewId(), s,wxPoint(pos.x,pos.y-Panel->GetCharHeight()/2) , wxDefaultSize, wxTE_READONLY|wxNO_BORDER);
        int w,h;
        Answer.n->GetTextExtent(Answer.n->GetLineText(0),&w,&h);
        Answer.n->SetSize(wxSize(w+4,h));
        pos.x+=Answer.n->GetSize().GetWidth();
        return pos;
 }

void CalculatorFrame::change_ans_format(wxString sel)
{
    //wxString sel= RadioBox1->GetStringSelection();
    if(calculator_controller.get_calculate_answer_errors().size()+calculator_controller.get_set_expression_errors().size()!=0) return;

    point pos=My_fract_ctrl->get_location();
    pos.x+=My_fract_ctrl->get_size().w;
    pos.y-=Panel->GetCharHeight()/2;
    Answer.s=new wxStaticText(Panel, wxNewId(),_("="), wxPoint(pos.x,pos.y));
    pos.x+=Answer.s->GetSize().GetWidth();
    pos.y+=Panel->GetCharHeight()/2;
    #ifdef __WXMSW__
      pos.x+=5;
    #endif

    Value val=calculator_controller.get_answer().get_value();

    if(val.is_int()) sel= _("целое");
    if(sel==_("автовыбор"))
    {
       if(My_fract_ctrl->has_fraction())
       {
         sel=_("смешанное число");
        // calculator_controller.set_answer_format("mixnum");
       }
       else
       {
         sel=_("десятичная дробь");
         //calculator_controller.set_answer_format("fraction");
       }
    }
    if(sel==_("смешанное число"))
    {
        my_mixnum m(val);
        if(m.getnum()==0) sel= _("дробь");
        else
        {
           pos=draw_num(pos,m.getnum());
           draw_fract(pos,abs_fract(m.getfract()));
        }
    }
    if(sel==_("дробь"))
    {
          draw_fract(pos,val);
    }
    if(sel==_("десятичная дробь"))
    {
        draw_doub(pos,val.make_double());
    }
    if(sel==_("целое")) draw_num(pos,val.make_int());
}

void CalculatorFrame::calculate_expr(wxCommandEvent& event)
{
    Answer.clear();
    std::string ans;
    std::string exp;
    std::ostringstream os;
    my_mixnum b;
    StatusBar1->SetStatusText(_(""));
    StatusBar1->SetBackgroundColour(wxNullColour);
    exp=My_fract_ctrl->get_str_val();
    if(exp=="") return;
    vector<const CalculatorError* > errors;
    if(calculator_controller.set_expression(StringExpression(exp)))
    {
      if(calculator_controller.calculate_answer())
      {
        if(!calculator_controller.is_assigment_expression())change_ans_format(curr_sel);
        else StatusBar1->SetStatusText(_("Значение переменной установлено"));
        return;
      }
      else
      {
        errors=calculator_controller.get_calculate_answer_errors();
      }
    }
    else
    {
      errors=calculator_controller.get_set_expression_errors();
    }
//need to print erros
     const CalculatorError* e=errors.front();
    if(dynamic_cast<const SyntaxError*>( e ) )
    {
      ans="Синтаксическая ошибка";
    }
    if(dynamic_cast<const BracketError*>( e ) )
    {
      ans="Синтаксическая ошибка";
    }
    if(dynamic_cast<const ZeroDivide*>( e ) )
    {
      ans="Деление на ноль";
    }

    wxString q(ans.c_str(),wxConvUTF8);
    wxMessageBox(q);
    StatusBar1->SetBackgroundColour(*wxRED);
    StatusBar1->SetStatusText(q);
}
//-------------------------------------------------------------------
//---------------BUTTONS EVENTS--------------------------------------
//-------------------------------------------------------------------

void CalculatorFrame::Onb1Click(wxCommandEvent& event){ AddSymb("1");}

void CalculatorFrame::Onb2Click(wxCommandEvent& event){ AddSymb("2");}

void CalculatorFrame::Onb3Click(wxCommandEvent& event){ AddSymb("3");}

void CalculatorFrame::Onb4Click(wxCommandEvent& event){ AddSymb("4");}

void CalculatorFrame::Onb5Click(wxCommandEvent& event){ AddSymb("5");}

void CalculatorFrame::Onb6Click(wxCommandEvent& event){ AddSymb("6");}

void CalculatorFrame::Onb7Click(wxCommandEvent& event){ AddSymb("7");}

void CalculatorFrame::Onb8Click(wxCommandEvent& event){ AddSymb("8");}

void CalculatorFrame::Onb9Click(wxCommandEvent& event){ AddSymb("9");}

void CalculatorFrame::Onb0Click(wxCommandEvent& event){ AddSymb("0");}

void CalculatorFrame::OnbpClick(wxCommandEvent& event){ AddSymb("+");}

void CalculatorFrame::OnbmClick(wxCommandEvent& event){ AddSymb("-");}

void CalculatorFrame::OnbmulClick(wxCommandEvent& event){ AddSymb("*");}

void CalculatorFrame::OnbdClick(wxCommandEvent& event){ AddSymb("/");}

void CalculatorFrame::OnbdotClick(wxCommandEvent& event){AddSymb(".");}

void CalculatorFrame::OnbceClick(wxCommandEvent& event)
{
  StatusBar1->SetBackgroundColour(wxNullColour);
  StatusBar1->SetStatusText(_(""));
   Answer.clear();
   delete My_fract_ctrl;
   My_fract_ctrl=  new FractCtrl(NULL,point(10,Panel->GetPosition().y+Panel->GetSize().GetHeight()/2));
   My_fract_ctrl->SetActive();
}

void CalculatorFrame::OnbcaClick(wxCommandEvent& event)
{
  Answer.clear();
}

void CalculatorFrame::OnButtonAddBracketItemClicked(wxCommandEvent& event)throw (debug_err)
{
    Answer.clear();
    try{
    if(ActiveCtrl==0) throw debug_err("ActiveCtrl==0");
  ActiveCtrl->parent->AddBracketItem(ActiveCtrl);
  } catch(debug_err& a ){ wxMessageBox(wxString(a.what(),wxConvLocal)); }
}

void CalculatorFrame::OnButtonAddFractionClicked(wxCommandEvent& event)throw (debug_err)
{
    Answer.clear();
    try{
    if(ActiveCtrl==0) throw debug_err("ActiveCtrl==0");
  ActiveCtrl->parent->AddFractionItem(ActiveCtrl);
  } catch(debug_err& a ){ wxMessageBox(wxString(a.what(),wxConvLocal)); }
}
//-------------------------------------------------------------------
//---------------OTHER EVENTS----------------------------------
//-------------------------------------------------------------------
void CalculatorFrame::OnChar(wxKeyEvent& event)
{
     wxCommandEvent a;
    //wxString s;s.Printf(_("%d %d"),int(WXK_RETURN),event.GetKeyCode());
     //wxMessageBox(s);

   //if(event.GetKeyCode()==61) wxMessageBox(_("OK"));
   wxCommandEvent ccevent;
  if(event.GetKeyCode()==WXK_RETURN/*&||(event.GetKeyCode()==61&&!event.ShiftDown())*/) calculate_expr(a);
 if(event.ControlDown())
  {
    if(event.GetKeyCode()==70) OnButtonAddFractionClicked(ccevent);
    if(event.GetKeyCode()==66) OnButtonAddBracketItemClicked(ccevent);
    //if(event.GetKeyCode()==81) OnbcaClick(ccevent);
    //if(event.GetKeyCode()==69) OnbceClick(ccevent);
  //  if(event.GetKeyCode()==66) Button1->Command(ccevent);
  }
}

void CalculatorFrame::OnRadioBox1Select2(wxCommandEvent& event)
{
    curr_sel=_("автовыбор");
   // calculate_expr(event);
}

void CalculatorFrame::OnRadioButton2Select(wxCommandEvent& event)
{
    curr_sel=_("дробь");
    //calculate_expr(event);
}

void CalculatorFrame::OnRadioButton3Select(wxCommandEvent& event)
{
    curr_sel=_("смешанное число");
    //calculate_expr(event);
}

void CalculatorFrame::OnRadioButton4Select(wxCommandEvent& event)
{
    curr_sel=_("десятичная дробь");
    //calculate_expr(event);
}


void CalculatorFrame::OnMenuItem4Selected(wxCommandEvent& event)
{
  if (wxTheClipboard->Open())
  {
    wxString s(My_fract_ctrl->get_str_val().c_str(),wxConvUTF8);
    wxTheClipboard->SetData(new wxTextDataObject(s));
    wxTheClipboard->Close();
  }
}

void CalculatorFrame::OnMenuItem5Selected(wxCommandEvent& event)
{
  if (wxTheClipboard->Open())
  {
  //  Panel1->Raise();
    //CalculatorFrame::ActiveCtrl->textctrl->SetEditable(false);
    //Panel1->SetFocus();
    wxClientDC cdc(Panel1);
    wxBitmap bmp(/*NULL,wxBITMAP_TYPE_PNM,*/My_fract_ctrl->get_size().w, My_fract_ctrl->get_size().h);
    wxMemoryDC mdc(bmp);
    mdc.Blit(0,0, My_fract_ctrl->get_size().w, My_fract_ctrl->get_size().h, &cdc, My_fract_ctrl->get_wx_location().x, My_fract_ctrl->get_wx_location().y);
    mdc.SelectObject(wxNullBitmap);
   // bmp.SaveFile(_("exp.png"), wxBITMAP_TYPE_BMP);
   // wxFileDataObject* dataobj=new wxFileDataObject();
    //dataobj->AddFile(_("exp.png"));
    wxTheClipboard->SetData(new wxBitmapDataObject(bmp));
  //  wxTheClipboard->SetData(dataobj);
    wxTheClipboard->Close();
   // CalculatorFrame::ActiveCtrl->textctrl->SetEditable(true);
  }
}
//-------------------------------------------------------------------
//---------------CLOSE, QUIT AND E. G.-------------------------------
//-------------------------------------------------------------------
CalculatorFrame::~CalculatorFrame()
{
    delete My_fract_ctrl;
}

void CalculatorFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void CalculatorFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void CalculatorFrame::OnMenuItem3Selected(wxCommandEvent& event)
{
  wxString str=wxString(_("Программа разработана и реализована\n Завадским Максимом Олеговичем(7maximus7@mail.com)\n 2008-2010. All rights reserved © \n"))+

  wxString(_("Интерфейс:\n\t Версия: "))+wxString(GUIBuildInfo::get_full_version().c_str(),wxConvUTF8)+
  wxString(_("\n\t Дата выпуска "))+wxString(GUIBuildInfo::get_build_date_string().c_str(),wxConvUTF8)+

  wxString(_("\nЯдро:\n\t Версия: "))+wxString(BuildInfoController::get_full_version().c_str(),wxConvUTF8)+
  wxString(_("\n\t Дата выпуска "))+wxString(BuildInfoController::get_build_date_string().c_str(),wxConvUTF8);
  wxMessageBox(str);
}



void CalculatorFrame::OnMenuItem2Selected(wxCommandEvent& event)
{
  wxMessageBox(_("1.добавление нового выражения со скобками или обыкновенной дроби производится в  туда, где находится мигающий курсор\n2.при нажатии на кнопку «=» производится вычисление значения выражения\n3.результат вычисления выводится в выбранном формате\n4.вывод сообщений об ошибках производится в строку состояния\n5.перемещаться по вводимому выражению можно с помощью стрелок ( на аппаратной клавиатуре)\n6.элементы выражения можно удалять с помощью клавиш «delete» и «backspace»\n7.Появилась возможность вводить переменные и использовать их значения. Для задания значения пишите <переменная>=<любое выражение, включая сложное>. По умолчанию все переменные равны нулю."),wxT("Краткая справка"), wxICON_INFORMATION);
}

void CalculatorFrame::OnPanel1Paint(wxPaintEvent& event)
{
}

void CalculatorFrame::OnMenuItem10Selected(wxCommandEvent& event)
{
  #ifdef __WXMSW__
    wxURL url(wxString(wxT("http://disk.karelia.ru/m/maxim93/My%20Soft/Fraction%20Calculator/Windows/Calculator.exe")));
  #endif
  #ifdef __UNIX__
    wxURL url(wxString(wxT("http://disk.karelia.ru/m/maxim93/My%20Soft/Fraction%20Calculator/Linux/Calculator")));
  #endif
  if(!url.GetError()==wxURL_NOERR)
  {
    wxMessageBox(_("Ошибка соединения с сервером"));
    return;
  }

  wxString htmldata;
  wxInputStream *in = url.GetInputStream();
  if(!(in && in->IsOk()))
  {
      wxMessageBox(_("Ошибка загрузки обновления"));
      return;
  }

  wxString program_file_name;
  #ifdef __WXMSW__
    program_file_name=_("./Update/Calculator.exe");
    wxFileName dirname( _("./Update"), _("") );
   dirname.Mkdir(/*wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL*/);
    wxFileOutputStream file_stream(program_file_name);
    in->Read(file_stream);
    wxMessageBox(_("Загрузка обновления завершена.\n Сейчас в папке с калькулятором появилась папка Update. Закройте приложение, замените исполняемый вами файл на файл, лежащий в папке Update и перезапустите программу."));
  #endif
  #ifdef __UNIX__
      program_file_name=_("Calculator");



      if(!wxRemoveFile(program_file_name))
      {
        wxMessageBox(wxString(_("Чтобы обновить программу имя исполняемого файла должно быть "))+program_file_name);
        return;
      }

      wxFileOutputStream file_stream(program_file_name);
      in->Read(file_stream);
      wxMessageBox(_("Загрузка обновления завершена.\nПерезапустите программу для завершения обновления."));
  #endif
  delete in;
}

