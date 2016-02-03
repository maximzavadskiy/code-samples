#ifndef MY_REGEX
#define MY_REGEX

  #include<stdexcept>
  #include<vector>

  #include<string>
  #include<sstream>
  #include<iostream>
  #include "regex.h"
  /*
   Флаги для my_regex(),set_pattern():
    REG_NOSUB    --несохронять совпадения рег. выражений и подвыраженй
    REG_EXTENDED --расширенное регулярное выражение
    REG_ICASE    --игнорирование регистра символов
    REG_NEWLINE  --Обрабатывает символ перевода строки в строке как деление строки на многократные строки, так, чтобы " $ " мог соответствовать перед символом перевода строки, а " ^ " мог соответствовать после. Также, не разрешает "." соответствовать символу перевода строки, и не разрешает " [^. . .] " соответствовать символу перевода строки.
   Флаги для match(), replace():
    REG_NOTBOL -- Не расценивает начало заданной строки как начало строки; более вообще, не делает ни каких предположений относительно того, что текст мог бы предшествовать ей.
    REG_NOTEOL--  Не расценивает конец заданной строки как конец строки; более обще, не делает ни каких предположений относительно того, что текст мог бы следовать за ней
   */
  class incorrect_flag          :public std::exception//хотя бы один из флагов неправильный
  {
    private:
      std::string  error;
    public:
      incorrect_flag (int flag, int flagnum)
      {
        std::ostringstream ss("");
        ss<<"Неверный флаг, номер флага: "<<flagnum<<" ,значение флага: "<<flag;
        error=ss.str();
      }
      ~incorrect_flag() throw() {};
      virtual const char* what() const throw() { return error.c_str(); }
  };

  class incorrect_submatch_index:public std::exception{};

  class compile_reg_error       :public std::exception //ошибка при компилировании регулярного выражения
  {
    private:
      const char* error;
    public:
       compile_reg_error(int errcode,regex_t* compiled);

    virtual const char* what() const throw() { return error;}
    virtual ~compile_reg_error() throw() {}
  };

  class my_regex
  {
  private:
    void is_correct_index(int index)  const throw(incorrect_submatch_index);//если номер подвыражения(index)--неправильный, то генерирование ошибки: неправильный индекс подсоответствия
    int nsubmatch ;//кол-во подвыражений

    std::string text; //строка проверяющаяся на соответствие регулярному выражению
    std::string reg;//строковое представление регулярного выражения
    regex_t regular;
    std::vector<regmatch_t> results;
    void compile(std::string,int,int,int,int) throw(incorrect_flag,compile_reg_error);
  public:
    my_regex        (std::string pattern="",int flag1=REG_EXTENDED,int flag2=0,int flag3=0,int flag4=0)throw(incorrect_flag,compile_reg_error);
    ~my_regex();
    void set_pattern(std::string pattern="", int flag1=REG_EXTENDED,int flag2=0,int flag3=0,int flag24=0) throw(incorrect_flag,compile_reg_error);//обновить рег. выр.
    bool match(std::string str, int flag1=0,int flag2=0) throw(incorrect_flag);//совпало ли str с рег. выр.
    bool replace(std::string& str,std::string otr, int flag1=0,int flag2=0) throw(incorrect_flag);//если str совпало с рег. выр., то замена совпавшей части str на otr
    std::string get_pattern() const;//получить строковое представление регулярного выражения

    std::string get_match(int submatch=0) const throw (incorrect_submatch_index);// получить подвыражение
    int begin            (int num=0)      const throw (incorrect_submatch_index);//начало подвыражения

    int get_num_of_matches() const;//получить количество плдвыражений
  };


#endif
