#include <CoreLib/config_corelib.h>
template<class T>
std::string VarToString(T i)
{
	std::stringstream ss;
	std::string s;
	ss << i;
	s = ss.str();
	return s;
}