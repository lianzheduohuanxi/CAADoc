---
```vbscript
title: "VisualizationBase Framework Modifications in V5R21"
category: "use-case"
module: "CAACenAPIChangesR21"
version: "V5R21"
tags: []
source_file: "Doc/online/CAACenAPIChangesR21/VisualizationBase.htm"
converted: "2026-05-11T17:33:51.703010"
```

---
| 
# CAA C++ API Modifications

| 
##  VisualizationBase Framework Modifications in V5R21 

* * *

**Entity|  SP| Modification| To Do** | VisualizationBase/Public/CAT3DAxisRep.h/3DAxisRep/3DAxisRep  
**Prototype:**`CAT3DAxisRep(CATModelIdentificator& one_ident,CATVisuController*iCntl)`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)| CAA Exposition Error: Methods Were using non exposed resources, so were not usable and have been removed.  
---|---|---|---  
VisualizationBase/Public/CAT3DCurveRep.h/CAT3DCurveRep/CAT3DCurveRep  
**Prototype:**`CAT3DCurveRep(CATModelIdentificator& one_ident,CATVisuController*iCntl)`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)  
VisualizationBase/Public/CAT3DCurveRep.h/CAT3DCurveRep/CAT3DCurveRep
VisualizationBase/Public/CAT3DPlanRep.h/CAT3DPlanRep/CAT3DPlanRep  

**Prototype:**`CAT3DPlanRep(CATModelIdentificator& one_ident,CATVisuController*iCntl)`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)  
VisualizationBase/Public/CAT3DCurveRep.h/CAT3DCurveRep/CAT3DCurveRep
VisualizationBase/Public/CAT3DPlanRep.h/CAT3DPlanRep/CAT3DPlanRep
VisualizationBase/Public/CATSupport.h/CATSupport/GetLetter  

**Prototype:**`l_CATSupport&GetLetter() const;`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)  
VisualizationBase/Public/CAT3DPlanRep.h/CAT3DPlanRep/CAT3DPlanRep
VisualizationBase/Public/CATSupport.h/CATSupport/GetLetter
VisualizationBase/Public/CATViewPoint.h/CATViewPoint/GetVizViewer  

**Prototype:**`CATVizViewer*GetVizViewer()const;`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)  
VisualizationBase/Public/CATSupport.h/CATSupport/GetLetter
VisualizationBase/Public/CATViewPoint.h/CATViewPoint/GetVizViewer
VisualizationBase/Public/CATViewPoint.h/SetViewer/CATFont  

**Prototype:**`void SetViewer(CATVizViewer*iViewer);`| GA| [INDM](CAACenAPIChangeDetail.htm#Abstract)
