---
```vbscript
title: "New Geometric Modeler Interfaces Layer"
category: "use-case"
module: "CAACenQuickRefs"
tags: ["CATICGMTopWire_h_", "CATIPGMTopBlendInt", "CAA2Usage", "CATICGMxxx", "CATIPGMOperator", "CAACGMItfVisualStudio", "CATIPGMSolidCylinder", "CAA2Level", "CATIPGMTopBlend", "CATICGMTopWire", "CAAMathematics", "CATIA", "CAACGMItfMacros", "CATICGMGeoToTopOperator"]
source_file: "Doc/online/CAACenQuickRefs/CAACenGobInterfacesMigration.htmmd"
converted: "2026-05-11T17:33:46.528911"
```

---
tags: ["CATICGMTopWire_h_", "CATIPGMTopBlendInt", "CAA2Usage", "CATICGMxxx", "CATIPGMOperator", "CAACGMItfVisualStudio", "CATIPGMSolidCylinder", "CAA2Level", "CATIPGMTopBlend", "CATICGMTopWire", "CAAMathematics", "CATIA", "CAACGMItfMacros", "CATICGMGeoToTopOperator"]
source_file: "Doc/online/CAACenQuickRefs/CAACenGobInterfacesMigration.htmmd"
converted: "2026-05-11T17:33:46.528911"
New Geometric Modeler Interfaces Layer

---
converted: "2026-05-11T17:33:46.528911"
New Geometric Modeler Interfaces Layer
Technical Article
Abstract This article lists the modifications, and their migration path for the Geometric Modeler.

  * The Need for GM Interfaces
  * What Has Changed?
  * The New CAA Frameworks
  * The New GM Interface Description vs. CAA V5 Operators
  * How to Use GM Interfaces vs. CAA V5 Operators
  * Migration Tools
    * The Step-by-Step Migration Procedure
    * How to Fix Compilation Errors
  * Detail of Interfaces Mapping

---
The Need for GM Interfaces One of the CAA V6 architecture goal is to minimize the code size at installation and manage to load the code which is strictly necessary for the achievement of some identified scenarios (open a model, perform measures on it ...). The new interfaces allow an application to load dynamically the dlls which are strictly needed for the execution of a given scenario. What Has Changed? Two interface frameworks are created:

  * GMModelInterfaces to read a model and perform measures
  * GMOperatorsInterfaces to modify a model by using geometric and topological operators

The Tessellation, NewTopologicalObjects, GeometricOperators, TopologicalOperators, FreeFormOperators and AdvancedTopologicalOpe are no longer exposed. Their APIs are exposed through the GMModelInterfaces and GMOperatorsInterfaces frameworks. The New CAA Frameworks Before

  * Mathematics
  * Tessellation
  * AdvancedMathematics
  * GeometricObjects
  * NewTopologicalObjects
  * GeometricOperators
  * TopologicalOperators
  * FreeFormOperators
  * AdvancedTopologicalOpe
  * BasicTopologicalOpe

**Now**

  * CATMathStream
  * Mathematics
  * AdvancedMathematics
  * GeometricObjects
  * GMModelInterfaces
  * GMOperatorsInterfaces

GMModelInterfaces contains interfaces previously contained in the GeometricOperators, NewTopologicalObjects, Tessellation and BasicTopologicalOpe frameworks. GMOperatorsInterfaces contains interfaces previously contained in NewTopologicalObjects, BasicTopologicalOpe, FreeFormOperators and AdvancedTopologicalOpe frameworks. The frameworks below are no longer packaged in the CAA offer:

  * Tessellation
  * NewTopologicalObjects
  * GeometricOperators
  * TopologicalOperators
  * AdvancedTopologicalOpe
  * BasicTopologicalOpe
  * FreeFormOperators.

The New GM Interface Description vs. CAA V5 Operators

  * **Here is an example of a CAA V5 GM operator.**
        #ifndef CATTopWire_h
        #define CATTopWire_h
        /**
        * @CAA2Level L1
        * @CAA2Usage U1
        */
        #include "CATGeoToTopOperator.h"
        ...
        class ExportedByPrimitives CATTopWire :public CATGeoToTopOperator
        {
class ExportedByPrimitives CATTopWire :public CATGeoToTopOperator
          CATCGMVirtualDeclareClass(CATTopWire);
          public:

          /** @nodoc */
```vbscript
CATCGMVirtualDeclareClass(CATTopWire);
public:
          CATTopWire(CATGeoFactory *iFactory,
                     CATTopData * iData);

```

          /** @nodoc */
          ...
```vbscript
CATTopWire(CATGeoFactory *iFactory,
CATTopData * iData);
          virtual ~CATTopWire(#);
```

        }
        /**
         * Creates an operator to build a wire body from several curves...
         ...
         */
        ExportedByPrimitives
          CATTopWire * CATCreateTopWire(CATGeoFactory *iFactory,
                                        CATTopData *iData,...);

        /** @nodoc */
ExportedByPrimitives
CATTopWire * CATCreateTopWire(CATGeoFactory *iFactory,
CATTopData *iData,...);
        ExportedByPrimitives CATBody * CATCreateWire(CATGeoFactory *iFactory,
                                                     CATTopData *iData, ...);

        #endif

  * **Here is a CAA V6 GM interface**
        #ifndef CATICGMTopWire_h_
        #define CATICGMTopWire_h_
        ...
        /**
         * @CAA2Level L1
         * @CAA2Usage U3
         */
        #include "CATGMOperatorsInterfaces.h"
        #include "CATICGMGeoToTopOperator.h"
        ...
        extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopWire;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopWire;
        class ExportedByCATGMOperatorsInterfaces CATICGMTopWire: public CATICGMGeoToTopOperator

        {
extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopWire;
class ExportedByCATGMOperatorsInterfaces CATICGMTopWire: public CATICGMGeoToTopOperator
          public:
            CATICGMTopWire(#);

          protected:
            virtual ~CATICGMTopWire(#); // -> delete can't be called

        }
        /**
         * Creates an operator to build a wire body from several curves...
         ...
        */
        ExportedByCATGMOperatorsInterfaces
          CATICGMTopWire *CATCGMCreateTopWire(CATGeoFactory *iFactory, ...);
        #endif

ExportedByCATGMOperatorsInterfaces
CATICGMTopWire *CATCGMCreateTopWire(CATGeoFactory *iFactory, ...);
How to Use GM Interfaces vs. CAA V5 Operators

  * A code excerpt in CAA V5

        **#include "CATTopWire.h"**
        ...
        **CATTopWire** * pWire0 = ::**CATCreateTopWire**(piGeomFactory,
                                                 &topdata,
                                                 nbcurve0,
                                                 ListOfCurves0,
                                                 curLimits0,
                                                 wireOrientations0);

        ...
nbcurve0,
ListOfCurves0,
curLimits0,
wireOrientations0);
        pWire0->Run(#);

        ...
curLimits0,
wireOrientations0);
pWire0->Run(#);
        CATBody * pWireBody0 = pWire0->GetResult(#);

        ...
        **delete** pWire0; pWire0=NULL;

---
  * Creating, running and releasing a GM operator with CAA V6

        **#include "CATICGMTopWire.h"**
        ...
        **CATICGMTopWire** * pWire0 = ::**CATCGMCreateTopWire**(piGeomFactory,
                                                        &topdata,
                                                        nbcurve0,
                                                        ListOfCurves0,
                                                        curLimits0,
                                                        wireOrientations0);

        ...
nbcurve0,
ListOfCurves0,
curLimits0,
wireOrientations0);
        pWire0->Run(#);

        ...
curLimits0,
wireOrientations0);
pWire0->Run(#);
        CATBody * pWireBody0 = pWire0->GetResult(#);

        ...
pWire0->Run(#);
CATBody * pWireBody0 = pWire0->GetResult(#);
        pWire0->**Release**(#); pWire0=NULL;

---

**List of modifications**

  1. The operator name: CATxxx -> CATICGMxxx
  2. The global function to create the operator:; CATCreatexxx->CATCGMCreatexxx
  3. The way to delete the operator `delete pWire0->pWire0->Release(#)`

Migration Tools A migration tool is provided in GeometricObjects. You can run it:

  * either on a whole framework, the IdentityCard.h, Imakefile.mk and code files (.h, .cpp) will be migrated
  * either on a module, the Imakefile.mk and code files (.h, .cpp) will be migrated.
  * or on a single code file.

The Step-by-Step Migration Procedure **Step 1** Run the tck_list command to display the list of available tck profile identifiers then run the mkmk profile: `tck_profile _myProfile_`
---
```vbscript
Refer to Using TCKs for Accessing Tools for more information.  You can also open a command window from MsDev by using the CAA customization. **Step 2:** Set the CGMITF_WS_DIR environment variable `set CGMITF_WS_DIR=_E/MyWorkspace_`
---
```
**Step 3:**   Run the profile below `CAAMathematics.edu/Data.d/Tools/CGMItfProfile.bat`
---
**Step 4:** Run either command below: `CGMItfMigrate MyFramework`
---
or `CGMItfMigrate MyFramework/MyModule`
---
or `CGMItfMigrate MyFramework/MyModule`
or `CGMItfMigrate MyFramework/MyModule/src/MyCode.cpp`

---
or `CGMItfMigrate MyFramework/MyModule`
or `CGMItfMigrate MyFramework/MyModule/src/MyCode.cpp`
The files generated by this command have the `.CGMItf_new extension` and a log file is generated in the ToolsData/CGMItfMigration folder.  **Step 5:** Run either command below: `CGMItfMerge [-replace_all] MyFramework`

---
or `CGMItfMigrate MyFramework/MyModule/src/MyCode.cpp`
The files generated by this command have the `.CGMItf_new extension` and a log file is generated in the ToolsData/CGMItfMigration folder.  **Step 5:** Run either command below: `CGMItfMerge [-replace_all] MyFramework`
or `CGMItfMerge [-replace_all] MyFramework/MyModule`

---
The files generated by this command have the `.CGMItf_new extension` and a log file is generated in the ToolsData/CGMItfMigration folder.  **Step 5:** Run either command below: `CGMItfMerge [-replace_all] MyFramework`
or `CGMItfMerge [-replace_all] MyFramework/MyModule`
or `CGMItfMerge [-replace_all] MyFramework/MyModule/src/MyCode.cpp`

---
or `CGMItfMerge [-replace_all] MyFramework/MyModule`
or `CGMItfMerge [-replace_all] MyFramework/MyModule/src/MyCode.cpp`
The migrated files together with the CATIA Version 5 files are displayed.
Note: The vdiff32 tool is used by default to display the file differences. If need be, you can specify a different tool by using the `CGMITF_DIFF` environment variable. Exit the vdiff32 application. The question below is displayed:
```vbscript
Do you want to get the migrated source? Y(es)/N(o)/Q(uit) Reply:

```

  * Y, to rename the initial CATIA V5 files with the CGMItf_save extension and replace your initial source by the new one.
  * N not to rename the CATIA V5 files, the CGMItf_new are redisplayed, the initial CATIA V5 files are not renamed.
  * Q to exit directly the vdiff32 application and only keep the CGMItf_new files.

How to Fix Compilation Errors Once you have migrated your application, you have to re-build your code. The migration tools described here above can leave some compilation errors behind. If so,  here is a way to fix the major part of these compilation errors. **Step 1:** When re-compiling your frameworks, redirect the output in a text file. Example: `mkcpl _MyFramework_ >c/temp/traces.txt`
---
**Step 2:** In Visual Studio, install the CGM Interface Migration Macros. To do so, open the directory CAAMathematics.edu/Data.d/CGMItfVisualStudio in your Explorer and double-click on `CAACGMItfVisualStudio.vsmacros`
The `CAACGMItfMacros` macros are now installed. They can be viewed in the Visual Studio Macro Explorer (`Alt+F8`).  ![Visual Studio Macro Explorer](images/CAACenGobImg2.jpg) **Step 3:** The FixCGMItfErrors  macro should be launched first. Double-click the FixCGMItfErrors macro in the tree view above. The dialog box below is displayed.  ![Compilation traces file Dialog Box](images/CAACenGobImg1.jpg) To fill in field, enter the path of your trace file. Click OK. **Step 4:** Fix the other errors by clicking the other macros in the Macro Explorer tree structure. Here are the macro descriptions:

**AddReleasePtr**
    Adds a Release(#) operation onto an operator pointer.
`{ if (MyOperatorPointer) { MyOperatorPointer->Release(#); MyOperatorPointer= 0; }`
---
See Creating, Running and Releasing a GM Operator in CAA V6

**FindInInterfaces**
See Creating, Running and Releasing a GM Operator in CAA V6
    Searches for a pattern in the GM interface frameworks.

**FixCGMItfErrors**
See Creating, Running and Releasing a GM Operator in CAA V6
Searches for a pattern in the GM interface frameworks.
    Specifies your trace file and initializes the error fixing.

**ProtectRelease**
Searches for a pattern in the GM interface frameworks.
Specifies your trace file and initializes the error fixing.
    Checks the operator pointer validity prior to releasing it.
_**Example:**_

    // CAA V5
Checks the operator pointer validity prior to releasing it.
_**Example:**_
    MyOperatorPointer->Release(#);

---
is modified in:

    // CAA V6
    			{ if (MyOperatorPointer) { MyOperatorPointer->Release(#); MyOperatorPointer= 0; }

---
**ReplaceAutoVarByCreate**
    Replaces an automatic variable (incorrect use in CATIA version 5) by an appropriate pointer.
**_Example_** :

    // CAA V5
    {
      CATSolidCylinder cylinder1 (factory, topdata, ..., ...)
      ...
    }

---
which is converted into `// CAA V6 right after migration { CATIPGMSolidCylinder cylinder1 (factory, topdata, ..., ...) ... }

`
---
which is converted into `// CAA V6 right after migration { CATIPGMSolidCylinder cylinder1 (factory, topdata, ..., ...) ... }
does not build because the CATIPGMSolidCylinder class is virtual.
The ReplaceAutoVarByCreate adds the appropriate creation fonctions, as well as the Release(#) statement:

    // CAA V6 after ReplaceAutoVarByCreate is activated
    {
The ReplaceAutoVarByCreate adds the appropriate creation fonctions, as well as the Release(#) statement:
      CATIPGMSolidCylinder *pcylinder1 = CATPGMCreateSolidCylinder(Factory, TopData,p1, p2, p3);

      // ### CGMInterfaces AddRef(#)/Release(#) - BEGIN
      pcylinder1->Release(#); pcylinder1 = NULL;
      // ### CGMInterfaces AddRef(#)/Release(#) - END
    }

---
**ReplaceDeleteByRelease**
    Replaces the previous operator delete by a Release(#). Example:

    // CAA V5
    delete MyOperatorPointer;

---
is modified in:

    // CAA V6
    MyOperatorPointer->Release(#);

---
MyOperatorPointer->Release(#);
The macro takes into account CATSysDeletePtr, CATShDelete, CATPrt_DELETE, SAFE_DELETE, Remove, RemoveMapping.

**SetPrereqWsPath**
MyOperatorPointer->Release(#);
The macro takes into account CATSysDeletePtr, CATShDelete, CATPrt_DELETE, SAFE_DELETE, Remove, RemoveMapping.
    Sets the directory which contains the CGM interface frameworks.

**SetWSPath**
The macro takes into account CATSysDeletePtr, CATShDelete, CATPrt_DELETE, SAFE_DELETE, Remove, RemoveMapping.
Sets the directory which contains the CGM interface frameworks.
    Not to be used

**ValidateEndOfLife**
Sets the directory which contains the CGM interface frameworks.
Not to be used
    Should be launched prior to using VerifyEndOfLifeInFiles. Select a line containing `// ### CGMInterfaces AddRef(#)/Release(#) /- END.`
and run the macro. The  `// ### CGMInterfaces` string is replaced by `// CGMInterfaces` so that it can no longer be treated by the VerifyEndOfLifeInFiles macro.

**VerifyEndOfLifeInFiles**
Not to be used
Should be launched prior to using VerifyEndOfLifeInFiles. Select a line containing `// ### CGMInterfaces AddRef(#)/Release(#) /- END.`
and run the macro. The  `// ### CGMInterfaces` string is replaced by `// CGMInterfaces` so that it can no longer be treated by the VerifyEndOfLifeInFiles macro.
    Searches for the `// ### CGMInterfaces AddRef(#)/Release(#) /- END` and `// ### CGMInterfaces new/delete /- END`
These statements may have been inserted after a `return`! Running the macro helps you to find these statements and relocate them properly if need be (i.e before the return).  Another point to be checked: The CATCatchs block in which these statements should be duplicated.

**VerifyItfInCastInFiles**
and run the macro. The  `// ### CGMInterfaces` string is replaced by `// CGMInterfaces` so that it can no longer be treated by the VerifyEndOfLifeInFiles macro.
Searches for the `// ### CGMInterfaces AddRef(#)/Release(#) /- END` and `// ### CGMInterfaces new/delete /- END`
These statements may have been inserted after a `return`! Running the macro helps you to find these statements and relocate them properly if need be (i.e before the return).  Another point to be checked: The CATCatchs block in which these statements should be duplicated.
    Searches for the prohibited cast operations.
Example:

    // CAA V5
Searches for the prohibited cast operations.
Example:
```vbscript
      _GSDOperator = (CATTopBlendInt*)CATCreateTopBlend (_Factory,...);

```

---
which is converted into

    // CAA V6 right after migration
```vbscript
    			_GSDOperator = (CATIPGMTopBlendInt*)CATPGMCreateTopBlend (_Factory,...);

```

---
```vbscript
_GSDOperator = (CATIPGMTopBlendInt*)CATPGMCreateTopBlend (_Factory,...);
The CAA V5 code is not correct because the CATCreateTopBlend function  returns a CATTopBlend pointer. Casting it as a derived class CATTopBlendInt is not recommended as nothing guarantees that the returned object type matches. It is a potential source of crash.
This is how it should be coded:

```

    // CAA V6 right after migration
The CAA V5 code is not correct because the CATCreateTopBlend function  returns a CATTopBlend pointer. Casting it as a derived class CATTopBlendInt is not recommended as nothing guarantees that the returned object type matches. It is a potential source of crash.
This is how it should be coded:
    CATIPGMTopBlend *pTopBlend = CATPGMCreateTopBlend (_Factory, ...);
```vbscript
    if (pTopBlend != NULL)

```

    {
CATIPGMTopBlend *pTopBlend = CATPGMCreateTopBlend (_Factory, ...);
if (pTopBlend != NULL)
      HRESULT hr = pTopBlend->QueryInterface(IID_CATIPGMTopBlendInt, (void **)&_GSDOperator);
      pTopBlend->Release(#);
      pTopBlend = NULL;

    }

---
pTopBlend->Release(#);
pTopBlend = NULL;
_**Recommendation:**_ Run the **VerifyItfInCastInFiles.** For each cast, verify the class hierarchy:

  * If the target class is a parent class, the cast is safe but probably useless. Try to remove it. The code below (CATIPGMOperator being the parent class of CATIPGMTopBlend):

        // not clear !!!!!!
_**Recommendation:**_ Run the **VerifyItfInCastInFiles.** For each cast, verify the class hierarchy:
        CATIPGMOperator *pOperator = CATPGMCreateTopBlend (_Factory,...);

        ...
        CATIPGMTopBlend *pTopBlend = (CATIPGMTopBlend *)pOperator;

---
CATIPGMOperator *pOperator = CATPGMCreateTopBlend (_Factory,...);
CATIPGMTopBlend *pTopBlend = (CATIPGMTopBlend *)pOperator;
should be replaced by

        CATIPGMTopBlend *pTopBlend = CATPGMCreateTopBlend (_Factory,...);
        CATIPGMOperator *pOperator = pTopBlend;

        ...

---
  * If the target class is a derived class, the cast should be replaced by a `QueryInterface`.

Detail Of Interfaces Mapping Frameworks | Replaced APIs
---|---
Detail Of Interfaces Mapping Frameworks | Replaced APIs
AdvancedTopologicalOpe | [Replaced Interfaces](CAACenBUAdvancedTopologicalOpe.md)
BasicTopologicalOpe | [Replaced Interfaces](CAACenBUBasicTopologicalOpe.md)
FreeFormOperators | [Replaced Interfaces](CAACenBUFreeFormOperators.md)
GeometricObjects | [Replaced Interfaces](CAACenBUGeometricObjects.md)
GeometricOperators | [Replaced Interfaces](CAACenBUGeometricOperators.md)
NewTopologicalObjects | [Replaced Interfaces](CAACenBUNewTopologicalObjects.md)
Tessellation | [Replaced Interfaces](CAACenBUTessellation.md)
TopologicalOperators | [Replaced Interfaces](CAACenBUTopologicalOperators.md)
Some .h files have also been moved into other frameworks, the complete list is available [here](CAACenWhatsNew.htm#CGMArchiR20).

* * *

TopologicalOperators | [Replaced Interfaces](CAACenBUTopologicalOperators.md)
Some .h files have also been moved into other frameworks, the complete list is available [here](CAACenWhatsNew.htm#CGMArchiR20).
History Version: **1** [Oct 2006] | Document created

* * *
