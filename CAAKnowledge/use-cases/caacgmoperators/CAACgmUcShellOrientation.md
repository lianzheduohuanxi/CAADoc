---
```vbscript
title: "Modifying the Faces Orientation in a Shell"
category: "use case"
module: "CAACgmOperators"
tags: ["CATICGMTopShellOrientation", "CAAGMOperatorsInterfaces", "CAAGMOperatorsShellOrientation"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcShellOrientation.htm"
converted: "2026-05-11T17:33:49.037216"
```

---
tags: ["CATICGMTopShellOrientation", "CAAGMOperatorsInterfaces", "CAAGMOperatorsShellOrientation"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcShellOrientation.htm"
converted: "2026-05-11T17:33:49.037216"
Modifying the Face Orientations in a Shell  

---  
converted: "2026-05-11T17:33:49.037216"
Modifying the Face Orientations in a Shell
Use Case  
Abstract The faces in a shell do not have necessarily the same orientation as the shell itself. You can invert the orientation of the faces so that they all point to the same direction, the shell orientation.

    * Operator to be Used
    * Use Case Description
    * References  
---  
Abstract The faces in a shell do not have necessarily the same orientation as the shell itself. You can invert the orientation of the faces so that they all point to the same direction, the shell orientation.
Operator to be Used To modify the orientation of faces so that they all have the same orientation as the shell, you must use the CATICGMTopShellOrientation operator which is created by the CATCGMCreateTopShellOrientation global function. This is the only way to modify the orientation of faces in a shell. Use Case Description The CAAGMOperatorsShellOrientation.m module in CAAGMOperatorsInterfaces.edu illustrates how to modify face orientations. This use case is to be run with the FaceOrientation.NCGM input file which is delivered in CAAGMOperatorsInterfaces.edu/FunctionTests/InputData. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). With the input data below: Fig.1 Face Orientation: Input Data ![Shell orientation](images/CGM_shellOrient_input_0.png) 

Operator to be Used To modify the orientation of faces so that they all have the same orientation as the shell, you must use the CATICGMTopShellOrientation operator which is created by the CATCGMCreateTopShellOrientation global function. This is the only way to modify the orientation of faces in a shell. Use Case Description The CAAGMOperatorsShellOrientation.m module in CAAGMOperatorsInterfaces.edu illustrates how to modify face orientations. This use case is to be run with the FaceOrientation.NCGM input file which is delivered in CAAGMOperatorsInterfaces.edu/FunctionTests/InputData. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). With the input data below: Fig.1 Face Orientation: Input Data ![Shell orientation](images/CGM_shellOrient_input_0.png)
and the code below:

    CATICGMTopShellOrientation* ShellOrientationOpe = NULL;

    ...
and the code below:
CATICGMTopShellOrientation* ShellOrientationOpe = NULL;
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
    CATTopData topdata(pConfig, NULL);
    ShellOrientationOpe = CATCGMCreateTopShellOrientation(piGeomFactory, &amptopdata;, piBody );
    CATBody * piInvertedBody = NULL;  

---  
CATTopData topdata(pConfig, NULL);
ShellOrientationOpe = CATCGMCreateTopShellOrientation(piGeomFactory, &amptopdata;, piBody );
CATBody * piInvertedBody = NULL;
you get this result: Fig.2 Result after modifying the face orientation ![Shell Orientation Output Faces](images/CGM_shellOrient_output_0.png)  

---  
CATBody * piInvertedBody = NULL;
you get this result: Fig.2 Result after modifying the face orientation ![Shell Orientation Output Faces](images/CGM_shellOrient_output_0.png)
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  

[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)  
History Version: **1** [Feb 2014] | Document created  
---|---
