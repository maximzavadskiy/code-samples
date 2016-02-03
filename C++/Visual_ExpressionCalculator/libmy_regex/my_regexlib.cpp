#include"my_regexlib.h"
#include<iostream>


compile_reg_error::compile_reg_error(int errcode,regex_t* compiled)
{
  size_t length = regerror(errcode,compiled,NULL,0);
  char* buf=new char[length+1];
  regerror (errcode, compiled,buf, length);
  error=buf;
}
void my_regex::compile(std::string pattern, int flag1, int flag2, int flag3, int flag4) throw(incorrect_flag,compile_reg_error)
{
  if((flag1!=REG_NOSUB   ) && (flag1!=REG_EXTENDED  ) && (flag1!=REG_ICASE   ) && (flag1!=REG_NEWLINE   ) && (flag1!=0) ) throw incorrect_flag(flag1,1);

  if((flag2!=REG_NOSUB   ) && (flag2!=REG_EXTENDED  ) && (flag2!=REG_ICASE   ) && (flag2!=REG_NEWLINE   ) && (flag2!=0) ) throw incorrect_flag(flag2,2);

  if((flag3!=REG_NOSUB   ) && (flag3!=REG_EXTENDED  ) && (flag3!=REG_ICASE   ) && (flag3!=REG_NEWLINE   ) && (flag3!=0) ) throw incorrect_flag(flag3,3);

  if((flag4!=REG_NOSUB   ) && (flag4!=REG_EXTENDED  ) && (flag4!=REG_ICASE   ) && (flag4!=REG_NEWLINE   ) && (flag4!=0) ) throw incorrect_flag(flag4,4);

  int error=regcomp(&regular,pattern.c_str(), (flag1 | flag2 | flag3 | flag4) );
  results.resize(regular.re_nsub+2);

  nsubmatch=regular.re_nsub;//сохроняем nsubmatch
  if(error!=0) throw compile_reg_error(error,&regular);//если неудачно скомпилированл, сгенерировать ошибку
  reg=pattern;

  nsubmatch=regular.re_nsub;//сохроняем nsubmatch
}


my_regex::my_regex(std::string pattern, int flag1, int flag2, int flag3, int flag4) throw(incorrect_flag,compile_reg_error)
{
  compile(pattern,flag1,flag2,flag3,flag4);
}

my_regex::~my_regex() { /*delete[]  results;*/}

bool my_regex::match(std::string str, int flag1,int flag2) throw(incorrect_flag)
{

  if     ( (flag1!=REG_NOTBOL ) && (flag1!=REG_NOTEOL) && (flag1!=0) ) throw incorrect_flag(flag1,1);

  if     ( (flag2!=REG_NOTBOL ) && (flag2!=REG_NOTEOL) && (flag2!=0) ) throw incorrect_flag(flag2,2);
  text=str;//сохроняем строку

  if(regexec(&regular,str.c_str(), nsubmatch+1, &(results.at(0)),( flag1|flag2) )==0 )
  {
    return true;
  }
  else return false;
}


bool my_regex::replace(std::string& str,std::string otr, int flags1,int flags2) throw(incorrect_flag)
{
  if(match(str,flags1,flags2))
  {
    std::string::size_type beg=begin(0),len=get_match(0).length();
	  str.replace(beg,len,otr);
	  return true;
  }
  else
  {
    return false;
  }
}

void my_regex::is_correct_index(int index) const throw(incorrect_submatch_index)
{
  if( (index<0) || (index>nsubmatch) ) throw incorrect_submatch_index();
}


int my_regex::begin (int num) const throw (incorrect_submatch_index)
{
  is_correct_index(num);
  return results[num].rm_so;
}

std::string my_regex::get_match(int num) const throw (incorrect_submatch_index)
{
  is_correct_index(num);
  std::string::size_type i=begin(num),n=results[num].rm_eo-results[num].rm_so;
  //std::cout<<"reg: i="<<i<<" n="<<n;
  return text.substr(i,n);
}


std::string my_regex::get_pattern() const
{
  return reg;
}

int my_regex::get_num_of_matches() const
{
  return nsubmatch;
}

void my_regex::set_pattern(std::string pattern, int flags1,int flags2,int flags3,int flags4) throw(incorrect_flag,compile_reg_error)
{
  /*std::cout<<"delete[] results;\n"; delete[] results; std::cout<<"delete[] results;\n";*/
  compile(pattern, flags1, flags2,flags3, flags4);
}
