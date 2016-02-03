//#include "ExpressionParser.h"
//#include <string>
//#include <iostream>
//#include "Calculator.h"
//#include "Expressions.h"
//using namespace std;
//
//int main()
//{
//  Calculator calc;
//  ExpressionParser parser(calc);
//
//  while(true)
//  {
//    try
//    {
//      cout<<"Enter expression or ""q"" to quite: ";
//      string pre_exp;
//      getline (cin,pre_exp);
//      if(pre_exp=="q") break;
//      Expression* exp=parser.parse_Expression(pre_exp);
//      //exp->get_answer();
//      cout<<"answer="<<exp->get_answer()<<endl;
//      delete exp;
//    }
//    catch(ZeroDivide z) {cout<<z.get_message()<<endl;}
//    catch(SyntaxError s){cout<<s.get_message()<<endl;}
//    catch(BracketError b){cout<<b.get_message()<<endl;}
//  }
//
//  return 0;
//}
