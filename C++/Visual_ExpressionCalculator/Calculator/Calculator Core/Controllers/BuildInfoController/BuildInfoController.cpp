
#include "BuildInfoController.h"
#include "calculator_core_version.h"
#include <sstream>
namespace Controllers
{
  string BuildInfoController::get_full_version()
  {
    ostringstream oss;
    oss<<AutoVersion::STATUS<<" "<<AutoVersion::MAJOR<<"."<<AutoVersion::MINOR<<"."<<AutoVersion::BUILD<<"."<<AutoVersion::BUILDS_COUNT;
    return oss.str();
  }

  string BuildInfoController::get_build_date_string()
  {
    return string(AutoVersion::DATE)+string(".")+string(AutoVersion::MONTH)+string(".")+string(AutoVersion::YEAR);
  }


} // namespace Controllers
