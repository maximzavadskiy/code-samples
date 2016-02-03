/***************************************************************
 * Name:      CalculatorApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2009-03-28
 * Copyright:  ()
 * License:
 **************************************************************/

#include "CalculatorApp.h"
//(*AppHeaders
#include "CalculatorMain.h"
//*)
#include <wx/image.h>

IMPLEMENT_APP(CalculatorApp);

//`wx-config --libs`
//`wx-config --cflags`

bool CalculatorApp::OnInit()
{
   bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	CalculatorFrame* Frame = new CalculatorFrame(calculator_controller,0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    return wxsOK;
}
