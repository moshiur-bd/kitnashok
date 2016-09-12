cd /d %appdata% 
taskkill /f /fi "Imagename eq KitNashok.exe"
del /f /q "%appdata%\Microsoft\Windows\Start Menu\Programs\Startup\KitNashok.lnk"
del /f /q "%appdata%\Microsoft\Windows\Start Menu\Programs\Startup\KitNashok.bat"
rmdir /q /s "%appdata%\KitNashok"
exit
 