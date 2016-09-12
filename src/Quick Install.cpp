#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<ctype.h>
void shortcut(char *tar,char *lnk)
{
    FILE *fs=fopen("shortcut.vbs","w");
    fprintf(fs,"Set oWSS = WScript.CreateObject(\"WScript.Shell\")  \nshortCut = \"KitNashok.lnk\"  \nSet oLinkk = oWSS.CreateShortcut(shortCut) \noLinkk.TargetPath = \"%%appdata%%\\KitNashok\\KitNashok.exe\"\noLinkk.WorkingDirectory=\"%%appdata%%\\KitNashok\"\noLinkk.IconLocation = \"%%appdata%%\\KitNashok\\icon.ico, 0\"\noLinkk.Save");
    fclose(fs);
}
void batatstart()
{
    FILE *f=fopen("KitNashok.bat","w");
    fprintf(f,"cd /d \"%%appdata%%\\KitNashok\"\n\ndel /f /q sleeping.st\n start KitNashok.exe \n");
    fclose(f);
}
void generate()
{
    FILE *f=fopen("distribute.bat","w");
    fprintf(f,"move /y KitNashok.bat \"%%appdata%%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\"\nrmdir /s /q \"%%appdata%%\\KitNashok\"\nmkdir \"%%appdata%%\\KitNashok\"\ncopy /y bin\\*.*  \"%%appdata%%\\KitNashok\" ");
    fclose(f);
    system("distribute.bat");
    system(" del /f /q distribute.bat");
}

void short_distrib()
{
    FILE *f=fopen("distribute.bat","w");
    char *s=getenv("SystemDrive");
    strcat(s,"\\Users\\%username%\\Desktop\\KitNashok.lnk ");
    fprintf(f,"copy /y KitNashok.lnk \"%s\"",s);
    fclose(f);
    system("distribute.bat");

}
int getBOOL()
{
    while(char ch=getch())
    {
        if(ch=='1')
            return 1;
        else if(ch=='2')
            return 0;
        else if(ch==8)
            return -1;

    }
}
void setup()
{

}

int main()
{

    setup();
    batatstart();
    system("taskkill /f /fi \"Imagename eq KitNashok.exe\"");
    generate();

    shortcut("%%appdata%%\\KitNashok\\KitNashok.exe","KitNashok.lnk");
    system("shortcut.vbs");
    short_distrib();
    system(" del /f /q distribute.bat");
    system(" del /f /q shortcut.vbs");


    ///////////////////

    char s[]="del /f /q KitNashok.lnk\ncd /d \"%appdata%\\KitNashok\"\n start KitNashok.exe\n tree \n color 77 \n color 11 \n tree \n start KitNashok.exe\nexit\n";
    FILE *f=fopen("K.bat","w");
    fprintf(f,"%s\n",s);
    fclose(f);
    system("K.bat");
    return  system("del /f /q K.bat");

}
