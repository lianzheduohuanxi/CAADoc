whence CATCGMMigrateToItf >nul
if [ $? -ne 0 ]
then
  echo "ERROR: the executable CATCGMMigrateToItf can't be found." >&2
  echo "Set the workspace's runtime concatenation with mkGetPreq." >&2
else
  {
    printf "set PATH=%s\n" "$PATH"
    echo "set CATTraDecDir=NUL"
    echo "set CATICPath="
    printf "set CATDictionaryPath=%s\n" "$CATDictionaryPath"
    printf "set CATMsgCatalogPath=%s\n" "$CATMsgCatalogPath"
    echo "set CATUserSettingPath=NUL"
  } >$CGMITF_DATA_DIR/Tmp/mkrun_env.bat
fi
