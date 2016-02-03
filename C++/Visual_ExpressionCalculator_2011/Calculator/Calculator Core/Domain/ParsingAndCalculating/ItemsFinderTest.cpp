//#include "ItemsFinder.h"
//#include <iostream>
//#include <string>
//#include "Calculator.h"
//#include "Expressions.h"
//using namespace std;
//
//int main()
//{
//  Calculator calc;
//
//  OperandsFinder itf(calc);
//  ThirdPriorityOperatorsFinder tpof;
//  SecondPriorityOperatorsFinder spof;
//
//  string s="1";
//  while(true)
//  {
//    cout<<"Enter string to match in OperandsFinder or ""q"" to exit:";
//    getline (cin,s);
//
//    if(s=="q") break;
//    if(itf.match(s))
//    {
//      cout<<"Match: ";
//      ExpressionItem* item=itf.get_matched_operand().clone();
//      if(ExpressionNumber* num=dynamic_cast<ExpressionNumber*>(item))
//      {
//        cout<<"ExpressionNumber: answer=("<<num->get_answer()<<")"<<endl;
//        delete num;
//      }
//      else if(ExpressionVariable* var=dynamic_cast<ExpressionVariable*>(item))
//      {
//      	cout<<"ExpressionVariable: answer=("<<var->get_answer()<<"), name="<<var->get_name()<<endl;
//        delete var;
//      }
//      else cout<<"Nor ExpressionNumber nor ExpressionVariable--Strange!"<<endl;
//      cout<<"rest="<<itf.get_rest()<<endl;
//    }
//    else cout<<"Not matched"<<endl;
//  }
//
//  while(true)
//  {
//    cout<<"Enter string to match in ThirdPriorityOperatorsFinder or ""q"" to exit:";
//    getline (cin,s);
//    if(s=="q") break;
//    if(tpof.match(s))
//    {
//      cout<<"Match: ";
//      ExpressionOperator* operat=tpof.get_matched_operator().clone();
//      if(AdditionOperator* plus=dynamic_cast<AdditionOperator*>(operat))
//      {
//        cout<<"AdditionOperator"<<endl;
//        delete plus;
//      }
//      else if(SubtractionOperator* minus=dynamic_cast<SubtractionOperator*>(operat))
//      {
//      	cout<<"SubtractionOperator"<<endl;
//      	delete minus;
//      }
//      else cout<<"Nor AdditionOperator nor SubtractionOperator--Strange!"<<endl;
//      cout<<"rest="<<tpof.get_rest()<<endl;
//    }
//    else cout<<"Not matched"<<endl;
//  }
//
//  while(true)
//  {
//    cout<<"Enter string to match in SecondPriorityOperatorsFinder or ""q"" to exit:";
//    getline (cin,s);
//    if(s=="q") break;
//    if(spof.match(s))
//    {
//      cout<<"Match: ";
//      ExpressionOperator* operat=spof.get_matched_operator().clone();
//      if(MultiplicationOperator* plus=dynamic_cast<MultiplicationOperator*>(operat))
//      {
//        cout<<"MultiplicationOperator"<<endl;
//        delete plus;
//      }
//      else if(DivisionOperator* minus=dynamic_cast<DivisionOperator*>(operat))
//      {
//      	cout<<"DivisionOperator"<<endl;
//      	delete minus;
//      }
//      else cout<<"Nor MultiplicationOperator nor DivisionOperator--Strange!"<<endl;
//      cout<<"rest="<<spof.get_rest()<<endl;
//    }
//    else cout<<"Not matched"<<endl;
//  }
//  return 0;
//}
