#include "CalculatorController.h"
#include <iostream>
#include <string>
#include "PreExpression.h"
#include<stdexcept>
using namespace std;
class A:public PreExpression
{
  public:
  A(string s)
  {
    str=s;
  }
  string to_string()const{return str;}
  virtual A* clone() const {return new A(*this);}
  string str;
};

void print_errors(const vector<const CalculatorError * >& v)
{
  for(int i=0;i<v.size();i++) cout<<v[i]->get_message()<<endl;
}

void print_history(const History& h2)
{
  History h=h2;
  int i=1;
  while(!h.empty())
  {
    cout<<i<<": source="<<dynamic_cast<const A&>(h.top().source()).to_string()<<"  answer="<<h.top().answer()<<endl ;
    h.pop();
    i++;
  }
}
using namespace Controllers;
int main()
{

  CalculatorController calculator_controller;
	cout<<"Consructor&destr TEST(new)....."<<endl<<endl;
  CalculatorController* c=new CalculatorController;
  delete c;
  cout<<"OK"<<endl<<"-------------------------------------------------------------------------"<<endl;

  cout<<"other functions TEST....."<<endl<<endl;
  string exp;
	while(true)
	{
	  try
	  {
      string ans;
      cout<<"What function call?(q- quite)"<<endl<<
      "1-bool set_expression(const PreExpression & pe);"<<endl<<
      "2-vector<const CalculatorError * > get_set_expression_errors() const;"<<endl<<
      "3-bool calculate_answer();"<<endl<<
      "4-vector<const CalculatorError * > get_calculate_answer_errors() const;"<<endl<<
      "5-void set_answer_format(string & format);"<<endl<<
      "6-History get_expressions_history() const;"<<endl<<
      "7-Answer get_answer() ;"<<endl<<"number:"<<endl<<
      "8-bool is_assigment_expression() const"<<endl;
      cin>>ans;
      if(ans=="q") break;
      if(ans=="1")
      {
        cout<<"Exter pe(string):"; cin>>exp;
        cout<<"calling bool set_expression(const PreExpression & pe)...";
        bool ans=calculator_controller.set_expression(A(exp));
        cout<<"DONE result is ";
        cout<<ans<<endl<<endl;
      }
      if(ans=="2")
      {
        cout<<"calling vector<const CalculatorError * > get_set_expression_errors() const...";
         calculator_controller.get_set_expression_errors();
        cout<<"DONE result is ";
        print_errors(calculator_controller.get_set_expression_errors());
        cout<<endl<<endl;
      }
      if(ans=="3")
      {
        cout<<"calling bool calculate_answer()...";
        bool ans=calculator_controller.calculate_answer();;
        cout<<"DONE result is ";
        cout<<ans<<endl<<endl;
      }
      if(ans=="4")
      {
        cout<<"calling vector<const CalculatorError * > get_calculate_answer_errors() const...";
        calculator_controller.get_calculate_answer_errors();
        cout<<"DONE result is ";
        print_errors(calculator_controller.get_calculate_answer_errors());
        cout<<endl<<endl;
      }
      if(ans=="5")
      {
        cout<<"Exter format(string):"; cin>>exp;
        cout<<"calling void set_answer_format(string & format)...";
        calculator_controller.set_answer_format(exp);
        cout<<"DONE ";
        cout<<endl<<endl;
      }
      if(ans=="6")
      {
        cout<<"calling History get_expressions_history() const...";
        History ans=calculator_controller.get_expressions_history();
        cout<<"DONE result is ";
        print_history(ans);
        cout<<endl<<endl;
      }
      if(ans=="7")
      {
        cout<<"calling Answer get_answer() ...";
        Answer ans=calculator_controller.get_answer() ;
        cout<<"DONE result is ";
        cout<<ans<<endl<<endl;
      }
      if(ans=="8")
      {
        cout<<"calling bool is_assigment_expression() const...";
        bool ans=calculator_controller.is_assigment_expression();
        cout<<"DONE result is ";
        cout<<ans;
        cout<<endl<<endl;
      }

	  }
	  catch(std::exception& e)
	  {
	    cout<<"Error catch!!! "<<e.what()<<endl<<endl;
	  }
	}
	return 0;
}

