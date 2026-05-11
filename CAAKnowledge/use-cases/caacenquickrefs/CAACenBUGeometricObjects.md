---
```vbscript
title: "GeometricObjects Changed Classes or Interfaces"
category: "use-case"
module: "CAACenQuickRefs"
tags: []
source_file: "Doc/online/CAACenQuickRefs/CAACenBUGeometricObjects.htm"
converted: "2026-05-11T17:33:46.290452"
```

---
tags: []
source_file: "Doc/online/CAACenQuickRefs/CAACenBUGeometricObjects.htm"
converted: "2026-05-11T17:33:46.290452"
GeometricObjects Changed Classes or Interfaces

---
converted: "2026-05-11T17:33:46.290452"
GeometricObjects Changed Classes or Interfaces
This table summarizes the CAA V5 GeometricObjects classes, interfaces, methods, and global functions that you may have used in your applications built on top of CAA V5 and that have been replaced in the [New V5R20 CGM Interfaces Layer](CAACenGobInterfacesMigration.md). For each of these:

  * If a one-to-one mapping exists to replacing classes, interfaces, methods, or global functions, links to these substitutes are listed and pointed to
  * Otherwise, an article is pointed to to explain how to replace or get rid of them.

This table summarizes the CAA V5 GeometricObjects classes, interfaces, methods, and global functions that you may have used in your applications built on top of CAA V5 and that have been replaced in the [New V5R20 CGM Interfaces Layer](CAACenGobInterfacesMigration.md). For each of these:
Class or Interface | Comment

CATGeoFactory | Still available with the following method changes
| Method | Signature | Comment
| CreatePNurbs | virtual CATPNurbs* CreatePNurbs(CATKnotVector &iKnotVector;,
Class or Interface | Comment
CATGeoFactory | Still available with the following method changes
const CATLONG32 &iIsRational;,
const double* iVertices,
const double* iWeights,
CATSurface*iSupport,
const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization)=0 |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
const double* iWeights,
CATSurface*iSupport,
const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization)=0 |  Not supported any longer.
GeometricObjects | CATGeoFactory | CATCreatePNurbs

| CreateNurbsSurface | virtual CATNurbsSurface* CreateNurbsSurface(const CATKnotVector &iKnotVectorU;,
const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization)=0 |  Not supported any longer.
GeometricObjects | CATGeoFactory | CATCreatePNurbs
const CATKnotVector &iKnotVectorV;,
const CATLONG32 &iIsRational;,
const CATMathGridOfPoints &iVertices;,
const double* iWeights,
const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization)= 0 |  Not supported any longer.

**1 replacing method** | Framework | Class or Interface | Method
---|---|---
const CATMathGridOfPoints &iVertices;,
const double* iWeights,
const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization)= 0 |  Not supported any longer.
GeometricObjects | CATGeoFactory | CATCreateNurbsSurface
