#ifndef GUI_VERSION_H
#define GUI_VERSION_H

namespace GUIAutoVersion{
	
	//Date Version Types
	static const char DATE[] = "18";
	static const char MONTH[] = "11";
	static const char YEAR[] = "2010";
	static const char UBUNTU_VERSION_STYLE[] = "10.11";
	
	//Software Status
	static const char STATUS[] = "Release Candidate";
	static const char STATUS_SHORT[] = "rc";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 1;
	static const long BUILD = 45;
	static const long REVISION = 45;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 501;
	#define RC_FILEVERSION 1,1,45,45
	#define RC_FILEVERSION_STRING "1, 1, 45, 45\0"
	static const char FULLVERSION_STRING[] = "1.1.45.45";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 30;
	

}
#endif //GUI_VERSION_H
