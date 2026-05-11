
. "$CGMITF_TOOLS_DIR/Admin/CGMItfBase.sh"

unset usage_status

rm -f $TMP/ls_input_1_$$.txt

if [ $# -lt 1 ]
then
  if [ "$1" = "-h" ]
  then
    usage_status="h"
  else
    usage_status="KO"
  fi
else
  while [ $# -gt 0 ]
  do
    OneChar="$1"
    if [ "$OneChar" = "-" ]
    then
      if [ "$1" = "-h" ]
      then
        usage_status="h"
        break # <<<
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
  EOL="
"
  Usage="CGMItfMigrate directory_or_source..."
  Usage="$Usage${EOL}This command migrates the source files in order to use CGM interfaces. Migrated files are saved as xxx.CGMItf_new."

  if [ "$usage_status" = "h" ]
  then
    Out 0 "$Usage"
  else
    Out 5 "$Usage"
  fi
fi

migrate_option=""
PrereqType="Public"

# -> Full paths before changing the current directory
get_full_or_rel_path "$CGMITF_WS_DIR" <$TMP/ls_input_1_$$.txt >$TMP/ls_input_2_$$.txt

if [ ! -s "$TMP/ls_input_2_$$.txt" ]
then
  Out 2 "ERROR: No file or directory to be migrated"
fi

param_file=$ToolsDir/Admin/CGMLetterParam.txt
if [ ! -f "$param_file" ]
then
   Out 1 "ERROR: Unable to find $param_file. Please verify the CGM tools directories."
fi

WsDir=$(printf "%s\n" "$CGMITF_WS_DIR" | sed 's+\\+/+g')

first_migrated=1

keep_file_if_migrated()
{
  rm -f "$WsDir/$file_merge" # -> No more xxx.CGMItf_merge

  if [ ! -s "$WsDir/$file_new" ]
  then
    # The migrated file is empty -> nothing to be migrated
    rm -f "$WsDir/$file_new" # No .CGMItf_new
    return 1 # <<<
  fi

  diff -b "$WsDir/$file0" "$WsDir/$file_new" >nul
  if [ $? -eq 0 ]
  then
    # Pas de différence
    rm -f "$WsDir/$file_new" # No .CGMItf_new
    return 1 # <<<
  fi

  if [ "$first_migrated" = "1" ]
  then
    echo "\n---------------- Migration on $MigrationDate ------------------\n" >>$LogFile
    first_migrated=0
  fi

  printf "%-90s   ->   %s\n" "$file0" "$file_new" >>$LogFile
  return 0
}

migr_IdentityCard_h()
{
  awk '\
    function treat_comp(with_comp, add_comp, comp) \
    {
      if (! with_comp && add_comp)
      {
        if (first)
        {
          printf "\n// CGM Interfaces on '"$MigrationDate"'\n";
          first = 0;
        }
        print "AddPrereqComponent(\"" comp "\", '"$PrereqType"');";
        rc_out = 0; # A framework was added
      }
      return 0;
    }
    BEGIN \
    {
      num_file = 0;
      with_Model = 0;
      with_Operators = 0;
      with_AdvancedOperators = 0;
      with_CDMOperators = 0;
      with_ICMOperators =0;
      add_Model = 0;
      add_Operators = 0;
      add_AdvancedOperators = 0;
      add_CDMOperators = 0;
      add_ICMOperators = 0;

      rc_out = 5; # By default, nothing done
    }
    (FNR == 1) \
    {
      num_file++;
    }
    (num_file == 1) \
    {
      fw_comp_htab[$1] = $2;
    }
    (num_file == 2) \
    {
      fw = $0;
      nb_subst = sub("^[ 	]*AddPrereqComponent[ 	]*\([ 	]*\"", "", fw);
      if (nb_subst == 0)
        print $0; # No AddPrereqComponent...
      else
      {
        sub("\".*", "", fw);
        comp = fw_comp_htab[fw];
        if (comp == "")
        {
          # The framework is not interfaced
          print $0;

          if (! with_Model)
            with_Model = fw == "GMModelInterfaces";
          if (! with_Operators)
            with_Operators = fw == "GMOperatorsInterfaces";
          if (! with_AdvancedOperators)
            with_AdvancedOperators = fw == "GMAdvancedOperatorsInterfaces";
          if (! with_CDMOperators)
            with_CDMOperators = fw == "CDMOperatorsInterfaces";
          if (! with_ICMOperators)
            with_ICMOperators = fw == "ICMOperatorTopInterfaces";
        }
        else
        {
          # The framework is interfaced
          if (! add_Model)
            add_Model = index(comp, "GM_Model") > 0;
          if (! add_Operators)
            add_Operators = index(comp, "GM_Operators") > 0;
          if (! add_AdvancedOperators)
            add_AdvancedOperators = index(comp, "GM_AdvancedOperators") > 0;
          if (! add_CDMOperators)
            add_CDMOperators = index(comp, "CDM_Operators") > 0;
          if (! add_ICMOperators)
            add_ICMOperators = index(comp, "CATIA_ICEM_Topological_Operator_Interfaces") > 0;

          if (index("'"$basic_fw$partial_itf_fw"'", "|" fw "|") > 0)
            # The framework is a basic CGM one or it s a partially interfaced one -> it must be kept
            print $0;
          else
            rc_out = 0; # A framework is removed
        }
      }
    }
    END \
    {
      first = 1;
      treat_comp(with_Model,             add_Model,             "GMModelInterfaces");
      treat_comp(with_Operators,         add_Operators,         "GMOperatorsInterfaces");
      treat_comp(with_AdvancedOperators, add_AdvancedOperators, "GMAdvancedOperatorsInterfaces");
      treat_comp(with_CDMOperators,      add_CDMOperators,      "CDMOperatorsInterfaces");
      treat_comp(with_ICMOperators,      add_ICMOperators,      "ICMOperatorTopInterfaces");

      exit(rc_out);
    }' "$ls_fw_comp" "$WsDir/$file0" >"$WsDir/$file_new"

  if [ $? -eq 5 ]
  then
    rm -f "$WsDir/$file_new"
  else
    keep_file_if_migrated
  fi
}

migrate_file_to_itf()
{
  $ToolsDir/Admin/CGMItfMigrateFile.bat "$param_file" "$WsDir/$file0" $migrate_option >"$WsDir/$file_new"
}

migr_file()
{
  migrate_file_to_itf
  keep_file_if_migrated
}

impacted_fw=""
impact_files=""

migr_impacting_h()
{
  # The variable fw must be set, and set_file_to_migrate must have been called.
  migrate_file_to_itf
  keep_file_if_migrated
  if [ $? -eq 0 ]
  then
    impact_file="$CGMITF_DATA_DIR/impacts.$fw.$MigrationDay.txt"

    echo "$impacted_fw" | fgrep "|$fw|" >nul
    if [ $? -ne 0 ]
    then
      # First time
      echo "\n---------------- Migration on $MigrationDate ------------------\n" >>"$impact_file"
      impact_files="$impact_files
$impact_file"
      impacted_fw="$impacted_fw|$fw|"
    fi
    echo "$WsDir/$file0" >>"$impact_file"
  fi
}

migr_Imakefile_mk()
{
  awk '\
    BEGIN \
    {
      num_file = 0;
      in_LINK_WITH_XXX = 0;
      in_LINK_WITH = 0;
      only_LINK_WITH = 1;
      with_Model = 0;
      with_Operators = 0;
      with_AdvancedOperators = 0;
      add_Model = 0;
      add_Operators = 0;
      add_AdvancedOperators = 0;

      rc_out = 5; # Nothing done by default
    }
    (FNR == 1) \
    {
      num_file++;
    }
    (num_file == 1) \
    {
      fw_comp_htab[$1] = $2;
    }
    (num_file == 2) && ($2 == "MODULE") \
    {
      fw=$1;
      sub("/.*", "", fw);
      mod=$1;
      sub(".*/", "", mod);
      sub("\..*", "", mod);

      fw_mod_htab[mod] = fw;
    }
    (num_file == 3) \
    {
      if (! in_LINK_WITH_XXX)
      {
        if (match($0, "^[ 	]*LINK_WITH[ 	]*=") > 0)
        {
          in_LINK_WITH_XXX = 1;
          in_LINK_WITH = 1;
          
          if (only_LINK_WITH)
          {
            # Aucune définition de variable de LINK n a été trouvée -> l analyse des ajouts
            # peut se limiter au LINK_WITH
            add_Model = 0;
            add_Operators = 0;
            add_AdvancedOperators = 0;
          }
        }
        else if (match($0, "^[ 	]*(LINK_WITH_COMMON|WIZARD_LINK_MODULES)[ 	]*=") > 0)
        {
          in_LINK_WITH_XXX = 1;
          in_LINK_WITH = 0;
          only_LINK_WITH = 0;
        }
      }
      if (! in_LINK_WITH_XXX)
        print $0;
      else
      {
        line = $0;
        
        # Pay attention: in an Imakefile.mk, "\ # Comments" is authorized and "# Comments \" is not.
        comments = "";
        pos_comment = index(line, "#");
        if (pos_comment > 0)
        {
          comments = " " substr(line, pos_comment); # Final comments
          if (pos_comment > 1)
            line = substr(line, 1, pos_comment - 1);
          else
            line = "";
        }
        
        pos_backslash = match(line, "\\\\[ 	]*$");
        if (pos_backslash > 1)
          line = substr(line, 1, pos_backslash - 1);
        else if (pos_backslash == 1)
          line = "";

        gsub("\\\\", "", line); # Useless backslashes are removed

        first = 1;
        indent = line;
        sub("[^ 	].*", "", indent);
        sep = indent;
        nb_fields = split(line, field_array);

        for (cnt1 = 1; cnt1 <= nb_fields; cnt1++)
        {
          mod = field_array[cnt1];
          fw = fw_mod_htab[mod];
          if (fw == "")
          {
            # Not interfaced
            if (mod != "")
            {
              if (! with_Model)
                with_Model = mod == "CATGMModelInterfaces";
              if (! with_Operators)
                with_Operators = mod == "CATGMOperatorsInterfaces";
              if (! with_AdvancedOperators)
                with_AdvancedOperators = mod == "CATGMAdvancedOperatorsInterfaces";
              if (! with_CDMOperators)
                with_CDMOperators = mod == "CATCDMOperatorsInterfaces";
              if (! with_ICMOperators)
                with_ICMOperators = mod == "ICMOperatorTopInterfaces";

              printf(sep mod);
              sep = " ";
              first = 0;
            }
          }
          else
          {
            comp = fw_comp_htab[fw];

            if (! add_Model)
              add_Model = index(comp, "GM_Model") > 0;
            if (! add_Operators)
              add_Operators = index(comp, "GM_Operators") > 0;
            if (! add_AdvancedOperators)
              add_AdvancedOperators = index(comp, "GM_AdvancedOperators") > 0;
            if (! add_CDMOperators)
              add_CDMOperators = index(comp, "CDM_Operators") > 0;
            if (! add_ICMOperators)
              add_ICMOperators = index(comp, "CATIA_ICEM_Topological_Operator_Interfaces") > 0;

            rc_out = 0; # A module is removed
          }
        } # End of the loop of fields
        if (pos_backslash > 0)
        {
          if (! first)
            # Something was written
            printf(" \\%s\n", comments);
        }
        else
        {
          # No more backslash
          itf_mod = "";

          if (in_LINK_WITH)
          {
            sep = indent;
            if (sep == "")
              sep = "  ";
              
            if (add_Model && ! with_Model)
            {
              itf_mod = sep "CATGMModelInterfaces";
              sep = " ";
            }
            if (add_Operators && ! with_Operators)
            {
              itf_mod = itf_mod sep "CATGMOperatorsInterfaces";
              sep = " ";
            }
            if (add_AdvancedOperators && ! with_AdvancedOperators)
            {
              itf_mod = itf_mod sep "CATGMAdvancedOperatorsInterfaces";
              sep = " ";
            }
            if (add_CDMOperators && ! with_CDMOperators)
            {
              itf_mod = itf_mod sep "CATCDMOperatorsInterfaces";
              sep = " ";
            }
            if (add_ICMOperators && ! with_ICMOperators)
              itf_mod = itf_mod sep "ICMOperatorTopInterfaces";
          }

          if (itf_mod != "")
          {
            if (! first)
              printf(" \\%s\n%s", comments, itf_mod);
            else
              print itf_mod comments;

            rc_out = 0; # A module is added
          }
          else # Tant pis pour la ligne vide... if (! first)
            printf("%s\n", comments);

          in_LINK_WITH = 0;
          in_LINK_WITH_XXX = 0;
        }
      }
    }
    END \
    {
      exit(rc_out);
    }' "$ls_fw_comp" "$ls_fw_mod" "$WsDir/$file0" >"$WsDir/$file_new"

  if [ $? -eq 5 ]
  then
    # Nothing done
    rm -f "$WsDir/$file_new"
  else
    keep_file_if_migrated
  fi
}

migr_mod_itf()
{
  # Headers in the module

  cd $WsDir/$fw/$mod/LocalInterfaces 2>nul
  if [ $? -eq 0 ]
  then
    for h in *.h*
    do
      if [ "$h" = "*.h*" ]
      then
        break # <<<<<<
      fi

      set_file_to_migrate $fw/$mod/LocalInterfaces/$h
      if [ $? -eq 0 ]
      then
        migrate_file_to_itf
        keep_file_if_migrated
      fi
    done # End of the loop of .h
  fi
}

migr_mod_src()
{
  # Sources in the module

  cd $WsDir/$fw/$mod/src 2>nul
  if [ $? -eq 0 ]
  then
    for source in *.cpp *.h*
    do
      if [ "$source" = "*.cpp" -o "$source" = "*.h*" ]
      then
        break # <<<<<<
      fi

      set_file_to_migrate $fw/$mod/src/$source
      if [ $? -eq 0 ]
      then
        migrate_file_to_itf
        keep_file_if_migrated
      fi
    done # End of the loop of sources
  fi # End of if the src can be reached
}

migr_module()
{
  cd $WsDir/$fw/$mod 2>nul
  if [ $? -ne 0 ]
  then
    continue # <<<
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

migr_fw_itf()
{
  cd $WsDir/$fw/$fw_itf 2>nul
  if [ $? -eq 0 ]
  then
    echo "$fw/$fw_itf"
    for h in *.h*
    do
      if [ "$h" = "*.h*" ]
      then
        break # <<<<<<
      fi

      set_file_to_migrate $fw/$fw_itf/$h
      if [ $? -eq 0 ]
      then
        migr_impacting_h
      fi
    done # End of the loop of .h
  fi
}

migr_fw()
{
  cd "$WsDir/$fw" 2>nul
  if [ $? -ne 0 ]
  then
    printf "cd $WsDir/$fw failed\n" >&2
    continue # <<<
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
    if [ "$mod" = "*.m" ]
    then
      break # <<<<<<
    fi

    migr_module
  done # End of the loop of modules
}

# Get the couples frameworks/components

. "$ToolsDir/Admin/Init_fw_var.sh"

ls_fw_comp="$TMP/ls_fw_comp_$$.txt"

. "$ToolsDir/Admin/Gen_ls_fw_comp.sh"



ls_fw_mod="$ToolsDir/Admin/ls_fw_mod.txt"

# Loop of the input paths

MigrationDate=$(date +%Y/%m/%d-%H:%M:%S)

while read input_path
do
  analyze_input_path
  if [ $? -eq 0 ]
  then
    clean_input_path
    migr_input_path
  fi
done < $TMP/ls_input_2_$$.txt # End of the loop of input paths

echo "---------------------"
if [ "$first_migrated" = "0" ]
then
  echo "Files have been migrated: xxx -> xxx.CGMItf_new"
  printf "See the log "
  printf "%s\n" "$LogFile" | get_full_or_rel_path

  if [ "$impact_files" != "" ]
  then
    echo
    echo "Impacting headers have been migrated. See the following files:"
    printf "%s\n" $impact_files | get_full_or_rel_path
  fi
  echo
  echo "Run CGMItfMerge in order to get the migrated source."

else
  echo "Nothing to do."
fi

Out 0
