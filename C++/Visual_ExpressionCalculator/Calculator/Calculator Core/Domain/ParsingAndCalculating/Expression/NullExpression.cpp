#include "NullExpression.h"

NullExpression::NullExpression(){}

Expression* NullExpression::clone() const
{
  return new NullExpression();
}

Value NullExpression::calculate_value() const throw (ZeroDivide)
{
  return 0;
}

