
#include "Calculator.h"
#include "PreExpression.h"
#include "Expression.h"

Calculator::Calculator():source(NULL),expression(NULL),has_answer(false)  {}

Calculator::~Calculator()
{
 //free_memory();
}

void Calculator::set_expression(const PreExpression* s, Expression* exp)
{
  //free_memory();

  source=s;
  expression=exp;
  has_answer=false;
}

void Calculator::calculate_answer() throw(ZeroDivide)
{
  if(expression==NULL) throw system_error("in void Calculator::calculate_answer(): call set_expression(const PreExpression& s, Expression& exp) before calling this metod");
  if(has_answer==true) return;
  expression->calculate_answer();
  expression_history.add(*source,*expression);
  has_answer=true;
}

Answer Calculator::get_answer() throw(ZeroDivide)
{
  if(!has_answer) calculate_answer();
  return expression->get_answer();
}

bool Calculator::is_assigment_expression() const
{
	return expression->has_assigment_operator();
}

void Calculator::set_answer_format(string format)
{
  expression->set_answer_format(format);
}

History Calculator::get_expressions_history() const
{
  return expression_history.get_history();
}

void Calculator::set_var(string  name, Value  value)
{
  variable_set.set_var(name,value);
}

Value Calculator::get_var_value(string name) const
{
  return variable_set.get_var_value(name);
}

void Calculator::free_memory()
{
  delete expression;
  delete source;
}
