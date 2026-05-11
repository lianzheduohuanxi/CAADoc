---
```vbscript
title: "Creating a Blend"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAAGMOperatorsBlendWithCouplingModes", "CATICGMTopBlend", "CAAGMOperatorsBlendWithCouplingLines"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopBlend.htm"
converted: "2026-05-11T17:33:49.079944"
```

---
tags: ["CAAGMOperatorsInterfaces", "CAAGMOperatorsBlendWithCouplingModes", "CATICGMTopBlend", "CAAGMOperatorsBlendWithCouplingLines"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcTopBlend.htm"
converted: "2026-05-11T17:33:49.079944"
Blend

---
converted: "2026-05-11T17:33:49.079944"
Blend
Use Case
Abstract A blend is a surface that connects two wires with a skin. If the input wires are laid down on supports (it is not mandatory), the shape of resulting blend depends on the specifications related to the guides and the continuity between the blend and the surfaces supporting the input wires.

    * Operator to be Used
    * Use Case Description
    * References
---
Abstract A blend is a surface that connects two wires with a skin. If the input wires are laid down on supports (it is not mandatory), the shape of resulting blend depends on the specifications related to the guides and the continuity between the blend and the surfaces supporting the input wires.
Operator to be Used To create a blend, use the CATICGMTopBlend operator in GMOperatorsInterfaces. This operator has to be created by the CATCGMCreateTopBlend global function. Use Case Description The CAAGMOperatorsBlendWithCouplingLines.m and CAAGMOperatorsBlendWithCouplingModes.m modules in CAAGMOperatorsInterfaces.edu illustrate how to create a blend. These use cases create the input data to be passed to the operator. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). Case 1: With Coupling Lines With the input data below: Fig.1 Blend Operation: Input Data (Three Guides and Supporting Surfaces)  ![Blend Operation: Three Guides](images/CGM_blend_coupling_lines_0.png)

---
Operator to be Used To create a blend, use the CATICGMTopBlend operator in GMOperatorsInterfaces. This operator has to be created by the CATCGMCreateTopBlend global function. Use Case Description The CAAGMOperatorsBlendWithCouplingLines.m and CAAGMOperatorsBlendWithCouplingModes.m modules in CAAGMOperatorsInterfaces.edu illustrate how to create a blend. These use cases create the input data to be passed to the operator. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). Case 1: With Coupling Lines With the input data below: Fig.1 Blend Operation: Input Data (Three Guides and Supporting Surfaces)  ![Blend Operation: Three Guides](images/CGM_blend_coupling_lines_0.png)
and the code below:

    CATICGMTopBlend * pBlendOpe =::CATCGMCreateTopBlend(piGeomFactory,

    			 &topdata;, piWireLyingOn1, piWireLyingOn0,
and the code below:
CATICGMTopBlend * pBlendOpe =::CATCGMCreateTopBlend(piGeomFactory,
                                 piMainBody1,
                                 piMainBody0);

    ...
CATICGMTopBlend * pBlendOpe =::CATCGMCreateTopBlend(piGeomFactory,
piMainBody1,
piMainBody0);
    pBlendOpe->SetCouplingLines(&guides;);
    pBlendOpe->SetTransitionContinuity(1,2);  // curvature continuity at the first wire side
    pBlendOpe->SetTransitionContinuity(2,1);  // tangency continuity at the second wire side

    pBlendOpe->Run();
    CATBody * pBodyBlend = pBlendOpe->GetResult();
    pBlendOpe->Release();
    pBlendOpe=NULL;

---
pBlendOpe->Release();
pBlendOpe=NULL;
you get this result: Fig.2 Result of Blend Operation with Coupling Lines ![Blend Operation: Result G1G2 Continuity](images/CGM_blend_coupling_lines_1.png)

---
you get this result: Fig.2 Result of Blend Operation with Coupling Lines ![Blend Operation: Result G1G2 Continuity](images/CGM_blend_coupling_lines_1.png)
```vbscript
Case 2:  Blend With Coupling Mode With the input data below: Fig.3 Blend Operation: Input Data (No Guides Coupling Mode Specified)  ![Blend Operation: No Guides](images/CGM_blend_coupling_mode_0.png)

```

---
you get this result: Fig.2 Result of Blend Operation with Coupling Lines ![Blend Operation: Result G1G2 Continuity](images/CGM_blend_coupling_lines_1.png)
Case 2:  Blend With Coupling Mode With the input data below: Fig.3 Blend Operation: Input Data (No Guides Coupling Mode Specified)  ![Blend Operation: No Guides](images/CGM_blend_coupling_mode_0.png)
and the code below:

    CATICGMTopBlend * pBlendOpe =::CATCGMCreateTopBlend(piGeomFactory,

    			 &topdata;, piWireLyingOn1, piWireLyingOn0,
and the code below:
CATICGMTopBlend * pBlendOpe =::CATCGMCreateTopBlend(piGeomFactory,
                                 piMainBody1,
                                 piMainBody0);

    ...
CATICGMTopBlend * pBlendOpe =::CATCGMCreateTopBlend(piGeomFactory,
piMainBody1,
piMainBody0);
    pBlendOpe->SetCouplingMode(CATTopBlendCouplingMode_Edge);
    pBlendOpe->SetTransitionContinuity(1,2);  // curvature continuity at the first wire side
    pBlendOpe->SetTransitionContinuity(2,1);  // tangency continuity at the second wire side

    pBlendOpe->Run();
    CATBody * pBodyBlend = pBlendOpe->GetResult();
    pBlendOpe->Release();
    pBlendOpe=NULL;

---

pBlendOpe=NULL;
you get this result:   Fig.4 Result of Blend Operation with Coupling Mode ![Blend Operation: Result Coupling Mode](images/CGM_blend_coupling_mode_1.png)

---
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
[5] |  [Understanding Boolean Operators](CAACgmTaTopBoolean.md)
[6] |  [Overview of Topological Operators](CAACgmUcTopOverview.md)
History Version: **1** [Sept 2011] | Document created
---|---
