---
```vbscript
title: "FreeFormOperators Changed Classes or Interfaces"
category: "use-case"
module: "CAACenQuickRefs"
tags: ["CATICGMCrvDegreeModification", "CATICGMLiss", "CATICGMSurFittingToNurbsSur", "CATICGMCrvFittingToNurbsCrv", "CATICGMInterproxCrv", "CATICGMInterproxSur", "CATInterproxCrv", "CATICGMSurDegreeModification", "CATInterproxSur"]
source_file: "Doc/online/CAACenQuickRefs/CAACenBUFreeFormOperators.htmmd"
converted: "2026-05-11T17:33:46.278454"
```

---
tags: ["CATICGMCrvDegreeModification", "CATICGMLiss", "CATICGMSurFittingToNurbsSur", "CATICGMCrvFittingToNurbsCrv", "CATICGMInterproxCrv", "CATICGMInterproxSur", "CATInterproxCrv", "CATICGMSurDegreeModification", "CATInterproxSur"]
source_file: "Doc/online/CAACenQuickRefs/CAACenBUFreeFormOperators.htmmd"
converted: "2026-05-11T17:33:46.278454"
FreeFormOperators Changed Classes or Interfaces

---
converted: "2026-05-11T17:33:46.278454"
FreeFormOperators Changed Classes or Interfaces
This table summarizes the CAA V5 FreeFormOperators classes, interfaces, methods, and global functions that you may have used in your applications built on top of CAA V5 and that have been replaced in the [New V5R20 CGM Interfaces Layer](CAACenGobInterfacesMigration.md). For each of these:

  * If a one-to-one mapping exists to replacing classes, interfaces, methods, or global functions, links to these substitutes are listed and pointed to
  * Otherwise, an article is pointed to to explain how to replace or get rid of them.

This table summarizes the CAA V5 FreeFormOperators classes, interfaces, methods, and global functions that you may have used in your applications built on top of CAA V5 and that have been replaced in the [New V5R20 CGM Interfaces Layer](CAACenGobInterfacesMigration.md). For each of these:
Class or Interface | Comment

CATConvertCrvToNurbsCrv | Not supported any longer.
**1 replacing class**
| Framework | Class or Interface
---|---
CATConvertCrvToNurbsCrv | Not supported any longer.
GMOperatorsInterfaces | CATICGMCrvFittingToNurbsCrv
Class or Interface | Comment
CATConvertSurToNurbsSur | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATConvertSurToNurbsSur | Not supported any longer.
GMOperatorsInterfaces | CATICGMSurFittingToNurbsSur
Class or Interface | Comment
CATCrvDegreeModification | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATCrvDegreeModification | Not supported any longer.
GMOperatorsInterfaces | CATICGMCrvDegreeModification
Class or Interface | Comment
CATCrvFittingToNurbsCrv | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATCrvFittingToNurbsCrv | Not supported any longer.
GMOperatorsInterfaces | CATICGMCrvFittingToNurbsCrv
Class or Interface | Comment
CATInterproxCrv | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATInterproxCrv | Not supported any longer.
GMOperatorsInterfaces | CATICGMInterproxCrv
Class or Interface | Comment
CATInterproxSur | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATInterproxSur | Not supported any longer.
GMOperatorsInterfaces | CATICGMInterproxSur
Class or Interface | Comment
CATLiss | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATLiss | Not supported any longer.
GMOperatorsInterfaces | CATICGMLiss
Class or Interface | Comment
CATSurDegreeModification | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATSurDegreeModification | Not supported any longer.
GMOperatorsInterfaces | CATICGMSurDegreeModification
Class or Interface | Comment
CATSurFittingToNurbsSur | Not supported any longer.

**1 replacing class**
| Framework | Class or Interface
---|---
Class or Interface | Comment
CATSurFittingToNurbsSur | Not supported any longer.
GMOperatorsInterfaces | CATICGMSurFittingToNurbsSur
Global Functions | Signature | Comment
CATCreateInterproxCrv | CATInterproxCrv* CATCreateInterproxCrv(CATGeoFactory*iFactory,
CATSoftwareConfiguration* iConfig,
CATLISTP_CATCurve_ &iListe;,
const CATMathSetOfPointsND*iPoints,
const CATMathSetOfVectors*iVectors,
double & iTension,
double & iSmoothness,
double & iTolapp,
const int iImposition[2],
CATSkillValue iMode=BASIC) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
double & iTolapp,
const int iImposition[2],
CATSkillValue iMode=BASIC) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateInterproxCrv
CATCreateInterproxSur | CATInterproxSur* CATCreateInterproxSur(CATGeoFactory*iFactory,
CATSoftwareConfiguration* iConfig,
CATLISTP_CATSurface_ &iListe;,
const CATMathSetOfPointsND*iPoints,
const CATMathSetOfVectors*iVectors,
double & iTension,
double & iSmoothness,
double & tolapp,
const int*iImposition,
const CATMathDirection*iVect=NULL,
CATSkillValue iMode=BASIC) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
const int*iImposition,
const CATMathDirection*iVect=NULL,
CATSkillValue iMode=BASIC) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateInterproxSur
CATCreateLiss | CATLiss* CATCreateLiss(CATGeoFactory*iFactory,
CATSoftwareConfiguration* iConfig,
CATMathSetOfPointsND*iPoints,
double &iTol;,
CATSkillValue iMode=BASIC) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATMathSetOfPointsND*iPoints,
double &iTol;,
CATSkillValue iMode=BASIC) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateLiss
CATCreateCrvFittingToNurbsCrv | CATCrvFittingToNurbsCrv* CATCreateCrvFittingToNurbsCrv(CATGeoFactory*iFactory,
const CATCurve*iCurve,
const CATCrvLimits &iLimits;,
double iMaxDeviation,
CATLONG32 iRationalAllowed = 1,
CATSkillValue iMode = BASIC) |  Not supported any longer.

**2 replacing methods** | Frameworks | Classes or Interfaces | Methods
---|---|---
double iMaxDeviation,
CATLONG32 iRationalAllowed = 1,
CATSkillValue iMode = BASIC) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateCrvFittingToNurbsCrv
GMOperatorsInterfaces | Global function | CATCGMCreateCrvFittingToNurbsCrv
CATCreateSurFittingToNurbsSur | CATSurFittingToNurbsSur* CATCreateSurFittingToNurbsSur(CATGeoFactory*iFactory,
const CATSurface* iSurface,
const CATSurLimits & iLimits,
double iMaxDeviation,
CATLONG32 iRationalAllowed = 1,
CATSkillValue iMode = BASIC) |  Not supported any longer.

**2 replacing methods** | Frameworks | Classes or Interfaces | Methods
---|---|---
double iMaxDeviation,
CATLONG32 iRationalAllowed = 1,
CATSkillValue iMode = BASIC) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateSurFittingToNurbsSur
GMOperatorsInterfaces | Global function | CATCGMCreateSurFittingToNurbsSur
CreateCrvDegreeModification | CATCrvDegreeModification* CreateCrvDegreeModification(CATGeoFactory*iFactory,
CATCurve*iNurbsCurve,
const CATLONG32 iTargetDegree,
const double iTolerance,
CATSkillValue iMode = BASIC) |  Not supported any longer.

**2 replacing methods** | Frameworks | Classes or Interfaces | Methods
---|---|---
const CATLONG32 iTargetDegree,
const double iTolerance,
CATSkillValue iMode = BASIC) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateCrvDegreeModification
GMOperatorsInterfaces | Global function | CATCGMCreateCrvDegreeModification
CreateCrvDegreeModification | CATCrvDegreeModification* CreateCrvDegreeModification(CATGeoFactory*iFactory,
CATCurve*iNurbsCurve,
const CATLONG32 &iNewDegree;,
CATSkillValue iMode = BASIC) |  Not supported any longer.

**2 replacing methods** | Frameworks | Classes or Interfaces | Methods
---|---|---
CATCurve*iNurbsCurve,
const CATLONG32 &iNewDegree;,
CATSkillValue iMode = BASIC) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateCrvDegreeModification
GMOperatorsInterfaces | Global function | CATCGMCreateCrvDegreeModification
CreateInterproxCrv | CATInterproxCrv* CreateInterproxCrv(CATGeoFactory*iFactory,
CATLISTP_CATCurve_ &iListe;,
const CATMathSetOfPointsND*iPoints,
const CATMathSetOfVectors*iVectors,
double & iTension,
double & iSmoothness,
double & iTolapp,
const int iImposition[2],
CATSkillValue iMode=BASIC) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
double & iTolapp,
const int iImposition[2],
CATSkillValue iMode=BASIC) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateInterproxCrv
CreateInterproxSur | CATInterproxSur* CreateInterproxSur(CATGeoFactory*iFactory,
CATLISTP_CATSurface_ &iListe;,
const CATMathSetOfPointsND*iPoints,
const CATMathSetOfVectors*iVectors,
double & iTension,
double & iSmoothness,
double & tolapp,
const int*iImposition,
const CATMathDirection*iVect=NULL,
CATSkillValue iMode=BASIC) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
const int*iImposition,
const CATMathDirection*iVect=NULL,
CATSkillValue iMode=BASIC) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateInterproxSur
CreateLiss | CATLiss* CreateLiss(CATGeoFactory*iFactory,
CATMathSetOfPointsND*iPoints,
double &iTol;,
CATSkillValue iMode=BASIC) |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
CATMathSetOfPointsND*iPoints,
double &iTol;,
CATSkillValue iMode=BASIC) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateLiss
CreateSurDegreeModification | CATSurDegreeModification* CreateSurDegreeModification(CATGeoFactory*ifactory,
CATNurbsSurface*iNurbsSurface,
const CATLONG32 &iTargetDegreeU;,
const CATLONG32 &iTargetDegreeV;,
const double iTolerance,
CATSkillValue iMode = BASIC) |  Not supported any longer.

**2 replacing methods** | Frameworks | Classes or Interfaces | Methods
---|---|---
const CATLONG32 &iTargetDegreeV;,
const double iTolerance,
CATSkillValue iMode = BASIC) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateSurDegreeModification
GMOperatorsInterfaces | Global function | CATCGMCreateSurDegreeModification
CreateSurDegreeModification | CATSurDegreeModification* CreateSurDegreeModification(CATGeoFactory*iFactory,
CATNurbsSurface*iNurbsSurface,
const CATLONG32 &iNewDegreeU;,
const CATLONG32 &iNewDegreeV;,
CATSkillValue iMode = BASIC) |  Not supported any longer.

**2 replacing methods** | Frameworks | Classes or Interfaces | Methods
---|---|---
const CATLONG32 &iNewDegreeU;,
const CATLONG32 &iNewDegreeV;,
CATSkillValue iMode = BASIC) |  Not supported any longer.
GMOperatorsInterfaces | Global function | CATCGMCreateSurDegreeModification
GMOperatorsInterfaces | Global function | CATCGMCreateSurDegreeModification
