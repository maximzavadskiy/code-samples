#ifndef _SYNTAXANALYZER_H
#define _SYNTAXANALYZER_H
#include <vector>
#include "Errors.h"
#include <queue>
using namespace std;

class PreExpression;
class Expression;
class Calculator;

class SyntaxAnalyzer
{
  public:
    SyntaxAnalyzer(Calculator & calculator);
    ~SyntaxAnalyzer();

    bool set_expression(const PreExpression & pe);
    vector<const CalculatorError * >  get_set_expression_errors() const;

    bool calculate_answer();
    vector<const CalculatorError * >  get_calculate_answer_errors() const;

    bool has_no_errors();
  private:
    Calculator& calculator;
    bool no_compiling_err;
    bool no_calculating_err;
    vector<CalculatorError *>  compiling_errors;
    vector<CalculatorError *>  calculating_errors;
    queue<Expression* > buf_expressions;

    Expression* convert_to_Expression(const PreExpression & source) const throw(CalculatorError);
   // set_curr_exp(const Expression & exp);
    vector<const CalculatorError * > make_const_pointer_vec(const vector<CalculatorError*>& ) const;
    void clear_error_records();
};
#endif
