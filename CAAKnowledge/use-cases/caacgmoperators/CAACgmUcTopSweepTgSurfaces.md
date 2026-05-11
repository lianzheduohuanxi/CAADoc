---
```vbscript
title: "Creating a Sweep from a Spine and Two Tangency Surfaces"
category: "use case"
module: "CAACgmOperators"
tags: ["CATICGMTopSweepSkinSkinSegment", "CAAGMOperatorsInterfaces", "CAAGMOperatorsSweepTangentSkinSkin"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopSweepTgSurfaces.htm"
converted: "2026-05-11T17:33:49.337299"
```

---
tags: ["CATICGMTopSweepSkinSkinSegment", "CAAGMOperatorsInterfaces", "CAAGMOperatorsSweepTangentSkinSkin"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopSweepTgSurfaces.htm"
converted: "2026-05-11T17:33:49.337299"
Creating a Sweep from a Spine and Two Tangency Surfaces

---
converted: "2026-05-11T17:33:49.337299"
Creating a Sweep from a Spine and Two Tangency Surfaces
Use Case
Abstract The profile to be swept is implicitly defined. The generated sweep is tangent to the two input surfaces and can be trimmed or not with the input surfaces. This operator possibly produces several results which can be scanned.

    * Operator to be Used
    * Use Case Description
    * References
---
Abstract The profile to be swept is implicitly defined. The generated sweep is tangent to the two input surfaces and can be trimmed or not with the input surfaces. This operator possibly produces several results which can be scanned.
Operator to be Used To create a sweep tangent to two surfaces and using an implicit linear profile, use the CATICGMTopSweepSkinSkinSegment operator in GMOperatorsInterfaces. This operator has to be created by the CATCGMCreateTopSweepSkinSkinSegment global function. Use Case Description The CAAGMOperatorsSweepTangentSkinSkin.m module in CAAGMOperatorsInterfaces.edu illustrates how to create a sweep tangent to two skins. This use case creates the input data to be passed to the operator. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). With the input data below: Fig.1 Sweep Operation: Input Data (Spine and Tangency Surfaces) ![Sweep: Tangent to Two Surfaces - Implicit Profile](images/CGM_sweep_skinskin_0.png)

---
Operator to be Used To create a sweep tangent to two surfaces and using an implicit linear profile, use the CATICGMTopSweepSkinSkinSegment operator in GMOperatorsInterfaces. This operator has to be created by the CATCGMCreateTopSweepSkinSkinSegment global function. Use Case Description The CAAGMOperatorsSweepTangentSkinSkin.m module in CAAGMOperatorsInterfaces.edu illustrates how to create a sweep tangent to two skins. This use case creates the input data to be passed to the operator. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). With the input data below: Fig.1 Sweep Operation: Input Data (Spine and Tangency Surfaces) ![Sweep: Tangent to Two Surfaces - Implicit Profile](images/CGM_sweep_skinskin_0.png)
and the code below:

    CATICGMTopSweepSkinSkinSegment * SweepTopOp =
            CATCGMCreateTopSweepSkinSkinSegment(iFactory, iTopData, iGuideBody1, iGuideBody2, iSpineBody);

     ...
and the code below:
CATICGMTopSweepSkinSkinSegment * SweepTopOp =
CATCGMCreateTopSweepSkinSkinSegment(iFactory, iTopData, iGuideBody1, iGuideBody2, iSpineBody);
     int orient1 = -1; //solution desired on opposite side of first shell normal
     int orient2 = 1; //solution desired on same side of second shell normal

     SweepTopOp->SetFirstShellOrientation( orient1 );
     SweepTopOp->SetSecondShellOrientation( orient2 );

     ...
int orient2 = 1; //solution desired on same side of second shell normal
SweepTopOp->SetFirstShellOrientation( orient1 );
SweepTopOp->SetSecondShellOrientation( orient2 );
     CATDynSegmentationMode trim1 = CATDynTrim; //trim the results with first support
     CATDynSegmentationMode trim2 = CATDynNoTrim; // do not trim the results with second support

     SweepTopOp->SetFirstShellModeTrim( trim1 );
     SweepTopOp->SetSecondShellModeTrim( trim2 );

    SweepTopOp->Run();

    ...
SweepTopOp->SetFirstShellModeTrim( trim1 );
SweepTopOp->SetSecondShellModeTrim( trim2 );
SweepTopOp->Run();
    SweepTopOp->BeginningResult();
    int firstShellOrient = 0, secondShellOrient = 0, firstCoupledOrient = 0, secondCoupledOrient = 0, index = 0;
    CATSoftwareConfiguration * pConfig = iTopData->GetSoftwareConfiguration();

```vbscript
      while (SweepTopOp->NextResult())

```

            {
int firstShellOrient = 0, secondShellOrient = 0, firstCoupledOrient = 0, secondCoupledOrient = 0, index = 0;
CATSoftwareConfiguration * pConfig = iTopData->GetSoftwareConfiguration();
while (SweepTopOp->NextResult())
                CATCGMJournalList * pTempJournal =  new CATCGMJournalList(pConfig,NULL);//get the journal corresponding to this result

                CATBody * pTempBody = SweepTopOp->GetResult(pTempJournal);

                //get the signature of the current result
CATCGMJournalList * pTempJournal =  new CATCGMJournalList(pConfig,NULL);//get the journal corresponding to this result
CATBody * pTempBody = SweepTopOp->GetResult(pTempJournal);
                SweepTopOp->GetResultInformation(firstShellOrient

                    ,secondShellOrient
                    ,firstCoupledOrient
                    ,secondCoupledOrient
                    ,index);
SweepTopOp->GetResultInformation(firstShellOrient
                if( pTempJournal )

                {
```vbscript
if( pTempJournal )
                    delete pTempJournal;
                    pTempJournal = 0;
```

                }
            }
    ...

---
you get this result: Fig.2 Result of Sweep Operation: Spine and Two Tangency Surfaces  ![Sweep Operation: Tangency Surfaces Result1 ](images/CGM_sweep_skinskin_1.png)
---|---
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
[4] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)
[5] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)
History Version: **1** [Sept 2011] | Document created
---|---
