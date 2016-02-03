#include "ExpressionVariable.h"
#include "Calculator.h"

ExpressionVariable::ExpressionVariable(string _name, const Calculator& calc): calculator(calc),name(_name){}

string ExpressionVariable::get_name() const
{
  return name;
}

Value ExpressionVariable::calculate_value() const
{
  return calculator.get_var_value(name);
}

ExpressionVariable* ExpressionVariable::clone() const
{
  return new ExpressionVariable(*this);
}
