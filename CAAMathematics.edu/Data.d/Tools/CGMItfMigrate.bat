@echo OFF

if "%CGMITF_TOOLS_DIR%" == "" echo ERROR: You must run the profile CGMItfProfile.bat>&2 & goto :EOF

sh %CGMITF_TOOLS_DIR%/Admin/CGMItfMigrate.sh %*
