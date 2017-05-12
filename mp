#!/bin/bash
#---------------------------------------------------------------------
#
#  [Description]
#    Makeplate help tool. This file is not part of the template itself
#    and should be erased when creating a new project based on this
#    template.
#
#  [Author] 
#    Peter Malmberg <peter.malmberg@gmail.com>
#
#  [Licence] 
#     MIT
#    
#---------------------------------------------------------------------
#

# Display commands as they are executed
#set -o xtrace
# Display shell input lines as they are read
#set -v

# Exit script when a command fails. Append ||true if error is expected
set -o errexit # || true
# Exit script when undeclared variable is used
#set -o nounset
# Exit script when pipe fails
set -o pipefail

# Directory where script is located
scriptPath=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

# Name of script
scriptName=$(basename "$0")

#---------------------------------------------------------------------
# User defined Settings
#---------------------------------------------------------------------

MPT_DIR=makeplate_files
MPT_INSTALL_DIR=~/bin/${MPT_DIR}

# Check if MPT file exists
if [ -e ${scriptPath}/MPT ]; then
  MPT=1
else
  NEW=1
fi

# Local install directory
MP_LOCALDIR=~/bin

# system wide install directory
MP_SYSDIR=/usr/local/bin

# Settings directory
MP_CONFIG_DIR=~/.config/makeplates

MP_3DPARTY_DIR=${scriptPath}/3dparty

#---------------------------------------------------------------------
# User defined functions
#---------------------------------------------------------------------

# Install single makeplate
#
# arg1 source directory 
# arg2 destination directory
# arg3 makeplate
#
installMp() {

  # First remove all possible object files etc.
  cd ${1}/${3}
  make clean
	rm -rf backup
	rm -rf archive
  cd -
	
  # Copy makeplate
  mkdir -p ${2}
  cp -rf ${1}/${3}  ${2}/.
	

  # Check if tools link exists	
  if [ -L ${2}/${3}/tools ]; then 
  
    # Remove symbolic link
    rm -f ${2}/${3}/tools
	
    # Copy tools to project
    cp -rf ${2}/tools ${2}/${3}/.
  fi
}

# Create a directory if it does not exist
mpCreateDir() {
 if [ ! -d $1 ]; then
		 mkdir -p $1
	fi
}

mpConfigDir() { ## testing
  mpCreateDir ${MP_CONFIG_DIR}
#	mpCreateDir ${MP_CONFIG_DIR}/3r
#	mpCreateDir ${MP_CONFIG_DIR}
}



#
# arg1 install dir
# arg2 symbolic link dir
#
mpInstall() {

  # Create dir
  mkdir -p ${1}
	
  cp -rf ${scriptPath}/mp      ${1}/.
  cp -rf ${scriptPath}/tools   ${1}/.
	cp -rf ${scriptPath}/3dparty ${1}/.

  # Install makeplates
  installMp ${scriptPath}  ${1}  mp-c 
  installMp ${scriptPath}  ${1}  mp-cpp
  installMp ${scriptPath}  ${1}  mp-simple-c
  installMp ${scriptPath}  ${1}  mp-simple-cpp
	
 	
  # Create symlink
  ln -s ${1}/mp ${2}
  rm -f ${1}/MPT
}


install() { #C MPT Install makeplates on system
  assertRoot
  echo -e "Installing makeplates"
  rm -rf ${MP_SYSDIR}/${MPT_DIR}
  rm -rf ${MP_SYSDIR}/mp	
  mpInstall /usr/local/bin/makeplate_files  /usr/local/bin/
}

install-local() { ##C MPT Install makeplates localy for easy creating new projects
  echo -e "Installing makeplates locally"
  rm -rf ${MP_LOCALDIR}/${MPT_DIR}
  rm -rf ${MP_LOCALDIR}/mp
  mpInstall ~/bin/makeplate_files  ~/bin/
}

clean() { ##C MPT Clean out old files
  find . -name "*~"     -delete
  find . -name "*.orig" -delete
}

installPlate() {
  rm -rf ${1}/*
  cp -rf ${1}/* .
}



#
# Ask yes/no question
#
# arg1 question text
# arg2 result variable name
#
bpQuestionDy() {  ##D Ask yes/no question default yes 
  local __result=$2
  while true; do
	  read -p "${1}"" [Y/n]>" yn
    case $yn in
	    [Yy]* ) eval $__result='y'; break;;
			[Nn]* ) eval $__result='n'; break;;
			""    ) eval $__result='y'; break;;
			* ) echo "Please answer yes or no.";;
		esac
	done 	
}


createProject() {
  echo -e ${1}
	read -p "Project name>" pn
	bpQuestionDy "Create subdirectory?" res
	if [ ${res} == 'y' ]; then
	  echo "Creating directory"
		mkdir -p ${pn}
		cp -rf ${2}/* ${pn}/.
	else
		cp -rf ${2}/* .
	fi
	
}


##N- Kalle

##C- NEW

newC() { ##C NEW Create a new standard C makeplate project
  createProject "Creating new makeplate C project" ${scriptPath}/${MPT_DIR}/mp-c 
}

newCpp() { ##C NEW Create a new standard C++ makeplate project
  createProject  "Creating new makeplate C++ project" ${scriptPath}/${MPT_DIR}/mp-cpp
}

newSC() { ##C NEW Create a new simple C makeplate project
  createProject "Creating new simple makeplate C project"  ${scriptPath}/${MPT_DIR}/mp-simple-c
}

newSCpp() { ##C NEW Create a new simple C++ makeplate project
  createProject "Creating new simple makeplate C++ project" ${scriptPath}/${MPT_DIR}/mp-simple-cpp
}

newModule() { ##C NEW Create new C module
  ${scriptPath}/tools/ctemplate.py
}


list() {  ##C NEW List 3d party libraries
  ls -1 3dparty
}

eInstall() { ##C NEW Install 3d party library
  if [ -d ${MP_3DPARTY_DIR}/${2} ]; then
	  cp -rf ${MP_3DPARTY_DIR}/${2} .
		bpOk "Module \"${2}\" installed"
	else
	  bpError "Module \"${2}\" does not exist"
	fi
}


#--------------------------------------------------------------------- 
# Bashplate settings
#---------------------------------------------------------------------

# Script version info
VERSION="1.00"

##V Bashplate version
BPVERSION="1.10"   

##V Usage info
USAGE="Usage: ${scriptName} command [option]" 

# Description text
DESC="Help tool for makeplate project"

##V logfile (uncomment to use logfile)
#LOGFILE=${scriptPath}/${scriptName}.log

##V Default command (uncomment to use a default command )
DEFAULT=help

##V Programs that are required to run the script (uncomment to use)
#REQUIRED_PROGRAMS=(ls mv kalle)

##V Lock file (uncomment to use lock file feature )
#LOCK_FILE=/tmp/${scriptName}.lock

#--------------------------------------------------------------------- 
# Signal traps
#---------------------------------------------------------------------

signalInt() {
  bpCleanUp
  exit "$EX_OK"
}

signalHup() {
  bpCleanUp
}

signalQuit() {
  echo "Quit"
  bpCleanUp
}

signalTerm() {
  echo "Term"
  bpCleanUp
}

bpCleanUp() { ##D Cleanup function 
  rm -f "$LOCK_FILE"    # remove Lock file
}

bpExit() { ##D Function for safely exiting script
  bpCleanUp
  exit
}

bpErrorExit() {  ##D Safely exit script with a error 
  echo -e "${E_ERROR}${1}${E_END}"
  bpCleanUp
  exit
}

#--------------------------------------------------------------------- 
# System functions and settings
#---------------------------------------------------------------------

# ANSI foreground colors codes
#

E_BLACK='\e[0;30m'        # Black 
E_RED='\e[0;31m'          # Red
E_GREEN='\e[0;32m'        # Green
E_YELLOW='\e[0;33m'       # Yellow
E_BLUE='\e[0;34m'         # Blue
E_MAGENTA='\e[0;35m'      # Magenta
E_CYAN='\e[0;36m'         # Cyan
E_GRAY='\e[0;37m'         # Gray
E_DARKGRAY='\e[1;30m'     # Dark Gray
E_BR_RED='\e[1;31m'       # Bright Red
E_BR_GREEN='\e[1;32m'     # Bright Green
E_BR_YELLOW='\e[1;33m'    # Bright Yellow
E_BR_BLUE='\e[1;34m'      # Bright Blue
E_BR_MAGENTA='\e[1;35m'   # Bright Magenta
E_BR_CYAN='\e[1;36m'      # Bright Cyan
E_WHITE='\e[1;37m'        # White

# ANSI background color codes
#
E_ON_BLACK='\e[40m'       # Black
E_ON_RED='\e[41m'         # Red
E_ON_GREEN='\e[42m'       # Green
E_ON_YELLOW='\e[43m'      # Yellow
E_ON_BLUE='\e[44m'        # Blue
E_ON_MAGENTA='\e[45m'     # Magenta
E_ON_CYAN='\e[46m'        # Cyan
E_ON_WHITE='\e[47m'       # White

# ANSI Text attributes
E_ATTR_BOLD='\e[1m'
E_ATTR_LOWI='\e[2m' 
E_ATTR_UNDERLINE='\e[4m'
E_ATTR_BLINK='\e[5m'
E_ATTR_REVERSE='\e[7m'

# ANSI cursor operations
#
E_RETURN="\e[F"           # Move cursor to begining of line
E_UP="\e[A"               # Move cursor one line up
E_DOWN="\e[B"             # Move cursor one line down
E_FORWARD="\e[C"          # Move cursor forward
E_BACK="\e[D"             # Move cursor backward
E_HIDE="\e[?25l"          # Hide cursor 
E_SHOW="\e[?25h"          # Show cursor 

E_END="\e[m"              # Clear Attributes

# Message colors
E_OK=$E_BR_GREEN
E_INFO=$E_BR_CYAN
E_WARNING=$E_BR_YELLOW
E_ERROR=$E_BR_RED
E_CRITICAL=$E_ON_RED$E_WHITE
C_LINE=$E_GREEN
C_LINE_TEXT=$E_BR_GREEN

# Exit codes 
#
EX_OK=0            # successful termination 

##-

# Print text with row
#
# arg1 text to be printed
# arg2 text color
# arg3 line color
# arg4 middle character
# arg5 line character
bpPrintLineC() { ##D Print text with adjusted line after with selectable colors
  len1=${#1}
	len4=${#4}
	
	echo -en ${2}${1}${4}${3}
	l=$((${COLUMNS} - ${len1} - ${len4} - 3 ))
	seq -s${5} ${l}|tr -d '[:digit:]'
	echo -en ${E_END} 
}

# Print text with row
#
# arg1 text to be printed
# arg2 text color
# arg3 line color
bpTextLineC() { ##D Print text with adjusted line after with selectable colors
  bpPrintLineC $1 $2 $3 " " "-"
	return
}


# Print a divider row
printLine() { ##D Print a line  
	bpPrintLineC "" "${E_GRAY}" "${E_GRAY}" "" "-" 
}


bpTextLine() { ##D Print text with adjusted line after
  bpTextLineC "$1" "${C_LINE_TEXT}" "${C_LINE}"
}

# Print text into two columns
#
# arg1 text for column 1
# arg2 text for column 2
printInfo() {  
  printf "${E_BR_CYAN}%-20s${E_END} ${E_BR_GREEN}%s${E_END}\n" "$1" "$2"
}

# Print a variable + text into two columns
#
# arg1 variable for column 1
# arg2 text for column 2
printVar() {
  var="$1"
  if [ "${!var}" ]; then
    printInfo "$2" "${!var}"
  else 
    printf "${E_BR_CYAN}%-20s${E_END} ${E_BR_RED}N/A${E_END}\n" "$2"
  fi
}



#--------------------------------------------------------------------- 
# 
#---------------------------------------------------------------------

#
# Function logging to file
#
# Arg1 String to log to file
# 
bpLog() { ##D Log to file command
  # check for LOGFILE variable
  if [ -n "$LOGFILE" ]; then
    ts=$(date +"%Y-%m-%d %H:%M:%S")
     echo "$ts" "$1" >> "${LOGFILE}"
  fi
}

log() { ##C LOGFILE View logfile
  if [ -n "$LOGFILE" ]; then
    D=$(sed -r -e "s|\[Info\]|\[\\${E_INFO}Info\\${E_END}\]|"  \
            -e "s|\[Warn\]|\[\\${E_WARNING}Warn\\${E_END}\]|"  \
            -e "s|\[Erro\]|\[\\${E_ERROR}Erro\\${E_END}\]|"    \
            -e "s/[-0-9]+/\\${E_GREEN}&\\${E_END}/1"            \
            -e "s/[:0-9]+/\\${E_BR_GREEN}&\\${E_END}/6"            \
            -e "s|\[Crit\]|\[\\${E_ON_RED}\\${E_WHITE}Crit\\${E_END}\]|" < "${LOGFILE}" ) 

    echo -e "$D"
  else
    bpInfo "Logging is not activated"
    exit
  fi
}


bpOk() { ##D Success message 
  bpLog "[Ok] $1"
  echo -e "[${E_OK}Ok${E_END}] $1"
}

bpInfo() { ##D Info message 
  bpLog "[Info] $1"
  echo -e "[${E_INFO}Info${E_END}] $1"
}

bpWarning() { ##D Warning message
  bpLog "[Warn] $1"
  echo -e "[${E_WARNING}Warning${E_END}] $1"
}

bpError() { ##D Error message
  bpLog "[Erro] $1"
  echo -e "[${E_ERROR}Error${E_END}] $1"
}

bpCritical() { ##D Critical error message
  bpLog "[Crit] $1"
  echo -e "[${E_CRITICAL}Critical${E_END}] $1"
  bpExit
}

assertRoot() { ##D Assert that user is root
  if [ "$(whoami)" != root ]; then
    bpError "Must be root to use this command."
    bpExit
  fi
}


assertNoLockFile() { ##D Assert that lockfile is not present
  if [ -n "$LOCK_FILE" ]; then 
    if [ -f "$LOCK_FILE" ]; then
      echo -e "${E_ERROR}Script is already running. (${LOCK_FILE})${E_END} "
      exit  # do not use bpExit because lock belongs to other process
    fi
    touch "$LOCK_FILE"              
  fi
}

assertRequiredProgs() { ##D Assert that required programs are available on the system
  if [ -n "${REQUIRED_PROGRAMS}" ]; then
    for p in ${REQUIRED_PROGRAMS[@]}; do
      hash "$p" 2>&- || \
      { echo -e >&2 "${E_ERROR}Required program \"$p\" not found.${E_END}"; exit 1; }
    done
  fi
}

info() { ##D Show information about script
  printVar scriptName      "Script name" 
  printVar scriptPath      "Script path" 
  printVar VERSION         "Script version" 
  printVar BPVERSION       "Template version" 
  printVar LOGFILE         "Log file" 
  printVar LOCK_FILE       "Lock file" 
  printVar DEFAULT         "Default function" 
  printVar "REQUIRED_PROGRAMS" "Dependencies"
  printInfo "PID" $$  
  printVar DATE "Date" 
  printVar TIME "Time" 
}

check() { ##D Make a shellcheck
  shellcheck "$0"
}

# Change setting in config file (key value pair)
#
# arg1 config file
# arg2 setting to change
# arg3 new value for setting
#
chSetting() { 
  SETTING="$2"
  VAL="$3"
  sed -i "s/^\(${SETTING}\s*=\s*\).*\$/\1$VAL/" "$1"
}

printCommand() { 
  help_line=$1
  help_command=$(echo "$help_line" | sed -s 's/(.*//')
  help_info=$(echo "$help_line" | sed -s 's/^.*'"$2"'//')
  printInfo "$help_command" "$help_info" 
}

printCondCommand() {
  help_line=$1
  C=$(echo "$1" | sed -s 's/^.*##C//' | awk '{print $1}')
  eval "D=\$$C"
  if [ -n "$D" ]; then
    help_command=$(echo "$help_line" | sed -s 's/(.*//')
    help_info=$(echo "$help_line" | sed -s 's/^.*'"$C"'//')
    printInfo "$help_command" "$help_info"
  fi
}

printCondLine() {
  help_line=$1
  C=$(echo "$1" | sed -s 's/^.*##C-//' | awk '{print $1}')
  eval "D=\$$C"
  if [ -n "$D" ]; then
     printLine
  fi
}

##N- Kalle
printNamedLine() {
  name=$(echo "$1" | sed -s 's/^.*##N-//' | awk '{print $1}')
	bpTextLineC $C "${E_GRAY}" "${E_GRAY}"
}


SSSS=1
##K- SSSS asdfasdfasdf

help() { ## Print this help information
  echo "$USAGE"
  echo -e "$DESC"
  echo 
  printf "%-20s  %s\n" "Command" "Help"
  printLine
  IFS=$'\n'
  SC=$1
  help_lines=$(grep -h '##' "$0" | grep -v grep | grep -v '##D' | grep -v '##V' | grep -v '\*##C' | grep -v '\*##C-' |  grep -v '\"##' |  grep -v '##N-//' | grep -v help_line | grep -v printLine)
  for help_line in ${help_lines[@]} ; do
    case "$help_line" in
      *"##-"*)  printLine ;;
			*"##K-"*) printCondLine    "$help_line" ;;
			*"##N-"*) printNamedLine   "$help_line" ;;
      *"##C"*)  printCondCommand "$help_line" ;;
      *"##"*)   printCommand     "$help_line" '##' ;;
      *)    
      ;;   
    esac
  done 
}

ihelp() { ##D Print internal help information
  printLine
  IFS=$'\n'
  SC=$1
  help_lines=$(grep -h '##' "$0" | grep -v grep | grep -v '\*"##[ A-Z]"\*' | grep -v help_line | grep -v printLine)
  for help_line in ${help_lines[@]}; do
    case "$help_line" in
      "##-") printLine ;;
      *"##D"*) 
          printCommand "$help_line" '##D' ;;
      *)    
      ;;   
    esac
  done 
	
	printInfo "#" "Normal bash comment"
	printInfo "##" "Subcommand information comment (shown with help)"
	printInfo "##C" "Conditional subcommand comment (shown with help)"
	printInfo "##-" "Generates a line at output (shown with help)"
	printInfo "##d" "Internal function comment (shown ihelp)"
	printLine
}

vhelp() { ##D Print internal variable information
  IFS=$'\n'
  lines=$(grep -A 1 '##V' "$0" | grep -v 'lines')
  echo "$lines"
  for line in ${lines[@]}; do
    echo "$line"
#    case $line in
#      "##x") printLine ;;
#      *"##D"*) 
#          printCommand $help_line '##D' ;;
#      *)    
#      ;;   
#    esac
  done 

#  echo $lines
}

version() { ## Print version information
  echo "$VERSION"
}

# Check if a number of required programs are available on the system
requiredPrograms() {
  if [ -n "${REQUIRED_PROGRAMS}" ]; then
    for p in ${REQUIRED_PROGRAMS[@]}; do
	    hash "$p" 2>&- || \
	    { echo -e >&2 "${E_ERROR}Required program \"$p\" not installed.${E_END}"; exit 1; }
	  done
	fi
}

# Runs a function in this file as a command
runCommand() {
  if [ "$bpArguments" -eq 0 ]; then
   
    # check for a default command
    if [ -n "$DEFAULT" ]; then
      $DEFAULT "$1" "$2" "$3" "$4" "$5" "$6" "$7" "$8" "$9" "${10}"
      bpExit
    fi
    bpErrorExit "No command given"
  fi
  
  funks=$(grep "##" "$0" | grep -v grep | grep -v help_line)
  for line in ${funks[@]}; do
    command=$(echo "$line" | sed -s 's/(.*//')
    if [ "$command" == "$1" ]; then
      
      
      # execute prefunction if existing
      if [ -n "$PREFUNCTION" ]; then
        ${PREFUNCTION}
      fi
      
      # execute command
      ${command} "$1" "$2" "$3" "$4" "$5" "$6" "$7" "$8" "$9" "${10}"
      
      # execute postfunction if existing
      if [ -n "$POSTFUNCTION" ]; then
        ${POSTFUNCTION}
      fi      
      bpExit
    fi
  done
  bpErrorExit "Command \"$1\" not found"	 
}

# Init 
#
DATE=$(date +"%Y-%m-%d")
TIME=$(date +"%H:%M:%S")
COLUMNS=$(tput cols)
LINES=$(tput lines)

trap  signalQuit SIGQUIT
trap  signalInt  SIGINT
trap  signalHup  SIGHUP
trap  signalTerm SIGTERM

bpArguments=$#

# Run command parser
runCommand "$1" "$2" "$3" "$4" "$5" "$6" "$7" "$8" "$9" "${10}"

# Exit cleanly
bpExit


##-
