#include <stdio.h>
#include <stdarg.h>

#include <windows.h>
void get_time_str(char *time_buf)
{
	SYSTEMTIME currentTime;
    GetLocalTime(&currentTime);
    sprintf(time_buf,"%04u.%02u.%02u %02u:%02u:%02u.%02u",           
     currentTime.wYear,currentTime.wMonth,currentTime.wDay,
     currentTime.wHour,currentTime.wMinute,currentTime.wSecond,
     currentTime.wMilliseconds);
}

void print_by_user(char * str) 
{
	printf("usrp %s\n", str);
}
