@echo off
SETLOCAL

CALL %CGMITF_DATA_DIR%\Tmp\mkrun_env.bat
CATCGMMigrateToItf %*

ENDLOCAL
