---
title: "The Imakefile.mk Special File"
category: "use-case"
module: "CAABtlTechArticles"
tags: []
source_file: "Doc/online/CAABtlTechArticles/CAABtlMANimakefile.htm"
converted: "2026-05-11T17:33:46.091758"
---

RADE |  Multi-Workspace Application Builder |  The Imakefile.mk Special File _How to control the compilation of programs_  
---|---|---  
Technical Article  
  
* * *

Abstract The **Imakefile.mk** file is a text file which must be defined for each module in a framework and whose purpose is to describe what must be produced (by [mkmk](CAABtlMkmk.md)) from this module. The aim of this paper is to explain how to start with this file and secondly how to use advanced features. Before to start building your program, we advise you to read both the first part of this paper (including few samples) and the use of [mkmk](CAABtlMkmk.md).

  * **Why this kind of file?**
  * **Few samples**
    * Location
    * How to build a shared library
    * How to build an executable
    * How to Build a Java Module
    * Distinguish operating systems in Imakefile.mk
    * How to use personal preprocessing variables
  * **Syntax and variables**
    * Syntax rules
    * Variables interpreted by mkmk
  * **In Short**

  
---  
Why this kind of file? Every module should be associated with a **Imakefile.mk** file before attempt to build with the CAA Workbench Code Builder mkmk. The Imakefile.mk contains make-like macros which are used at compilation time and build time. So the Imakefile.mk syntax must comply to the global syntax of makefiles. Like explained in [mkmk](CAABtlMkmk.htm#Hide operating system specificities) paper, our environment proposes the same compiler for all operating systems where CNext can be run. This is a convenient way for developers to build their programs since they do not have to learn how to use different compilers and how to write (and keep up to date) makefiles. However all cannot be done by mkmk and users must explain at least what they want to generate. Few samples Here are the most basic samples of Imakefile.mk files you could have to write regarding the type of data to generate. Location ![](images/FileTree17.gif) How to build a shared library The type of result is specified by a variable named `_BUILT_OBJECT_TYPE_`. The most basic Imakefile.mk contains just one line:

> `_BUILT_OBJECT_TYPE=SHARED LIBRARY_`

Another type of library is the **archive**. It is less used than shared libraries but if you need to generate one, just replace the words "`_SHARED LIBRARY " _`by the word `_" ARCHIVE_`". How to build an executable A main program can be built by setting another value to the previous variable:

> `_BUILT_OBJECT_TYPE=LOAD MODULE_`

Another thing that could be interesting to control is the name of the program: this is achieved using another variable, for instance:

> `_PROGRAM_NAME=my_beautiful_program  
>  BUILT_OBJECT_TYPE=LOAD MODULE_`

If no name is defined, default names will be chosen regarding the type of data to build. How to Build a Java Module To build a Java module, include:

> `_PACKAGE_MODULE=my.package  
>  BUILT_OBJECT_TYPE=JAVA_`

where `my.package` is the root of the packages that are to be included in the Java module. Distinguish operating systems in Imakefile.mk Even if the same Imakefile.mk file can be used on any (supported) operating systems, you may want to mark some differences regarding the current operating system. To do this, consult the [declarative file preprocessor](CAABtlMANprepro.md) document. How to use personal preprocessing variables Preprocessing variables are often used in programs for different purposes:

  * Debug: print messages to trace execution
  * Variants of implementation: according to the current OS or for different levels of services

The Imakefile.mk syntax proposes a set of keyword (one per language) to add such variables, here is an example where we set a "`_DEBUG_`" variable for the compilation of C and C++ files and a "`_API3_`" variable for the compilation of C++ files (note the use of "`_$(...)_ "` to reference the value of a variable):

> `_LOCAL_CFLAGS=-DDEBUG  
>  LOCAL_CCFLAGS=$(LOCAL_CFLAGS) -DAPI3  
>  ..._`

Syntax and variables Syntax rules

  1. A variable can be defined from a previously defined variable. 
         
         _VAR2=$(VAR1)_

  2. The makefile syntax does not allow to define a variable from itself. Definition such as the following ones are not allowed: 
         
         _VAR1=val1 val2_
         _VAR1=$(VAR1) val3_

  3. Lines beginning by the '#' character are comments or pragma.
  4. Lines ending with a backslash '\' character continue on the next line.
  5. space characters are ignored on both sides of a equal '=' character.
  6. except if specified, the space character can be used as separator if a variable is set with several parameters

Variables interpreted by mkmk Note: Variables following the flag "**internal usage** " are those used for special purpose and may not be used outside Dassault Systmes. mandatory

> `_BUILT_OBJECT_TYPE_`= type of the module to build. Its value can be :

>   * `_LOAD MODULE_` to build a main program,
>   * `_SHARED LIBRARY_` to build a shared library or DLL,
>   * `_ARCHIVE_` to build an archive,
>   * `_EL LIBRARY_` for Explicitly Loaded, this kind of modules are explicitly loaded at run time. A shared library or DDL is built but it cannot be referenced by the other modules through the `_LINK_WITH_` macro
>   * `_JAVA_` to build a Java module.
> 

mandatory for Java

> `_PACKAGE_MODULE_`= root of the Java packages for the module to build, such as com.dev for a module containing the packages com.dev.view and com.dev.controller

internal usage

> `_NONE_` is used to group small modules into a bigger module. The name of the small module must be included in an `_INCLUDED_MODULES_` macro in the big module. The container module can be a LOAD MODULE or a SHARED LIBRARY. The container and its contents must belong to the same framework.

optional

> `_PROGRAM_NAME_`= name of the built module. Default value is the module directory name with a prefix or a suffix depending of the module type (see `_BUILT_OBJECT_TYPE_` variable). For example, if the module to build is in _mymodule.m_ directory, the generated output name is: BUILT_OBJECT_TYPE | Generated module name  
> ---|---  
> `_LOAD MODULE_` | mymodule (UNIX) mymodule.exe (Windows)  
> `_SHARED LIBRARY_` | libmymodule.a (AIX) libmymodule.sl (HP-UX) libmymodule.so (SunOS) mymodule.dll (Windows) mymodule.lib (Windows)  
> `_ARCHIVE_` | libmymodule.a (UNIX) mymodule.lib (Windows)  
> The naming of modules concerns only load modules `_(BUILT_OBJECT_TYPE= LOAD MODULE_`) and is advised for transparency reasons.

mandatory

> `_LINK_WITH = lib_1 lib_2 ... lib_n_` list of modules (i.e. libraries) to be used at link-edition time of the current module. This option is mandatory. **You must always at least include JS0GROUP in the list of load modules**. The statement becomes: `_LINK_WITH = JS0GROUP lib_2 ... lib_n_` When link-editing a module, mkmk uses the subset of libraries which belong to the prerequisite frameworks of the embedding framework of the module. mkmk only makes available the subset of libraries in the prerequisites that _`LINK_WITH`_ features. The library name to be used is either the one specified in the corresponding Imakefile.mk file or the default computed by mkmk (see PROGRAM_NAME keyword). Do not forget to referenced the prerequisite frameworks in the identity card ([IdentityCard.h](CAABtlMANIdCard.md) file) of the framework to avoid an mkmk error (_mkmk-WARNING: .....: Modules .... in LINK_WITH was found in component .... which is not directly referenced, ignored_). **For JS0GROUP, you must reference the System framework**.

optional

> `_INCLUDED_MODULES = mod_1 mod_2 ... mod_n_` list of modules of the current framework whose objects must be included in this module. Note that the ".m" code module suffix is not written. The type of the modules referenced in this macro must be `_NONE_` (`_BUILT_OBJECT_TYPE=NONE_`).

optional

> `_COMDYN_MODULE_`= module name which exports the CNext dynamic commons. Be careful the module name cannot be referenced in the `_LINK_WITH_` macro. This macro concerns only Fortran modules of course. If you need to share your own dynamic commons between sources, put the sources in the same module.

optional

> `_IMPACT_ON_IMPORT= YES_` to force the build of the modules which import this module. This solves the incoherences at runtime due to the no rebuild of libraries. The problem does not exist with C++ programs because the dependencies between modules are indicated in header files. The impact is automatically computed and the rebuild is done. But with Fortran language this problem exists as shown in the following sample. ![](images/makefile2.gif) 
> 
>   1. The m3 module in library3 has the m1 module from library1 as prerequisite.
>   2. The s1 symbol moves from m1 (library1) to m2 (library2).
>   3. So library3 must be rebuilt to be correct at the execution time.
> 
  
> ---|---  
> This macro must be included always in Fortran modules and never in other modules for performance reasons. With C++ programs it is not necessary to force the rebuild.

optional

> `_OPTIMIZATION_xxx_`= xxx can be either `_C_`, `_CPP_`, or `_FORTRAN_` This macro is used to define an optimization level for a language. The value is ignored if mkmk runs with -g or -dev option.

optional

> _`CXX_EXCEPTION=`_ mkmk deactivates by default C++ native exceptions. If you need to use C++ native exceptions in your module, add this macro to reactivate them. Do not add any value after the equal sign. Pay attention not to nest V5 exceptions and C++ native exceptions.

optional

> `_BUILD=NO_` module won't be rebuilt by mkmk until this macro is removed.  
>  Useful in `_OS_`-specific section.

optional

> `_LOCAL_xxFLAGS=_` additive compile-time options. The following table lists the name of the macro corresponding to the language to compile. Languages | Macro name  
> ---|---  
> C++ | `_LOCAL_CCFLAGS_`  
> C | `_LOCAL_CFLAGS_`  
> fortran | `_LOCAL_FFLAGS_`  
> assembler | `_LOCAL_ASFLAGS_`  
> express grammar | `_LOCAL_CKMFLAGS_`  
> yacc grammar (on UNIX only) | `_LOCAL_YFLAGS_`  
> lex grammar (on UNIX only) | `_LOCAL_LFLAGS_`  
  
optional

> `_LOCAL_LDFLAGS_`= additive link-time options

optional

> `_SYS_LIBPATH_`= additive link-edit time system library directories (-L options)

optional

> `_SYS_LIBS_`= additive link-edit time system library directories (-l options)

optional

> `_MKMFC_DEPENDENCY_`=`_yes_` additive link-edit time option. Required to build shared libraries directly using MFC classes or load modules producing _Windows WPF Applications_ (per opposition to _Windows Console Applications_). In this last case, the `_$(SUB_WIN)_` keywork is also mandatory:
>     
>     
>     BUILT_OBJECT_TYPE=LOAD MODULE
>     
>     LINK_WITH = ...
>     
>     OS = Windows_NT 
>     MKMFC_DEPENDENCY = yes
>     LOCAL_LDFLAGS = $(SUB_WIN)
>     
>     
>       
>     ---  
>     
>       
    
    
      [Top]
      
    
    * * *
    
    
      
      In Short
      
    
    
        
        * Mkmk needs an Imakefile.mk file for every module.
    
        
        * The minimum required is to specify what to built (cf macro _BUILT_OBJECT_TYPE_).
    
        
        * You can expressed specific sections for all (supported) operating
              systems;
    
        
        * You can add your own preprocessing variables as well as external
              libraries.
    
      
    
      [Top
      
    
    * * *
    
    
      
      History
      
        
          Version: **1** [Mar 2000]
          | Document created
          
    
        
          [Top]
          
    
      
      
    
    * * *
    
    
      
      _Copyright  2000, Dassault Systmes. All rights reserved._
      
    
    
    
    
    
