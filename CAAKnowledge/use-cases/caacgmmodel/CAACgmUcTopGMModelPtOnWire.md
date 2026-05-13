---
title: "Creating a Point on a Wire"
category: "use case"
module: "CAACgmModel"
tags: "["CAAGMModelInterfaces", "CATICGMBodyFromLengthOnWire", "CAAGMModelBodyfromLengthOnWire"]"
source_file: "Doc/online/CAACgmModel/CAACgmUcTopGMModelPtOnWire.htm"
converted: "2026-05-11T17:33:48.597676"
---
Creating a Point on a Wire

    ---

    		Use Case

    		Abstract
    		Given a vertex located on a wire (CATWire), you can create a topological point
    		(CATBody)
    		on the wire at a given curvilinear distance from the input vertex
    		(CATVertex).

            * Operator to be Used

            * Use Case Description

            * References

    ---

    Operator to be Used
    The CATICGMBodyFromLengthOnWire operator is to be used.
    This operator has to be created by the CATCGMCreateBodyFromLengthOnWire global function.
    Use Case Description
    The CAAGMModelBodyfromLengthOnWire.m module in CAAGMModelInterfaces.edu
    illustrates how to create a topological point (CATBody) on a wire. This use case
    is to be run with the WireBody.ncgm file which is delivered in the FunctionTests/InputData
    folder. If you are not already
    familiar with geometric modeler use cases, go to

    [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).
illustrates how to create a topological point (CATBody) on a wire. This use case
is to be run with the WireBody.ncgm file which is delivered in the FunctionTests/InputData
folder. If you are not already
familiar with geometric modeler use cases, go to
    With the input data below:

      Fig.1 Create a topological point on a wire : Input Data
    	(origin vertex in purple)

    	![Point on Wire: Input data](images/CGM_point_on_wire_0.png)

    ---

    and the code below:

    CATICGMBodyFromLengthOnWire* pPointOnWire = ::CATCGMCreateBodyFromLengthOnWire(
    	piGeomFactory,

            &topdata;,
CATICGMBodyFromLengthOnWire* pPointOnWire = ::CATCGMCreateBodyFromLengthOnWire(
piGeomFactory,
            pWire,
    	pVertex, // the origin vertex (in purple)
    	300.0);  // the arc length in mm

    ...
pWire,
pVertex, // the origin vertex (in purple)
300.0);  // the arc length in mm
    pPointOnWire->Run(#);
    CATBody* pResultBody = pPointOnWire->GetResult(#);

    ---

    you get this result:

      Fig.2 Point on a Wire: Result

        ![Point on a Wire: Result](images/CGM_point_on_wire_2.png)

    References

    		[1]
    		|
    		[
    		Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)

    		[2]
    		|
    		[About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)

    		[3]
    		|
    		[How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)

    		[4]
    		|
    		[How to Use Geometric Operators](../CAACgmModel/CAACgmUcGMModelOpeOverw.md)

    History

    		Version: **1** [Dec 2011]
    		| Document created
