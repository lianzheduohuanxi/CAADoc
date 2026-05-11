#!/bin/ksh
# Set the variable CGMItf_DEBUG in order to keep the temporary files in <Ws>/ToolsData/CGMItfMigration/Tmp.
# For example, you may regenerate ls_fw_mod.txt in order to deliver it
# in CGMInterfaces.tst\Data.d\Tools\Admin.

TMP=$(printf "%s\n" "$CGMITF_DATA_DIR/Tmp" | sed 's+\\+/+g')

# =====================================================================
# Out function
# =====================================================================

unset OutCompCall # Pour exécuter quelque chose en sortie

Out()
{
  trap ' ' HUP INT QUIT TERM
  ExitCode=$1
  shift
  if [ $# -ge 1 ]
  then
    if [ $ExitCode -eq 0 ]
    then
      printf "%s\n\n" "$*"
    else
      printf "%s\n\n" "$*" >&2
    fi
    echo
  fi
  [ $ExitCode -ne 0 ] && echo "##### THE COMMAND ENTIRELY OR PARTIALLY FAILED #####" >&2

  $OutCompCall
  [ -z "$CGMItf_DEBUG" ] && \rm -fr "$TMP"/*_$$.*

  exit $ExitCode
}

trap 'Out 9999 "Command interrupted" ' HUP INT QUIT TERM

ToolsDir=$(printf "%s\n" "$CGMITF_TOOLS_DIR" | sed 's+\\+/+g')

whence adl_co >nul
if [ $? -eq 0 ]
then
  with_scm=1
else
  with_scm=0
fi

# =====================================================================
# Options treatment
# =====================================================================
typeset -L1 OneChar
CheckOptArg()
{
  # Usage : CheckOptArg opt arg
  OneChar="$2"
  if [ "$2" = "" -o "$OneChar" = "-" ]
  then
    Out 5 "The option $1 requires an argument."
  fi
}

# =====================================================================
# MKS ?
# =====================================================================
sh_is_mks=1
p1=$(which mksinfo.exe 2>nul)
if [ -z "$p1" ]
then
  sh_is_mks=0 # Ouf, pas MKS
else
  p2=$(which sh.exe 2>nul)
  if [ ${p1%/*} != ${p2%/*} ]
  then
    sh_is_mks=0
  fi
fi

# =====================================================================
# file0...
# =====================================================================
set_file_to_migrate()
{
  if [ ! -f "$WsDir/$1" ]
  then
    return 1
  fi
  file0="$1" # The file to be migrated
  file_new="$1.CGMItf_new"
  file_save="$1.CGMItf_save"
  file_merge="$1.CGMItf_merge"
}

# =====================================================================
# Get the full or relative path
# =====================================================================
get_full_or_rel_path()
{
  cscript /NoLogo $CGMITF_TOOLS_DIR\\Admin\\GetFullOrRelPath.vbs "$@" | sed 's+\\+/+g'
}

# =====================================================================
# Log
# =====================================================================
MigrationDay=$(date +%Y_%m_%d) # One log per day
LogFile="$CGMITF_DATA_DIR/Log_$MigrationDay.txt"

# =====================================================================
# Analyze the input path
# =====================================================================
analyze_input_path()
{
  cd "$WsDir" 2>nul

  remainder="$input_path/"
  fw=${remainder%%/*}
  fw_idc=0
  fw_itf=""
  mod=""
  if [ ! -d "$fw" ]
  then
    echo "ERROR: $input_path is not under a valid framework" >&2
    return 1 # <<<<
  fi

  remainder=${remainder#*/}
  piece2=${remainder%%/*}
  remainder=${remainder#*/}
  piece3=${remainder%%/*}
  remainder=${remainder#*/}

  if [ "$piece2" = "IdentityCard" ]
  then
    fw_idc=1
  elif [ "${piece2%Interfaces}" != "$piece2" ]
  then
    fw_itf="$piece2"
  elif [ "${piece2%.m}" != "$piece2" ]
  then
    mod="$piece2"
  fi
  
  return 0
}

# =====================================================================
# Cleans *.CGMItf_new
# =====================================================================
clean_input_path()
{
  if [ -f "$WsDir/$input_path" -o -d "$WsDir/$input_path" ]
  then
    # Removing *.CGMItf_new
    find "$WsDir/$input_path" -name "*.CGMItf_new" -exec rm -f {} \;
  fi
}

# =====================================================================
# Migrate the file or the ones contained in the directory
# =====================================================================
migr_input_path()
{
  if [ -z "$piece2" ]
  then
    # Migrate the whole framework
    migr_fw
    return 0 # <<<<
  fi

  if [ -z "$piece3" ]
  then
    if [ "$fw_idc" = "1" ]
    then
      # Migrate IdentityCard.h
      set_file_to_migrate "$fw/IdentityCard/IdentityCard.h"
      if [ $? -eq 0 ]
      then
        migr_IdentityCard_h
      fi
    elif [ ! -z "$fw_itf" ]
    then
      # Migrate fw/xxxInterfaces
      migr_fw_itf
    elif [ ! -z "$mod" ]
    then
      # Migrate the whole module
      migr_module
    else
      echo "ERROR: Unable to find what to be migrated for $input_path" >&2
      return 1 # <<<<
    fi
    return 0 # <<<<
  fi

  set_file_to_migrate "$input_path" 2>nul
  if [ $? -eq 0 ]
  then
    # Migrate the specified file
    if [ "$piece3" = "Imakefile.mk" ]
    then
      migr_Imakefile_mk
    else
      migr_file
    fi
    return 0 # <<<<
  fi

  if [ ! -d "$input_path" ]
  then
    echo "ERROR: $input_path is neither a file nor a directory" >&2
    return 1 # <<<<
  fi

  if [ ! -z "$mod" ]
  then
    if [ "$piece3" = "LocalInterfaces" ]
    then
      migr_mod_itf
      return 0 # <<<<
    elif [ "$piece3" = "src" ]
    then
      migr_mod_src
      return 0 # <<<<
    fi
  fi

  echo "WARNING: the directory $input_path is not managed" >&2
}

# =====================================================================
# Migrate the module
# =====================================================================
migr_module()
{
  cd $WsDir/$fw/$mod 2>nul
  if [ $? -ne 0 ]
  then
    return 1 # <<<
  fi

  echo "$fw/$mod"

  # Imakefile.mk
  set_file_to_migrate $fw/$mod/Imakefile.mk
  if [ $? -eq 0 ]
  then
    migr_Imakefile_mk
  fi

  # LocalInterfaces
  migr_mod_itf

  # src
  migr_mod_src
}

# =====================================================================
# Migrate the framework
# =====================================================================
migr_fw()
{
  cd "$WsDir/$fw" 2>nul
  if [ $? -ne 0 ]
  then
    printf "cd $WsDir/$fw failed\n" >&2
    return 1 # <<<
  fi

  impacted_fw=0

  # IdentityCard.h

  itf_mod=""

  set_file_to_migrate $fw/IdentityCard/IdentityCard.h # -> file0 ... file_save
  if [ $? -eq 0 ]
  then
    migr_IdentityCard_h
  fi

  # Headers directly in the framework

  for fw_itf in PublicInterfaces ProtectedInterfaces PrivateInterfaces
  do
    migr_fw_itf
  done

  cd $WsDir/$fw
  if [ $? -ne 0 ]
  then
    Out 1 "ERROR: cd $WsDir/$fw failed."
  fi

  # Loop of the modules

  for mod in *.m
  do
    migr_module
  done # End of the loop of modules
}
