#ifndef _ERRORS_H
#define _ERRORS_H


#include <string>
using namespace std;

class CalculatorError
{
  public:
    CalculatorError(string  mes="");
    virtual string get_message() const;
    virtual CalculatorError* clone() const;
  protected:
    string message;
};

class BracketError : public CalculatorError
{
  public:
    string get_message() const;
    virtual BracketError* clone() const;
    BracketError(string  mes="");
};

class SyntaxError : public CalculatorError
{
  public:
    string get_message()const;
    virtual SyntaxError* clone() const;
    SyntaxError(string  mes="");
};

class ZeroDivide : public CalculatorError
{
  public:
    string get_message()const;
    virtual ZeroDivide* clone() const;
    ZeroDivide(string  mes="");
};
#endif
