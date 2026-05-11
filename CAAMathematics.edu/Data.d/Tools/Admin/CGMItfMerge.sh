. "$CGMITF_TOOLS_DIR/Admin/CGMItfBase.sh"

unset usage_status
replace_all=0

rm -f $TMP/ls_input_1_$$.txt

if [ $# -lt 1 ]
then
  usage_status="KO"
else
  while [ ! -z "$1" ]
  do
    OneChar="$1"
    if [ "$OneChar" = "-" ]
    then
      if [ "$1" = "-h" ]
      then
        usage_status="h"
        break # <<<
      elif [ "$1" = "-replace_all" ]
      then
        replace_all=1
      else
        echo "ERROR: The option \"$1\" is not managed." >&2
        usage_status="KO"
        break # <<<
      fi
    else
      # The argument is not an option
      printf "%s\n" "$1" >>$TMP/ls_input_1_$$.txt
    fi
    shift
  done
fi

if [ ! -z "$usage_status" -o ! -s "$TMP/ls_input_1_$$.txt" ]
then
  Usage="CGMItfMerge [-replace_all] directory_or_source...
-replace_all: migrated sources replace sources without any user interaction
This command merges the migrates sources with the origin ones.
For each migrated file xxx.CGMItf_new:
  xxx -> xxx.CGMItf_save
  xxx.CGMItf_new -> xxx
If you run the command within a SCM environment, the graphic merger tool is used."

  if [ "$usage_status" = "h" ]
  then
    Out 0 "$Usage"
  else
    Out 5 "$Usage"
  fi
fi

unset with_merger
if [ "$replace_all" = "0" ]
then
  if [ ! -z "$CGMITF_DIFF" ] && whence "$CGMITF_DIFF" >nul 2>nul
  then
    with_merger=0
  elif [ ! -z "$ADL_MERGER" ] && whence "$ADL_MERGER" >nul 2>nul
  then
    with_merger=1
  else
    Out 2 "ERROR: Neither merger tool nor diff tool. Set CGMITF_DIFF with a valid diff tool."
  fi
fi

# -> Full paths before changing the current directory
get_full_or_rel_path "$CGMITF_WS_DIR" <$TMP/ls_input_1_$$.txt >$TMP/ls_input_2_$$.txt

if [ ! -s "$TMP/ls_input_2_$$.txt" ]
then
  Out 2 "ERROR: No file or directory to consider."
fi

param_file=$ToolsDir/Admin/CGMLetterParam.txt
if [ ! -f "$param_file" ]
then
   Out 1 "ERROR: Unable to find $param_file. Please verify the CGM tools directories."
fi

WsDir=$(printf "%s\n" "$CGMITF_WS_DIR" | sed 's+\\+/+g')

first_merged=1

with_co=0
whence adl_co >nul
if [ $? -eq 0 ]
then
  with_co=1
fi

mv_merged_to_do=0

typeset -l response

merge_files()
{
  if [ "$first_merged" = "1" ]
  then
    echo "\n---------------- Merge on $MigrationDate ------------------\n" >>$LogFile
    first_merged=0
  fi

  if [ "$replace_all" = "1" ]
  then
    # Replace all
    cp -f "$WsDir/$file_new" "$WsDir/$file_merge"

  elif [ "$with_merger" = "1" ]
  then
    # Use the SCM merger
    merger_option=""
    if [ -f "$WsDir/$file_save" ]
    then
      merger_option="-anc $WsDir/$file_save"
    fi

    echo
    echo "==========================================================================="
    echo "Merging $file0 before and after migration"
    echo
    echo "<<<<< Current = Original source         Conflicting = Migrated source >>>>>"
    echo

    rm -f $WsDir/$file_merge
    $ADL_MERGER "$WsDir/$file0" "$WsDir/$file_new" $merger_option -out "$WsDir/$file_merge"
    if [ $? -ne 0 ]
    then
      echo "ERROR: Merging failed"
      echo "ERROR: Manual merging $file0 failed" >>$LogFile
      rm -f "$WsDir/$file_merge"
      
      echo
      response=""
      while [ "$response" != "y" ]
      do
        printf "Do you want to continue with the next source? Y(es)/N(o) "
        read response
        if [ $? -ne 0 ]
        then
          response="n" # No input
        fi
        if [ "$response" = "n"  ]
        then
          Out 0 "Cancelled"
        fi
      done
      echo
      
      return 1 # <<<<<<<<<<
    fi
  else
    # Use the diff tool
    echo
    echo "==========================================================================="
    echo "Comparing $file0 before and after migration"
    echo
    echo "<<<<< Original source                                 Migrated source >>>>>"
    echo
    rm -f $WsDir/$file_merge
    "$CGMITF_DIFF" "$WsDir/$file0" "$WsDir/$file_new"
    
    echo
    response=""
    while [ "$response" != "y" ]
    do
      printf "Do you want to get the migrated source? Y(es)/N(o)/Q(uit) "
      read response
      if [ $? -ne 0 ]
      then
        response="q" # No input
      fi
      if [ "$response" = "n" -o "$response" = "q" ]
      then
        echo "REFUSED: $file0" >>$LogFile
        if [ "$response" = "q" ]
        then
          Out 0 "Cancelled"
        fi
        echo
        return 1 # <<<<<<<<<<
      fi
    done
    echo
    
    cp -f "$WsDir/$file_new" "$WsDir/$file_merge"
  fi
  
  cmp -s "$WsDir/$file0" "$WsDir/$file_merge" >nul
  if [ $? -eq 0 ]
  then
    # The user choosed the whole original file
    cp -f "$WsDir/$file0" "$WsDir/$file_save"
    rm -f "$WsDir/$file_merge"
    rm -f "$WsDir/$file_new"
    
    printf "Keeping %s as is\n" "$file0" >>$LogFile
  else
    if [ ! -w "$WsDir/$file0" -a "$with_co" = "1" ]
    then
      echo "adl_co $WsDir/$file0"
      adl_co "$WsDir/$file0"
      if [ -w "$WsDir/$file0" ]
      then
        echo "adl_co $file0 -> successful" >>$LogFile
      else
        echo "adl_co $file0 -> failure" >>$LogFile
        
        echo "adl_mk_priv $WsDir/$file0"
        adl_mk_priv "$WsDir/$file0"
        if [ -w "$WsDir/$file0" ]
        then
          echo "adl_mk_priv $file0 -> successful" >>$LogFile
        else
          echo "adl_mk_priv $file0 -> failure" >>$LogFile
        
          echo
          response=""
          while [ "$response" != "y" ]
          do
            printf "Do you want to continue with the next source? Y(es)/N(o) "
            read response
            if [ $? -ne 0 ]
            then
              response="n" # No input
            fi
            if [ "$response" = "n"  ]
            then
              Out 0 "Cancelled"
            fi
          done
          echo
        fi
      fi
    fi

    if [ -w "$WsDir/$file0" ]
    then
      # The origin file can be replaced
      mv -f "$WsDir/$file0" "$WsDir/$file_save"
      mv -f "$WsDir/$file_merge" "$WsDir/$file0"
      rm -f "$WsDir/$file_new"

      printf "Replacing %s\n" "$file0" >>$LogFile
    else
      # The origin file can't be replaced
      printf "WARNING: %s is read-only: you'll have to replace it with %s.\n\n" "$file0" "$file_merge"
      printf "### MOVE TO DO: %-90s\n" "$file_merge" >>$LogFile
      mv_merged_to_do=1
    fi
  fi
}

migr_IdentityCard_h()
{
  if [ -f "$WsDir/$file_new" ]
  then
    merge_files
  fi
}

migr_impacting_h()
{
  if [ -f "$WsDir/$file_new" ]
  then
    merge_files
  fi
}

migr_Imakefile_mk()
{
  if [ -f "$WsDir/$file_new" ]
  then
    merge_files
  fi
}

migr_source_dir()
{
  cd $WsDir/$source_dir 2>nul
  if [ $? -eq 0 ]
  then
    for source_new in *.CGMItf_new
    do
      if [ "$source_new" = "*.CGMItf_new" ]
      then
        break # <<<<<<
      fi

      source=${source_new%.CGMItf_new}
      set_file_to_migrate $source_dir/$source
      if [ $? -ne 0 ]
      then
        echo "ERROR: a migrated source $source_new exists but no matching source $source exists."
      else
        merge_files
      fi
    done # End of the loop of sources
  fi
}

migr_mod_itf()
{
  # Headers in the module
  source_dir=$fw/$mod/LocalInterfaces
  migr_source_dir
}

migr_mod_src()
{
  # Sources in the module
  source_dir=$fw/$mod/src
  migr_source_dir
}

migr_fw_itf()
{
  source_dir=$fw/$fw_itf
  migr_source_dir
}

migr_file()
{
  if [ -f "$WsDir/$file_new" ]
  then
    merge_files
  fi
}

# Loop of the input paths

MigrationDate=$(date +%Y/%m/%d-%H:%M:%S)

for input_path in $(<$TMP/ls_input_2_$$.txt)
do
  analyze_input_path
  if [ $? -eq 0 ]
  then
    migr_input_path
  fi
done # End of the loop of input paths

echo "---------------------"
if [ "$first_merged" = "0" ]
then
  echo "Files have been merged: xxx.CGMItf_new -> xxx"
  if [ "$mv_merged_to_do" = "1" ]
  then
    echo
    echo "WARNING: All the migrated files can't be moved. Some are renamed xxx.CGMItf_merge. You should move them as xxx."
  fi
  printf "See the log "
  printf "%s\n" "$LogFile" | get_full_or_rel_path
  echo
  echo "You should keep the files xxx.CGMItf_save for the next time: they will ease merging."
else
  echo "Nothing to do."
fi

Out 0
