
#include "Expression.h"
Expression::Expression():has_answer(false){}
 const Answer&  Expression::get_answer()   const   /*throw(ZeroDivide)*/
{
  if(!has_answer)  calculate_answer();
  return ans;
}

void Expression::set_answer_format(string format)
{
  ans.set_format(format);
}

void  Expression::calculate_answer() const/*throw(ZeroDivide)*/
{
  ans=calculate_value();
  has_answer=true;
}

bool Expression::has_assigment_operator() const
{
	return false;
}
