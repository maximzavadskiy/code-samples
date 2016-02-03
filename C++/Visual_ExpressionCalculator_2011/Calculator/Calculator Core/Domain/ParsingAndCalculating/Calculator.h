#ifndef _CALCULATOR_H
#define _CALCULATOR_H


#include "Answer.h"
#include "ExpressionHistory.h"
#include "VariableSet.h"
#include <string>
using namespace std;
#include "Value.h"

class PreExpression;
class Expression;
class VariableSet;

class Calculator
{
  public:
    Calculator();
    ~Calculator();
    void set_expression(const PreExpression* s, Expression* exp);
    void calculate_answer() throw(ZeroDivide) ;
    Answer get_answer()  throw(ZeroDivide) ;
    bool is_assigment_expression() const;
    void set_answer_format(string  format);

    void set_var(string  name, Value  value);
    Value get_var_value(string  name) const;//must generate an error

    History get_expressions_history() const;
  private:
    ExpressionHistory expression_history;
    VariableSet variable_set;

    const PreExpression* source;
    Expression* expression;
    bool has_answer;

    void free_memory();
};
#endif
