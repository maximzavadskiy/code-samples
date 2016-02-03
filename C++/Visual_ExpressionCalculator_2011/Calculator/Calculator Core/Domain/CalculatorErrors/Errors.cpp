#include  "Errors.h"

string CalculatorError::get_message()const
{
  return message;
}

CalculatorError::CalculatorError(string  mes):message(mes) {}

CalculatorError* CalculatorError::clone() const
{
  return new CalculatorError(*this);
}

string BracketError::get_message()const
{
  string mes=CalculatorError::get_message();
  if(mes=="") return string("Bracket error");
  else return  string("Bracket error: ")+ CalculatorError::get_message();
}


BracketError::BracketError(string  mes):CalculatorError(mes) {}

BracketError* BracketError::clone() const
{
  return new BracketError(*this);
}


string SyntaxError::get_message()const
{
  string mes=CalculatorError::get_message();
  if(mes=="") return string("Syntax error");
  else return  string("Syntax error: ")+ CalculatorError::get_message();
}

SyntaxError::SyntaxError(string  mes):CalculatorError(mes) {}

SyntaxError* SyntaxError::clone() const
{
  return new SyntaxError(*this);
}

string ZeroDivide::get_message()const
{
  string mes=CalculatorError::get_message();
  if(mes=="") return string("Zero divide");
  else return  string("Zero divide: ")+ CalculatorError::get_message();
}

ZeroDivide::ZeroDivide(string  mes):CalculatorError(mes){}

ZeroDivide* ZeroDivide::clone() const
{
  return new ZeroDivide(*this);
}
