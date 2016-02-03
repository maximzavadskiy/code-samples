#include "ComplexExpression.h"
#include "AssigmentOperator.h"

ComplexExpression::ComplexExpression(Expression* left_op, ExpressionBinaryOperator* bin_op, Expression* right_op)
:  left_operand(left_op),right_operand(right_op),binary_operator(bin_op) {}

ComplexExpression::~ComplexExpression()
{
  if(left_operand!=0) delete  left_operand;
  if(right_operand!=0) delete  right_operand;
  if(binary_operator!=0) delete  binary_operator;
}

ComplexExpression* ComplexExpression::clone() const
{
  ComplexExpression* new_exp=new ComplexExpression(*this);
  new_exp->binary_operator=binary_operator->clone();
  new_exp->right_operand=right_operand->clone();
  new_exp->left_operand=left_operand->clone();
 // new_exp->answer=left_operand->answer;
  return new_exp;
}

Value ComplexExpression::calculate_value() const throw(ZeroDivide)
{
  return binary_operator->calculate(*left_operand,*right_operand);
}

bool ComplexExpression::has_assigment_operator() const
{
	return dynamic_cast<AssigmentOperator*>(binary_operator);
}
