//#include <windows.h>
#include <stdlib.h>

int main()
{
	srand(GetTickCount());
	int duration;
	int freq;
while(true)
    {
        freq=(rand() % 1000)+800;
        duration=(rand() % 1000)+400;

        Beep((DWORD)freq,(DWORD)duration);
    }
}
