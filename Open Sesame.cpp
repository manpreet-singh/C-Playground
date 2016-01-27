#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

void openTray();

int main(int argc, char[] *argv)
{
	time_t start_time = time(&start_time);
	time_t execution_time;
	double time_diff;
	
	while(true)
	{
		time(execution_time);
		time_diff = difftime(execution_time, start_time);
		
		if(time_diff == 600)
		{
			openTray();
			time(&start_time);
		}
	}
	return 0;
} 

void openTray()
{
	mciSendString("set cdaudio door open", NULL, NULL, NULL);
}
