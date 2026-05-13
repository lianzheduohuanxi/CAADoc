---
```vbscript
title: "Extracting Isoparametric Curves"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAAGMOperatorsExtractIsoPar", "CATICGMTopWire", "CATIsoParameter", "CATIsoParamU"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopExtractIsoParam.htmmd"
converted: "2026-05-11T17:33:49.157864"
```

---
tags: ["CAAGMOperatorsInterfaces", "CAAGMOperatorsExtractIsoPar", "CATICGMTopWire", "CATIsoParameter", "CATIsoParamU"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopExtractIsoParam.htmmd"
converted: "2026-05-11T17:33:49.157864"
Isoparametric Curves

---
converted: "2026-05-11T17:33:49.157864"
Isoparametric Curves
Use Case
Abstract When relying on a surface, curves of constant parameter along u or v can be extracted by using the CATSurface::ExtractIsoParametricCurve method.

    * Operator to be Used
    * Use Case Description
    * References
---
Abstract When relying on a surface, curves of constant parameter along u or v can be extracted by using the CATSurface::ExtractIsoParametricCurve method.
Operator to be Used To compute the isoparametric curve along u or v passing through a point on a surface, use the CATSurface::ExtractIsoParametricCurve method. The resulting geometry is a curve whose limits do not necessarily fit the topology boundaries. To create a wire with the face boundaries as limits, you have to compute the equivalent limits of the extracted curve on the face. This is done by using the CATCrvLimits::GetEquivalentLimits method. Use Case Description The CAAGMOperatorsExtractIsoPar.m module in CAAGMOperatorsInterfaces.edu illustrates how to create a wire representing an isoparametric curve. The curve "equivalent limits", that is the curve limits on the face are therefore computed. This use case requires the ExtractIsopar.NCGM file as input data. This file is delivered in the FunctionTests/InputData folder of CAAGMOperatorsInterfaces.edu framework.  If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).With the input data below: Fig.1 Extract Isoparametric Curve : Input Data ![Extract Isopar - Input Data](images/CGM_extract_isopar_0.png)

---
Operator to be Used To compute the isoparametric curve along u or v passing through a point on a surface, use the CATSurface::ExtractIsoParametricCurve method. The resulting geometry is a curve whose limits do not necessarily fit the topology boundaries. To create a wire with the face boundaries as limits, you have to compute the equivalent limits of the extracted curve on the face. This is done by using the CATCrvLimits::GetEquivalentLimits method. Use Case Description The CAAGMOperatorsExtractIsoPar.m module in CAAGMOperatorsInterfaces.edu illustrates how to create a wire representing an isoparametric curve. The curve "equivalent limits", that is the curve limits on the face are therefore computed. This use case requires the ExtractIsopar.NCGM file as input data. This file is delivered in the FunctionTests/InputData folder of CAAGMOperatorsInterfaces.edu framework.  If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md).With the input data below: Fig.1 Extract Isoparametric Curve : Input Data ![Extract Isopar - Input Data](images/CGM_extract_isopar_0.png)
and the code below (given only along U):

    CATSurface * mySurface = myFace->GetSurface(#);

    //      Get face limits
and the code below (given only along U):
CATSurface * mySurface = myFace->GetSurface(#);
    CATSurLimits *FaceLim;
    FaceLim = (CATSurLimits *)myFace->Get2DBoundingBox(#);
    CATCrvLimits CurveLimits, IsoParLimit;

    //     Extract IsoParU
CATSurLimits *FaceLim;
FaceLim = (CATSurLimits *)myFace->Get2DBoundingBox(#);
CATCrvLimits CurveLimits, IsoParLimit;
    CATIsoParameter isoParU = CATIsoParamU;
    CATCurve* pCATCurveU = mySurface->ExtractIsoParametricCurve(isoParU,
    		surParamPt, piGeomFactory);

    ...

    //    Reset the boundary to the limits of the face
CATCurve* pCATCurveU = mySurface->ExtractIsoParametricCurve(isoParU,
surParamPt, piGeomFactory);
    pCATCurveU->GetLimits(CurveLimits);
    IsoParLimit = CurveLimits;
    CATSurLimits surLim;
    mySurface->GetLimits(surLim);
    IsoParLimit.GetEquivalentLimits(surLim,*FaceLim,isoParU,CurveLimits);

    //   Create the wire along U
CATSurLimits surLim;
mySurface->GetLimits(surLim);
IsoParLimit.GetEquivalentLimits(surLim,*FaceLim,isoParU,CurveLimits);
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration(#);
        CATTopData topdata(pConfig, NULL);
    short orientations[1] = {1};
    CATICGMTopWire* pTopWire = CATCGMCreateTopWire(piImplicitFactory, &topdata;,
    		1, &pCATCurveU;, &CurveLimits;, orientations);

    ...
CATTopData topdata(pConfig, NULL);
short orientations[1] = {1};
CATICGMTopWire* pTopWire = CATCGMCreateTopWire(piImplicitFactory, &topdata;,
1, &pCATCurveU;, &CurveLimits;, orientations);
    pTopWire->Run(#);
    CATBody* pBody = pTopWire->GetResult(#);
    pTopWire->Release(#); pTopWire=NULL;

    ---

pTopWire->Release(#); pTopWire=NULL;
    you get this result (along U and V):

      Fig.2 Extract Isoparametric Curve: Result

    	![Extract Isoparametric Curve - Result](images/CGM_extract_isopar_1.png)

    ---

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
    		[Understanding Boolean Operators](CAACgmTaTopBoolean.md)

    		[5]
    		|
    		[Overview of Topological Operators](CAACgmUcTopOverview.md)

    History

    		Version: **1** [Oct 2011]
    		| Document created
