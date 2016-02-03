  #include "GUIBuildInfo.h"
  #include "gui_version.h"
  #include <sstream>

  string GUIBuildInfo::get_full_version()
  {
    ostringstream oss;
    oss<<GUIAutoVersion::STATUS<<" "<<GUIAutoVersion::MAJOR<<"."<<GUIAutoVersion::MINOR<<"."<<GUIAutoVersion::BUILD<<"."<<GUIAutoVersion::BUILDS_COUNT;
    return oss.str();
  }

  string GUIBuildInfo::get_build_date_string()
  {
    return string(GUIAutoVersion::DATE)+string(".")+string(GUIAutoVersion::MONTH)+string(".")+string(GUIAutoVersion::YEAR);
  }
