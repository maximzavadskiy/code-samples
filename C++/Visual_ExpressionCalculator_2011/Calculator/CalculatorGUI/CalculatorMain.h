/***************************************************************
 * Name:      CalculatorMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2009-03-28
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef CALCULATORMAIN_H
  #define CALCULATORMAIN_H
#endif
//(*Headers(CalculatorFrame)
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#ifndef EXP-CLASSES_H
  #define EXP-CLASSES_H
  #include "exp-classes.h"
#endif

#include "PreExpression.h"
#include <sstream>
#include <wx/msgdlg.h>
#include <ios>
#include <wx/clipbrd.h>
#include <wx/dataobj.h>
#include <wx/textctrl.h>
#include <wx/dcmemory.h>
#define DEBUG
#include "CalculatorController.h"
using namespace Controllers;

class my_fraction;
class CalculatorFrame: public wxFrame
{
    public:
        static wxPanel* Panel;
        static ans Answer;
        static TextCtrlItem* ActiveCtrl;
        static CalculatorFrame* curr_frame;
        void change_ans_format(wxString s);
        int  bit;
        CalculatorFrame(CalculatorController& calc_ctrl,wxWindow* parent,wxWindowID id = -1);
        virtual ~CalculatorFrame();
        FractCtrl* My_fract_ctrl;
        void OnChar(wxKeyEvent& event);
        wxString curr_sel;
    private:
        CalculatorController& calculator_controller;
        void calculate_expr(wxCommandEvent& event);
        void AddSymb(const char* p);
        void draw_fract(point pos,my_fraction);
         point draw_num(point pos,long long num)  ;
         point draw_doub(point pos,long double num)  ;


        //(*Handlers(CalculatorFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnRadioButton3Select(wxCommandEvent& event);
        void OnRadioButton2Select(wxCommandEvent& event);
        void OnRadioBox1Select(wxCommandEvent& event);
        void OnButtonAddBracketItemClicked(wxCommandEvent& event)throw (debug_err);
        void OnButtonAddFractionClicked(wxCommandEvent& event)throw (debug_err);
        void Onb1Click(wxCommandEvent& event);
        void Onb2Click(wxCommandEvent& event);
        void Onb3Click(wxCommandEvent& event);
        void Onb4Click(wxCommandEvent& event);
        void Onb5Click(wxCommandEvent& event);
        void Onb6Click(wxCommandEvent& event);
        void Onb7Click(wxCommandEvent& event);
        void Onb8Click(wxCommandEvent& event);
        void Onb9Click(wxCommandEvent& event);
        void Onb0Click(wxCommandEvent& event);
        void OnbpClick(wxCommandEvent& event);
        void OnbmClick(wxCommandEvent& event);
        void OnbmulClick(wxCommandEvent& event);
        void OnbdClick(wxCommandEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnbdotClick(wxCommandEvent& event);
        void OnbceClick(wxCommandEvent& event);
        void OnbcaClick(wxCommandEvent& event);
        void OnPanel1Char(wxKeyEvent& event);
        void OnMenuItem3Selected(wxCommandEvent& event);
        void OnMenuItem4Selected(wxCommandEvent& event);
        void OnMenuItem5Selected(wxCommandEvent& event);
        void OnMenuItem6Selected(wxCommandEvent& event);
        void OnRadioBox1Select2(wxCommandEvent& event);
        void OnRadioButton4Select(wxCommandEvent& event);
        void OnLeftDown(wxMouseEvent& event);
        void OnMenuItem2Selected(wxCommandEvent& event);
        void OnPanel1Paint(wxPaintEvent& event);
        void OnMenuItem10Selected(wxCommandEvent& event);
        //*)

        //(*Identifiers(CalculatorFrame)
        static const long ID_PANEL1;
        static const long ID_BUTTON17;
        static const long ID_BUTTON16;
        static const long ID_BUTTON15;
        static const long ID_BUTTON7;
        static const long ID_BUTTON14;
        static const long ID_BUTTON13;
        static const long ID_BUTTON12;
        static const long ID_BUTTON6;
        static const long ID_BUTTON11;
        static const long ID_BUTTON10;
        static const long ID_BUTTON9;
        static const long ID_BUTTON5;
        static const long ID_BUTTON3;
        static const long ID_BUTTON18;
        static const long ID_BUTTON8;
        static const long ID_BUTTON4;
        static const long ID_BUTTON2;
        static const long ID_BUTTON1;
        static const long ID_BUTTON19;
        static const long ID_BUTTON20;
        static const long ID_STATUSBAR1;
        static const long ID_MENUITEM1;
        static const long ID_MENUITEM4;
        static const long ID_MENUITEM5;
        static const long ID_MENUITEM6;
        static const long ID_MENUITEM7;
        static const long ID_MENUITEM8;
        static const long ID_MENUITEM9;
        static const long ID_MENUITEM10;
        static const long ID_MENUITEM2;
        static const long ID_MENUITEM3;
        //*)

        //(*Declarations(CalculatorFrame)
        wxMenuItem* MenuItem8;
        wxButton* bm;
        wxMenuItem* MenuItem7;
        wxButton* b7;
        wxButton* b3;
        wxMenuItem* MenuItem5;
        wxMenuItem* MenuItem2;
        wxButton* b9;
        wxButton* Button1;
        wxButton* bdot;
        wxButton* b0;
        wxPanel* Panel1;
        wxMenuItem* MenuItem10;
        wxButton* Button2;
        wxButton* bp;
        wxButton* bce;
        wxButton* b1;
        wxMenuItem* MenuItem3;
        wxButton* b5;
        wxButton* Button3;
        wxButton* b8;
        wxStatusBar* StatusBar1;
        wxMenuItem* MenuItem6;
        wxButton* bd;
        wxMenuBar* MenuBar1;
        wxButton* bca;
        wxButton* b2;
        wxMenu* Menu6;
        wxButton* bmul;
        wxMenuItem* MenuItem9;
        wxButton* b6;
        wxButton* b4;
        wxMenu* Menu5;
        wxMenu* Menu4;
        //*)


        DECLARE_EVENT_TABLE()
};

class StringExpression:public PreExpression
{
  public:
  StringExpression(string s)
  {
    str=s;
  }
  string to_string()const{return str;}
  virtual StringExpression* clone() const {return new StringExpression(*this);}
  string str;
};
