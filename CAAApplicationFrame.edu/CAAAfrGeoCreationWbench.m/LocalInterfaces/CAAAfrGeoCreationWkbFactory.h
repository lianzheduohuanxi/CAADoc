#ifndef CAAAfrGeoCreationWkbFactory_h
#define CAAAfrGeoCreationWkbFactory_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document (CAAGeometry) with its own workshop and 
//  commands.
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Class representing the factory that creates the CAAAfrGeoCreationWkb 
//  workbench.
//  You must create such a factory for each workbench, by means of macros.
//  This class is a data extension of CATApplicationFrame and it implements
//  CAAIAfrGeoAnalysisWkbFactory.
//
//  Illustrates:
//     - creating a workbench
//
//===========================================================================

// Contains the CATDeclareConfigurationFactory macro
#include "CATWorkshopConfigurationFactory.h" 

//Used in conjunction with CATImplementWorkshopFactory in the .cpp file 
CATDeclareConfigurationFactory(CAAAfrGeoCreationWkb);

#endif
