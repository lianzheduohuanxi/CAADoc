---
```vbscript
title: "Splitting a Wire"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAAGMOperatorsSplitShell", "CATICGMHybSplit"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcSplitShell.htm"
converted: "2026-05-11T17:33:49.047706"
```

---
tags: ["CAAGMOperatorsInterfaces", "CAAGMOperatorsSplitShell", "CATICGMHybSplit"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcSplitShell.htm"
converted: "2026-05-11T17:33:49.047706"
Splitting a Shell  

---  
converted: "2026-05-11T17:33:49.047706"
Splitting a Shell
Use Case  
Abstract A shell can be split by another shell or a wire.

    * Operator to be Used
    * Use Case Description
      * Case 1: Split a Shell by a Shell
      * Case 2: Split a Shell by a Shell (Extrapolation id Needed)
      * Case 3: Split a Shell by a Wire
    * References  
---  
Operator to be Used To split a shell, use the CATICGMHybSplit operator in GMOperatorsInterfaces. This operator is created by the CATCGMCreateTopSplitShell global function in which the last argument (CATHybSelectionMode) defines the partitions to be kept.  Use Case Description The CAAGMOperatorsSplitShell.m module in CAAGMOperatorsInterfaces.edu framework illustrates how split a shell. This use case is to be run with the splitShellInputs.NCGM input file which is delivered in CAAGMOperatorsInterfaces.edu/FunctionTests/InputData.  If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). Case 1: Split a Shell by a Shell  The CATHybSelectionMode identifies which partitions of the split body are kept. For a shell cut by a shell: 

Operator to be Used To split a shell, use the CATICGMHybSplit operator in GMOperatorsInterfaces. This operator is created by the CATCGMCreateTopSplitShell global function in which the last argument (CATHybSelectionMode) defines the partitions to be kept.  Use Case Description The CAAGMOperatorsSplitShell.m module in CAAGMOperatorsInterfaces.edu framework illustrates how split a shell. This use case is to be run with the splitShellInputs.NCGM input file which is delivered in CAAGMOperatorsInterfaces.edu/FunctionTests/InputData.  If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). Case 1: Split a Shell by a Shell  The CATHybSelectionMode identifies which partitions of the split body are kept. For a shell cut by a shell:
POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE
    The partitions to keep are pointed to by the orientation of the cutting shell.
NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE
    The partitions to remove are pointed to by the orientation of the cutting shell.
BOTH_SIDES
    Should not be used.
With the input data below:  
Fig.1 Split a shell by a shell (shell orientation in blue - shell to be split in light green - splitting shell in dark green) ![SplitShellByShell Input Data 0](images/CGM_splitShellByShell_0.png) 

BOTH_SIDES
Should not be used.
With the input data below:
Fig.1 Split a shell by a shell (shell orientation in blue - shell to be split in light green - splitting shell in dark green) ![SplitShellByShell Input Data 0](images/CGM_splitShellByShell_0.png)
and the code below:

    CATICGMHybSplit * pSplitShellByShellOpe = CATCGMCreateTopSplitShell (piGeomFactory, &topdata;, pShell1, pShell2,
    		NEGATIVE_NEGATIVE_SIDE);

    ...
and the code below:
CATICGMHybSplit * pSplitShellByShellOpe = CATCGMCreateTopSplitShell (piGeomFactory, &topdata;, pShell1, pShell2,
NEGATIVE_NEGATIVE_SIDE);
    pSplitShellByShellOpe->Run();
    CATBody * pSplitShellByShellResult = pSplitShellByShellOpe->GetResult();

    ...
NEGATIVE_NEGATIVE_SIDE);
pSplitShellByShellOpe->Run();
CATBody * pSplitShellByShellResult = pSplitShellByShellOpe->GetResult();
    pSplitShellByShellOpe->Release(); pSplitShellByShellOpe=NULL;

---  
pSplitShellByShellOpe->Release(); pSplitShellByShellOpe=NULL;
you get this result: Fig.2 Split a shell by a shell: result  ![Split a shell by a shell: Result](images/CGM_splitShellByShell_1.png)  

---  
you get this result: Fig.2 Split a shell by a shell: result  ![Split a shell by a shell: Result](images/CGM_splitShellByShell_1.png)
The same result is obtained if you specify NEGATIVE_POSITIVE_SIDE for the CATHybSelectionMode.  Case 2: Split a Shell by a Shell (Extrapolation is Needed) If the shell to be split is the one in dark green and the splitting shell the one in light green, with the code below: 

    CATICGMHybSplit * pSplitShellByShellOpe1 = CATCGMCreateTopSplitShell (piGeomFactory, &topdata;, pShell2, pShell1,
    		NEGATIVE_NEGATIVE_SIDE);

    ...
The same result is obtained if you specify NEGATIVE_POSITIVE_SIDE for the CATHybSelectionMode.  Case 2: Split a Shell by a Shell (Extrapolation is Needed) If the shell to be split is the one in dark green and the splitting shell the one in light green, with the code below:
CATICGMHybSplit * pSplitShellByShellOpe1 = CATCGMCreateTopSplitShell (piGeomFactory, &topdata;, pShell2, pShell1,
NEGATIVE_NEGATIVE_SIDE);
    pSplitShellByShellOpe1->Run();
    CATBody * pSplitShellByShellResult1 = pSplitShellByShellOpe1->GetResult();

    ...
NEGATIVE_NEGATIVE_SIDE);
pSplitShellByShellOpe1->Run();
CATBody * pSplitShellByShellResult1 = pSplitShellByShellOpe1->GetResult();
    pSplitShellByShellOpe1->Release(); pSplitShellByShellOpe1=NULL;  

---  
CATBody * pSplitShellByShellResult1 = pSplitShellByShellOpe1->GetResult();
pSplitShellByShellOpe1->Release(); pSplitShellByShellOpe1=NULL;
you get this result: Fig.3 Split a shell by a shell: extrapolation is needed ![Split a Shell by a Shell \(extrapolation is needed\)](images/CGM_splitShellByShell_2.png)   

---  
pSplitShellByShellOpe1->Release(); pSplitShellByShellOpe1=NULL;
you get this result: Fig.3 Split a shell by a shell: extrapolation is needed ![Split a Shell by a Shell \(extrapolation is needed\)](images/CGM_splitShellByShell_2.png)
Case 3: Split a Shell by a Wire With the input data below:  Fig.4 Split a Shell by a Wire: Splitting Wire in green - wire and shell orientations in blue  ![Split a shell by a wire: Result](images/CGM_splitShellByWire_0.png)   

---  
you get this result: Fig.3 Split a shell by a shell: extrapolation is needed ![Split a Shell by a Shell \(extrapolation is needed\)](images/CGM_splitShellByShell_2.png)
Case 3: Split a Shell by a Wire With the input data below:  Fig.4 Split a Shell by a Wire: Splitting Wire in green - wire and shell orientations in blue  ![Split a shell by a wire: Result](images/CGM_splitShellByWire_0.png)
and the code below: 

    CATICGMHybSplit * pSplitShellByWireOpe = CATCGMCreateTopSplitShell (piGeomFactory, &topdata;,
                       pShell1, pBodyWire1,NEGATIVE_NEGATIVE_SIDE);

    ... 
and the code below:
CATICGMHybSplit * pSplitShellByWireOpe = CATCGMCreateTopSplitShell (piGeomFactory, &topdata;,
pShell1, pBodyWire1,NEGATIVE_NEGATIVE_SIDE);
    pSplitShellByWireOpe->Run();
    CATBody * pSplitShellByWireResult = pSplitShellByWireOpe->GetResult();

    ...
pShell1, pBodyWire1,NEGATIVE_NEGATIVE_SIDE);
pSplitShellByWireOpe->Run();
CATBody * pSplitShellByWireResult = pSplitShellByWireOpe->GetResult();
    pSplitShellByWireOpe->Release(); pSplitShellByWireOpe=NULL;

---  
pSplitShellByWireOpe->Release(); pSplitShellByWireOpe=NULL;
you get this result: Fig.5 Split a Shell by a Wire (wire in right): Result  ![Split a shell by a wire: Result](images/CGM_splitShellByWire_1.png)  

---  
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)  
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)  
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)  
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)  
History Version: **1** [Feb 2012] | Document created  
---|---
