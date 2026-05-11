---
title: "mkIc2Xml"
category: "use-case"
module: "CAABtlQuickRefs"
tags: ["CATIAR211", "CATIAR209"]
source_file: "Doc/online/CAABtlQuickRefs/CAABtlMkIc2XmlV5.md"
converted: "2026-05-11T17:33:49.978874"
---

RADE |  Multi-Workspace Application Builder |  mkIc2Xml Migrate .h ID cards to XML  
---|---|---  
Quick Reference  
  
* * *

!-- -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-comment-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= -->  Abstract This article explains how to use the mkIc2Xml command to migrate your framework Identity Cards from .h to XML files.
      * Synopsis
      * Usage
      * Options
      * Example
      * Limitations
        * Comments in Parameters not Supported
        * #elsif not Supported
        * #ifdef in #ifdef not Supported
      * In Short  
---  
Synopsis **mkIc2Xml** [**-W** WSPath] [**-a** | **-L** FWlist | FW1 [FW2 ...]] [**-f** file] [**-o** oFile] [**-type** fwType ] [**-doInclude**] [**-h** | **-help** | **-?**] Usage This command is used to transform a .h (IdentityCard or included file, components) to .xml. It is dedicated to be used one shot (migration) or for a process in migration Most of the type, mkIc2Xml fw1 fw2 is enough, possibly with -doInclude to also recursively migrate included .h. mkIc2Xml ComponentsDefinition.cmp will convert all components The -f, -type, and -o options are used for three reasons: Transformation when you cannot write in the file tree of the .h and need the .xml for another process or transformation of .h which are not IdentityCard. In that case, the -type is not mandatory, mkIc2Xml will rely on the extension of the directory to decide the type. If the .h is not in a V6 file tree, you will need to use the -type. Options mkIc2Xml accepts the following options: Option | Description  
---|---  
`-a` | Process all the frameworks of the workspace.  
`-doInclude` | Process included files recutsively.  
`-f file` | Process a file the name of which is not IdentityCard.h. Use with `-o` and possibly `-type` options.  
`-h|-help|-?` | Display the command help.  
`-L FWlist` | Process the frameworks the names of which are listed in the file located at the path FWlist.  
`-o oFile` | Output file name if the file to process is not named IdentityCard.h. Use with `-f` and possibly `-type` options.  
`-type fwType` | Framework type, to use if the command is not run in a V6 workspace file tree. Use with `-f` and `-o` options. Valid values are:
      * `codeFramework`: a framework used to create applications.
      * `testFramework`: a framework used to store test objects.
      * `eduFramework`: a framework used for education purposes.  
`-W WSPath` | Path of the workspace to process. Default is the current folder.  
`FW1 [FW2 ...]` | Process frameworks FW1, FW2? etc.  
Example Conversion of frameworks A, A.tst, A.edu Identity Cards from .h to XML.
    
    >ls *\IdentityCard\*.h
    A.edu/IdentityCard/IdentityCard.h  A.tst/IdentityCard/IdentityCard.h  A/IdentityCard/IdentityCard.h
    >mkIc2Xml A A.edu A.tst
    == Starting generation: 3 framework(s) to do
    A Done [1/3]
    A.edu Done [2/3]
    A.tst Done [3/3]
    == Generation done
    >ls *\IdentityCard\*.xml
    A.edu/IdentityCard/IdentityCard.xml  A.tst/IdentityCard/IdentityCard.xml  A/IdentityCard/IdentityCard.xml
    

[Top] Limitations This part list limitation and unsupported cases. Comments in Parameters not Supported This case:
    
    AddPrereqComponent("A", Private /*Protected*/);  
    

Is not supported and will make mkIc2Xml fail. Remove such comments before using mkIc2Xml. #elsif not Supported The #elsif preprocessor directive has no match in IdentityCard.xml. The condition need to be rewritten before using mkIc2Xml. For instance
    #ifdef CATIAR211
    XXX
    #elsif CATIAR209
    YYY
    #else 
    ZZZ
    #endif
    
#ifdef in #ifdef not Supported #ifdef in #ifdef is not supported if both are used for a level monocoding or for an operating system monocoding. For example, this is supported:
    #ifdef CATIAR211
    #if os intel_a
    xxx
    #endif
    #else
    ...
    

This is not supported:
    #ifdef CATIAR209
    #ifdef CATIAR211
    xxx
    #endif
    #else
    ...
    

[Top] In Short In this article you have learnt how to migrate your framework Identity Cards from .h to XML. History Version: **1** [Jun 2011] | Document created  
---|---  
[Top] _Copyright 2013, Dassault Systmes. All rights reserved._
