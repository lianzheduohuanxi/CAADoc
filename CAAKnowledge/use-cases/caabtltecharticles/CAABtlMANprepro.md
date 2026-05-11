---
title: "The Declarative File Preprocessor"
category: "use-case"
module: "CAABtlTechArticles"
tags: []
source_file: "Doc/online/CAABtlTechArticles/CAABtlMANprepro.md"
converted: "2026-05-11T17:33:46.116441"
---

    
    
    
    
    
    
      
        
          RADE
        
        | 
          Multi-Workspace Application Builder
        
        | 
          The Declarative File Preprocessor
          _How to distinguish specific operating system sections_
        
    
      
        Technical Article
        
    
    
    
    
    * * *
    
    
    
    
    
      
        
          Abstract
          Some declarative files are `preprocessed' (i.e. Imakefile.mk,
          IdentityCard.h) in order to distinguish specific sections (such as
          operating systems under which the workspace is being built).
          
    
    
            
        * **Syntax**
    
            
        * **Sample**
    
            
        * **In Short**
    
          
    
        
        
    ---  
    
    
    Syntax
    The preprocessor is an internal step which parse any lines that begin with a
    `**#** ' character in first column and is followed by an interpreted keyword,
    any others are translated to declarative file parser.  
    
    Such lines cannot be continued on next line with the `**\** ' continuing
    character.
    The comments are encapsulated with `**/*** ' and `***/** ' sequence
    characters.
    The following keywords are available:
    
      
         
        | **#define** _FlagName_
        
    
      
         
        | **#undef** _FlagName_
        
    
      
         
        | are used for special purpose and may not be used outside Dassault
          Systmes
        
    
      
         
        |  
        
    
      
         
        | **#if** _Expression_
        
    
      
         
        | **#elif** _Expression_
        
    
      
         
        | **#else**
        
    
      
         
        | **#endif**
        
    
      
         
        | are used to check flag(s) by analysing _**Expression**_.
    
    Expression consist of test flag clauses that can be mixed with booleans
    operators and grouped with parenthesis `**(**...**)** '.  
    
    Only following operators are supported (comparison's are not) :
    
      
        |  
        | **& &**
        | (AND)
        
    
      
         
        | **||**
        | (OR)
        
    
      
         
        | **!**
        | (NOT)
        
    
    
      
    
    A clause consist of a flag existence test (not a value test), by using the
    following keywords :  
    
    
      
         
        | **defined** _FlagName_
        
    
      
         
        | used for special purpose and may not be used outside Dassault Systmes
        
    
      
         
        |  
        
    
      
         
        | **os** _OSName_
        
    
      
         
        | test predefined flags set by [mkmk](CAABtlMkmk.md),
          depending on the operating system it is executed. Such flags names
          correspond to value of environment variables _MkmkOS_NAME_ (platform
          notion) and _MkmkOS_Buildtime_ (targeted operating system notion, the
          one for which the code is being built)
        
    
    
      
    
    List of actually supported OS names is described in the following table:
    
      
        Operating system
        | Value of OSName flag
        
    
      
        AIX (IBM)
        | _**AIX**_  
    
          _**aix_a**_
        
    
      
        HP-UX (Hewlett Packard)
        | _**HP-UX**_  
    
          _**hpux_a**_
        
    
      
        SunOS (Sun MicroSystems)
        | _**SunOS**_  
    
          _**solaris_a**_
        
    
      
        Windows (Microsoft)
        | _**Windows_NT**_  
    
          _**intel_a**_ (Windows 2000)  
    
          _**win_a**_ (Windows 98)
        
    
    
    Sample
    This example is not optimized in term of logic but it just shows the syntax
    that can be used to distinguish operating systems specifics in a declarative
    file:
    
    
    
      ... common section (available for all operating systems) ...
     
      _#if os**AIX**_
      ... section available for IBM platform ...
    
      _#elif os**SunOS**_
      ... section available for SUN platform ...
    
      _#elif os**HP-UX**_
      ... section available for HP platform ...
    
      _#elif os**Windows_NT**_
      ... section available for Windows platform (intel_a, win_a ) ...
    
      
    
    
    _#if os**intel_a**_
      ... section available for Windows NT operating systems ...
    _#elif os**win_a**_
      ... section available for Windows 98 operating system ...
    _#endif_ /* "**#if os intel_a** " block closing instruction */
    _#else_ /*"**#if os AIX** " else instruction */
      ... section available all other operating system ...
    _#endif_ /* "**#if os AIX** " block closing instruction */
    ... common section (available for all operating systems) ...

* * *

In Short

  * Preprocessor is invoked for framework and module declarative files
  * It can be used to express specific sections for all (supported) operating systems.

[Top]

* * *

History Version: **1** [Mar 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
