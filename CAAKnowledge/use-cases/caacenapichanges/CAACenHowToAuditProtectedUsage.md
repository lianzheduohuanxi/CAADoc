---
```vbscript
title: "Auditing CAA Code on ProtectedInterfaces Usage"
category: "use-case"
module: "CAACenAPIChanges"
tags: ["CAABlobUIIC", "CAABlob", "CATINamingPart", "CAABlobBlobize", "CAAProtectedChecker", "CAACheckPro", "CAABlobUI", "CAABlobBlobizer"]
source_file: "Doc/online/CAACenAPIChanges/CAACenHowToAuditProtectedUsage.htm"
converted: "2026-05-11T17:33:50.063318"
```

---
tags: ["CAABlobUIIC", "CAABlob", "CATINamingPart", "CAABlobBlobize", "CAAProtectedChecker", "CAACheckPro", "CAABlobUI", "CAABlobBlobizer"]
source_file: "Doc/online/CAACenAPIChanges/CAACenHowToAuditProtectedUsage.htm"
converted: "2026-05-11T17:33:50.063318"
CAA V5 Encyclopedia |    |  Auditing CAA Code on ProtectedInterfaces Usage _How to effectively check ProtectedInterfaces usage in a CAA application_

converted: "2026-05-11T17:33:50.063318"
CAA V5 Encyclopedia |    |  Auditing CAA Code on ProtectedInterfaces Usage _How to effectively check ProtectedInterfaces usage in a CAA application_
Technical Article

* * *

Abstract Your CAA application might use headers coming from the ProtectedInterfaces folders of the frameworks installed from the previous releases of CAA CD-ROMS. Refer to [ CAA V5 Authorized API Identification, Usage, Deprecation, and Stability](../CAADocTechArticles/CAADocLxUsageRules.md) to understand why you shoud get rind of ProtetedInterfaces in your CAA applications. This article describes a procedure allowing you to effectively check such header usage in your CAA application. This procedure uses a tool that is only available on Windows.
      * **Launching the Audit Procedure**
      * **Analyzing the Resulting Trace**
      * **Cleaning-up the Application**
**Notes** :
      * The described process uses undocumented mkmk features that might not work anymore on coming releases
      * Please make sure to run this audit for actual code in production, not for prototypes.
---

* * *

Launching the Audit Procedure
      * Create a workspace containing all the frameworks you want to assess.
You can also use an existing workspace. No source will be modified. A few files will be created in a new framework called DummyFW and files called IdentityCard.mk will be created in the IdentityCard folders of the existing frameworks
.

**Note** : The set of frameworks that you assess must only use Dassault Systmes' frameworks. All frameworks that are not present in this workspace will be considered as Dassault Systmes frameworks in the subsequent steps and usage of their ProtectedInterfaces will so generate traces and compilation errors.

      * Set up a mkmk environment [1] and build the workspace prerequisites:

            E:> **< mkmk_install>**\intel_a\code\command\tck_init
            E:> tck_profile **TCK**
            E:> cd myWorkspace
            E/myWorkspace> mkGetPreq -p ...

---
E:> tck_profile **TCK**
E:> cd myWorkspace
E/myWorkspace> mkGetPreq -p ...
Where:

        * `**< mkmk_install>**` is the root directory where the CAA RADE tools are installed
        * `**TCK**` is the tool level to use. To know which ` **TCK**` you can use, type `**tck_list**` after running `tck_init`, and choose the level that matches your installation among those available.
**Note** :** You can use the C++ Dashboard to perform those steps and then open a CAA command window (Tools/Open Command Window) to perform the following ones.

      * Use the **CAACheckPro.bat** utility. It basically:
        * Removes any derived objects
        * Completely rebuilds the workspace
        * Launches the analyzer that creates a dummy framework and new IdentityCard.mk files
        * Changes all frameworks prerequisite modes into Public
        * Rebuilds on new prerequisites and generates dummy .h files, using a special mkmk mode
        * Generates a trace file called **trace_CAACheckPro.out** in the workspace root directory
To run CAACheckPro, type:

    E/myWorkspace> CAACheckPro

---
[Top] Analyzing the Resulting Trace The trace file is divided into the following parts.
      * Standard mkRemoveDo/mkmk (first step) trace

            10/11/2004 12:59:35 : Starting mkRemoveDo
            #mkmk-INFO: Command -> All frameworks of the workspace will be treated.
            #mkmk-INFO: Start of the cleaning procedure.

---
      * Compilation errors issued by this first step must be ignored. Then starts the detection of included ProtectedInterfaces headers
            # Analyzing framework named: E/mkClos4\.\CAABlobUI
            #  NEW Identity card path name: E/mkClos4\.\CAABlobUI\IdentityCard\IdentityCard.mk
            #  Loading dependencies databases named: E/mkClos4\.\CAABlobUI\IdentityCard/Objects/iintel_a/Xref/Dependencies.mkXDB ...
            #   Analyzing dependencies ...
            # +  New direct prerequisite to DummyFW level Public added
            # +  New direct prerequisite to SpecialAPI level Public added
            # ++ **Using non public header** AdvancedTopologicalOpe\ProtectedInterfaces\CATCreateTopProjection.h
            # ++ **Using non public header** MechanicalModeler\ProtectedInterfaces\CATMfAlgoConfigServices.h
            # ++ **Using non public header** MechanicalModeler\ProtectedInterfaces\CATINamingPart.h

---
All the headers listed are the CAA ProtectedInterfaces files **recursively** included by the application, meaning that they may either be directly included by the application headers or included by a CAA Protectednterfaces header included by the application.

      * After detection of such headers, a second build starts with the created IdentityCard files that turn the prerequisites to Dassault Systmes' frameworks to Public
            ## start step: CIbuild   at 10/11/2004-14:28:53
            #make: CAABlobUI intel_a\code\productIC\CAABlobUIIC.script
All the headers listed are the CAA ProtectedInterfaces files **recursively** included by the application, meaning that they may either be directly included by the application headers or included by a CAA Protectednterfaces header included by the application.
            Redefinition line(54) :  AddPrereqComponent("SpecialAPI",Public,NotExported)
            Script Error >>> file: E/mkClos4\BlobUI\IdentityCard\IdentityCard.mk line: 0 compilation failed <<<

---
      * Those IdentityCard compilation errors can be ignored. Then, whenever a ProtectedInterfaces header is **directly** included in the application, the following message appears:

            **CAAProtectedChecker INCLUDEPRO MechanicalModeler/ProtectedInterfaces/CATMfAlgoConfigServices.h

**
---
      * And if this file is actually needed to compile, you will have related compilation errors:

            **E/mkClos4\.\CAABlobUI\CAABlobBlobizer.m\src\CAABlobBlobize.cpp(16) : error C2653: 'CATMfAlgoConfigServices' : is not a class or namespace name
            E/mkClos4\.\CAABlob\CAABlobBlobizer.m\src\CAABlobBlobize.cpp(17) : error C2065: 'CreateConfigurationData' : undeclared identifier**

---
**Notes** :
      * Error messages may also be issued because of modifications in the CAA API
      * Please ignore the errors about CATWarningPromote.h, TIE_CATISelectShow, and CATDataType.h. They will also be ignored by mkmk
[Top] Cleaning-up the Application You now have a list of all the ProtectedInterfaces headers your application is using. To clean-up your applications, you can process as follows:
      1. **Remove unused headers**
`INCLUDEPRO` messages that are not followed by a compilation error denote unused include files. Remove them from the corresponding sources.

1. **Remove unused headers**
      2. **Replace headers with CAA V5R15 Authorized APIs whenever possible** For each remaining compilation error, check:
         1. Whether the error comes from an API change (refer to the [C++ APIs Changes](CAACenAPIChangeDetail.md)) or is deprecated and now removed (refer to the current  Deprecated Index, and refer also to the Deprecated Indexes of the previous releases you may have online, or through the  CAA Internet Site) to know how to replace that header in error
         2. Whether the interfaces, classes, or functions in error could be replaced with one of those listed in [ CAA Authorized APIs Replacing ProtectedInterfaces](CAACenAuditReplacingAPIs.md)
         3. If an equivalent can be found in the C++ API Reference.

      3. **Report the actual ProtectedInterfaces header usage

**Report the remaining problems through the local support that will execute the appropriate "cleaning" support process.
**Note:** When you have corrected some or all of the errors, you may want to check your corrections. Before rebuilding your CAA application in the workspace used above, to temporarily get rid of the modifications brought by the **CAACheckPro.bat** utility, set the following variables:

3. **Report the actual ProtectedInterfaces header usage
    E/myWorkspace> set MKMK_EXPNOINDIRECT=yes
    E/myWorkspace> set MKMK_IDCARDEXTEND=.mk

Then rebuild your CAA application. To resume checking for PortectedInterfaces headers usage, run again the **CAACheckPro.bat** utility. [Top]

* * *

References [1] |  [ Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  CAA Internet Site
[Top]

* * *

History Version: **1** [Jan 2005] | Document created
---|---
[Top]

* * *

_Copyright 1994-2005, Dassault Systmes. All rights reserved._
