
#include "MultiplicationOperator.h"
#include "Expression.h"

 //MultiplicationOperator::MultiplicationOperator() {}

Value MultiplicationOperator::calculate(Expression& left_op, Expression& right_op)
{
  Value left_val= left_op.get_answer().get_value();
  Value right_val= right_op.get_answer().get_value();
  return left_val*right_val;
}

MultiplicationOperator* MultiplicationOperator::clone() const
{
  return new MultiplicationOperator(*this);
}

