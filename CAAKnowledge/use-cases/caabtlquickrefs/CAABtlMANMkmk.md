---
title: "mkmk"
category: "general"
module: "CAABtlQuickRefs"
tags: []
source_file: "Doc\online\CAABtlQuickRefs\CAABtlMANMkmk.htm"
converted: "2026-05-11T17:33:49.944363"
---

RADE |  Multi-Workspace Application Builder |  mkmk _CAA V5 code builder_  
---|---|---  
Quick Reference  
  
* * *

Purpose The **mkmk** command builds sources written in C, C++, Express, Fortran, JAVA. If you use another language, please contact Dassault Systmes for the integration of your language in the CAA Workbench product. [Top] Default Usage Run without any option, mkmk by default executes the four following phases:
    * "ID card compilation": processes the [container] framework ID card
    * "header list generation": produces the list of headers made public by the [container] framework. Corresponding file is _< fw_name>/various/$MkmkOS_VAR/Public<fw_name>.lh_
    * "Imakefile.mk checking": the Imakefile.mk  are checked and update module if necessary. For updating, see -u, -g or -dev options.
    * The build itself. When processing a shared library, mkmk splits the phase in two, in order to successfully build a series of them: 
      * forced standalone generation of the (shared) library, even when symbols are missing
      * generation of the shared library (not OK if symbols are missing).
[Top] Usage `mkmk -h`

> to consult the usage of the command

`mkmk [-showcmd] [-jobs <nbproc>] [-noci | -idcard] [-u | -nomk] [-w | -g | -dev] [-mkdataonly] [-nobuild] [-bsc] [-a | <FW1> [<FW2>...] | <Mod> [<Mod2>...] | <Fw/Mod>] | -lFW /path/FWlst [-lMod /path/Modlst] ]` internal usage `-jobs <nbproc>`

> Multiprocessing mode. nbproc is the maximum number of parallel tasks mkmk forks

`-showcmd`

> Prints command lines before to executing them.

`-noci`

> Does not intend to recompile the (embedding) framework identity card. This is not the default.

`-idcard`

> Intend to recompile only the (embedding) framework identity card. No module are built. This is not the default.

`-u`

> Forces the update of the build time data.

`-w`

> Compilations with warning messages.

`-g`

> Compilations in debug mode. Please note that with Windows, mkmk forces the usage of the release version of the Visual C++ runtime library instead of the debug version. This allows you to load in the same process CAA code built in debug mode using mkmk and V5 products code built in release mode. Third party dlls used in mkmk build should conform to the same logic: 
>     * Either use the release version of such libraries, even in debug sessions.
>     * Or use a debug version linked against non debug versions of Visual C++ runtime libraries.

`-dev`

> Disables the optimized mode at compile-time.

`-nomk`

> Deactivates the Build Time update. 

`-mkdataonly`

> Only regenerates the Build Time data.

`-nobuild`

> Does not start the build. Useful when coupled with option -u. mkmk then only regenerates the Build Time data.

To specify what target to process: `[nothing]`

> when in a module directory, mkmk processes current module

`-a`

> mkmk processes data under current position in the file system:

>       * when in a work space root directory: every framework (and embedded modules).
>       * when in a framework directory: every module in current framework.

`<FW1> [<FW2>...]`

> all the modules in the (list of) framework(s),

`-lFW /path/FWlst`

> all the modules in the specified list of framework(s).

`-lMod /path/Modlst`

> all the modules in the specified list of module(s), which belong to the current framework.

`<Mod> [<Mod>...]`

> all the modules in the list, which belong to current framework.

The table hereunder gives you a view on what could be used: **Current working  
directory** **Parameters on the command line** |  **If you're in the workspace root directory** |  **If you're in the directory of framework FW1:  
WS/FW1** |  **If you're in the directory of module Mod1:  
WS/FW1/Mod1**  
---|---|---|---  
-lFW fwlst | FWs: the fwlst list Mods: all the modules of the Frameworks | FWs: the fwlst list Mods: all the modules of the Frameworks | FWs: the fwlst list Mods: all the modules of the Frameworks  
-lMod modlst | **ERROR: at least one framework must be specified** | FWs: current FW Mods: the modlst list | FWs: current FW Mods: the modlst list  
-a | FWs: all FW Mods: all modules of all FW | FWs: current FW Mods: all modules belonging to this current FW | FWs: current FW Mods: all modules belonging to this current FW  
FW1 FW2 | FWs: FW1, FW2 Mods: all modules belonging to FW1 or FW2 | **ERROR: FW1 and FW2 will be considered like modules of the current FW** | **ERROR: FW1 and FW2 will be considered like modules of the current FW**  
Mod1 Mod2 | **ERROR: Mod1 and Mod2 will be considered like frameworks of the current WS** | FWs: current FW Mods:Mod1, Mod2 | FWs: current FW Mods: Mod1, Mod2  
FW1/Mod1 FW2/Mod2 | FWs: FW1, FW2 Mods: Mod1, Mod2 | FWs: **current FW** , FW1, FW2 Mods: Mod1, Mod2 | FWs: **current FW** , FW1, FW2 Mods: Mod1, Mod2  
{nothing} | **ERROR: at least one framework must be specified** | FWs: current FW Mods: all modules. | FWs: current FW Mods: current module.  
[Top] Examples **Beginners** : if you are not (yet) familiar with the make principles, we recommend you to use: `mkmk`

> 1. The list of header files exported by the framework is updated. 2. The identity card of the framework is updated if needed. 3. The Build Time Data  is updated if needed. 4. The dependencies between derived objects and source objects are recomputed. 5. The derived objects which set of dependencies changed, or for which at least one prerequisite changed, are rebuilt.

[Top]

* * *

History Version: **1** [Mar 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
