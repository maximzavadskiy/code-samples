
#include "SubtractionOperator.h"
#include "Expression.h"

 SubtractionOperator::SubtractionOperator() {}

Value SubtractionOperator::calculate( Expression & left_op,  Expression & right_op)
{
  Value left_val=   left_op.get_answer().get_value();
  Value right_val= right_op.get_answer().get_value();
  return left_val-right_val;
}

 SubtractionOperator* SubtractionOperator::clone() const
 {
   return new SubtractionOperator(*this);
 }
