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
    loop:
     system("cls");

    printf("KitNashok Installer\n\n\tSetup with-\n\n\t\t");
    printf(" *  Default settings\n\t\t[C] Custom settings\n\n\n\n\n");
    printf("hints:\npress key 'C' to go through custom installation process and \n\n*** press any other key to select default settings.\n ");
    printf("\n\t\t:>");

    if(toupper(getch())=='C')
    {
        system("cls");
        char set[6][100]=
        {
            "Execution effect-",
            "Clean new inserted drives automatically-",
            "Ask before cleaning every drive-",
            "Remove shortcut(.lnk) files-",
            "Recover data from removable drives-",
            "Jam single link shortcut virus-"

        } ;
        char option[6][2][30]= {"Yes","No",
                                "Yes","No",
                                "Yes","No",
                                "Aggressively","Smartly"
                                ,"Always","Smartly",
                                "Yes","No"

                               };
        char help[6][500]=
        {
            "launching effect!! \n* set this yes and pop-up window will stay even shorter for newly inserted drive",
            "you are advised to set this yes. if you set this no, you will never get the \nmaximum protection through KitNashok",
            "set yes only if you want to connect a drive containing lnk/vbs/vbe/init files\nwhat might be valuable to you.\n*** if you connect a windows bootable drive then whatever your choice be, \nKitNashok will always ask for your permission!",
            "this setting is only for fixed drives. \n* aggressive shortcut deletion will delete each and every shortcut file from\n  fixed drive unless that drive is a system drive(we didn't forget that you\n  might have multi-OS).\n* on the other hand, smart shortcut remover removes shotcut file if it's name\n  is same as it's parent directory. ",
            "For any previous versions, whenever you connected a removable drive KitNashok \ndeletes suspects from the drive and recovers data from it blindly which is more\ntime consuming\nfrom now on, recovery will only execute when it successfully delete any suspect\nfrom removable drives.",
            "If you connect a Drive and all the data of the drive is replaced with a single\nshortcut named similar to Drive label, then set Yes .otherwise no. "

        };
        int a[6];
        FILE *f=fopen("bin\\settings.txt","w");
        //fprintf(f,"100 ");
        for(int i=0; i<6; i++)
        {
            if(i<0)
                    goto loop;
            printf("<- [backspace] back\n\n\t%s\n",set[i]);
            printf("\n\t\t[1] %s\n\t\t[2] %s\n\n\n\nhints:\n",option[i][0],option[i][1]);
            printf(help[i]);
            printf("\n\n\t\t:>");
            a[i]=getBOOL();
            if(a[i]==-1)
                i-=2;
            system("cls");

        }
        for(int i=0; i<6; i++)
            fprintf(f,"%d ",a[i]);
        fclose(f);



    }
    else system("del /f /q bin\\settings.txt");
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
