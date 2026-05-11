// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAAfrGeometryWks.h"
#include "CAAAfrGeometryWksFactory.h"

// To create the TIE object
#include <TIE_CAAIAfrGeometryWksFactory.h>

// Macro to automatically create the factory class for the Geometry workshop, as a 
// data extension of the CATApplicationFrame class .
CATImplementWorkshopFactory(CAAAfrGeometryWks, CAAIAfrGeometryWksFactory);

//
// To declare that CATApplicationFrame implements CAAIAfrGeometryWksFactory,  
// insert the following line in the interface dictionary:
//
//    CATApplicationFrame  CAAIAfrGeometryWksFactory libCAAAfrGeometryWks

//
// To declare that the factory creates an instance of the Geometry class, 
// insert the following line in the factory dictionary:
// 
//    CAAAfrGeometryKws           CAAIAfrGeometryWksFactory 
