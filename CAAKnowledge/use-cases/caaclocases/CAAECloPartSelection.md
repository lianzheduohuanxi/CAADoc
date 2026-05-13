---
title: "Part Selection"
category: "use case"
module: "CAACloUseCases"
tags: "["CAACommonLayoutItf", "CAACloPartSelection", "CATICloPartSelection", "CATICatalogDescription", "CATIUnknownList", "CAAECloPartSelection", "CATICkeParm"]"
source_file: "Doc/online/CAACloUseCases/CAAECloPartSelection.htm"
converted: "2026-05-11T17:33:49.550794"
---
tags: ["CAACommonLayoutItf", "CAACloPartSelection", "CATICloPartSelection", "CATICatalogDescription", "CATIUnknownList", "CAAECloPartSelection", "CATICkeParm"]
source_file: "Doc/online/CAACloUseCases/CAAECloPartSelection.htmmd"
converted: "2026-05-11T17:33:49.550794"
Equipment & Systems |  Systems Layout |  Part Selection _How to customize part selection_

converted: "2026-05-11T17:33:49.550794"
Equipment & Systems |  Systems Layout |  Part Selection _How to customize part selection_
Use Case

* * *

Abstract This article discusses the CAAECloPartSelection use case.
    * **What You Will Learn With This Use Case**
    * **The CAAECloPartSelection Use Case**
      * What Does CAAECloPartSelection Do
      * How to use CAAECloPartSelection
      * Where to Find the CAAECloPartSelection Code
    * **Step-by-Step**
    * **In Short**
---

* * *

What You Will Learn With This Use Case This use case is intended to show you how to customize the part selection during part placement using the interface CATICloPartSelection. During part placement, one or more parts that can be placed are located in the part or the specification catalog.  This list of the parts found are displayed on the part selection panel to allow designer to select one of the part to be placed.  This interface can be implemented to provide additional processing to further select the suitable parts. [Top] The CAAECloPartSelection Use Case CAAECloPartSelection is a use case of the CAACommonLayoutItf.edu framework that illustrates the capabilities to provide custom code to select the desired parts to be available for user selection during part placement. [Top] What Does CAAECloPartSelection Do The goal of CAAECloPartSelection is to show you how to use the interfaces CATICloPartSelection from CATCommonLayoutInterfaces framework. [Top] How to Use CAAECloPartSelection To use CAAECloPartSelection , you will need to set up the build time environment, then compile CAAECloPartSelection along with its prerequisites, set up the run time environment, and then place a part.
    1. Customize your implementation in CAAECloPartSelection.cpp
    2. Remove #CAA# before CATPiping  CATICloPartSelection in CNext/code/dictionary/CAACommonLayoutItf.dico to enable the implementation for CATICloPartSelection.
    3. Compile the source code. See the compiler documentation for more information.
    4. Copy the shared library CAACloPartSelection.dll or libCAACloPartSelection depending on the operating system to your run time bin directory.
    5. Copy the CAACommonLayoutItf.edu.dico to your run time dictionary directory.
    6. Do the following to test your implementation:

       * Start CNext and select Piping Design workbench.
       * Route a run and place an Elbow.
       * CAAECloPartSelection should be invoked and a elbow should be created since there is only one elbow selected.
[Top] Where to Find the CAAECloPartSelection Code CAAECloPartSelection code is located in the CAACloPartSelection.m use case module of the CAACommonLayoutItf.edu framework: Windows | `InstallRootDirectory/CAACommonLayoutItf.edu/CAACloPartSelection.m/src/CAAECloPartSelection.cpp`
---|---
Unix | `InstallRootDirectory/CAACommonLayoutItf.edu/CAACloPartSelection.m/src/CAAECloPartSelection.cpp`
The following contains the dictionary file that references the implementation: Windows | `InstallRootDirectory/CAACommonLayoutItf.edu/CNext/code/dictionary/CAACommonLayoutItf.edu.dico`

Unix | `InstallRootDirectory/CAACommonLayoutItf.edu/CAACloPartSelection.m/src/CAAECloPartSelection.cpp`
The following contains the dictionary file that references the implementation: Windows | `InstallRootDirectory/CAACommonLayoutItf.edu/CNext/code/dictionary/CAACommonLayoutItf.edu.dico`
Unix | `InstallRootDirectory/CAACommonLayoutItf.edu/CNext/code/dictionary/CAACommonLayoutItf.edu.dico`
where `InstallRootDirectory` is the root directory of your CAA V5 installation. [Top] Step-by-Step
    1. Prolog
    2. Inspecting the filtering parameters
    3. Inspecting the sorting parameters
    4. Filtering the parts

[Top] Prolog The user will have to provide Implementation for CATICloPartSelection. The interface is called directly by the commands that create the part during part placement.  [Top] Inspecting the filtering parameters Prints out the filtering parameter for information and allocates the output oListDescription.

    //dump out all the filtering parameters
3. Inspecting the sorting parameters
4. Filtering the parts
      unsigned int nFilterParameters = 0;
      if ( iLFilterParameters ) ((CATIUnknownList*)iLFilterParameters)->Count(&nFilterParameters);
      cout << "list of filter parameters:" << endl;
```vbscript
      for ( unsigned int n = 0; n < nFilterParameters; n++ )

```

      {
unsigned int nFilterParameters = 0;
if ( iLFilterParameters ) ((CATIUnknownList*)iLFilterParameters)->Count(&nFilterParameters);
cout << "list of filter parameters:" << endl;
for ( unsigned int n = 0; n < nFilterParameters; n++ )
        IUnknown* piUnknown = NULL;

        ((CATIUnknownList*)iLFilterParameters)->Item( n, &piUnknown );
cout << "list of filter parameters:" << endl;
for ( unsigned int n = 0; n < nFilterParameters; n++ )
IUnknown* piUnknown = NULL;
```vbscript
        if ( piUnknown )

```

        {
IUnknown* piUnknown = NULL;
if ( piUnknown )
          CATUnicodeString parmValue;
          CATICkeParm* piCkeParm = NULL;
          piUnknown->QueryInterface(IID_CATICkeParm,(void**)&piCkeParm);
```vbscript
          if ( piCkeParm )

```

          {
CATUnicodeString parmValue;
CATICkeParm* piCkeParm = NULL;
piUnknown->QueryInterface(IID_CATICkeParm,(void**)&piCkeParm);
if ( piCkeParm )
            cout << (piCkeParm->Name(#)).ConvertToChar(#) << "=" << (piCkeParm->Show(#)).ConvertToChar(#) << endl;
            piCkeParm->Release(#);   piCkeParm = NULL;

          }
```vbscript
if ( piCkeParm )
cout << (piCkeParm->Name(#)).ConvertToChar(#) << "=" << (piCkeParm->Show(#)).ConvertToChar(#) << endl;
piCkeParm->Release(#);   piCkeParm = NULL;
          piUnknown->Release(#); piUnknown = NULL;
```

        }
      }

---
Inspecting the sorting parameters. Prints out the sorting parameters for information.

    //dump out all the parameters used for sorting the order of the descriptions
Inspecting the sorting parameters. Prints out the sorting parameters for information.
      unsigned int nSortParameters = 0;
      if ( iLSortParameters ) ((CATIUnknownList*)iLSortParameters)->Count(&nSortParameters);
      cout << "list of sort parameters:" << endl;
```vbscript
      for ( n = 0; n < nSortParameters; n++ )

```

      {
unsigned int nSortParameters = 0;
if ( iLSortParameters ) ((CATIUnknownList*)iLSortParameters)->Count(&nSortParameters);
cout << "list of sort parameters:" << endl;
for ( n = 0; n < nSortParameters; n++ )
        IUnknown* piUnknown = NULL;

        ((CATIUnknownList*)iLSortParameters)->Item( n, &piUnknown );
cout << "list of sort parameters:" << endl;
for ( n = 0; n < nSortParameters; n++ )
IUnknown* piUnknown = NULL;
```vbscript
        if ( piUnknown )

```

        {
IUnknown* piUnknown = NULL;
if ( piUnknown )
          CATUnicodeString parmValue;
          CATICkeParm* piCkeParm = NULL;
          piUnknown->QueryInterface(IID_CATICkeParm,(void**)&piCkeParm);
```vbscript
          if ( piCkeParm )

```

          {
CATUnicodeString parmValue;
CATICkeParm* piCkeParm = NULL;
piUnknown->QueryInterface(IID_CATICkeParm,(void**)&piCkeParm);
if ( piCkeParm )
            cout << (piCkeParm->Name(#)).ConvertToChar(#) << "=" << (piCkeParm->Show(#)).ConvertToChar(#) << endl;
            piCkeParm->Release(#);   piCkeParm = NULL;

          }
```vbscript
if ( piCkeParm )
cout << (piCkeParm->Name(#)).ConvertToChar(#) << "=" << (piCkeParm->Show(#)).ConvertToChar(#) << endl;
piCkeParm->Release(#);   piCkeParm = NULL;
          piUnknown->Release(#); piUnknown = NULL;
```

        }
      }

---
Filtering the parts.  For this example, if the description has a keyword "CenterToFace", select it only if the keyword has a value equal or greater than 3in (0.076meter.)  All other cases, all descriptions in iListDescription are stored in oListDescription and returned to allow for user selection.

    //checking the description selected
Filtering the parts.  For this example, if the description has a keyword "CenterToFace", select it only if the keyword has a value equal or greater than 3in (0.076meter.)  All other cases, all descriptions in iListDescription are stored in oListDescription and returned to allow for user selection.
      unsigned int nDescriptions = 0;
      if ( iListDescription ) ((CATIUnknownList*)iListDescription)->Count(&nDescriptions);
      int selected = 0;
      cout << "list of descriptions:" << endl;
```vbscript
      for ( n = 0; n < nDescriptions; n++ )

```

      {
```cpp
if ( iListDescription ) ((CATIUnknownList*)iListDescription)->Count(&nDescriptions);
int selected = 0;
cout << "list of descriptions:" << endl;
for ( n = 0; n < nDescriptions; n++ )
        IUnknown* piUnknown = NULL;
```

        ((CATIUnknownList*)iListDescription)->Item( n, &piUnknown );
cout << "list of descriptions:" << endl;
for ( n = 0; n < nDescriptions; n++ )
IUnknown* piUnknown = NULL;
```vbscript
        if ( piUnknown )

```

        {
IUnknown* piUnknown = NULL;
if ( piUnknown )
          CATUnicodeString parmValue;
          CATICatalogDescription* piDescription = NULL;
          piUnknown->QueryInterface(IID_CATICatalogDescription,(void**)&piDescription);
```vbscript
          if ( piDescription )

```

          {
CATUnicodeString parmValue;
CATICatalogDescription* piDescription = NULL;
piUnknown->QueryInterface(IID_CATICatalogDescription,(void**)&piDescription);
if ( piDescription )
            CATUnicodeString descName;
            piDescription->GetName(descName);
            cout << descName.ConvertToChar(#) << endl;

```vbscript
            if ( iuPartType == "PipingNonReduceElbow" )

```

            {
              //add code for filtering...use CenterToFace >= 3in only for example
cout << descName.ConvertToChar(#) << endl;
if ( iuPartType == "PipingNonReduceElbow" )
              double oValue = 0.0;

              HRESULT rcode = piDescription->GetDouble ("CenterToFace", oValue);
```vbscript
              if ( SUCCEEDED(rcode)  )

```

              {
double oValue = 0.0;
HRESULT rcode = piDescription->GetDouble ("CenterToFace", oValue);
if ( SUCCEEDED(rcode)  )
```vbscript
```vbscript
                if ( oValue >= 0.076 ) oListDescription->Add(selected++, piUnknown);

```

```

              }
HRESULT rcode = piDescription->GetDouble ("CenterToFace", oValue);
if ( SUCCEEDED(rcode)  )
```vbscript
if ( oValue >= 0.076 ) oListDescription->Add(selected++, piUnknown);
```

              else

                //keyword "CenterToFace" not found, skip filtering
```vbscript
if ( oValue >= 0.076 ) oListDescription->Add(selected++, piUnknown);
else
                oListDescription->Add(selected++, piUnknown);
```

            }
else
oListDescription->Add(selected++, piUnknown);
            else

            {
oListDescription->Add(selected++, piUnknown);
else
              oListDescription->Add(selected++, piUnknown);

            }
else
oListDescription->Add(selected++, piUnknown);
            piDescription->Release(#); piDescription=NULL;

          }
oListDescription->Add(selected++, piUnknown);
piDescription->Release(#); piDescription=NULL;
          piUnknown->Release(#); piUnknown = NULL;

        }
      }
piDescription->Release(#); piDescription=NULL;
piUnknown->Release(#); piUnknown = NULL;
      if ( selected > 0 ) RC = S_OK;
      else RC = E_FAIL;
      return RC;

>

---
[Top]   [Top]

* * *

In Short This use case has demonstrated how to the interfaces CATICloPartSelection from CATCommonLayoutInterfaces framework to perform part selection. [Top]

* * *

References |
---|---

* * *

History Version: **1** [May 2004] | Document created
---|---
[Top]

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
