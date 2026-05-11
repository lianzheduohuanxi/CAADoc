# Find and remove xxx.CGMItf_new

. "$CGMITF_TOOLS_DIR/Admin/CGMItfBase.sh"

unset usage_status
if [ $# -eq 0 ]
then
  usage_status="KO"
elif [ "$1" = "-h" -o "$1" = "/?" ]
then
  usage_status="h"
fi
if [ ! -z "$usage_status" ]
then
  Usage="CGMItfClean directory...
This command deletes all the files xxx.CGMItf_new that are remaining after a previous migration."
  if [ "$usage_status" = "h" ]
  then
    Out 0 "$Usage"
  else
    Out 5 "$Usage"
  fi
fi

cd "$CGMITF_WS_DIR" || Out 2 "ERROR: unable to set the current directory to $CGMITF_WS_DIR"

while [ ! -z "$1" ]
do
  printf "Cleaning %s\n" "$1"
  find "$1" -name "*.CGMItf_new" -exec rm -f {} \;

  shift
done

Out 0
