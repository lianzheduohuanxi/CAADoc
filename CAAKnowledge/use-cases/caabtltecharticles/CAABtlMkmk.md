---
```vbscript
title: "The Workbench Code Builder mkmk"
category: tech-article
module: "CAABtlTechArticles"
tags: []
source_file: "Doc/online/CAABtlTechArticles/CAABtlMkmk.htmmd"
converted: "2026-05-11T17:33:46.154216"
```

---
tags: []
source_file: "Doc/online/CAABtlTechArticles/CAABtlMkmk.htmmd"
converted: "2026-05-11T17:33:46.154216"
RADE |  Multi-Workspace Application Builder |  The Workbench Code Builder mkmk _Principles - What does it do for CAA developers?_

converted: "2026-05-11T17:33:46.154216"
RADE |  Multi-Workspace Application Builder |  The Workbench Code Builder mkmk _Principles - What does it do for CAA developers?_
Technical Article

* * *

Abstract mkmk is a tool that is used to build programs from source files. CAA source files are managed and delivered in components which structure respects a particular organization (we call it the CAA FileTree). This paper has been written to explain the main features of mkmk (and related tools) and what files and directories any mkmk user should be aware of in order to be efficient in the use of this tool.

  * **What does mkmk for you?**
    * Developing is more interesting than building
    * Hiding operating system specifics
    * Supporting component-oriented design
    * Supporting concurrent engineering
  * **Principles of use**
    * mkmk and the CAA FileTree
    * How to start with mkmk
    * New build step checking interfaces usage - **_New !_**
    * mkmk compilation phases
    * [mkmk and Java](CAABtlMANJava.md)
    * [Support of type libraries import in C++ sources for Windows](CAABtlMANtlb.md)
    * How to access prerequisite frameworks
    * Running a program
  * **Tips and hints**
  * **References**
  * **In Short**

---
What does mkmk for you? Developing is more interesting than building Before being able to see the result of what he has written, the developer must build his program with the appropriate compiler and linker. This is not a simple task especially when one must take into account various locations of source files, multiple operating systems, several languages, multiple compilers with different and numerous options and so on. Those who have experienced makefiles management know the problem... With mkmk, the Workbench proposes a single tool to compile and link applications wherever the user is working and whatever the [programming language(s) used](../CAABtlQuickRefs/CAABtlMANMkmk.md). Hiding operating system  specifics mkmk offers the same independence from the development platforms as CNext components: they offer the same interfaces and methods no matter whether you're writing code for NT or Unix platforms. It's the same with mkmk:

  * same development data for all platforms
  * same location (workspace) for all operating systems with all platforms
    * source files stay at the same place
    * generated data is placed in its _operating system_ directory
  * same way of running
    * whatever the language(s)
    * whatever the operating system

Supported platforms and operating systems are:

  * Windows NT 4.0
    * Intel architecture
  * Unix
    * AIX, HP-UX, SunOS

Supporting component-oriented design mkmk recognizes the CAA organization of components, the structure of frameworks and modules has no secret for it. mkmk lets the developer work at the framework/module level, specifies what are the components he's really working on and what prerequisite frameworks he needs (prerequisite frameworks which services are used by his own frameworks).
---|---
One can consider that users think of component organization and dependencies while mkmk translates their meaning into concrete information on files and directories. For example, a user needing services offered by framework X to implement his own framework will just declare that X is a prerequisite framework for him, then mkmk will find the related libraries (regarding the current operating system) and header files which are needed for compilation. Two special files are strongly related to frameworks and modules and are analyzed by mkmk:

  * **IdentityCard.h** [1]: associated with each framework and gives the name of the prerequisite framework(s)
  * **Imakefile.mk** [2]: associated with each module and explains what must be produced from this module
One can consider that users think of component organization and dependencies while mkmk translates their meaning into concrete information on files and directories. For example, a user needing services offered by framework X to implement his own framework will just declare that X is a prerequisite framework for him, then mkmk will find the related libraries (regarding the current operating system) and header files which are needed for compilation. Two special files are strongly related to frameworks and modules and are analyzed by mkmk:
(executable, shared library, archive, etc.)

Supporting distributed data Concurrent engineering is mainly supported by the WSManager that allows people to share and integrate data in workspaces. However, WSManager commands are used to copy files into a workspace and it is not a good idea to have copies of all frameworks in every workspaces. To avoid this situation the user can set up a special path by specifying one or several workspace root directories where mkmk will look in to find prerequisite frameworks.

  * The whole set of frameworks can be dispatched among number of workspaces (this is done by WSManager commands)
  * Any user, inside his workspace, needing prerequisite frameworks, specifies the location of workspaces containing the frameworks he needs. This information is used by mkmk to find out the corresponding libraries and header files to achieve the local compilation (prerequisite resources stay in their own workspace, no copy is performed).
  * Any user decides whether the access to prerequisites should be static (isolated work) or dynamic (impacted by prerequisite changes). This is explained below.

Principles of use mkmk and the CAA FileTree The aim of this section is to explain where to find mkmk special files and what directories and files are managed by the tool. ![](images/FileTree13.gif) Note that you must have one IdentityCard.h file per framework and one Imakefile.mk file per module.If your framework does not need any external service, its identity card will be empty, otherwise it will contain references to the corresponding frameworks. The minimum required for the Imakefile.mk file is to contain the type of data which must be produced from the container module: consult the [Imakefile.mk](CAABtlMANIdCard.md) article to learn its syntax. As said before, mkmk recognizes frameworks and modules inside the CAA FileTree, it means that you can run mkmk in any directory (somewhere under the root directory) and it will build what corresponds to this level.    How to start with mkmk _My first program!_ Before to compile a program with mkmk, some things must exist. Here is the smallest file tree you can have if you use mkmk, Our example consists in a single source file just to say "_Hello World_ ". ![](images/FileTree15.gif) _My first compilation!_ The first thing to know is where is mkmk. Considering that mkmk has been installed under <mkmk> directory, you should execute the following command to set up your path: **Unix platform** | **NT platform**
---|---
Principles of use mkmk and the CAA FileTree The aim of this section is to explain where to find mkmk special files and what directories and files are managed by the tool. ![](images/FileTree13.gif) Note that you must have one IdentityCard.h file per framework and one Imakefile.mk file per module.If your framework does not need any external service, its identity card will be empty, otherwise it will contain references to the corresponding frameworks. The minimum required for the Imakefile.mk file is to contain the type of data which must be produced from the container module: consult the [Imakefile.mk](CAABtlMANIdCard.md) article to learn its syntax. As said before, mkmk recognizes frameworks and modules inside the CAA FileTree, it means that you can run mkmk in any directory (somewhere under the root directory) and it will build what corresponds to this level.    How to start with mkmk _My first program!_ Before to compile a program with mkmk, some things must exist. Here is the smallest file tree you can have if you use mkmk, Our example consists in a single source file just to say "_Hello World_ ". ![](images/FileTree15.gif) _My first compilation!_ The first thing to know is where is mkmk. Considering that mkmk has been installed under <mkmk> directory, you should execute the following command to set up your path: **Unix platform** | **NT platform**
Open a shell window | Open a DOS window
Enrich your shell path

`_._ _< mkmk>_` Ask your tools administrator to get the exact installation path. | Enrich your DOS environment
`_< mkmk>_` On NT, the exact installation path may be given under UNC format (`//machine/shared_name/...`)
Open a shell window | Open a DOS window
Enrich your shell path
Once your path has been updated, next commands are the same no matter _whether you're working on NT or on UNIX_ (AIX, HP-UX, SunOS operating systems). The first compilation should be global to be sure to build all what is needed: in the example below, we go under the framework we want to build and run mkmk with option -a to compile all what can be find under it.

> `_$ cd <workspace_root_directory>/Hello
>  $ mkmk -a
>  ..._`

```vbscript
If our example had two modules, we could choose to compile just one of them by giving its name to mkmk:

```

> `_$ cd <workspace_root_directory>/Hello
>  $ mkmk hello.m
>  ..._`

We propose the reader to consult the mkmk[ reference page](../CAABtlQuickRefs/CAABtlMANMkmk.md) to know all about the mkmk options. _Where is my program?_ When a compilation is successfully completed, its results (programs or libraries) can be found under a related OS directory. For our "hello" example, we should get a "hello" program on Unix platform and a "hello.exe" program on NT platform. |
---|---
New build step checking interfaces usage A new build step has been added to mkmk to check the interfaces architecture. This new step will check two rules: 1 - A Public interface can only use other Public interfaces The hierarchy of interfaces level from upper to lower is:

  * Public interfaces
  * Protected interfaces
  * Private interfaces
  * Local (of a module) interfaces

If an interface uses a lower level header, an error message is displayed. Example: _/WS/MyFW/PublicInterfaces/NameOfTheInterface.h file PUBLIC cannot use /WS/MyFW/ProtectedInterfaces/UsedInterface.h as include since it is PROTECTED.
# make-ERROR: MyFW/PublicInterfaces/NameOfTheInterface.h_ 2 - If an interface uses an header from another framework, it must be a direct prerequisite framework. If an interface uses interfaces from a non direct prerequisite an error message is displayed. Example: _/WS/MyFW/PublicInterfaces/NameOfTheInterface.h cannot use /WS/PrereqFW/PublicInterfaces/UsedInterface.h as include since it is in framework [PrereqFW] which is not a direct prerequisite
# make-ERROR: MyFW/PublicInterfaces/NameOfTheInterface.h_ _**Those new messages have no effect on the build time process. There is only new messages in the output of the command.**_ mkmk compilation phases When you run mkmk (whether to compile a framework or a module), the compilation goes through four main steps. These steps can be controlled using specific mkmk [ options](../CAABtlQuickRefs/CAABtlMANMkmk.htm#Usage).

```vbscript
If an interface uses a lower level header, an error message is displayed. Example: _/WS/MyFW/PublicInterfaces/NameOfTheInterface.h file PUBLIC cannot use /WS/MyFW/ProtectedInterfaces/UsedInterface.h as include since it is PROTECTED.
  1. Identity Card compilation
mkmk processes the (container) framework Identity Card
  2. Header list generation
mkmk computes the list of headers made public by the (container) framework
  3. Build Time Data update
mkmk (re)generates makefiles used during step 4
  4. The build itself
two passes for shared libraries, to successfully build a series of them

Note about step 4:
two passes are needed when several libraries must be produced from a framework because they may call each others, so they are first built (standalone) and then missing symbols are resolved. If you decide to build shared libraries one by one, you may encounter some "unresolved symbols" problems, in such cases, run mkmk on the whole framework, all modules will be treated in the right order. How to access prerequisite frameworks Prerequisite frameworks are frameworks which services are used by your own frameworks, by the way you need:

```

  * at build time, to access the corresponding header files (compilation) and libraries (link),
  * at run time: to access the corresponding (shared) libraries.

The way you specify where to find prerequisite data is based on workspaces and more precisely on workspace root directories:

  * before to start the first build, use the command [mkGetPreq](../CAABtlQuickRefs/CAABtlMkOthers.htm#mkGetPreq) to specify the root directory (ies)of the workspace(s) managing the framework(s) you need
  * during the compilation, mkmk goes under the specified directory (ies) to find the header files and libraries.

As soon as prerequisite data are stored in a CAA FileTree, the root directory is enough for mkmk, no need to specify the exact location of each files. More than one workspace can be referenced to look for prerequisite frameworks, this is done by setting a "prerequisite path" :

  * prerequisite workspaces are specify from the most interesting to the less interesting, i.e. if a framework exists in several workspaces, take it from the first specified
  * in a same way, if the first workspace does not contain a prerequisite framework, mkmk will look for it in the second one, and so on, until to find it (if no one contains the framework, mkmk will raise an error).

As anybody is able to choose his own prerequisite workspace(s), we advice the users to decide what are the "reference" workspace(s), otherwise this situation may lead to real problem during integrations of developments. A safety way for a workspace to reference prerequisite frameworks is to used those defined by its father workspace. Running a program Here are some pointers for those who are developing CNext applications. The purpose of the following commands is to set up the user environment in order to access the right resources and libraries (remember that applications are mainly composed of shared libraries and that a wrong search path could lead to load a wrong library at runtime):

  * [ mkCreateRuntimeView](../CAABtlQuickRefs/CAABtlMkOthers.htm#mkCreateRuntimeView): this command is used to install application resources (icons, message files, ...) from every frameworks to a single place.
  * [mkrun](../CAABtlQuickRefs/CAABtlMkOthers.htm#mkrun): this command runs CNext based applications with parameters, the search path is set up to access libraries, taking into account the path that was set up before, for the compilation, to access the prerequisite frameworks. This ensures that you use the same libraries both at buildtime and at runtime. This command can be used also to attach a debugger to the program.  Note that with Windows, mkrun requires the folder C/temp. Make sure this folder exists on your computer.

The mkrun command is not the only way to run programs which are developed and built in a CAA FileTree but in any cases, you must take care of your search path to be sure to use the right libraries. Tips and hints This section is intended for people having started with mkmk and who know a little bit more about mkmk capabilities. Skip mkmk compilation steps If you know that neither the IdentityCard.h file, nor the Imakefile.mk file, nor prerequisite frameworks have changed, then try the option -nomk. Derived objects will be produced faster.

> `_$ mkmk -nomk_`

Choose between dynamic or static access to prerequisites We told you that [mkGetPreq](../CAABtlQuickRefs/CAABtlMkOthers.htm#mkGetPreq) is the command to specify the location of prerequisite frameworks, in fact there is another command (named [mkCopyPreq](../CAABtlQuickRefs/CAABtlMkOthers.htm#mkCopyPreq)) which can be used to copy these frameworks locally. This can be useful if you don't want to be impacted each time your prerequisites changed. However, the choice between static and dynamic access must be decided at team level (and not by each user) in order to have a proper integration. In short

  * mkmk is the CAA compiler, it is available with both NT and UNIX platforms, with same options and behavior, native compilers are hidden to simplify user's tasks.
  * Two files must be managed by the developer: _IdentityCard.h_ is defined for each framework and specifies the prerequisite frameworks, _Imakefile.mk_ is a template defined for each module and specifies what must be produced by it (a shared library, an archive or an executable).
  * mkmk allows the user to reference and dynamically access multiple workspaces to search for prerequisite frameworks.

Before to start, we advise the developer to consult the papers describing the mkmk special files where it can find additional information on how he can control the way mkmk works (see below). [Top]

* * *

References [1] | [The Identity Card Special File](CAABtlMANIdCard.md)
---|---
[2] | [The Imakefile.mk Special File](CAABtlMANimakefile.md)
[3] | [mkmk and Java](CAABtlMANJava.md)
[4] | [Support of type libraries import in C++ sources for Windows](CAABtlMANtlb.md)
[5] | [Summary of Commands Around mkmk](../CAABtlQuickRefs/CAABtlMANMkThemIx.md)
[Top]

* * *

History Version: **1** [Mar 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
