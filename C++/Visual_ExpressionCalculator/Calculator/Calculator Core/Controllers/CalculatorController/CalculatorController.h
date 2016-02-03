#ifndef _CALCULATORCONROLLER_H
#define _CALCULATORCONROLLER_H

#include "Errors.h"
#include "Answer.h"
#include "Calculator.h"
#include "SyntaxAnalyzer.h"
#include <string>
using namespace std;

class PreExpression;
class Calculator;

namespace Controllers
{

  class CalculatorController
  {
    public:
      CalculatorController();

      bool set_expression(const PreExpression & pe);
      vector<const CalculatorError * > get_set_expression_errors() const;
      bool calculate_answer();
      vector<const CalculatorError * > get_calculate_answer_errors() const;
      Answer get_answer() ;
      bool is_assigment_expression() const;
      void set_answer_format(string & format);
      History get_expressions_history() const;

    private:
      SyntaxAnalyzer  syntax_analyzer;
      Calculator calculator ;
  };

}
#endif
