#ifndef _EXPRESSIONPARSER_H
#define _EXPRESSIONPARSER_H

//#define DEBUG
#include "Errors.h"
#include <string>
#include "ItemsFinder.h"
using namespace std;

class Expression;
class Calculator;

class ExpressionParser
{
  public:
    ExpressionParser(Calculator& calc);
    ~ExpressionParser();
    Expression* parse_Expression(string pre_exp);

  private:
    struct ans
    {
      string rest;
      Expression* exp;

      ans(string r,Expression* e):rest(r),exp(e){}
    };

    ans parse_third_priority(string);
    ans parse_second_priority(string);
    ans parse_first_priority(string);
    ans parse_brackets(string);
    ans parse_simple_operands(string);


    Calculator& calculator;
   // ThirdPriorityOperatorsFinder third_priority_operators_finder;
   // SecondPriorityOperatorsFinder second_priority_operators_finder;
   // OperandsFinder simple_operands_finder;
};

#endif
