#include "ExpressionParser.h"
#include "Expressions.h"
#include "Calculator.h"

ExpressionParser::ExpressionParser(Calculator& calc):
calculator(calc)
//third_priority_operators_finder(ThirdPriorityOperatorsFinder()),
//second_priority_operators_finder(SecondPriorityOperatorsFinder()),
//simple_operands_finder(OperandsFinder(calc))
{
}

ExpressionParser::~ExpressionParser()
{

}

Expression* ExpressionParser::parse_Expression(string pre_exp)
{
  //if(curr_exp!=NULL) {delete curr_exp; curr_exp=NULL;}
  try
  {
    if(pre_exp=="") return new NullExpression;
    else
    {
      ans answer=parse_third_priority(pre_exp);
      if(answer.rest!="") throw SyntaxError();
      return answer.exp;
    }
  }
  catch(zero_divide)
  {
    throw ZeroDivide();
  }
}
ExpressionParser::ans ExpressionParser::parse_third_priority(string pre_exp)
{
  static int _n=1;
  int n=_n;  _n++;
  #ifdef DEBUG
    cout<<"BEGIN <"<<n<<"> parse_third_priority###############################################3333"<<endl;
  #endif
  ThirdPriorityOperatorsFinder third_priority_operators_finder;
  string rest=pre_exp;
  Expression* left;
  Expression* curr_exp;
  ans res=parse_second_priority(rest);
  rest=res.rest;
  curr_exp=left=res.exp;
  #ifdef DEBUG
    cout<<"parse_second_priority(rest) (38) rest="<<rest<<" val="<<curr_exp->get_answer().get_value()<<endl;
  #endif
  while(third_priority_operators_finder.match(rest))
  {
     rest=third_priority_operators_finder.get_rest();
     ans res=parse_second_priority(rest);
     rest=res.rest;

     ComplexExpression* comp_exp = new ComplexExpression(left,third_priority_operators_finder.get_matched_operator().clone(),res.exp);
    #ifdef DEBUG
    cout<<"cmp_exp rest="<<rest<<" l_val="<<curr_exp->get_answer().get_value()<<" r_val="<<res.exp->get_answer().get_value()<<endl;
    if(dynamic_cast<SubtractionOperator* >(third_priority_operators_finder.get_matched_operator().clone())) cout<<"Subtract!!!!"<<endl;
  #endif
 /*    comp_exp->set_left_operand(*left);
     comp_exp->set_operator(third_priority_operators_finder.get_matched_operator());
     comp_exp->set_right_operand(*ans.exp);
 */
     left=curr_exp=comp_exp;
  #ifdef DEBUG
    cout<<"end while  rest="<<rest<<" val="<<curr_exp->get_answer().get_value()<<endl;
  #endif
  }
  #ifdef DEBUG
    cout<<" after while rest="<<rest<<" value="<<curr_exp->get_answer().get_value()<<endl;
  #endif
    #ifdef DEBUG
    cout<<"END <"<<n<<"> parse_third_priority###################################33333333"<<endl;
  #endif

  return  ans(rest,curr_exp);
}

ExpressionParser::ans ExpressionParser::parse_second_priority(string pre_exp)
{//делать в цикле
   static int _n=1;
  int n=_n;
  _n++;
    #ifdef DEBUG
    cout<<"BEGIN <"<<n<<"> parse_second_priority------------------------"<<endl;
  #endif
  SecondPriorityOperatorsFinder second_priority_operators_finder;
  string rest=pre_exp;
  Expression* left;
  Expression* curr_exp;
  ans res=parse_first_priority(rest);
  rest=res.rest;
  curr_exp=left=res.exp;
  #ifdef DEBUG
    cout<<"parse_first_priority(rest) (84) rest="<<rest<<" val="<<curr_exp->get_answer().get_value()<<endl;
  #endif
  while(second_priority_operators_finder.match(rest))
  {
     rest=second_priority_operators_finder.get_rest();
     ans res=parse_first_priority(rest);
     rest=res.rest;

     ComplexExpression* comp_exp = new ComplexExpression(left,second_priority_operators_finder.get_matched_operator().clone(),res.exp);
  #ifdef DEBUG
    cout<<"parse_second_priority(rest) (38) rest="<<rest<<" val="<<curr_exp->get_answer().get_value()<<endl;
  #endif
//      comp_exp->set_left_operand(*left);
//      comp_exp->set_operator(third_priority_operators_finder.get_matched_operator());
//      comp_exp->set_right_operand(*ans.exp);

     left=curr_exp=comp_exp;
      #ifdef DEBUG
    cout<<"end while  rest="<<rest<<" val="<<curr_exp->get_answer().get_value()<<endl;
  #endif
  }
  #ifdef DEBUG
    cout<<"rest="<<rest<<" value="<<curr_exp->get_answer().get_value()<<endl;
  #endif
  #ifdef DEBUG
    cout<<"END <"<<n<<"> parse_second_priority------------------------"<<endl;
  #endif

  return  ans(rest,curr_exp);
}

ExpressionParser::ans ExpressionParser::parse_first_priority(string pre_exp)
{
    static int _n=1;
  int n=_n;_n++;
    #ifdef DEBUG
    cout<<"BEGIN <"<<n<<"> parse_first_priority------------------"<<endl;
  #endif
  string rest=pre_exp;
  Expression* left;
  Expression* curr_exp;
  ans res=parse_brackets(rest);
  rest=res.rest;
  curr_exp=left=res.exp;

  if(rest[0]=='=')
  {
    if(dynamic_cast<ExpressionVariable*>(left))
    {
      rest=rest.substr(1);
       ans res=parse_third_priority(rest);
      ComplexExpression* comp_exp = new ComplexExpression(left,new AssigmentOperator(calculator),res.exp);
      curr_exp=comp_exp;
      rest=res.rest;
    }
    else
    {
      throw SyntaxError();
    }
  }
  #ifdef DEBUG
    cout<<"in rest="<<rest<<" value="<<curr_exp->get_answer().get_value()<<endl;
  #endif
  #ifdef DEBUG
    cout<<"END <"<<n<<"> parse_first_priority-------------------"<<endl;
  #endif
  return  ans(rest,curr_exp);
}

ExpressionParser::ans  ExpressionParser::parse_brackets(string pre_exp)
{
    static int _n=1;
  int n=_n;_n++;
      #ifdef DEBUG
    cout<<"BEGIN <"<<n<<"> parse_parse_brackets--------"<<endl;
  #endif
  string rest=pre_exp;
  Expression* curr_exp;
  if(pre_exp[0]=='(')
  {
     rest=rest.substr(1);
     ans res=parse_third_priority(rest);
     rest=res.rest;
     if(rest[0]==')')
     {
       curr_exp=res.exp;
       rest=rest.substr(1);
     }
     else throw BracketError();
  }
  else
  {
    ans res=parse_simple_operands(rest);
    rest=res.rest;
    curr_exp=res.exp;
  }
      #ifdef DEBUG
    cout<<"in rest="<<rest<<" value="<<curr_exp->get_answer().get_value()<<endl;
  #endif
        #ifdef DEBUG
    cout<<"END <"<<n<<"> parse_parse_brackets---------"<<endl;
  #endif
  return ans(rest,curr_exp);
}

ExpressionParser::ans ExpressionParser::parse_simple_operands(string pre_exp)
{
   static int _n=1;
  int n=_n;_n++;
   #ifdef DEBUG
    cout<<"BEGIN <"<<n<<"> parse_simple_operands"<<endl;
  #endif
  OperandsFinder simple_operands_finder(calculator);
   if(simple_operands_finder.match(pre_exp))
   {
    #ifdef DEBUG
     cout<<":rest="<<simple_operands_finder.get_rest()<<" value="<<simple_operands_finder.get_matched_operand().get_answer().get_value()<<endl;
    #endif
       #ifdef DEBUG
    cout<<"END <"<<n<<"> parse_simple_operands"<<endl;
  #endif
      return ans(simple_operands_finder.get_rest(),simple_operands_finder.get_matched_operand().clone());
   }
   else throw SyntaxError("Operand expected");

}
