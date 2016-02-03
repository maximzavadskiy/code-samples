/***************************************************************
 * Name:      CalculatorApp.h
 * Purpose:   Defines Application Class
 * Author:     ()
 * Created:   2009-03-28
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef CALCULATORAPP_H
#define CALCULATORAPP_H

#include <wx/app.h>
#include "CalculatorController.h"
using namespace Controllers;
#include <wx/msgdlg.h>
class CalculatorApp : public wxApp
{
    CalculatorController calculator_controller;
    public:
        virtual bool OnInit();
};


#endif // CALCULATORAPP_H
