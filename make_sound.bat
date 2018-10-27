@echo off
call config.bat

echo ********Making Sounds PCM********

cd %DIR_SOUND_INPUT_DATA%

echo off
for %%i in (*.wav) do (
        %SATURN_ORBIT%\TOOLS\RB_SaturnPCM.exe %%i
   )

echo ********Packing Sounds********
   
copy /b *.pcm SFX.bin   


echo ********Make size header********   

for %%A in (*.pcm) do (

echo #define %%~nA_SIZE %%~zA >> soundheader.h

)   
for %%A in (*.bin) do (

echo #define %%~nA_SIZE %%~zA >> soundheader.h

) 


echo ********Moving Sounds PCM********

del *.pcm
move SFX.bin %DIR_OUTPUT_DATA%

move soundheader.h %SS_PROJECT%\src

cd %SS_PROJECT%  
pause