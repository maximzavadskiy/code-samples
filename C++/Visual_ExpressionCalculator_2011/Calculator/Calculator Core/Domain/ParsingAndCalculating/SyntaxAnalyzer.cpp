
#include "SyntaxAnalyzer.h"
#include "Calculator.h"
#include "ExpressionParser.h"

SyntaxAnalyzer::SyntaxAnalyzer(Calculator & calc):
calculator(calc),
no_compiling_err(true),
no_calculating_err(true)
{}

SyntaxAnalyzer::~SyntaxAnalyzer()
{
  clear_error_records();
  while(!buf_expressions.empty())
  {
    delete  buf_expressions.front();
    buf_expressions.pop();
  }
}

bool SyntaxAnalyzer::set_expression(const PreExpression& source)
{
  clear_error_records();
  try
  {

    Expression* exp=convert_to_Expression(source);//errors here
    buf_expressions.push(exp);

    no_compiling_err=true;
    calculator.set_expression(&source,exp);
  }
  catch(CalculatorError& e)
  {
    no_compiling_err=false;
    compiling_errors.push_back(e.clone());
  }
  return no_compiling_err;
}

vector<const CalculatorError * > SyntaxAnalyzer::get_set_expression_errors() const
{
  return make_const_pointer_vec(compiling_errors);
}

bool SyntaxAnalyzer::calculate_answer()
{
  try
  {
    calculator.calculate_answer();//errors here
    if(buf_expressions.size()==2)
    {
       delete  buf_expressions.front();
       buf_expressions.pop();
    }
    no_calculating_err=true;
  }
  catch(CalculatorError& e)
  {
    no_calculating_err=false;
    calculating_errors.push_back(e.clone());
  }
  return no_calculating_err;
}

vector<const CalculatorError * >  SyntaxAnalyzer::get_calculate_answer_errors() const
{
  return make_const_pointer_vec(calculating_errors);
}

bool SyntaxAnalyzer::has_no_errors()
{
  return no_compiling_err&&no_calculating_err;
}
//-------------------------private functions-------------------------------
Expression* SyntaxAnalyzer::convert_to_Expression(const PreExpression & source) const throw(CalculatorError)
{
  ExpressionParser parser(calculator);
  return parser.parse_Expression(source.to_string());
}


 vector<const CalculatorError*> SyntaxAnalyzer::make_const_pointer_vec(const vector<CalculatorError*>& p_vec) const
{
  vector<const CalculatorError*> const_p_vec;
  for(int i=0;i<p_vec.size();i++) const_p_vec.push_back(p_vec[i]);
  return const_p_vec;
}

void SyntaxAnalyzer::clear_error_records()
{
	for(int i=0;i<compiling_errors.size();i++) {delete compiling_errors[i];compiling_errors[i]=NULL;}
	for(int i=0;i<calculating_errors.size();i++) {delete calculating_errors[i];calculating_errors[i]=NULL;}
  compiling_errors.clear();
  calculating_errors.clear();
}



