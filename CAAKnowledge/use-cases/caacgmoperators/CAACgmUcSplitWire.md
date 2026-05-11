---
```vbscript
title: "Splitting a Wire"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAAGMOperatorsSplitWire", "CATICGMHybSplit"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcSplitWire.htm"
converted: "2026-05-11T17:33:49.056921"
```

---
tags: ["CAAGMOperatorsInterfaces", "CAAGMOperatorsSplitWire", "CATICGMHybSplit"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcSplitWire.htm"
converted: "2026-05-11T17:33:49.056921"
Splitting a Wire

---
converted: "2026-05-11T17:33:49.056921"
Splitting a Wire
Use Case
Abstract A wire can be split by another wire, a shell or a vertex.

    * Operator to be Used
    * Use Case Description
      * Case 1: Split a Wire by a Shell when the Shell does not cut the Wire
      * Case 2: Split a Wire by a Wire
      * Case 3: Split a Wire by a Vertex
    * References
---
Operator to be Used To split a wire, use the CATICGMHybSplit operator in GMOperatorsInterfaces. This operator is created by the CATCGMCreateTopSplitWire global function in which the last argument (CATHybSelectionMode) defines the partitions to be kept.  Use Case Description The CAAGMOperatorsSplitWire.m module in CAAGMOperatorsInterfaces.edu framework illustrates how split a wire. This use case is to be run with the splitWireInputs.NCGM input file which is delivered in CAAGMOperatorsInterfaces.edu/FunctionTests/InputData.  If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). Case 1: Split a Wire by a Shell when the Shell does not Cut the Wire The CATHybSelectionMode identifies which partitions of the split body are kept. For a wire cut by a shell:

Operator to be Used To split a wire, use the CATICGMHybSplit operator in GMOperatorsInterfaces. This operator is created by the CATCGMCreateTopSplitWire global function in which the last argument (CATHybSelectionMode) defines the partitions to be kept.  Use Case Description The CAAGMOperatorsSplitWire.m module in CAAGMOperatorsInterfaces.edu framework illustrates how split a wire. This use case is to be run with the splitWireInputs.NCGM input file which is delivered in CAAGMOperatorsInterfaces.edu/FunctionTests/InputData.  If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). Case 1: Split a Wire by a Shell when the Shell does not Cut the Wire The CATHybSelectionMode identifies which partitions of the split body are kept. For a wire cut by a shell:
POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE
    The partitions to keep are pointed to by the shell orientation.
NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE
    The partitions to remove are pointed to by the shell orientation.
BOTH_SIDES
    Should not be used.
When the wire to be split and the shell do not intersect, the CATICGMHybSplit throws an exception with a message indicating that the input bodies do not intersect. You can use the CATICGMHybSplit::SetKeepHalfSpaceMode method to indicate which partition of the space is to be kept (TRUE must be specified).With the input data below Fig.1 Split a wire by a plane (shell orientation in blue) ![SplitWireByShell Input Data](images/CGM_splitWireByShell_0.png)

---
The partitions to remove are pointed to by the shell orientation.
BOTH_SIDES
Should not be used.
When the wire to be split and the shell do not intersect, the CATICGMHybSplit throws an exception with a message indicating that the input bodies do not intersect. You can use the CATICGMHybSplit::SetKeepHalfSpaceMode method to indicate which partition of the space is to be kept (TRUE must be specified).With the input data below Fig.1 Split a wire by a plane (shell orientation in blue) ![SplitWireByShell Input Data](images/CGM_splitWireByShell_0.png)
and the code below:

    CATICGMHybSplit * pSplitWireByShellOpe = CATCGMCreateTopSplitWire (piGeomFactory, &topdata;,
      pWire1, pShellBody, POSITIVE_NEGATIVE_SIDE);

    ...
and the code below:
CATICGMHybSplit * pSplitWireByShellOpe = CATCGMCreateTopSplitWire (piGeomFactory, &topdata;,
pWire1, pShellBody, POSITIVE_NEGATIVE_SIDE);
    pSplitWireByShellOpe->SetKeepHalfSpaceMode(TRUE);
    pSplitWireByShellOpe->Run();
    CATBody * pSplitWireByShellResult = pSplitWireByShellOpe->GetResult();

    ...
pSplitWireByShellOpe->SetKeepHalfSpaceMode(TRUE);
pSplitWireByShellOpe->Run();
CATBody * pSplitWireByShellResult = pSplitWireByShellOpe->GetResult();
    pSplitWireByShellOpe->Release(); pSplitWireByShellOpe=NULL;

---
CATBody * pSplitWireByShellResult = pSplitWireByShellOpe->GetResult();
pSplitWireByShellOpe->Release(); pSplitWireByShellOpe=NULL;
you get this result: Fig.2 Split a wire by a plane: result  ![Split a wire by a plane: Result](images/CGM_splitWireByShell_1.png)

---
pSplitWireByShellOpe->Release(); pSplitWireByShellOpe=NULL;
you get this result: Fig.2 Split a wire by a plane: result  ![Split a wire by a plane: Result](images/CGM_splitWireByShell_1.png)
The same result is obtained if you specify POSITIVE_POSITIVE_SIDE for the CATHybSelectionMode. But, if you specify NEGATIVE_NEGATIVE_SIDE or NEGATIVE_POSITIVE_SIDE, the result is NULL. Case 2: Split a Wire by a Wire The CATHybSelectionMode identifies which partitions of the split wire are kept. When splitting a wire by a wire, the split partitions are alternately assigned NEGATIVE and POSITIVE values, the first partition being NEGATIVE when moving along the direction of the wire to be cut (going from the start vertex to the end vertex). The result is independent on the cutting wire orientation.

POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE
    The POSITIVE partitions are kept.
NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE
    The POSITIVE partitions are removed.
BOTH_SIDES
    Should not be used.
With the input data below: Fig.3 Split a wire by a wire: partitioning  ![Split a wire by a wire](images/CGM_splitWireByWire_0.png)

---
The POSITIVE partitions are removed.
BOTH_SIDES
Should not be used.
With the input data below: Fig.3 Split a wire by a wire: partitioning  ![Split a wire by a wire](images/CGM_splitWireByWire_0.png)
and the code below:

    CATICGMHybSplit * pSplitWireByWireOpe = CATCGMCreateTopSplitWire (piGeomFactory, &topdata;, pWire1, pWire2,
    		POSITIVE_NEGATIVE_SIDE);

    ...
and the code below:
CATICGMHybSplit * pSplitWireByWireOpe = CATCGMCreateTopSplitWire (piGeomFactory, &topdata;, pWire1, pWire2,
POSITIVE_NEGATIVE_SIDE);
    pSplitWireByWireOpe->Run();
    CATBody * pSplitWireByWireResult = pSplitWireByWireOpe->GetResult();
    pSplitWireByWireOpe->Release(); pSplitWireByWireOpe=NULL;

---
CATBody * pSplitWireByWireResult = pSplitWireByWireOpe->GetResult();
pSplitWireByWireOpe->Release(); pSplitWireByWireOpe=NULL;
you get this result: Fig.4 Split a wire by a wire: result  ![Split a wire by a wire: Result](images/CGM_splitWireByWire_1.png)

---
you get this result: Fig.4 Split a wire by a wire: result  ![Split a wire by a wire: Result](images/CGM_splitWireByWire_1.png)
```vbscript
Case 3: Split a Wire by a Vertex The wire is split into two partitions. The CATHybSelectionMode identifies which partition of the split wire is kept.  The NEGATIVE part is the first one in the wire when moving along the wire direction (going from the start vertex to the end vertex).

```

POSITIVE_POSITIVE_SIDE or POSITIVE_NEGATIVE_SIDE
    The POSITIVE partitions are kept.
NEGATIVE_POSITIVE_SIDE or NEGATIVE_NEGATIVE_SIDE
    The POSITIVE partitions are removed.
BOTH_SIDES
    Should not be used.
With the input data below: Fig.5 Split a wire by a vertex: input data (splitting vertex in green) ![Split a wire by a vertex: Result](images/CGM_splitWireByVertex_0.png)

---
The POSITIVE partitions are removed.
BOTH_SIDES
Should not be used.
With the input data below: Fig.5 Split a wire by a vertex: input data (splitting vertex in green) ![Split a wire by a vertex: Result](images/CGM_splitWireByVertex_0.png)
and the code below:

    CATBody * pVertexInVolumeBody  =  piGeomFactory->CreateBody();
    CATVertexInVolume *  pVertexInVolume = NULL;
```vbscript
    if  (!!pVertexInVolumeBody)

```

    {
CATBody * pVertexInVolumeBody  =  piGeomFactory->CreateBody();
CATVertexInVolume *  pVertexInVolume = NULL;
if  (!!pVertexInVolumeBody)
```vbscript
```vbscript
    		pVertexInVolume =  pVertexInVolumeBody->CreateVertexInVolume();
    		if  (!!pVertexInVolume)

```

```

    		{
```vbscript
if  (!!pVertexInVolumeBody)
```vbscript
```vbscript
pVertexInVolume =  pVertexInVolumeBody->CreateVertexInVolume();
if  (!!pVertexInVolume)
```

```

    			pVertexInVolume->AddCell(pVertex);
    			pVertexInVolumeBody->AddDomain(pVertexInVolume);
```

    		}
    }
pVertexInVolume->AddCell(pVertex);
pVertexInVolumeBody->AddDomain(pVertexInVolume);
    CATICGMHybSplit * pSplitWireByVertexOpe = CATCGMCreateTopSplitWire (piGeomFactory, &topdata;, pWire1,
    		pVertexInVolumeBody, POSITIVE_NEGATIVE_SIDE);

    ...
CATICGMHybSplit * pSplitWireByVertexOpe = CATCGMCreateTopSplitWire (piGeomFactory, &topdata;, pWire1,
pVertexInVolumeBody, POSITIVE_NEGATIVE_SIDE);
    pSplitWireByVertexOpe->Run();
    CATBody * pSplitWireByVertex = pSplitWireByVertexOpe->GetResult();

---
pSplitWireByVertexOpe->Run();
CATBody * pSplitWireByVertex = pSplitWireByVertexOpe->GetResult();
you get this result: Fig.6 Split a wire by a vertex: result  ![Split a wire by a vertex: Result](images/CGM_splitWireByVertex_1.png)

---
CATBody * pSplitWireByVertex = pSplitWireByVertexOpe->GetResult();
you get this result: Fig.6 Split a wire by a vertex: result  ![Split a wire by a vertex: Result](images/CGM_splitWireByVertex_1.png)
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)

[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)
History Version: **1** [Feb 2012] | Document created
---|---
