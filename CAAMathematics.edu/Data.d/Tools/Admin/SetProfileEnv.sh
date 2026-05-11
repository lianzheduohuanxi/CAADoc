tools_dir=$(printf "%s\n" "$CGMITF_TOOLS_DIR" | sed 's+\\+/+g')
cleaned_path=$(printf "%s\n" "$PATH" | sed 's+'"$tools_dir"';++g')

printf "set PATH=%s\n" "$tools_dir;$cleaned_path"

printf "set CGMITF_WS_DIR="
printf "%s\n" "$CGMITF_WS_DIR" | cscript /nologo "$CGMITF_TOOLS_DIR/Admin/GetFullOrRelPath.vbs"
