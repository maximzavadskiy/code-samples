
#include "CalculatorController.h"
#include "PreExpression.h"

#include "SyntaxAnalyzer.h"
namespace Controllers
{

  CalculatorController::CalculatorController():
    calculator(),
    syntax_analyzer(calculator)
  {}

  bool CalculatorController::set_expression(const PreExpression & pe)
  {
    return syntax_analyzer.set_expression(pe);
  }

  vector<const CalculatorError * > CalculatorController::get_set_expression_errors() const
  {
    return syntax_analyzer.get_set_expression_errors();
  }

  bool CalculatorController::calculate_answer()
  {
    return syntax_analyzer.calculate_answer();
  }

  vector<const CalculatorError * > CalculatorController::get_calculate_answer_errors() const
  {
    return syntax_analyzer.get_calculate_answer_errors();
  }

  Answer CalculatorController::get_answer()
  {
    if(syntax_analyzer.has_no_errors()) return calculator.get_answer();
    else throw system_error("in Answer CalculatorController::get_answer() : Expression has errors");
  }

  bool CalculatorController::is_assigment_expression() const
  {
    return calculator.is_assigment_expression();
  }

  void CalculatorController::set_answer_format(string & format)
  {
    return calculator.set_answer_format(format);
  }

  History CalculatorController::get_expressions_history() const
  {
    return calculator.get_expressions_history();
  }

} // namespace Controllers
