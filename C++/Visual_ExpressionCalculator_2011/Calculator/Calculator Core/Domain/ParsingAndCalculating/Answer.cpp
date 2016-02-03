#include "Answer.h"

Answer::Answer(Value v,string f):value(v),format(f){}

void Answer::set_value(Value  val)
{
  value=val;
}

void Answer::set_format(string  f)
{
  format=f;
}

Value Answer::get_value() const
{
  return value;
}

string Answer::get_format() const
{
  return format;
}


ostream& operator<<(ostream& os,const Answer& ans)
{
  os<<" value="<<ans.get_value()<<" format="<<ans.get_format();
  return os;
}


