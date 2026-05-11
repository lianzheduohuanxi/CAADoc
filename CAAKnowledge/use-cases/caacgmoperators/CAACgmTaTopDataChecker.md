---
```vbscript
title: "How to Use the CGM Data Checker"
category: "tutorial"
module: "CAACgmOperators"
tags: ["CATINTCurve", "CATIntCurveType", "CATICPath", "CATIntCurve", "CATIA"]
source_file: "Doc/online/CAACgmOperators/CAACgmTaTopDataChecker.htm"
converted: "2026-05-11T17:33:48.656134"
```

---
tags: ["CATINTCurve", "CATIntCurveType", "CATICPath", "CATIntCurve", "CATIA"]
source_file: "Doc/online/CAACgmOperators/CAACgmTaTopDataChecker.htm"
converted: "2026-05-11T17:33:48.656134"
How to Use the CGM Data Checker

---
converted: "2026-05-11T17:33:48.656134"
How to Use the CGM Data Checker
Technical Article
Abstract CGM objects are valid if they fulfill a certain number of rules. When a given object is created, it can be checked for a given rule. If any problem is found, a core dump is issued and the developer has to take a look at the core dump traces to get some clue about why the object is invalid. The rule checker itself is a detection tool which does not repair any object. If no core dump has been issued, this only means that the CGM object to be validated complies with a specified rule. Other rules may not be fulfilled making the object invalid.

    * The Rules to be Satisfied
    * How to Activate the Rules
    * The Topological Checks
    * The Geometrical Checks
---
The Rules to be Satisfied Each rule is defined by an identifier. This identifier is used to activate the data checker as described in How to Activate the Rules. Rules to be checked | Identifiers
---|---
The Rules to be Satisfied Each rule is defined by an identifier. This identifier is used to activate the data checker as described in How to Activate the Rules. Rules to be checked | Identifiers
A body should not contain any touched topology | `TRE_1`
A closed wire should be made up of at least two edges | `CWE_1`
A topologically smooth edge should be geometrically smooth  | `ESH_1`
A loop should not be closed in 3D and open in 2D | `SCE_0`
A CATPointOnEdgeCurve should be on its EdgeCurve | `PCE_1`
Any CATCrvParam of a POEC should be in the maximum limits of its spec curve. | `PPO_1`
The gap between the curves making up a CATINTCurve should be less than the resolution | `ICG_1`
Limit Box of a PCurve curve should be inside the Support's limits box. (Check for PCurve::CloneAndMove service) | `PSS_0`
Limit Box of a PCurve curve should be inside the Support's limits box. (Check for PCurve::SetSurface service) | `PSS_1`
Curve continuity should be at least C1 | `CCC_0`
Surface continuity should be at least C1 | `CCC_1`
SetOfPointsMapping for curve limits inclusion for CATSetOfPointsMapX for ref/co curves of an edge curve should be within the resolution | `SPM_1`
The internal gap in a macro point should be less than the resolution. | `MPG_1`
Check for ref curve and curve from MapX for an edge curve, that curve useful limits are included in it's max limits. | `ULO_0`
Curve continuity OK in V6 (at least C2) | `CGC_0`
Surface continuity OK in V6 (at least C2) | `CGC_1`
The EdgeCurve should not have identical PCurves in the same tree | `EIP_1`
The MathRep of canonical curves (Circle & Ellipse) should be in the model infinite | `INF_2`
How to Activate the Rules Here are the preliminary steps to follow prior to activating the data checker: **Step 1**

    * Either create a CATIA environment, edit it and modify the value of the CATICPath variable.

          <install_CATIA>\intel_a\code\productIC

should be modified in:

          <install_CATIA>\intel_a\code\productIC;<install ENOVIA Studio>\intel_a\code\productIC

You can install ENOVIA Studio and CATIA at the same place.
    * Or copy the contents of:

          <install ENOVIA Studio>\intel_a\code\productIC

Into:

          <install_CATIA>\intel_a\code\productIC

**Step 2**
    * Activate the CDC license in the Tools/Option Licensing Menu.
**Step 3**
    1. Exit CATIA, activate the CATCAADataCheck variable plus the appropriate rule variables as described below:

1. Exit CATIA, activate the CATCAADataCheck variable plus the appropriate rule variables as described below:
```vbscript
           set CATCAADataCheck=1

```

to activate all the rules.

           set CATCAADataCheck=1
```vbscript
```vbscript
           set CATCGMCleanerRules=_XXX_1;YYY_1_ ;...

```

```

to activate only a set of rules. XXX_1, YYYY_1 are the rule identifiers.
    2. Restart CATIA.
The Topological Checks Body should not contain any touched topology A cell is touched when it is intended to be used in some specific operations like the "smart duplication" (see the CATSmartBodyDuplicator in the Encyclopedia). Note there is other operators that require touched objects as their input data. After the operation has completed the touched cells should return to an untouched status. If they remain touched, further operations on the initial body may lead to unexpected results. A valid topology should not contain any touched cells. The CD traces are similar to the ones below: **CGM Rule: TRE_1**
Short msg: "Residual touched cells checking failed.";
Extended msg: "Residual touched cells on ... checking failed.";

---
2. Restart CATIA.
The Topological Checks Body should not contain any touched topology A cell is touched when it is intended to be used in some specific operations like the "smart duplication" (see the CATSmartBodyDuplicator in the Encyclopedia). Note there is other operators that require touched objects as their input data. After the operation has completed the touched cells should return to an untouched status. If they remain touched, further operations on the initial body may lead to unexpected results. A valid topology should not contain any touched cells. The CD traces are similar to the ones below: **CGM Rule: TRE_1**
Short msg: "Residual touched cells checking failed.";
Extended msg: "Residual touched cells on ... checking failed.";
A closed wire should be made up of at least two edges An edge cannot be closed on itself, in other words any closed wire should be made up of at least two edges.  **CGM Rule: CWE_1**
Short msg: "Closed wire with edgecount > 1 checking failed.";
Extended msg: "Closed wire with edgecount > 1 on ... checking failed.";

---
A closed wire should be made up of at least two edges An edge cannot be closed on itself, in other words any closed wire should be made up of at least two edges.  **CGM Rule: CWE_1**
Short msg: "Closed wire with edgecount > 1 checking failed.";
Extended msg: "Closed wire with edgecount > 1 on ... checking failed.";
A topologically smooth edge should be geometrically smooth The edges that are considered as smooth should not have a geometrical sharpness greater than 2.3 deg. If there is no consistency between topological and geometrical sharpness, operations such as fillets and offset cannot succeed.  **CGM Rule: ESH_1**
Short msg: = "Edge sharpness checking failed.";
Extended msg: "Edge sharpness on /p1 checking failed.";

---
A topologically smooth edge should be geometrically smooth The edges that are considered as smooth should not have a geometrical sharpness greater than 2.3 deg. If there is no consistency between topological and geometrical sharpness, operations such as fillets and offset cannot succeed.  **CGM Rule: ESH_1**
Short msg: = "Edge sharpness checking failed.";
Extended msg: "Edge sharpness on /p1 checking failed.";
A loop should not be closed in 3D and open in 2D A loop relying on a surface should not be closed on itself. For example, a cylinder should not be made up of one single loop. In the right-hand side figures, the first one exhibits an invalid loop.

Short msg: = "Edge sharpness checking failed.";
Extended msg: "Edge sharpness on /p1 checking failed.";
A loop should not be closed in 3D and open in 2D A loop relying on a surface should not be closed on itself. For example, a cylinder should not be made up of one single loop. In the right-hand side figures, the first one exhibits an invalid loop.
The CD traces are similar to the ones below: **CGM Rule: SCE_0**
On CGM Object: ...
From Feature: ...
Short msg: "Surface closure for Loop checking failed.";
Extended msg: "Surface closure for Loop ... checking failed.";

---
On CGM Object: ...
From Feature: ...
Short msg: "Surface closure for Loop checking failed.";
Extended msg: "Surface closure for Loop ... checking failed.";
A CATPointOnEdgeCurve should be on its EdgeCurve Reminder: An CATPointOnEdgeCurve is specified by couples of data including a CATCrvParam and the CATCurve associated with this CATCrvParam. The list of data couples is referred to as a "spec". The "spec" defines a CATPointOnEdgeCurve. The EdgeCurve itself is made up of several curves. When scanning and analyzing each spec curve of a CATPointOnEdgeCurve by using CATPointOnEdgeCurve::GetSpec for example, one should find that each retrieved CATCurve is contained into the CATEdgeCurve. **CGM Rule: PCE_1**
On CGM Object: ...
From Feature: ...
Short msg: "POEC curve in edge curve checking failed.";
Extended msg: "POEC curve in edge curve on ... checking failed.";

---
On CGM Object: ...
From Feature: ...
Short msg: "POEC curve in edge curve checking failed.";
Extended msg: "POEC curve in edge curve on ... checking failed.";
Any CATCrvParam of a POEC should be in the maximum limits of its spec curves When scanning and analyzing each spec curve of a CATPointOnEdgeCurve, one should find that each retrieved CATCrvParam is within the limits of the reference curve.  **CGM Rule: PP0_1**
On CGM Object: ...
From Feature: ...
Short msg: "POEC spec param inside spec curve limits checking failed.";
Extended msg: "POEC spec param inside spec curve limits on /p1 checking failed.";

---
On CGM Object: ...
From Feature: ...
Short msg: "POEC spec param inside spec curve limits checking failed.";
Extended msg: "POEC spec param inside spec curve limits on /p1 checking failed.";
The Geometrical Checks The gap between the curves making up a CATINTCurve should be less than the resolution Checks the Gap between the corresponding points of component curves of a CATIntCurve.  **CGM Rule: ICG_1**
On CGM Object: CATIntCurveType
From Feature: ...
Short msg: "IntCurve gap less than resolution checking failed.";
Extended msg: "IntCurve gap less than resolution on /p1 checking failed.";

---
On CGM Object: CATIntCurveType
From Feature: ...
Short msg: "IntCurve gap less than resolution checking failed.";
Extended msg: "IntCurve gap less than resolution on /p1 checking failed.";
Limit Box of a PCurve curve should be inside the Support's limits box. (Check for PCurve::CloneAndMove service) Checks whether the limits of PCurve are included in the limits of its support. The check is called from **PCurve::CloneAndMove** method **CGM Rule: PSS_0**
On CGM Object: CATPCurveType
From Feature: ...
Short msg: "PCurve outside its support.";
Extended msg: "PCurve outside its ... support..";

---
On CGM Object: CATPCurveType
From Feature: ...
Short msg: "PCurve outside its support.";
Extended msg: "PCurve outside its ... support..";
Limit Box of a PCurve curve should be inside the Support's limits box. (Check for PCurve::SetSurface service) Checks whether the limits of PCurve are included in the limits of its support. The check is called from **PCurve::SetSurface** method **CGM Rule: PSS_1**
On CGM Object: CATPCurveType
From Feature: ...
Short msg: "PCurve outside its support.";
Extended msg: "PCurve outside its ... support..";

---
On CGM Object: CATPCurveType
From Feature: ...
Short msg: "PCurve outside its support.";
Extended msg: "PCurve outside its ... support..";
Curve continuity should be at least C1 Checks whether the Curve is C1 continuous  **CGM Rule: CCC_0**
On CGM Object: CATCurveType
From Feature: ...
Short msg: " Curve continuity is at least C1 checking failed.";
Extended msg: " Curve continuity is at least C1 on /p1 checking failed.";

---
On CGM Object: CATCurveType
From Feature: ...
Short msg: " Curve continuity is at least C1 checking failed.";
Extended msg: " Curve continuity is at least C1 on /p1 checking failed.";
Surface continuity should be at least C1 Checks whether the Surface is C1 continuous **CGM Rule: CCC_1**
On CGM Object: CATSurfaceType
From Feature: ...
Short msg: " Surface continuity is at least C1 checking failed.";
Extended msg: " Surface continuity is at least C1 on /p1 checking failed.";

---
On CGM Object: CATSurfaceType
From Feature: ...
Short msg: " Surface continuity is at least C1 checking failed.";
Extended msg: " Surface continuity is at least C1 on /p1 checking failed.";
SetOfPointsMapping for curve limits inclusion for CATSetOfPointsMapX for ref/co curves of an edge curve should be within the resolution For every point in SetOfPointsMapping, the geometrical distance between the reference curve and the other curves of the map should be less than the factory resolution. **CGM Rule: SPM_1** On CGM Object: CATEdgeCurveType
From Feature: ...
Short msg: " EdgeCurve SetOfPointsMappingLimits checking failed.";
Extended msg: " EdgeCurve SetOfPointsMappingLimits on /p1 checking failed.";

---
SetOfPointsMapping for curve limits inclusion for CATSetOfPointsMapX for ref/co curves of an edge curve should be within the resolution For every point in SetOfPointsMapping, the geometrical distance between the reference curve and the other curves of the map should be less than the factory resolution. **CGM Rule: SPM_1** On CGM Object: CATEdgeCurveType
From Feature: ...
Short msg: " EdgeCurve SetOfPointsMappingLimits checking failed.";
Extended msg: " EdgeCurve SetOfPointsMappingLimits on /p1 checking failed.";
The internal gap in a macro point should be less than the resolution. Checks the Gap between the component POECs of the MacroPoint. The distance is measured between one reference point and other points. **CGM Rule: MPG_1** On CGM Object: CATMacroPointType
From Feature: ...
Short msg: " Macro Point has a too big gap between its internal points.";
Extended msg: " Gap inside Macro Point on /p1 checking failed.";

---
The internal gap in a macro point should be less than the resolution. Checks the Gap between the component POECs of the MacroPoint. The distance is measured between one reference point and other points. **CGM Rule: MPG_1** On CGM Object: CATMacroPointType
From Feature: ...
Short msg: " Macro Point has a too big gap between its internal points.";
Extended msg: " Gap inside Macro Point on /p1 checking failed.";
Check for ref curve and curve from MapX for an edge curve, that curve useful limits are included in its max limits. The useful limits of the RefCurve and curves of an EdgeCurve should be included in the maxlimit of edge curve. **CGM Rule: ULO_1** On CGM Object: CATEdgeCurveType
From Feature: ...
Short msg: " Curve Limits - Useful Outside Max checking failed.";
Extended msg: " Curve Limits - Useful Outside Max on /p1 checking failed.";

---
Check for ref curve and curve from MapX for an edge curve, that curve useful limits are included in its max limits. The useful limits of the RefCurve and curves of an EdgeCurve should be included in the maxlimit of edge curve. **CGM Rule: ULO_1** On CGM Object: CATEdgeCurveType
From Feature: ...
Short msg: " Curve Limits - Useful Outside Max checking failed.";
Extended msg: " Curve Limits - Useful Outside Max on /p1 checking failed.";
Curve continuity should be at least C2 in V6 The curve should be at least C2 continuous in V6. **CGM Rule: CGC_0** On CGM Object: CATCurveType
From Feature: ...
Short msg: " Curve continuity checking failed.";
Extended msg: " Curve continuity on /p1 checking failed.";

---
Curve continuity should be at least C2 in V6 The curve should be at least C2 continuous in V6. **CGM Rule: CGC_0** On CGM Object: CATCurveType
From Feature: ...
Short msg: " Curve continuity checking failed.";
Extended msg: " Curve continuity on /p1 checking failed.";
Surface continuity should be at least C2 in V6  The surface should be at least C2 continuous: in V6. **CGM Rule: CGC_1** On CGM Object: CATSurfaceType
From Feature: ...
Short msg: " Surface continuity checking failed.";
Extended msg: " Surface continuity on /p1 checking failed.";

---
Surface continuity should be at least C2 in V6  The surface should be at least C2 continuous: in V6. **CGM Rule: CGC_1** On CGM Object: CATSurfaceType
From Feature: ...
Short msg: " Surface continuity checking failed.";
Extended msg: " Surface continuity on /p1 checking failed.";
The edge curve should not have identical PCurves in the same tree The edge curve should not contain identical PCurves in the same tree. But they can exist in different trees.  ![Edge Curves](images/CAACgmTopEIP_1.jpg) | The EdgeCurve-EC has one PCurve (PC) and one Merged Curve (MC) which again has two component PCurves. The First case is OK because PC1 is in different trees. The second case is KO because both PC2 s are in the same tree.

**CGM Rule: EIP_1** On CGM Object: CATEdgeCurveType
Extended msg: " Surface continuity on /p1 checking failed.";
The edge curve should not have identical PCurves in the same tree The edge curve should not contain identical PCurves in the same tree. But they can exist in different trees.  ![Edge Curves](images/CAACgmTopEIP_1.jpg) | The EdgeCurve-EC has one PCurve (PC) and one Merged Curve (MC) which again has two component PCurves. The First case is OK because PC1 is in different trees. The second case is KO because both PC2 s are in the same tree.
From Feature: ...
Short msg: " The EdgeCurve Should Not Have Identical PCurves In The Same Tree checking failed.";
Extended msg: " The EdgeCurve Should Not Have Identical PCurves In The Same Tree on /p1 checking failed. ";

---
From Feature: ...
Short msg: " The EdgeCurve Should Not Have Identical PCurves In The Same Tree checking failed.";
Extended msg: " The EdgeCurve Should Not Have Identical PCurves In The Same Tree on /p1 checking failed. ";
The MathRep of the canonical curves (Circle & Ellipse) should be in the model infinite **Authorized** : the mathematical circle
(in dashed green) is in the infinite. | **Not authorized** : the complete mathematical circle
(in dashed green) is not in the infinite.

The MathRep of the canonical curves (Circle & Ellipse) should be in the model infinite **Authorized** : the mathematical circle
(in dashed green) is in the infinite. | **Not authorized** : the complete mathematical circle
(in dashed green) is not in the infinite.
Definition of Model Infinite & Model space   | Until CATIA V5R13 | From CATIA V5R14

(in dashed green) is not in the infinite.
Definition of Model Infinite & Model space   | Until CATIA V5R13 | From CATIA V5R14
Model Size | [-100 meters, + 100 meters]
on each coordinate | [-1 000 meters, + 1 000 meters]
on each coordinate
Model infinite | [-1 000 meters, + 1 000 meters]
on each coordinate | [-10 000 meters, + 10 000 meters]
on each coordinate

**CGM Rule: INF_2**
on each coordinate
Model infinite | [-1 000 meters, + 1 000 meters]
on each coordinate | [-10 000 meters, + 10 000 meters]
on each coordinate
On CGM Object: CATCircleType, CATEllipseType
From Feature: ...
Short msg: " Circle/Ellipse - MathRep Inside Model Infinite checking failed. ";
Extended msg: " Circle/Ellipse - MathRep Inside Model Infinite on /p1 checking failed. ";

---
On CGM Object: CATCircleType, CATEllipseType
From Feature: ...
Short msg: " Circle/Ellipse - MathRep Inside Model Infinite checking failed. ";
Extended msg: " Circle/Ellipse - MathRep Inside Model Infinite on /p1 checking failed. ";
History Version: **1** [Aug 2004] | Document created

Short msg: " Circle/Ellipse - MathRep Inside Model Infinite checking failed. ";
Extended msg: " Circle/Ellipse - MathRep Inside Model Infinite on /p1 checking failed. ";
History Version: **1** [Aug 2004] | Document created
Version: **2** [Jul 2005] | Document modified
