#include "VariableSet.h"


void VariableSet::set_var(string name, Value value)
{
  Variable var(name,value);
  vars[name]=var;
}

Value VariableSet::get_var_value(string name) const
{
  return vars[name].get_value();
}

