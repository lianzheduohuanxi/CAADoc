#ifndef CAAAfrGeometryWksFactory_h
#define CAAAfrGeometryWksFactory_h

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
//  Class representing the factory that creates the CAAAfrGeometryWks workshop.
//  You must create such a factory for each workshop, by means of macros.
//  This class is a data extension of CATApplicationFrame and it implements
//  CAAIAfrGeometryWksFactory Factory.
//
//  Illustrates:
//     - creating a workshop
//
//===========================================================================

// Contains the CATDeclareWorkshopFactory macro
#include <CATWorkshopFactory.h> 

// Used in conjunction with CATImplementWorkshopFactory in the .cpp file 
CATDeclareWorkshopFactory(CAAAfrGeometryWks);

#endif
