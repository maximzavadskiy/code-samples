
#include "ExpressionNumber.h"

ExpressionNumber::ExpressionNumber(Value  v):value(v){}

ExpressionNumber* ExpressionNumber::clone() const
{
  return new ExpressionNumber(*this);
}

Value ExpressionNumber::calculate_value() const throw(ZeroDivide)
{
  return value;
}

