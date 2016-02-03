
#include "AssigmentOperator.h"
#include "Expression.h"
#include "Calculator.h"
#include "ExpressionVariable.h"
#include <typeinfo>

AssigmentOperator::AssigmentOperator( Calculator & calc):calculator(calc) {}

Value AssigmentOperator::calculate(Expression & a, Expression & b)
{
  try
  {
    const ExpressionVariable& var=dynamic_cast<const ExpressionVariable& > (a);
    b.calculate_answer();
    Value val=b.get_answer().get_value();
    calculator.set_var(var.get_name(),val);
    return val;
  }
  catch(std::bad_cast){ throw system_error("in Value AssigmentOperator::calculate : left operand is not ExpressionVariable"); }
}

AssigmentOperator* AssigmentOperator::clone() const
{
  return new AssigmentOperator(*this);
}


