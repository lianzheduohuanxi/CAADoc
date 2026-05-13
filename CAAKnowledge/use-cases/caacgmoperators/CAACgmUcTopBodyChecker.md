---
```vbscript
title: "Using the Body Checker"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CATICGMContainer", "CAADoc", "CAAGMOperatorsBodyChecker", "CATICGMObject", "CAATopBodyChecker", "CATICGMBodyChecker"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopBodyChecker.htmmd"
converted: "2026-05-11T17:33:49.090808"
```

---
tags: ["CAAGMOperatorsInterfaces", "CATICGMContainer", "CAADoc", "CAAGMOperatorsBodyChecker", "CATICGMObject", "CAATopBodyChecker", "CATICGMBodyChecker"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopBodyChecker.htmmd"
converted: "2026-05-11T17:33:49.090808"
Using the Body Checker

---
converted: "2026-05-11T17:33:49.090808"
Using the Body Checker
Use Case
Abstract A CGM surface which exhibits curvature radii less than the resolution is not valid. The "Body Checker" can be used to determine whether a surface is valid with respect to this criteria.

    * What You Will Learn With This Use Case
    * The CAAGMOperatorsBodyChecker Use Case
      * What Does CAAGMOperatorsBodyChecker Do?
      * How to Launch CAAGMOperatorsBodyChecker
      * Where to Find the CAAGMOperatorsBodyChecker Code
    * Step-by-Step
    * References
---
What You Will Learn With This Use Case This use case is intended to help you determine whether a surface is valid in terms of curvature radius. This is done by using the CATICGMBodyChecker.h interface. Today, the rule to check whether a shell self-intersects is not implemented yet (see the interface documentation in the encyclopedia). The CAAGMOperatorsBodyChecker Use Case CAAGMOperatorsBodyChecker is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. What Does CAAGMOperatorsBodyChecker Do? The CAAGMOperatorsBodyChecker use case:
    * Loads the container and retrieves the body to be checked.
    * Creates and uses the body checker.
    * Displays the diagnosis.
    * Closes the container.
What You Will Learn With This Use Case This use case is intended to help you determine whether a surface is valid in terms of curvature radius. This is done by using the CATICGMBodyChecker.h interface. Today, the rule to check whether a shell self-intersects is not implemented yet (see the interface documentation in the encyclopedia). The CAAGMOperatorsBodyChecker Use Case CAAGMOperatorsBodyChecker is a use case of the CAAGMOperatorsInterfaces.edu framework that illustrates the GMOperatorsInterfaces framework capabilities. What Does CAAGMOperatorsBodyChecker Do? The CAAGMOperatorsBodyChecker use case:
How to Launch CAAGMOperatorsBodyChecker To launch CAAGMOperatorsBodyChecker , you will need to set up the build time environment, then compile CAAGMOperatorsBodyChecker.m along with its prerequisites, set up the run time environment, and then execute the use case [1]. `CAAGMOperatorsBodyChecker e/bodyChecker1.NCGM` where `bodyChecker1.NCGM` is the input file delivered in the CAAGMOperatorsInterfaces.edu/FunctionTests/InputData file [1].  Where to Find the CAAGMOperatorsBodyChecker Code The CAAGMOperatorsBodyChecker use case is made of a main named CAATopBodyChecker.cpp located in the CAAGMOperatorsBodyChecker.m module of the CAAGMOperatorsInterfaces.edu framework: `InstallRootFolder/CAADoc/CAAGMOperatorsInterfaces.edu/CAAGMOperatorsBodyChecker.m/` where `InstallRootFolder` [1] is the folder where the API CD-ROM is installed. Step-by-Step There are thee main steps in CAATopBodyChecker.cpp:
    1. Loading the Container and Retrieving the Body to Be Checked
    2. Creating and Running the CATICGMBodyChecker Object
    3. Displaying the Diagnosis
    4. Closing the Container
Loading the Container and Retrieving the Body to Be Checked The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular). In this use case, the factory is defined by reading a NCGM file that was previously stored,  the global function `::CATLoadCGMContainer` must be used to retrieve the factory. The body is retrieved by using the CATICGMContainer::FindObjectFromTag method. There is only one body in the container which is loaded. 2353356 is the body tag.

    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);

    ...
4. Closing the Container
Loading the Container and Retrieving the Body to Be Checked The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular). In this use case, the factory is defined by reading a NCGM file that was previously stored,  the global function `::CATLoadCGMContainer` must be used to retrieve the factory. The body is retrieved by using the CATICGMContainer::FindObjectFromTag method. There is only one body in the container which is loaded. 2353356 is the body tag.
CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(2353356);

Creating and Running the CATICGMBodyChecker Object The CATICGMBodyChecker object is created by using the `CATICGMBodyChecker::Create` static function. To activate all the checker rules, you must specify the `BodyChkModeFull` mode. So far, only the check of the curvature radius is implemented for curves and surfaces.

    CATICGMBodyChecker * pBodyChecker = CATICGMBodyChecker::Create(piGeomFactory, &topdata, piBodyToBeChecked);

    //
    // b - Specify the Full Mode
Creating and Running the CATICGMBodyChecker Object The CATICGMBodyChecker object is created by using the `CATICGMBodyChecker::Create` static function. To activate all the checker rules, you must specify the `BodyChkModeFull` mode. So far, only the check of the curvature radius is implemented for curves and surfaces.
CATICGMBodyChecker * pBodyChecker = CATICGMBodyChecker::Create(piGeomFactory, &topdata, piBodyToBeChecked);
```vbscript
    if (NULL != pBodyChecker)

```

    {
CATICGMBodyChecker * pBodyChecker = CATICGMBodyChecker::Create(piGeomFactory, &topdata, piBodyToBeChecked);
if (NULL != pBodyChecker)
    CATCGMBodyCheckMode eChkMode = CATCGMBodyChkModeFull;
    pBodyChecker->SetCheckMode(eChkMode);

    //
    // c - Run the operator
CATCGMBodyCheckMode eChkMode = CATCGMBodyChkModeFull;
pBodyChecker->SetCheckMode(eChkMode);
    CATBoolean bRet = FALSE;
```vbscript
    bRet = pBodyChecker->Run(#);

```

    ....

CATBoolean bRet = FALSE;
bRet = pBodyChecker->Run(#);
Displaying the Diagnosis All the errors found in the body to be checked are displayed if you have specified the Full Mode. If the light mode is specified, several errors of the same type can be diagnosed.

    pBodyChecker->BeginningDiagnosis(#);
    while( pBodyChecker->NextDiagnosis(#) )

    {
Displaying the Diagnosis All the errors found in the body to be checked are displayed if you have specified the Full Mode. If the light mode is specified, several errors of the same type can be diagnosed.
pBodyChecker->BeginningDiagnosis(#);
while( pBodyChecker->NextDiagnosis(#) )
    CATUnicodeString strDiagnosis;
    pBodyChecker->GetDiagnosis(strDiagnosis);

    cout << strDiagnosis.ConvertToChar(#) << endl;

    }

pBodyChecker->GetDiagnosis(strDiagnosis);
cout << strDiagnosis.ConvertToChar(#) << endl;
This is the message which is displayed on the standard output at execution:

    CATTabulatedCylinder[2353360] : Surface has invalid curvature
    Invalid curvature radius found = 0.000403962 <= Allowed [0.001]
    At surface parameter = (PatchU=48, ParamU=373.951; PatchV=1, ParamV=0)

Closing the Container The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.

    //
     // Closes the container
     //
     **::CATCloseCGMContainer**(piGeomFactory);

References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] | [Overview of the Topological Operators](CAACgmUcTopOverview.md)
History Version: **1** [Aug 2004] | Document created
---|---
