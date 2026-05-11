---
title: "Manufactu Modifications"
category: "general"
module: "CAACenAPIChangesR14"
tags: ["CAAManufacturingItf", "CATIMfgResourceQuery", "CATIMfgResourceQueryUserDataBase"]
source_file: "Doc\online\CAACenAPIChangesR14\ManufacturingInterfaces.htm"
converted: "2026-05-11T17:33:50.928331"
---

| CAA C++ API Modifications|  ManufacturingInterfaces  |   
---|---|---  
  
* * *

**Entity|  SP| Modification| To Do** | ManufacturingInterfaces/Public/CATIMfgResourceQueryUserDataBase.h/CATIMfgResourceQueryUserDataBase/GetCorrectors  
**Prototype:** `virtual HRESULT GetCorrectors(const int &iElem;,CATListOfCATUnicodeString &oListPoints;,CATListOfInt &oListNumber;,CATListOfInt &oListLengthNumber;,CATListOfInt &oListRadiusNumber;,CATListOfDouble &oListDiameter;,CATIMfgResourceQuery::MfgResourceQueryType iResourceType=MfgCurrent);`| GA|  NPVM| A new method has been added on the base class (CATIMfgResourceQuery). See example of implementation in CAAManufacturingItf.edu framework for details on how to implement it.  
---|---|---|---  
ManufacturingInterfaces/Public/CATIMfgResourceQueryUserDataBase.h/CATIMfgResourceQueryUserDataBase/InstanciateResourceInDocument  
**Prototype:** `virtual HRESULT InstantiateResourceInDocument(const int &iEleCATBaseUnknown;_var &hBUResources;,CATIMfgResourceQuery::MfgResourceQueryType iRourceType=MfgCurrent,CATDocument*piDoc = NULL);`| GA|  NPVM| A new method has been added on the base class (CATIMfgResourceQuery). See example of implementation in CAAManufacturingItf.edu framework for details on how to implement it.
