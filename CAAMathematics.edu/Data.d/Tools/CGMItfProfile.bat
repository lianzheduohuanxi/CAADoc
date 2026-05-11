@echo off

set CGMITF_DATA_DIR=

rem Look for the directory

FOR /F %%I IN ("%0") DO set CGMITF_TOOLS_DIR=%%~dpI
if exist "%CGMITF_TOOLS_DIR%\CGMItfProfile.bat" goto after_CGMITF_TOOLS_DIR
FOR /F %%I IN ("CGMItfProfile.bat") DO set CGMITF_TOOLS_DIR=%%~dp$PATH:I
if not exist "%CGMITF_TOOLS_DIR%\CGMItfProfile.bat" ECHO %CGMITF_TOOLS_DIR%\CGMItfProfile.bat can't be found.>&2& SET CGMITF_TOOLS_DIR=& goto :EOF
:after_CGMITF_TOOLS_DIR

if not "%ADL_IMAGE_DOS_DIR%" == "" set CGMITF_WS_DIR=%ADL_IMAGE_DOS_DIR%& goto after_scm

if "%CGMITF_WS_DIR%" == "" echo ERROR: Please set the environment variable CGMITF_WS_DIR with the workspace's directory and run the profile again:& echo set CGMITF_WS_DIR=E:\WS\xxx& echo %CGMITF_TOOLS_DIR%\CGMItfProfile& set CGMITF_TOOLS_DIR=& goto :EOF

:after_scm

if not "%CGMITF_DIFF%" == "" goto after_cgmdiff

if not "%ADL_MERGER%" == "" if exist "%ADL_MERGER%" echo The SCM merger will be used. You can set CGMITF_DIFF if you want to use another diff tool.& goto after_diff

set CGMITF_DIFF=vdiff32

:after_cgmdiff
echo The diff tool is %CGMITF_DIFF%. You can set CGMITF_DIFF with another tool.

if not "%ADL_MERGER%" == "" if exist "%ADL_MERGER%" echo If you unset CGMITF_DIFF, the SCM merger will be used.

:after_diff

cd /d %CGMITF_WS_DIR%
if not "%ERRORLEVEL%" == "0" echo ERROR: Unable to access the workspace's directory %CGMITF_WS_DIR%.>&2 & goto :EOF

set CGMITF_DATA_DIR=%CGMITF_WS_DIR%\ToolsData\CGMItfMigration
if exist "%CGMITF_DATA_DIR%\Tmp" goto after_working_dir
mkdir %CGMITF_DATA_DIR%\Tmp
if not "%ERRORLEVEL%" == "0" echo ERROR: Unable to create the working directory %CGMITF_DATA_DIR%.>&2 & set CGMITF_TOOLS_DIR=& goto :EOF

:after_working_dir
sh "%CGMITF_TOOLS_DIR%\Admin\SetProfileEnv.sh" -dos >%CGMITF_DATA_DIR%\Tmp\set_env.bat
if not "%ERRORLEVEL%" == "0" echo ERROR: Unable to write into the working directory %CGMITF_DATA_DIR%\Tmp.>&2 & set CGMITF_TOOLS_DIR=& goto :EOF
CALL %CGMITF_DATA_DIR%\Tmp\set_env.bat

echo ----------
echo Traces and logs will be stored in %CGMITF_DATA_DIR%
echo ----------
echo Trying to get the runtime environment.
echo ...

del /q %CGMITF_DATA_DIR%\Tmp\mkrun_env.bat >nul 2>&1
CALL mkrun -c "sh %CGMITF_TOOLS_DIR%\Admin\SetMkrunEnv.sh"

if not exist "%CGMITF_DATA_DIR%\Tmp\mkrun_env.bat" echo ERROR: unable to get the mkrun environment.>&2 & set CGMITF_TOOLS_DIR=& goto :EOF

echo mkrun environment OK.

cmd /c "@echo off & CALL %CGMITF_TOOLS_DIR%\Admin\CGMItfMigrateFile.bat -h" >nul
if not "%ERRORLEVEL%" == "0" echo ERROR: CATCGMMigrateToItf.exe can't be found with the mkrun environment. Please verify that the framework GeometricObjects can be found and that it's built.>&2 & set CGMITF_TOOLS_DIR=& goto :EOF

echo ...
echo If you begin a new migration round, don't forget to run CGMItfClean ^<framework...^>
