@echo off
call config.bat


if not exist %DATA_BUILDED% (
	md %DATA_BUILDED%
)

cd %DATA_BUILDED%
echo ********Making Sprites********

for %%i in (*.tga) do (
        move %%i %TOOL_BGCON%
   )
for %%i in (*.txt) do (
        move %%i %TOOL_BGCON%
   )

cd %TOOL_BGCON%
bgcon.exe TGA2DHUF.TXT

for %%i in (*.tga) do (
        move %%i %DATA_BUILDED%
   )
for %%i in (*.txt) do (
        move %%i %DATA_BUILDED%
   )

move *.BIN %DIR_OUTPUT_DATA%
 
cd %SS_PROJECT%
pause