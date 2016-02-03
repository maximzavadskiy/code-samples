#ifndef MY_REGEX_VERSION_H
#define MY_REGEX_VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "18";
	static const char MONTH[] = "11";
	static const char YEAR[] = "2010";
	static const char UBUNTU_VERSION_STYLE[] = "10.11";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 2;
	static const long MINOR = 0;
	static const long BUILD = 1;
	static const long REVISION = 1;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 27;
	#define RC_FILEVERSION 2,0,1,1
	#define RC_FILEVERSION_STRING "2, 0, 1, 1\0"
	static const char FULLVERSION_STRING[] = "2.0.1.1";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 0;
	

}
#endif //MY_REGEX_VERSION_H
