awk '\
  BEGIN \
  {
    in_fw = 0;
  }
  /^\[/ \
  {
    if ($1 == "[framework]")
      in_fw = 1;
    else if (in_fw)
      exit; # <<<<<
  }
  ! /^\[/ && (in_fw) \
  {
    fw = $1;
    sub("//.*", "", fw);
    if (fw != "")
      print $1 " " $3;
  }' "$param_file" >"$ls_fw_comp"
