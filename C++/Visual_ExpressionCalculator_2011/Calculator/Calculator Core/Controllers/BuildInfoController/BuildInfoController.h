#ifndef BUILDINFOCONTROLLER_H
#define BUILDINFOCONTROLLER_H

#include <string>
using namespace std;

namespace Controllers
{

  class BuildInfoController
  {
    public:
      static string get_full_version();
      static string get_build_date_string();
  };

} // namespace Controllers
#endif
