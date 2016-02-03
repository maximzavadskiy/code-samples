//#include "SyntaxAnalyzer.h"
//#include <iostream>
//#include <string>
//#include "PreExpression.h"
//#include "Calculator.h"
//using namespace std;
//class A:public PreExpression
//{
//  public:
//  A(string s)
//  {
//    str=s;
//  }
//  string to_string()const{return str;}
//  virtual A* clone() const {return new A(*this);}
//  string str;
//};
//
//void print_errors(const vector<const CalculatorError * >& v)
//{
//  for(int i=0;i<v.size();i++) cout<<v[i]->get_message()<<endl;
//}
//
//
//int main()
//{
//  Calculator calculator;
//	SyntaxAnalyzer syntax_analyzer(calculator);
//	string exp;
//
//	cout<<"Consructor&destr TEST(new)....."<<endl<<endl;
//  SyntaxAnalyzer* c=new SyntaxAnalyzer(calculator);
//  delete c;
//  cout<<"OK"<<endl<<"-------------------------------------------------------------------------"<<endl;
//  cout<<"set_expression&get_set_expression_errors/calculate_answer&get_calculate_answer_errors  TEST(new)....."<<endl<<endl;
//	while(true)
//	{
//    cout<<"Enter expression or ""q"" to quite: ";
//    getline (cin,exp);
//    if(exp=="q") break;
//    A a(exp);
//    cout<<"syntax_analyzer.set_expression(a);...";
//    bool ok=syntax_analyzer.set_expression(a);
//    cout<<"DONE:";
//    if(ok==true) cout<<"no errors"<<endl;
//    else
//    {
//      cout<<"there's errors!"<<endl;print_errors(syntax_analyzer.get_set_expression_errors());
//      continue;
//    }
//
//    cout<<"syntax_analyzer.calculate_answer();...";
//    ok=syntax_analyzer.calculate_answer();
//    cout<<"DONE:";
//    if(ok==true)
//    {
//      cout<<"no errors, answer is";
//      cout<<calculator.get_answer()<<endl;
//    }
//    else
//    {
//      cout<<"there's errors!"<<endl;print_errors(syntax_analyzer.get_calculate_answer_errors());
//    }
//	}
//	return 0;
//}
//
