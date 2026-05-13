---
```vbscript
title: "mkmk Handbook"
category: "use-case"
module: "CAABtlQuickRefs"
tags: ["CATIA"]
source_file: "Doc/online/CAABtlQuickRefs/CAABtlMkHandBook.htmmd"
converted: "2026-05-11T17:33:49.970359"
```

---
tags: ["CATIA"]
source_file: "Doc/online/CAABtlQuickRefs/CAABtlMkHandBook.htmmd"
converted: "2026-05-11T17:33:49.970359"
RADE |  Multi-Workspace Application Builder |  mkmk Handbook _Summary of mkmk capabilities_

converted: "2026-05-11T17:33:49.970359"
RADE |  Multi-Workspace Application Builder |  mkmk Handbook _Summary of mkmk capabilities_
Quick Reference

* * *

Quick Reference
Purpose This page is intended for developers and people getting started with [mkmk](CAABtlMANMkmk.md) and [related tools](CAABtlMANMkThemIx.md). The reader will find here how to set up his environment to access commands and a brief description on the most useful commands and topics. Note that all commands or options are not given here, please refer to the [manual pages](CAABtlMANMkThemIx.md) to get them. We advice you to add a bookmark to this page or to print it.
Build objects | Manage prerequisites (frameworks)

Purpose This page is intended for developers and people getting started with [mkmk](CAABtlMANMkmk.md) and [related tools](CAABtlMANMkThemIx.md). The reader will find here how to set up his environment to access commands and a brief description on the most useful commands and topics. Note that all commands or options are not given here, please refer to the [manual pages](CAABtlMANMkThemIx.md) to get them. We advice you to add a bookmark to this page or to print it.
Build objects | Manage prerequisites (frameworks)
Run applications | Main file suffixes

* * *

[Top] Build objects **Purpose** | **Commands** | **Parameter(s)**
---|---|---
Get a command usage | _`command_name`_ | `_-h_` (**h** for **h** elp)
Build a framework | _`cd ws_root_dir/framework`_
_`[mkmk](CAABtlMANMkmk.md)`_ or _`cd ws_root_dir`_
_`mkmk`_ |  _`-a`_ (**a** for **a** ll) nbsp;
  _`{framework}`_
Build a module | _`cd ws_root_dir/fw_name/module_name`_
_`mkmk`_ or _`cd ws_root_dir/fw_name`_
_`mkmk module_name`_ |      _`{framework/module}`_
Build an identity card | _`cd ws_root_dir/framework`_
_`mkmk -idcard`_ or _`mkCI`_ |

(*) If you have set the "Workspace Manager" environment, you already have access to build commands. (**) The given example may not correspond to your local installation, please ask your administrator for the location of your own installation. [Top] Manage prerequisites (frameworks) **Purpose** | **Commands** | **Param** eter(s)
---|---|---
_`mkmk module_name`_ |      _`{framework/module}`_
Build an identity card | _`cd ws_root_dir/framework`_
_`mkmk -idcard`_ or _`mkCI`_ |
Specify prerequisites of a framework | Edit file _`framework/IdentityCard/IdentityCard.h`_ | Add following line for each
prerequisite framework: _`AddPrereqComponent("framework", Public);`_
Refer prerequisites for dynamic access | _`[mkGetPreq](CAABtlMkOthers.htm#mkGetPreq)`_ | _`-p ws_root_dir[:ws_root_dir]`_
_`[-simu]`_
Refer prerequisites for static access | _`[mkCopyPreq](CAABtlMkOthers.htm#mkCopyPreq)`_ | _`-p ws_root_dir[:ws_root_dir]`_

`_[-f] [-d]_` `_[-copysrc | -copyall] [-simu]_`
[Top] Run applications **Purpose** | **Commands** | **Parameter(s)**
---|---|---
```vbscript
```vbscript
Set environment before
```
```

```vbscript
```vbscript
Set environment before
```
```

running a program | _`[mkCreateRuntimeView](CAABtlMkOthers.htm#mkCreateRuntimeView)`_ | _`[-c | -l | -f] [-d]`_
Run "CATIA based" application
built in current workspace | _`[mkrun](CAABtlMkOthers.htm#mkrun)`_ | _`-c command_name`_
_`[{command_parameters}]`_

[Top] Main file suffixes Here are the main file suffixes that are used in CATIA developments and the corresponding locations in the file tree.
running a program | _`[mkCreateRuntimeView](CAABtlMkOthers.htm#mkCreateRuntimeView)`_ | _`[-c | -l | -f] [-d]`_
Run "CATIA based" application
built in current workspace | _`[mkrun](CAABtlMkOthers.htm#mkrun)`_ | _`-c command_name`_
_`[{command_parameters}]`_
Following suffixes must be used in order to let mkmk chooses the right compiler for the right file. **Suffix** | **Location** | **Meaning**

.h | framework/PublicInterfaces/ | C or C++ header file defining the framework services for clients.
  | framework/PrivateInterfaces/ | C or C++ header file providing services from a module to the other modules of the same framework. Such resources are not visible outside the framework.
  | framework/ProtectedInterfaces/ | C or C++ header file defining the framework services for internal clients.
  | framework/module.m/LocalInterfaces/ | C or C++ header file private to the module.
.cpp | framework/module.m/src/ | C++ source file.
.c | framework/module.m/src/ | C source file.
[.mk](../CAABtlTechArticles/CAABtlMANimakefile.md) | framework/module.m/ | Template for [mkmk](CAABtlMANMkmk.md) and specifying what to produce from this module.
.f | framework/module.m/src/ | Fortran source file.
.l or .lc | framework/module.m/src/ | Lex source file, use .l to generate C++ source code and .lc to generate C source code.( only on UNIX plateform)
.y or .yc | framework/module.m/src/ | Yacc source file, use .y to generate C++ source code and .yc to generate C source code. (only on UNIX plateform)
.sh | framework.tst/FunctionTests/TestCases/...
framework.tst/FunctionTests/SwitchTestCases/... | Shell program used for tests or for any purpose.
.idl | framework/PublicInterfaces/ | IDL (Interface Definition Language).
[Top]

* * *

History Version: **1** [Mar 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
