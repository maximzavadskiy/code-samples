
#include "DivisionOperator.h"
#include "Expression.h"

 DivisionOperator::DivisionOperator() {}

Value DivisionOperator::calculate(Expression&  left_op, Expression & right_op) throw(ZeroDivide)
{
  try
  {
    Value left_val= left_op.get_answer().get_value();
    Value right_val= right_op.get_answer().get_value();
    return left_val/right_val;
  }
  catch(zero_divide)
  {throw ZeroDivide();}
}

DivisionOperator* DivisionOperator::clone() const
{
  return new DivisionOperator(*this);
}

