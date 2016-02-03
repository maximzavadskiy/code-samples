#include <typeinfo>
#include <sstream>
#include "ItemsFinder.h"
#include "ExpressionOperator.h"
#include "ExpressionItem.h"
#include "Expressions.h"
#include "Calculator.h"

#ifdef DEBUG
  #include <iostream>
#endif
//-----------------------------ItemsFinder----------------------------
bool ItemsFinder::match(string exp)
{
  bool is_match=false;
  my_regex reg/*("",0,0,0,0)*/;
  for(int i=0;i<item_patterns.size();i++)
  {
     reg.set_pattern(item_patterns[i].first);
     if(reg.match(exp))
     {
       is_match=true;
       rest=exp.substr(reg.begin(0)+reg.get_match(0).length());
       set_item(item_patterns[i].second,reg);
       break;
     }
  }
  return is_match;
}

string ItemsFinder::get_rest()
{
  return rest;
}

//-----------------------------OperatorsFinder----------------------------
OperatorsFinder::OperatorsFinder():matched_operator(NULL){}

ExpressionBinaryOperator& OperatorsFinder::get_matched_operator()
{
  return *matched_operator;
}

OperatorsFinder::~OperatorsFinder()
{
  delete matched_operator;
}
//-----------------------------OperandsFinder----------------------------
OperandsFinder::OperandsFinder(Calculator& calc):calculator(calc),matched_operand(NULL)
{
  item_patterns.push_back(make_pair("^[a-zA-Z]+","name"));

  item_patterns.push_back(make_pair("^([+-]?[0-9]+) ?\\(([0-9]+)\\)[\\/#]\\(([0-9]+)\\)","mixnum"));
  item_patterns.push_back(make_pair("^([+-]?[0-9]+) ([0-9]+)[\\/#]([0-9]+)","mixnum"));

  item_patterns.push_back(make_pair("^\\(([0-9]+)\\)[\\/#]\\(([0-9]+)\\)","fraction"));
  item_patterns.push_back(make_pair("^([+-])\\(([0-9]+)\\)[\\/#]\\(([0-9]+)\\)","unary_m/p_br_fraction"));
  item_patterns.push_back(make_pair("^([+-]?[0-9]+)[\\/#]([0-9]+)","fraction"));

  item_patterns.push_back(make_pair("^([+-]?[0-9]+)\\.([0-9]+)","float"));

  item_patterns.push_back(make_pair("^([+-]?[0-9]+)","integer"));
}

OperandsFinder::~OperandsFinder()
{
  if(matched_operand!=NULL) delete matched_operand;
}

void OperandsFinder::set_item(const string name,const my_regex& reg)
//проверку на количество submatch(get_match)
{
  if(matched_operand!=NULL)
  {
    delete matched_operand;
    matched_operand=NULL;
  }

  #ifdef DEBUG
  	cout<<"in OperandsFinder::set_item: name="<<name<<endl;
  #endif
  if(name=="name")
  {
    matched_operand=new ExpressionVariable(reg.get_match(),calculator);
  }
  if(name=="mixnum")
  {
    matched_operand=new ExpressionNumber(my_mixnum(atoi(reg.get_match(1).c_str() ), atoi( reg.get_match(2).c_str() ), atoi( reg.get_match(3).c_str() )));
  }
  if(name=="fraction")
  {
    matched_operand=new ExpressionNumber(my_fraction(atoi( reg.get_match(1).c_str() ), atoi( reg.get_match(2).c_str() )  ));
  }
  if(name=="unary_m/p_br_fraction")
  {
    my_fraction fract= my_fraction(atoi( reg.get_match(2).c_str() ), atoi( reg.get_match(3).c_str() )  );
    if(reg.get_match(1)=="-") fract=-fract;
    matched_operand=new ExpressionNumber(fract);
  }
  if(name=="float")
  {
//    double num=atoi(reg.get_match(1).c_str());
//    double fract=atoi(reg.get_match(2).c_str())/(pow(10.0,reg.get_match(2).length()));
//    if(num<0) fract=-fract;
//    double d=num+fract;
    istringstream iss(reg.get_match());
    double d;
    iss>>d;
    #ifdef DEBUG
      cout<<"in OperandsFinder::set_item: val="<<d<<endl;
    #endif
    matched_operand=new ExpressionNumber(d);
  }
  if(name=="integer")
  {
    matched_operand=new ExpressionNumber(atoi(reg.get_match(1).c_str()));
  }
}

ExpressionItem& OperandsFinder::get_matched_operand()
{
	return *matched_operand;
}
//-----------------------------ThirdPriorityOperatorsFinder----------------------------

ThirdPriorityOperatorsFinder::ThirdPriorityOperatorsFinder()
{
   item_patterns.push_back(make_pair("^\\+","plus"));
   item_patterns.push_back(make_pair("^-","minus"));
}

void ThirdPriorityOperatorsFinder::set_item(const string name,const my_regex& reg)
{
    #ifdef DEBUG
      cout<<"in ThirdPriorityOperatorsFinder::set_item: name="<<name<<endl;
    #endif
  if(matched_operator!=NULL)
  {
    delete matched_operator;
    matched_operator=NULL;
  }

  if(name=="plus")
  {
    matched_operator=new AdditionOperator();
  }
  if(name=="minus")
  {
    matched_operator=new SubtractionOperator();
  }
}
//-----------------------------SecondPriorityOperatorsFinder----------------------------
SecondPriorityOperatorsFinder::SecondPriorityOperatorsFinder()
{
  //item_patterns.push_back(make_pair("^#","over"));
  item_patterns.push_back(make_pair("^\\*","multiply"));
  item_patterns.push_back(make_pair("^\\/","divide"));
  item_patterns.push_back(make_pair("^\\#","divide"));
}

void SecondPriorityOperatorsFinder::set_item(const string name,const my_regex& reg)
{
      #ifdef DEBUG
      cout<<"in SecondPriorityOperatorsFinder::set_item: name="<<name<<endl;
    #endif
  if(name=="multiply")
  {
    matched_operator=new MultiplicationOperator();
  }
  if(name=="divide")
  {
    matched_operator=new DivisionOperator();
  }
}
