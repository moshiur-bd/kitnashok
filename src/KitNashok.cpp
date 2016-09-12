#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#define _WIN32_WINNT 0x0500
#include<windows.h>

#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
using namespace std;
char sys[]="C:\\";
char cmd[1000];
FILE *rem;
char omitted_drives[100]="";
char current_selected_drive;
int run=1;
char d_label[100];
char queued_drives[100];

bool call_from_design=1;
int sleeping_time=100;
//////////////////rules///////////
char removable_rules[1000]="*.lnk *.vbe *.vbs *.init desktop.ini autorun.inf *humbs.db *.INIT";
char fixed_rules[1000]="fofo.vb* COOL.vb*";
char fixed_file[1000]="AutoIt3.exe";
char fixed_folder[1000]="Google Skypee";

//////settings_var////
bool recover_data=0;//fast cleaner
bool show_hide_effect=0;//fast launching
bool need_permission=0;//prompting
bool all_link_clean=0;//delete shortcut link files
bool hidden_monitor=1;//startup
bool svchost_killer=1;
//about us
//contact us
//upgrade
///\settings////////


//////////version//////
char version[]="\n\n\n\n\n\n\n\tName\t\t: KitNashok\n\tversion\t\t: 1.4\n\trelease date\t: 27 November, 2014";
/////////\version\\\\\\



////////prototypes\\\\\\\\\\\\\\\\
void settings(char *);
void removable_design();
void fixed_bat_creator_autoit(char*,char*,char);
void settings(char *);
////////\prototypes\\\\\\\\\\\\\\\\

bool file_exist(char s[])
{
    FILE *f=fopen(s,"r");
    if(f!=NULL)
    {
        fclose(f);
        return 1;
    }
    return 0;


}
bool file_exist_var_path(char path[])
{
    FILE *f=fopen("file.flag","w");
    fclose(f);
    char s[100]="dir ";
    strcat(s,path);
    strcat(s," >>file.flag\n");
    f=fopen("file.flag","r");
    system(s);
    int line=0;
    char ch;
    while(fscanf(f,"%c",&ch)!=EOF)
        if(ch=='\n')
            line++;

    fclose(f);
    system("cls");
    if(line<=5)    return 0;
    return 1;


}
void letToPath(char l,char path[])
{
    strcpy(path,"C:\\");
    path[0]=l;
    return;
}

int killProcessByName(const char *filename)
{
    int v;

    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof (pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
        if (strcmp(pEntry.szExeFile, filename) == 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                                          (DWORD) pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                v=TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
    return v;
}

void process_killing_list()
{
    killProcessByName("AutoIt3.exe");
    killProcessByName("wscript.exe");
    system("reg delete HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Run /v fofo /f");
    system("reg delete HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Run /v AntiUsbWorm /f");
    system("reg delete HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Run /v AntiWormUpdate /f");

}

char *alldriveschar()
{
    char str[100]="";
    int i=0;
    DWORD dwSize = MAX_PATH;
    char szLogicalDrives[MAX_PATH] = {0};
    DWORD dwResult = GetLogicalDriveStrings(dwSize,szLogicalDrives);

    if (dwResult > 0 && dwResult <= MAX_PATH)
    {
        char* szSingleDrive = szLogicalDrives;
        while(*szSingleDrive)
        {
            str[i++]=szSingleDrive[0];

// get the next drive
            szSingleDrive += strlen(szSingleDrive) + 1;
        }
    }
    str[i]=NULL;

    return str;
}
bool getVolInfo(char ltr[],char label[],char type[])
{
    DWORD dwSize = MAX_PATH;
    char szLogicalDrives[MAX_PATH] = {0};
    DWORD dwResult = GetLogicalDriveStrings(dwSize,szLogicalDrives);
    TCHAR szVolumeName[100]    = "";
    TCHAR szFileSystemName[10] = "";
    DWORD dwSerialNumber       = 0;
    DWORD dwMaxFileNameLength  = 0;
    DWORD dwFileSystemFlags    = 0;
    if(::GetVolumeInformation(ltr,
                              szVolumeName,
                              sizeof(szVolumeName),
                              &dwSerialNumber,
                              &dwMaxFileNameLength,
                              &dwFileSystemFlags,
                              szFileSystemName,
                              sizeof(szFileSystemName)) == TRUE)
    {

        strcpy(label,szVolumeName);
        if(strlen(label)==0)
        {
            strcpy(label,"No Name");
        }
        strcpy(type,szFileSystemName);
        return 1;

    }
    return 0;
}
char get_drives(char *removable, char *fixed)
{
    char *sys=getenv("SystemDrive");
    int i,j=0,k=0;
    char str[100];
    strcpy(str,alldriveschar());
    int len=strlen(str);
    for(i=0; i<len; i++)
    {
        char s[12]="C:\\";
        s[0]=str[i];
        char garb[100];
        if(!getVolInfo(s,garb,garb))
            continue;
        switch(GetDriveType(s))
        {
        case 2:
            removable[j++]=s[0];
            break;
        case 3:
            if(sys[0]==s[0])   break;
            fixed[k++]=s[0];
        }
    }
    fixed[k]=removable[j]=NULL;

    return sys[0];

}
bool isremovable(char drc)
{
    char hdd[30],rmv[30];
    get_drives(rmv,hdd);
    for(int i=0; i<strlen(rmv); i++)
        if(drc==rmv[i])
            return 1;
    return 0;
}
bool permit()
{
    system("cls");
    char dr[]="D:\\\\bootmgr";
    dr[0]=current_selected_drive;
    if(file_exist(dr)&&isremovable(dr[0]))
    {
        printf("Seems like a windows bootable drive!!!\n");
        goto jump;
    }

    if(need_permission==0)
    {
        system("cls");
        return 1;
    }
jump:
    ShowWindow( GetConsoleWindow(), SW_RESTORE );
    printf("\n\n\t\t\tStarting to clean from %c:\n \t\t\t Are you sure?(Y/N)\n\t\t\t:>",current_selected_drive);
    char c=getch();
    if(c=='Y'||c=='y')
    {
        system("cls");
        return 1;

    }
    return 0;
}
void removable_bat_creator_recover(char *dir)
{
    strcat(cmd,"\ncd /d ");
    strcat(cmd,dir);
    strcat(cmd,"\nattrib -a -s -h -r *.* /s /d");
    strcat(cmd,"\nattrib +h +s \"System Volume Information\"\n");
}
void removable_bat_creator(char *rules,char *dir)
{
    strcpy(cmd,"cd /d ");
    strcat(cmd,dir);
    strcat(cmd,"\ndel /f /s /q /a shar ");
    strcat(cmd,rules);
    char s[]="C:\\*.lnk";
    s[0]=dir[0];
    if(call_from_design||recover_data||file_exist_var_path(s))
        removable_bat_creator_recover(dir);
    strcat(cmd,"\nexit\n");


}
void clean_removable_drive(char tmp)
{
    char dr[10]="D:\\";
    dr[0]=tmp;
    current_selected_drive=dr[0];
    if(!permit())
        return;
    removable_bat_creator(removable_rules,dr);
    rem=fopen("rem.bat","w");
    fprintf(rem,"%s\n",cmd);
    fclose(rem);
    system("rem.bat");
    fixed_bat_creator_autoit(fixed_folder,fixed_file,dr[0]);
    rem=fopen("rem.bat","w");
    fprintf(rem,"%s",cmd);
    fclose(rem);
    system("rem.bat");
    system("del /f /q rem.bat");

}


char mismatch(char *a, char*b)
{
    int i,j,la=strlen(a),lb=strlen(b);
    int newdr=0;
    char send;
    for(i=0; i<la; i++)
    {
        for(j=0; j<lb; j++)
        {
            if(a[i]==b[j])
            {
                a[i]=2;
                b[j]=3;
                break;
            }
        }
        if(j>=lb)
        {
            current_selected_drive=a[i];

            if(!newdr++)
            {
                send =a[i];
            }
            else
            {
                queued_drives[newdr-2]=a[i];
            }
        }

    }
    queued_drives[newdr-1]=NULL;
    in_queue=newdr-1;
    return send;
}

char  hide(char remab[],bool flag_run)
{

    char removable[27];
    char fixed[27];

    if(file_exist("sleeping.st"))
        exit(0);
    else
    {

        fclose(fopen("sleeping.st","w"));
    }
    if(hidden_monitor==0)
        exit(0);
    ////////////
    ShowWindow( GetConsoleWindow(), SW_HIDE );
    int x=0;
    while(1)
    {
        get_drives(removable,fixed);
        if(strcmp(remab,removable)!=0&&strlen(removable)>strlen(remab))
            break;
        else strcpy(remab,removable);

        if(svchost_killer&&(x%100)==0)
        {

            system("taskkill /f /fi \"imagename eq svchost.exe\" /fi \"username eq %username%\"");
        }
        x++;
        if(x>=100) x=x%100;

        Sleep(sleeping_time);

    }



    ShowWindow( GetConsoleWindow(), SW_MINIMIZE );
    system("del /f /q *.st");

    system("start KitNashok.exe");
    call_from_design=0;
    return mismatch(removable,remab);

}
///////////////
void fixed_bat_creator_lnk_smart(char *dir)
{
    strcpy(cmd,"cd /d ");
    strcat(cmd,dir);
    strcat(cmd,"\nFOR /D /R %dir% %%X  IN (*.*) do if exist \"%%X\\%%~nX.lnk\"    del /f /q /a shar \"%%X\\%%~nX.lnk\"\n\nexit");
}

void fixed_bat_creator_lnk(char *dir)
{
    if(dir[0]==sys[0])
    {
        cmd[0]=NULL;
        return;
    }
    strcpy(cmd,"cd /d ");
    strcat(cmd,dir);
    strcat(cmd,"\n IF exist Windows If exist Users exit");
    strcat(cmd,"\ndel /f /s /q /a shar *.lnk");
}
void fixed_bat_creator_ext(char *rules,char *dir)
{
    strcpy(cmd,"cd /d ");
    strcat(cmd,dir);
    strcat(cmd,"\ndel /f /s /q /a shar ");
    strcat(cmd,rules);
}

void fixed_bat_creator_autoit(char *folders,char *files,char dir)
{
    strcpy(cmd,"cd /d ");
    char s[500]="D:\\";
    s[0]=dir;
    strcat(cmd,s);
    strcat(cmd,"\nFOR /D /R %dir% %%X  IN (");
    strcat(cmd,folders);
    strcat(cmd,") do ");


    int o=0;
    while(sscanf(files,"%s%n",s,&o)!=EOF)
    {
        strcat(cmd,"if exist \"%%X\\");
        strcat(cmd,s);
        strcat(cmd,"\"   ");
        files+=o;
    }


    strcat(cmd," RMDIR /S /Q \"%%X\"\nexit");
}

void clean_fixed_drive(char tmp)
{
    system("cls");
    int i=0;
    char dr[10]="D:\\";
    dr[0]=tmp;
    current_selected_drive=dr[0];
    if(!permit())
        return;
    process_killing_list();
    fixed_bat_creator_autoit(fixed_folder,fixed_file,dr[0]);
    rem=fopen("rem.bat","w");
    fprintf(rem,"%s",cmd);
    fclose(rem);
    system("rem.bat");

    fixed_bat_creator_ext(fixed_rules,dr);
    rem=fopen("rem.bat","w");
    fprintf(rem,"%s",cmd);
    fclose(rem);
    system("rem.bat");

    if(all_link_clean)
    {
        fixed_bat_creator_lnk(dr);
        rem=fopen("rem.bat","w");
        fprintf(rem,"%s",cmd);
        fclose(rem);
        system("rem.bat");
    }
    fixed_bat_creator_lnk_smart(dr);
    rem=fopen("rem.bat","w");
    fprintf(rem,"%s",cmd);
    fclose(rem);
    system("rem.bat");
    system("del /q /f rem.bat");
}

void first_scan(char fixeddr[],char removabledr[])
{
    system("cls");

    printf("Windows script host will appear shortly. \n\nwhen the window appears,\n\n\t> give a tick on \"stop script host after specified number of seconds\"\n\t> set 1 seconds\n\t> press apply button and then ok button\n\n\n\n\n\n\t\tpress any key.....");
    getch();
    system("wscript.exe");
    system("cls");

    printf("\n\n\nKitNashok was installed on your pc successfully!!\n\n\n\nA whole system scan is needed.");
    printf("\n\n\n\t\t\t Do you want to proceed? (Y/N):");
    char c='Y';

    if(c!='Y'&&c!='y')
    {
        system("cls");
        return;

    }

    int i,l=strlen(fixeddr);
    clean_fixed_drive(sys[0]);
    for(i=0; i<l; i++)
        clean_fixed_drive(fixeddr[i]);

    l=strlen(removabledr);
    for(i=0; i<l; i++)
    {
        current_selected_drive=removabledr[i];
        if(permit())
            clean_removable_drive(removabledr[i]);
    }
    return;



}
void fixed_design()
{
    ShowWindow( GetConsoleWindow(), SW_SHOW );
    char removable[27],fixed[27];
restart:
    sys[0]=get_drives(removable,fixed);
    system("cls");
    printf("[backspace] Removable Drive cleaner\t\t\t\t[esc] Exit\n\n\t\t\t\t\t\t\t\t[tab] Settings");

    if(fixed[0]==NULL)
    {
        printf("\n\n\n\n\n\n\n\n\t\t");
        printf("no drives found!! press any key to refresh!\n\n\n\n\n");
        switch(getch())
        {
        case 8:
            removable_design();
            break;
        case 9:
            settings("");
            break;
        case 27:
            exit(0);

        }

    }
    else
    {
        printf("\n\n\n\n\n\t\t\t\t");
        printf("CLEAN FIXED DRIVES:\n\n");
        printf("\t\t    [space] *: All Drives\n");

        int i=0,len=strlen(fixed);
        for(i=-1; i<len; i++)
        {
            if(i==-1)
            {
                char lab[100],type[100];

                getVolInfo(sys,lab,type);
                printf("\t\t\t[%d] %c: ",i+1,sys[0]);
                int spc=20-printf(lab);
                for(int j=0; j<spc; j++)
                    printf(" ");
                printf("\t");
                printf(type);
                printf("\n");
                continue;
            }
            char lab[100],type[100],let[10];
            letToPath(fixed[i],let);
            getVolInfo(let,lab,type);


            printf("\t\t\t[%d] %c: ",i+1,fixed[i]);
            int spc=20-printf(lab);
            for(int j=0; j<spc; j++)
                printf(" ");
            printf("\t");
            printf(type);
            printf("\n");
        }
        printf("\n\t\t\t\t:>");
        char slt=getch();
        slt-=('1');
        if((slt+'1')==' ')
        {
            for(int k=-1; k<len; k++)
                if(k==-1)
                    clean_fixed_drive(sys[0]);
                else
                    clean_fixed_drive(fixed[k]);
        }
        if(slt>=0&&slt<len)
        {
            clean_fixed_drive(fixed[slt]);
        }
        else if(slt==-1)
        {
            clean_fixed_drive(sys[0]);
        }
        else if((slt+'1')==8)
        {
            removable_design();
        }
        else if((slt+'1')==27 )
        {
            exit(0);
        }
        else if((slt+'1')==9 )
        {
            settings("");
        }


    }

    goto restart;

}

///////////
bool get_bool(char *y,char *n)
{
restart:
    system("cls");
    printf("\n\n\n\n\n\n\n\t\t\t\t");

    printf("[1]%s\n",y);
    printf("\t\t\t\t[2]%s\n\t\t\t\t:>",n);
    char ch=getch();
    switch(ch)
    {
    case '1':
        return 1;
    case '2':
        return 0;
    }
    goto restart;
}
void uninstaller()
{
    system("cls");
    printf("\n\n\n\n\n\n\t\tDo you really want to Uninstall KitNashok?\n");
    printf("\n\t\t\t\t[1]Yes");
    printf("\n\t\t\t\t[2]No");
    printf("\n\n\t\t\t\t:>");
    if(getch()=='1');
    else return ;
    char dl[200]="del /q /f ";
    char *s=getenv("SystemDrive");
    strcat(s,"\\Users\\%username%\\Desktop\\KitNashok.lnk");
    strcat (dl,s);
    system(dl);
    FILE *f=fopen("rem.bat","w");
    fprintf(f,"cd /d %%appdata%% \ntaskkill /f /fi \"Imagename eq KitNashok.exe\"\ndel /f /q \"%%appdata%%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\KitNashok.lnk\"\ndel /f /q \"%%appdata%%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\KitNashok.bat\"\nrmdir /q /s \"%%appdata%%\\KitNashok\"\nexit\n ");
    fclose(f);

    system("start rem.bat \" ");



}
void relaunch()
{
    system("cls");
    printf("\n\n\n\n\n\n\n need to restart KitNashok.  Don't select yes while cleaning any drive.\n this action will kill all the instances of this program\n and restart it as well \n");
    printf("\n\t\tAry you sure to re-launch KitNashok?\n");
    printf("\n\t\t\t\t[1]Yes");
    printf("\n\t\t\t\t[2]No");
    printf("\n\n\t\t\t\t:>");
    if(getch()=='1');
    else return ;
    FILE *f=fopen("rem.bat","w");
    fprintf(f,"taskkill /f /fi \"Imagename eq KitNashok.exe\"\ndel /f /q *.st\nstart KitNashok.exe\n\clncls\ncls\cls\ncolor 71\n\cls\ncls\ncls\cls\ncolor 71\ntree %%appdata%% \ndir %%appdata%%\nstart KitNashok.exe\n exit\n ");
    fclose(f);
    system("start rem.bat");

}
char *get_defaults()
{
    system("cls");
    printf("\n\n\n\n\n\n\n\t\t");
    printf("Ary you sure to save default Settings?\n");
    printf("\n\t\t\t\t[1]Yes");
    printf("\n\t\t\t\t[2]No");
    printf("\n\n\t\t\t\t:>");
    if(getch()=='1');
    else return "";
    system("del /f /q settings.txt");
    relaunch();
    return "Default settings saved!";

}
void contact_us()
{
    system("cls");
    printf("\n\n\tLike Us or Contact Us:\n\t\t[0]\tFacebook Page\t: www.facebook.com/KitNashok\n");
    printf("\n\n\n\n\tDevelopers:\n\t\tMd. Moshiur Rahman Rabby:\n\n\t\t\t");
    printf("Mobile\t: +880 175-3838158\n\t\t");
    printf("[1]\tFacebook ID\t: www.facebook.com/moshiur.rahmanrabby\n");
    printf("\n\n\n\t\tSudipto Roy:\n\n\t\t\t");
    printf("Mobile\t: +880 194-4984923\n\t\t");
    printf("[2]\tFacebook ID\t: www.facebook.com/sudipto.roy.313\n");
    printf("\n\t\t\t\t:>");
    switch(getch())
    {
    case  '0':
        system ("cls");
        printf("\n\n\n\n\n\n\n\t\t\t\tOpening KitNashok fan page=>\n\t\t\t\t\t");
        Sleep(1500);
        system("start www.facebook.com/KitNashok");
        printf("Loading.");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        break;

    case '1':
        system ("cls");
        printf("\n\n\n\n\n\n\n\t\t\t\tConnecting to Moshiur=>\n\t\t\t\t\t");
        Sleep(1500);
        system("start www.facebook.com/moshiur.rahmanrabby");
        printf("Loading.");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        break;
    case '2':
        system ("cls");
        printf("\n\n\n\n\n\n\n\t\t\t\tConnecting to Sudipto=>\n\t\t\t\t\t");
        Sleep(1500);
        system("start www.facebook.com/sudipto.roy.313");
        printf("Loading.");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        break;

    }
}
char *save()
{
    system("cls");
    printf("\n\n\n\n\n\n\n\t\t");
    printf("Ary you sure to save current Settings?\n");
    printf("\n\t\t\t\t[1]Yes");
    printf("\n\t\t\t\t[2]No");
    printf("\n\n\t\t\t\t:>");
    if(getch()=='1');
    else return "Not Saved!";
    system("del /f /q settings.txt");
    FILE *f=fopen("settings.txt","w");
    fprintf(f,"%d %d %d %d %d %d\n",sleeping_time,hidden_monitor,need_permission,all_link_clean,recover_data,svchost_killer);
    fclose(f);
    relaunch();
    return "Current settings saved!";
}
void settings(char *msg)
{
restart:
    system("cls");
    printf("[backspace] back\t\t\t\t\t\t[esc] Save\n\n\t\t\t\t\t\t\t\t[tab] UnInStAlL\n");
    printf("%s\n",msg);
    printf("\n\n\t\t<<SETTINGS>>\n\n");
    char opt[10][40]= {"Auto Clean\t","Ask Before Cleaning","Shortcut remover","Data Recovery  ","INIT virus jammer","Default Settings","Contact us","About","Show Hide Effect"};
    char ans[10][2][20]= {"No","Yes","No","Yes","Smart","Aggressive","Smart","Always ","No","Yes","No","Yes"};
    printf("\t[%d]%s\t: %s\n",1,opt[8],ans[5][show_hide_effect]);//exception index 5
    printf("\t[%d]%s\t: %s\n",2,opt[0],ans[0][hidden_monitor]);
    printf("\t[%d]%s\t: %s\n",3,opt[1],ans[1][need_permission]);
    printf("\t[%d]%s\t: %s\n",4,opt[2],ans[2][all_link_clean]);
    printf("\t[%d]%s\t: %s\n",5,opt[3],ans[3][recover_data]);
    printf("\t[%d]%s\t: %s\n",6,opt[4],ans[4][svchost_killer]);
    printf("\t[%d]%s\t: =>\n",7,opt[5]);
    printf("\t[%d]%s\t\t: =>\n",8,opt[6]);
    printf("\t[%d]%s\t\t: =>\n",9,opt[7]);
    printf("\n\n\t:>");
    char ch=getch();
    system("cls");
    printf("\n\n\n\n\n\n\n\t\t\t\t");
    int wrong_click=0;
    switch(ch)
    {
    case '1':
        show_hide_effect=get_bool("Yes","No");
        break;
    case '2':
        hidden_monitor=get_bool("Yes","No");
        break;
    case '3':
        need_permission=get_bool("Yes","No");
        break;
    case '4':
        all_link_clean=get_bool("Aggressive","Smart");
        break;
    case '5':
        recover_data=get_bool("Always","Smart");
        break;
    case '6':
        svchost_killer=get_bool("Yes","No");
        break;
    case '7':
        msg=get_defaults();
        goto restart;
    case '8':
        contact_us();
        wrong_click=1;
        break;
    case '9':
        system("cls");
        printf("%s\n",version);
        printf("\n\n\n\n\n\t\tpress any key to go back....");
        getch();
        wrong_click=1;
        break;
    case 8:
        return ;
    case 9:
        uninstaller();
        wrong_click=1;
        break;
    case 27:
        msg=save();
        goto restart;
    default :
        wrong_click=1;

    }
    if(!wrong_click)
    {
        char str[]="changes applied! but not saved. press esc button to save";
        msg=str;
    }
    else
    {
        char str[]="";
        msg=str;
    }
    goto restart;

}
void removable_design()
{
    ShowWindow( GetConsoleWindow(), SW_SHOW );
    call_from_design=1;

    char removable[27],fixed[27];
restart:
    system("cls");
    sys[0]=get_drives(removable,fixed);
    printf("[backspace] Fixed Drive cleaner\t\t\t\t\t[esc] Exit\n\n\t\t\t\t\t\t\t\t[tab] Settings");
    if(removable[0]==NULL)
    {

        printf("\n\n\n\n\n\n\n\n\t\t");
        printf("no removable drives found!! press any key to refresh!\n\n\n\n\n");
        char ch=getch();
        switch(ch)
        {
        case 8:
            fixed_design();
            break;
        case 9:
            settings("");
            break;

        case 27:
            exit(0);
            break;
        default:
            goto restart;
        }
    }
    else
    {

        printf("\n\n\n\n\n\t\t\t\t");
        printf("CLEAN REMOVABLE DRIVES:\n\n");
        int i=0,len=strlen(removable);
        printf("\t\t    [space] *: All Drives\n");
        for(i=0; i<len; i++)
        {

            char lab[100],type[100],let[10];
            letToPath(removable[i],let);
            getVolInfo(let,lab,type);
            printf("\t\t\t[%d] %c: ",i+1,removable[i]);
            int spc=20-printf(lab);
            for(int j=0; j<spc; j++)
                printf(" ");
            printf("\t");
            printf(type);
            printf("\n");
        }
        printf("\n\t\t\t:>");
        int slt=getch();
        slt-=('0'+1);
        if((slt+'1')==' ')
        {
            for(int k=0; k<len; k++)
                clean_removable_drive(removable[k]);
        }
        else if(slt>=0&&slt<len)
        {
            clean_removable_drive(removable[slt]);
        }
        else if((slt+'1')==8)
        {
            fixed_design();
        }
        else if((slt+'1')==27 )
        {
            exit(0);
        }
        else if((slt+'1')==9 )
        {
            settings("");
        }


    }
    goto restart;
}
///////////////////closing events modification\\\\\\\\\\\\\\\\\\\\
// Handler function will be called on separate thread!
static BOOL WINAPI console_ctrl_handler(DWORD dwCtrlType)
{
    switch (dwCtrlType)
    {
    case CTRL_C_EVENT: // Ctrl+C
        break;
    case CTRL_BREAK_EVENT: // Ctrl+Break
        break;
    case CTRL_CLOSE_EVENT: // Closing the console window
        remove("running.st");
        break;
    case CTRL_LOGOFF_EVENT: // User logs off. Passed only to services!
    case CTRL_SHUTDOWN_EVENT: // System is shutting down. Passed only to services!
        system("del /f /q *.st");
        break;
    }

    // Return TRUE if handled this message, further handler functions won't be called.
    // Return FALSE to pass this message to further handlers until default handler calls ExitProcess().
    return FALSE;
}


////////////////////////

void set_settings()
{
    if(!file_exist("settings.txt"))
        return;
    FILE *f=fopen("settings.txt","r");
    int h;

    fscanf(f,"%o",&h);
    show_hide_effect=h;
    fscanf(f,"%o",&h);
    hidden_monitor=h;
    fscanf(f,"%o",&h);
    need_permission=h;
    fscanf(f,"%o",&h);
    all_link_clean=h;
    fscanf(f,"%o",&h);
    recover_data=h;

    fscanf(f,"%o",&h);
    svchost_killer=h;
    //printf("%d %o %o %o %o\n",sleeping_time,hidden_monitor,need_permission,all_link_clean,recover_data);
    fclose(f);
    return ;
}
void clean_queued()
{
    for(int i=0; i<in_queue; i++)
        clean_removable_drive(queued_drives[i]);

}
int main()
{

    set_settings();
    if(show_hide_effect)
        ShowWindow( GetConsoleWindow(), SW_HIDE );
    SetConsoleCtrlHandler(console_ctrl_handler, TRUE);
    char removable[100],fixed[100];
    get_drives(removable,fixed);
    run=0;
    if(svchost_killer)
    {

        system("taskkill /f /fi \"imagename eq svchost.exe\" /fi \"username eq %username%\"");
    }


    if(!file_exist("sleeping.st"))
    {
        clean_removable_drive(hide(removable,0));
        if(in_queue)
            clean_queued();
        return 0;
    }
    if(file_exist("first.run"))
    {
        system("del /f /q first.run");
        ShowWindow( GetConsoleWindow(), SW_SHOW );
        first_scan(fixed,removable);

        return 0;
    }

    removable_design();
    return 0;

}
