#include<stdexcept>
using namespace std;

class system_error:public exception
{
  public:

    system_error(const char* mes)
    {
      message=mes;
    }

    const char* what() const throw() {return message;}
  private:
    const char* message;
};
