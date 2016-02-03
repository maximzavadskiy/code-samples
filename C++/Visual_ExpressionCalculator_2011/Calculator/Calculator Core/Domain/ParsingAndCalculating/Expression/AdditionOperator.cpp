
#include "AdditionOperator.h"
#include "Expression.h"

Value AdditionOperator::calculate( Expression & left_op, Expression & right_op)
{
  Value left_val= left_op.get_answer().get_value();
  Value right_val= right_op.get_answer().get_value();
  return left_val+right_val;
}

AdditionOperator* AdditionOperator::clone() const
{
  return new AdditionOperator(*this);
}


