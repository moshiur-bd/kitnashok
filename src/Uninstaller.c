#include<stdio.h>
int main()
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
    return 0;


}
