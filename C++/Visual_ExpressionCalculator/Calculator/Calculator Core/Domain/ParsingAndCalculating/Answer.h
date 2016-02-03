#ifndef _ANSWER_H
#define _ANSWER_H

#include "Value.h"
#include <string>
using namespace std;


class Answer {
  private:
    Value value;
    string format;
  public:
    Answer(Value val=0,string f="mixnum");

    void set_value(Value  val);
    void set_format(string  f);

    Value get_value() const;
    string get_format() const;
};

ostream& operator<<(ostream& os,const Answer& ans);

#endif
