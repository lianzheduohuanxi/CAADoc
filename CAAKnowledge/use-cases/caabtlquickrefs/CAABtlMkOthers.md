---
```vbscript
title: "mkmk Commands"
category: "use-case"
module: "CAABtlQuickRefs"
tags: ["CAA2", "CATIA"]
source_file: "Doc/online/CAABtlQuickRefs/CAABtlMkOthers.htm"
converted: "2026-05-11T17:33:50.021658"
```

---
tags: ["CAA2", "CATIA"]
source_file: "Doc/online/CAABtlQuickRefs/CAABtlMkOthers.htm"
converted: "2026-05-11T17:33:50.021658"
RADE |  Multi-Workspace Application Builder |  mkmk Commands _Quick Reference to mkmk commands_

converted: "2026-05-11T17:33:50.021658"
RADE |  Multi-Workspace Application Builder |  mkmk Commands _Quick Reference to mkmk commands_
Quick Reference

* * *

 **mkCopyPreq**
---
Purpose **mkCopyPreq** copies the prerequisite frameworks into a workspace. Contrary to mkGetPreq physical copies are made. The user thus isolates his work space from the changes in his prerequisites, which stabilizes his environment. Please note that mkCopyPreq replaces the existing frameworks only for a case where these frameworks were previously created by the mkCopyPreq command. For disk space economy reasons and performances, mkCopyPreq does not copy the entire data of a prerequisite framework. For instance, the source code is not copied locally, which won't allow a local work on these frameworks. mkCopyPreq reprocesses the identity card of the local framework. If one of the frameworks is already existing in the target workspace, it is not copied, an error message is displayed but the copy continues. When the -remove option is set, mkCopyPreq deletes data had been eventually copied locally by a previous mkCopyPreq.

* * *

Usage `mkCopyPreq -h`
      * to consult the usage of the command
`mkCopyPreq [-v] [-p <LPath>] [-o <OS1> [-o <OS2>]...] [-W <OriginDir>] [-t <TargetDir>] [-f] [-d] [-j <nbproc>] [-copysrc | -copyall] [-simu]`   `-v`

> To activate the verbose mode.

`-p <LPath>`

> LPath is a list of workspaces where frameworks are searched for.

Warning
      * The syntax is different between Unix and Windows:

> Path1:Path2:Path3 is the AIX syntax Path1;Path2;Path3 is the Windows syntax

`[-o <OS1> [-o <OS2>] ...]`

> the effect of this option is to limit the getting data related to any operating systems (OS1 and OS2 for example) from the prerequesite frameworks. By default mkCopyPreq grabs data for all the known operating systems.

`[-W <OriginDir>]`

> OriginDir is the full path name of the workspace in which the framework to be processed is. The default is current workspace root directory. For instance if the command is run in /u/users/gus/ws/MyFramework/MyModule.m, /u/users/gus/ws is considered as the current workspace directory.

`[-t <TargetDir>]`

> directory into data will be copied. Default is the OriginDir if the -W option is set; or current workspace root directory if it is not set.

`[-f]`

> to copy the FunctionTests directories of the prerequesite frameworks.

`[-d]`

> to copy the CNext data directories of the prerequesite frameworks.

`[-j <nbproc>]`

> Limits the number of copy scripts triggered by the command to the value. The default is 5. This is useful when the local machine CPU is already heavily used.

`[-copysrc | -copyall]`

> -copysrc copy source code of the modules -copyall copy every files

`[-simu]`

> Simulation mode : turn out the list of frameworks that would be removed.

* * *

Examples `mkCopyPreq -p /cnext/419 -t /s/users/dave/Preq ` This command line prompts mkCopyPreq to process the prerequisites of current workspace. It will get these prerequisites from /cnext/419, and copy what's necessary into /s/users/dave/Preq.    **mkGetPreq**
---
Purpose **mkGetPreq** is, like mkCopyPreq, a command designed to make available to a [local] workspace the prerequisite frameworks of frameworks present in the [local] workspace. Whereas mkCopyPreq performs a physical copy of the data useful for build-time and run-time in the identified prerequisites, mkGetPreq defines a dynamic search path, which later on is detected and interpreted by mkmk; mkmk then dynamically uses this concatenation of directories. You may want to run the command in simulation mode (-simu option) to know from what directory in the dynamic search path all the prerequisite frameworks are taken from. Note that if you want to focus on the prerequisites of a given [local] framework, use command mkPrintPreq.

* * *

Usage **Note** : Contrary to mkmk and other commands, mkGetPreq ignores any possible target. As its goal is to define a dynamic search path for every framework in a workspace, it never focuses on a given target framework. `mkGetPreq -h`

> to consult the usage of the command

`mkGetPreq [-W <WSroot>] -p <LWSpath> [-a] [-fwout file] [-mkinfo] [-noci] [-noq] [-pfile file] [-pfrom path] [-simul]` `[-W <WSroot>]`

> To indicate the root directory of the workspace to process. Default is current workspace directory.

`-p <LWSpath>`

> list/path of directories in which the prerequesites frameworks are looked for. mkGetPreq fails if one or several of the prerequisite frameworks cannot be found in the option -p path.

Warnings
      * On Unix the directories names are separated by a ':'; and on Windows by and ';'.
      * After the dynamic search path is modified, command mkmk should be run with option -u.
`-a `

> Consider all the frameworks of the workspace.

`-fwout file `

> Print the command output in a file. `file` is the full pathname of this file.

`-mkinfo `

> Print additional information when some errors are raised, such as a prerequisite framework not built.

`-noci `

> Avoid framework identity card compilation.

`-noq `

> Verbose mode.

`-pfile file `

> Concatenate workspaces where to search for the prerequisite frameworks. The workspace full pathnames are stored in a file, with a workspace pathname per line. `file` is the full pathname of this file. Ignored if -p is used.

`-pfrom path `

> Concatenate workspaces where to search for the prerequisite frameworks, starting from a single workspace pathname, and using the prerequisites of this workspace, if any. `path` is the full pathname of this workspace. Ignored if -p or -pfile is used.

`[-simul]`

> Simulate the result of the command. You see the prerequisites of all frameworks in the workspace.

* * *

Limitations The concatenation concept is very powerful because it avoids the developer to attach all the components that application needs to run. However there are some limitations to this feature that you should be aware of:
      1. Prerequisite modules must be specified explicitly using the LINK_WITH clause if Imakefile.mk files.
      2. If a NONE module has to be modified, the module which embeds this NONE module must be present in the workspace and not just visible throughout the concatenation.
      3. For the time being, all modules generating interfaces (_PrivateGenerated_ , _ProtectedGenerated_ and _PublicGenerated_) must be attached locally. This is a current limitation and it should disappear in a further version.
      4. If a module, which is referenced in a LINK_WITH directive, is destroyed in a local framework, it can be still visible because existing somewhere in the concatenation.
Only modules which are found at the first level of the concatenation (thus the workspace itself) can be modified. We consider that a framework is "local", and thus that its modules can be modified, if it contains the source of its Identity Card. As a consequence, it is possible to copy some frameworks locally and to prevent that they could be modified by deleting the local copy of their Identity Card source file.

* * *

4. If a module, which is referenced in a LINK_WITH directive, is destroyed in a local framework, it can be still visible because existing somewhere in the concatenation.
Only modules which are found at the first level of the concatenation (thus the workspace itself) can be modified. We consider that a framework is "local", and thus that its modules can be modified, if it contains the source of its Identity Card. As a consequence, it is possible to copy some frameworks locally and to prevent that they could be modified by deleting the local copy of their Identity Card source file.
Examples To define in workspace /u/users/me/myws_dir a dynamic prerequisit search path for mkmk

    $ cd /u/users/me/myws_dir
    $ ls
    SampleFramework aix_a
    $ mkGetPreq -p /u/lego/CXR1/BSF:/u/lego/CXR1rel/BSF
    $ ls
SampleFramework aix_a
    Install_config SampleFramework aix_a

Other examples: In the following example, framework Fw1 is made of modules Titi1 and Toto1. Module Titi1 needs services implemented by modules Toto1, Toto2 and Toto3. Given the content of the all workspaces in presence, mkGetPreq should be run in Ws_mine the following way: "`mkGetPreq -p Ws_b:Ws_c`". A further mkmk picks up in path Ws_b:Ws_c the prerequisites it needs. ![](images/linkwith.gif) Advanced Scenarios This paragraph sets out some scenarios `not that intuitive'. Read it to make sure you understand the combined effect of mkGetPreq and mkmk. Scenario 1: concatenation of modules In the following example, Ws_mine does not contain the entire framework Fw1(made of modules Titi1 and Toto1): only the module under work Titi1. Nevertheless, module Toto1 is present in Ws_Teamster. To build Titi1 in Ws_mine, work spaces WS_mine, WS_b ,WS_c and Ws_Teamster need to be concatenated. mkGetPreq makes it possible. ![](images/linkwith2.gif) Even if command mkGetPreq seems simple, it may lead to sharp situations. Scenario 2: prerequisite framework not complete In the following situation, the prerequisite framework is not complete in the first work space given in the -p option: ![](images/linkwith3.gif) The chosen behaviour of mkGetPreq in such a case is to only consider the modules of Fw2 presents in the first work space Fw2 was found. In the example, Toto2 only will be referred to at link-time.  **mkPrintPreq**

---
Install_config SampleFramework aix_a
Other examples: In the following example, framework Fw1 is made of modules Titi1 and Toto1. Module Titi1 needs services implemented by modules Toto1, Toto2 and Toto3. Given the content of the all workspaces in presence, mkGetPreq should be run in Ws_mine the following way: "`mkGetPreq -p Ws_b:Ws_c`". A further mkmk picks up in path Ws_b:Ws_c the prerequisites it needs. ![](images/linkwith.gif) Advanced Scenarios This paragraph sets out some scenarios `not that intuitive'. Read it to make sure you understand the combined effect of mkGetPreq and mkmk. Scenario 1: concatenation of modules In the following example, Ws_mine does not contain the entire framework Fw1(made of modules Titi1 and Toto1): only the module under work Titi1. Nevertheless, module Toto1 is present in Ws_Teamster. To build Titi1 in Ws_mine, work spaces WS_mine, WS_b ,WS_c and Ws_Teamster need to be concatenated. mkGetPreq makes it possible. ![](images/linkwith2.gif) Even if command mkGetPreq seems simple, it may lead to sharp situations. Scenario 2: prerequisite framework not complete In the following situation, the prerequisite framework is not complete in the first work space given in the -p option: ![](images/linkwith3.gif) The chosen behaviour of mkGetPreq in such a case is to only consider the modules of Fw2 presents in the first work space Fw2 was found. In the example, Toto2 only will be referred to at link-time.  **mkPrintPreq**
Purpose Prints out the list of the [direct and indirect] prerequesite frameworks of a given framework. The **mkPrintPreq** command may be compared with "mkGetPreq -simul", which also outputs a list of prerequisite frameworks. mkPrintPreq can be run on a given [local] framework, whereas mkGetPreq works on all the [local] frameworks.

* * *

Usage `mkPrintPreq -h`

> to consult the usage of the command

`mkPrintPreq [-W <WSroot>] [-l | -f | -d] [-a | -lFW /path/FWList | [<FW1> [<FW2>...]]] [-p Path1[:Path2]] [-e] [-fwout file] [-mkinfo] [-nort] [-pfile file] [-pfrom path] [-q] [-v]`

> By default the command uses the dynamic search path (file _Install_config_) possibly previously set with command mkGetPreq. If this file does not exist in the workspace, use mkGetPreq command first.

Warning

> On Unix the directories names are separated by a ':'; and on Windows by a ';'.

`[-W <WSroot>]`

> To indicate the root directory of the workspace to process, in which is the target framework. Default is current workspace directory.

`[-f]`

> By default, mkPrintPreq outputs the list of prerequisite(s) of the target framework(s) without indicating in which directory the prerequisite(s) was/were found (either in the search path previously defined my mkGetPreq ). Option -f prompts the command to explicit in which directory the prerequisite(s) must be taken from. Refer to the example in next paragraph.

`[-l]`

> By default, mkPrintPreq outputs the list of prerequisite(s) of the target framework(s) like a simple list. This option prompts the command to details prerequisite(s) for each framework.

`[-d]`

> By default, mkPrintPreq outputs the direct and indirect prerequisite(s) of the target framework(s). This option prompts the command to output only direct prerequisite(s).

`[-a | -lFW /path/FWLst] | <FW1> [<FW2>...]`

> Focuses the command on a (list of) framework(s). By default, the command processes at once all the frameworks in the workspace. Note that in this latter case, the output list is duplicated. Option -a can be set to apply the command on all frameworks belonging to the current workspace.

`[-p Path1[:Path2]]`

> Concatenate workspaces where to search for the prerequisite frameworks. `Path1` and `Path2` represent workspace root folder paths, and must be separated using a ":" (colon) with Unix and a ";" (semi-colon) with Windows. Windows workspace paths can be mapped drive paths, such a e/WorkspaceToAdd, or UNC paths, such as \\mycomputer\home\WorkspaceToAdd.

`[-e]`

> Add extended information to the detailed view of the prerequisites, framework per framework, with prerequisite modes (direct, indirect, etc.), and full pathnames.

`[-fwout file]`

> Print the command output in a file. `file` is the full pathname of this file.

`[-mkinfo]`

> Print additional information when some errors are raised, such as a prerequisite framework not built.

`[-nort]`

> Do not consider runtime prerequisite frameworks.

`[-pfile file]`

> Concatenate workspaces where to search for the prerequisite frameworks. The workspace full pathnames are stored in a file, with a workspace pathname per line. `file` is the full pathname of this file. Ignored if -p is used.

`[-pfrom path]`

> Concatenate workspaces where to search for the prerequisite frameworks, starting from a single workspace pathname, and using the prerequisites of this workspace, if any. `path` is the full pathname of this workspace. Ignored if -p or -pfile is used.

`[-q]`

> Quiet mode. Display only errors.

`[-v]`

> Verbose mode.

* * *

Examples In the current workspace, mkGetPreq was previously run to define a dynamic search path to access the prerequisites. To basically obtain the list of prerequisites of framework SampleFramework1:

    E/MyWorkspace<mkPrintPreq Framework1
    # Populating 2 workspace(s) with frameworks and modules ...
    # 2 workspace(s) populated with 301 frameworks and 1688 modules.
Examples In the current workspace, mkGetPreq was previously run to define a dynamic search path to access the prerequisites. To basically obtain the list of prerequisites of framework SampleFramework1:
E/MyWorkspace<mkPrintPreq Framework1
    BSFBuildtimeData
    LCCommon
    SpecialAPI
    System

To get more information:

    E/MyWorkspace<>mkprintpreq -l Framework1

    # Populating 2 workspace(s) with frameworks and modules ...
    # 2 workspace(s) populated with 301 frameworks and 1688 modules.

E/MyWorkspace<>mkprintpreq -l Framework1
    Required frameworks for: Framework1

    ------------------------------------
Required frameworks for: Framework1
    Direct   : BSFBuildtimeData in C/Program Files\Dassault Systemes\B24\.\BSFBuildtimeData
    Direct   : System           in C/Program Files\Dassault Systemes\B24\.\System
    Indirect : LCCommon         in C/Program Files\Dassault Systemes\B24\.\LCCommon
    Indirect : SpecialAPI       in C/Program Files\Dassault Systemes\B24\.\SpecialAPI

 **mkCopyFW**
---
Indirect : LCCommon         in C/Program Files\Dassault Systemes\B24\.\LCCommon
Indirect : SpecialAPI       in C/Program Files\Dassault Systemes\B24\.\SpecialAPI
Purpose **mkCopyFw** copies the build-time and run-time files of a framework from a workspace into another workspace. Please note that mkCopyFw replaces the existing frameworks only for a case where these frameworks were previously created by the mkCopyFw command. mkCopyFw can be used to copy frameworks from an Unix system into Windows system and vice versa. But this functionality can be involved only from a Windows platform. If one of the frameworks is already existing in the target workspace, an error message is displaying and the copy stops.

* * *

Usage `mkCopyFw -h`

> to consult the usage of the command

`mkCopyFw [-W <workspace path>] -p <LPath> [ [-no] | [-o <OS1> [-o <OS2>] ... ] ] [-d] [-f] [-remove] [-update] [-sniff] [-nm]  [-j<nbproc>] [-lFW /path/FWList | <FW1> [<FW2>..] ]` `[-W <workspace path>]a`

> target workspace directory path name. If not specified, mkCopyFw uses the current directory path name.

`-p <LPath1>`

> LPath is a list of workspaces where frameworks are searched for. Be carreful the syntax is different between Unix system and Windows system. Path1:Path2:Path3 is the AIX syntax Path1;Path2;Path3 is the Windows syntax

`[-no]`

> Derived objects are not copied.

`[-o OS1 [-o OS2] ...]`

> the effect of this option is to limit the getting derived data related to any operating systems (OS1 and OS2 for example) from the prerequesite frameworks. By default mkCopyFw grabs derived data for all the known operating systems.

`[-d]`

> copy the CNext-type data directories of the frameworks.

`[-f]`

> copy the FunctionTests directories of the prerequesite frameworks.

`[-remove]`

> cleans up in the target workspace the frameworks to be copied, if they already exist in there.

`[-update]`

> forces the copy even if the frameworks already exists in the target workspace. Note that mkCopyFw does not take care of deleted objects.

`[-sniff]`

> to copy the Sniff+ related directories of the prerequesite frameworks.

`[-nm]`

> the modules will be not copied (src and Objects directories).

**Internal usage** `[-j <nbproc>]`

> max number of parallel copy processes (default is 5).

`[-lFW /path/FWList | [<FW1> | [<FW2 >...] ]]`

> When a framework is already present in the target workspace, mkCopyFw emits an error message and stops. If the copy is nevertheless necessary, use the -remove option.

* * *

Examples `mkCopyFw -p /cnext/419 FW1` If run from directory /u/users/gus/MyWS, this command copies data from /cnext/419 into /u/users/gus/MyWS/FW1. Are copied the data related to every o.s. present in /cnext for FW1. `mkCopyFw -W /u/users/gus/MyWS -p /u/lego/CXR1/BSF -o aix_a -remove FW1 FW2` Run from directory /u/users/gus, this command copies data from /cnext/419 into /u/users/gus/MyWS/FW1 and /u/users/gus/MyWS/FW2. Only data related to aix_a are taken into account. In case these two directories would already exist, their aix_a-related data are first removed.  **mkRmFw**
---
Purpose **mkRmFw** deletes frameworks into a workspace. Note that this command addresses frameworks which have been installed by command  mkCopyPreq or command mkCopyFw.

* * *

Usage `mkRmFw -h`

> to consult the usage of the command

`mkRmFw [-W <workspace>] [-simu] [-preq] [-fw] [<FW1> [<FW2>..]` `-W <workspace>`

> to indicate the path of the workspace where the framework to delete is.

`[-simu]`

> to simulate the command and see the result

`[-preq]`

> to delete only the frameworks which are coming from the mkCopyPreq command

`[-fw]`

> to delete only the frameworks which are coming from the mkCopyFw

`[<FW1> [<FW2> ...]]`

> <FW1> [<FW2>... ] to indicate a list of frameworks to delete.

* * *

Examples `mkRmFw -preq` deletes any frameworks in the current workspace which are coming from mkCopyPreq commands  **mkRemoveDo**
---
Purpose This command is used to discard all derived objects into read-write frameworks of a development workspace. A framework is read-write only if a file named IdentityCard.h exists into the IdentityCard sub-directory. Note that mkCopyPreq command will create read-only versions for all prerequisites frameworks, then mkRemoveDo will not remove any files into frameworks created by the mkCopyPreq command. An operating system can be indicated to limit the scope of the deletion. **mkRemoveDo** deletes the derived objects which are coming from
      * the mkCopyPreq command
      * or from any framework whatever.

* * *

Usage `mkRemoveDo -h`

> to consult the usage of the command

`mkRemoveDo [-W <Workspace>] [-o <OS1> [-o <OS2>] ...] [-simul] [-a | -lFW /path/FWList | <FW1> [<FW2>...]] [-preq | -nopreq]` `[-W <Workspace>]`

> rootdir of the workspace. If not specified, use the current one.

`[-o <OS1> [-o <OS2>]...]`

> the effect of this option is to limit the deletion to any derived objects related to any operating systems (OS1 and OS2 for example). By default mkRemoveDo delete derived objects for all known operating systems.

`[-simul]`

> to simulate the execution of the command.

`[-a | -lFW /path/FWList | <FW1> [<FW2>...]] `

> List of frameworks separated with a blank character. Framework names can also be specified in a text file (-lFW text_file) containing one framework name per line. The framework names must be specified to delete derived objects FW1, FW2 ...:
>  to delete FW1, FW2, ... framework's derived objects.

`[ -preq | -nopreq]`

> -preq is used to delete ONLY derived objects of frameworks which have been installed with mkCopyPreq. -nopreq is used to delete ALL frameworks except frameworks which have been installed with mkCopyPreq.

* * *

Examples `mkRemoveDo -W /u/users/gus/MyWS -preq -o aix_a` This command deletes all _aix_a_ derived objects in the frameworks which have been copied by mkCopyPreq  **mkCreateRuntimeView**
---

* * *

Examples `mkRemoveDo -W /u/users/gus/MyWS -preq -o aix_a` This command deletes all _aix_a_ derived objects in the frameworks which have been copied by mkCopyPreq  **mkCreateRuntimeView**
Purpose They are two kinds of file trees: one for the build time and one for the run time. Some objects are used during the run time like icons, resources files and are stored in the frameworks architecture ($$CAA2 $$FileTree). In order to be used during the run time they must be copied in a run time file tree named RunTimeView. CATIA software knows only the RunTimeView. The **mkCreateRuntimeView** is a command to copy (copy or symbolic link) automatically files from the build time file tree into the run time file tree. ![](images/rtview.gif) CNext.xxx means specific operating systems. In this kind of directories are resources which are available only on some operating systems. These directories are named CNext.specifics_$OS. The following table shows the different values of $OS $OS |  Operating System

Purpose They are two kinds of file trees: one for the build time and one for the run time. Some objects are used during the run time like icons, resources files and are stored in the frameworks architecture ($$CAA2 $$FileTree). In order to be used during the run time they must be copied in a run time file tree named RunTimeView. CATIA software knows only the RunTimeView. The **mkCreateRuntimeView** is a command to copy (copy or symbolic link) automatically files from the build time file tree into the run time file tree. ![](images/rtview.gif) CNext.xxx means specific operating systems. In this kind of directories are resources which are available only on some operating systems. These directories are named CNext.specifics_$OS. The following table shows the different values of $OS $OS |  Operating System
aix_a | AIX | UNIX
hpux_a | HP-UX 10
hpux_b | HP-UX 11
solaris_a | SunOS
intel_a | Windows |
The values are hierarchical. It means if a file is both in CNext, CNext.specifics_AIX and CNext_specifics_UNIX, the run time view will contain the file coming from:

> - CNext.specifics_AIX on aix_a - CNext_specifics_UNIX on the other UNIX platforms - CNext on Windows.

intel_a | Windows |
The values are hierarchical. It means if a file is both in CNext, CNext.specifics_AIX and CNext_specifics_UNIX, the run time view will contain the file coming from:
Here is an example (for AIX operating system) where the same file appears in different CNext directories, the arrrows show what is taken into account. ![](images/rtview2.gif)

* * *

Usage `mkCreateRuntimeView -h`

> to consult the usage of the command

`mkCreateRuntimeView [-c|-f|-l] [-d] [-W <WSroot>] [-t <Targetroot>] [-s] [-v] [-k <FwType>]` `[-c|-f|-l]`

> to specify which files must be copied.

>       * -c: if the source is newer than the destination the file is copied
>       * -f: every files is copied into target file tree (default on Windows)

`Unix only`

> -l: symbolic links are defined and no file is copied (default on Unix)

`[-d]`

> to delete unknown files in the runtime view. It means if you put personal files in the runtimeview, they will be discard.

`[-W <WSroot>]`

> workspace directory name. Default is the current workspace.

`[-t <Targetroot>]`

> to indicate the root directory where the copy must be done. Default is $MkmkOS_VAR. If you used another value as the default value, modules are processing. It means that the modules in $MkmkOS_VAR/code/bin will be copied into the run time view.

Unix only `[-s]`

> It make sense with the -t option with other value as the default value.The modules will be stripped after the copy.

**Internal usage** `[-o]`

> In the $OS/Control directory files named as the framework names are created. They contain the list of the object which are coming from these frameworks.

`[-v]`

> to activate the debug mode

`[-k <FwType>]`

> to filter the type of framework to browse, <FwType> can be either _code_ , _edu_ or _tst_ (default is all).

* * *

Examples `mkCreateRuntimeView` creates symbolic links from the CNext directory in the current workspace into the _$Mkms_OS_VAR_ of the current workspace. `mkCreateRuntimeView -t /tmp/myCNext -c` creates the run time view of the current workspace into the /tmp/myCNext directory. `mkCreateRuntimeView -W /u/users/gus/ADELE/MYWS` creates the run time view of the /u/users/gus/ADELE/MYWS  **mkrun**
---

* * *

Purpose This command is used to execute a $$CNext program. It initializes the environment: PATH on Unix, LIBPATH on AIX, SHLIB_PATH on HP, LD_LIBRARY_PATH for Sun, path on Windows.

* * *

Usage `mkrun -h`

> to consult the usage of the command

`mkrun [-v] [-a] [-W <WSroot>] [-p <LPath>] [-type <LLevel>] [-r <Lconcatpath>] [-e <envir>] [-keep] [-c command ...] [-mkmk] [-x] [-s <LPath>]` `[-W <WSroot>]`

> path to find the program to execute

`[-p <LPath>]`

> to indicate a concatenation of paths . This concatenation replaced those defined with the mkGetPreq command and registered in the Install_config file.

Warning
      * The syntax is different between Unix and Windows:
        * Path1:Path2:Path3 is the Unix syntax
        * Path1;Path2;Path3 is the Windows syntax
      * With Windows, mkrun requires the folder C/temp. Make sure this folder exists on your computer.
`[-type <LLevel>]`

> to indicate a list of levels of concatenation:

>       * off for CNext
>       * dev for
>       * inst for CNext.inst
>       * debug for CNext.debug

> This option must be used with the -p option or if the mkGetPreq command has been executed (_Install_config_ file existing).

`[-r <Lconcatpath>]`

> to indicate a deeper concatenation of paths (until CNext.xxx directory). It can be used to point under debug levels.

Warning
      * The syntax is different between Unix and Windows:
        * Path1:Path2:Path3 is the Unix syntax
        * Path1;Path2;Path3 is the Windows syntax
`[-e <envir>]`

> to specify the environment name.

`[-keep]`

> to keep the shell which starts the command. Default the shell is removed after the run. The shell name is deduced from the environment name (-e option). Its name is $HOME/mkrun_envir.sh on Unix and C/temp\mkrun_envir.bat on Windows This shell will use the concatenation as defined by the mkGetPreq command (Install_config file).

`[-c command ...]`

> to indicate the command to run after the setting of the environment variables. This option must be the last one on the command line. The parameters after the -c option won't be interpreted by mkrun but automatically sent to _command_. **For legibility reason it is advised to set the command between double quote characters** (").

**Internal usage** `[-mkmk]` `[-x]` `[-s LPath]` `[-v]`

* * *

Examples `mkrun -p /u/lego/CXR1rel/BSF:/u/lego/CSSTOOLSCXR1rel/BSF -t off:dev:inst ...` The PATH variable will be:

    /u/lego/CXR1rel/BSF/aix_a/**CNext** /code/bin:/u/lego/CXR1rel/BSF/aix_a/code/bin:
    /u/lego/CXR1rel/BSF/aix_a/**CNext.inst** /code/bin:/u/lego/CSSTOOLSCXR1/BSF/aix_a/**CNext** /code/bin:
    /u/lego/CSSTOOLSCXR1/BSF/aix_a/code/bin:/u/lego/CSSTOOLSCXR1/BSF/aix_a/**CNext.inst** /code/bin:

`mkrun -c "CATRTV -check /u/users/gus/ws1:fw1:CNext"` will set the environment and execute the _CATRTV -check /u/users/gus/ws1:fw1:CNext_ command  **List of generated directories/files by CAA2 Workbench Code Builder**
---
This list is communicated for information. These directories are under the workspace root directory. Do not remove these files and directories. **Files or Directories** |  **Purpose**
---|---
This list is communicated for information. These directories are under the workspace root directory. Do not remove these files and directories. **Files or Directories** |  **Purpose**
FW/various/MkmkOS_VAR/HList/*.lh | Headers which are contained in the *Interfaces and *Generated directories of the framework
FW/*Generated/MkmkOS_VAR/* | Headers generated by mkmk
FW/IdentityCard/Objects/MkmkOS_VAR/* | Files used to generate the identity card of the framework
FW/ImportedInterfaces/MkmkOS_VAR/.HeaderTable.map | Authorized headers for the framework
FW/ImportedInterfaces/MkmkOS_VAR/*.h | Headers which are indirection into the external headers
FW/MOD/Objects/MkmkOS_VAR/*.o | Compilation results
FW/MOD/LocalGenerated/MkmkOS_VAR/.f .cpp.c ... | Grammar apply results
OS/code/bin/* | Librairies and load generated by mkmk

[Top]

* * *

History Version: **1** [Jan 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
