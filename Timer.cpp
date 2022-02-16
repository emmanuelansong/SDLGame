#include "Timer.h";
#pragma warning(disable: 4996)

bool Timer::getTime(char* buffer, int buffersize)
{
	//Get the current time
	time_t currentTime = std::time(0);
	//Get time information from current time -- secs, mins, etc. and save into a struct
	struct tm* info = localtime(&currentTime);
	//Format the time to (day_num/month_num/year time)
	size_t written = strftime(buffer, buffersize, "%d/%m/%y %T", info);
	//And return if the string was written or not
	return written != 0;
}


