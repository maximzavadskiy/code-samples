#ifndef GUIBUILDINFO_H
#define GUIBUILDINFO_H
#include <string>
using namespace std;

class GUIBuildInfo
{
  public:
    static string get_full_version();
    static string get_build_date_string();
};
#endif // GUIBUILDINFO_H
