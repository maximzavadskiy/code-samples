#include "Variable.h"

Variable::Variable( string n,Value val):name(n),value(val) {}

Value Variable::get_value() const
{
  return value;
}

string Variable::get_name() const
{
  return name;
}

