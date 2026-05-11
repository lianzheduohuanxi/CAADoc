#ifndef CAAIAfrGeoCreationWkbFactory_h
#define CAAIAfrGeoCreationWkbFactory_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document (CAAGeometry) with its own workshop and 
//  commands.
//     
//===========================================================================
//  Abstract of the interface:
//  -------------------------
//
//  Interface of the factory that creates the CAAAfrGeoCreationWkb workbench.
//  You must define such an interface for each workbench.
//  This interface must derive from CATIGenericFactory.
//
//  Illustrates:
//     - creating a workbench
//
//===========================================================================
//  Inheritance:
//  ------------
//          CATIGenericFactory ( ObjectModelerBase Framework )
//             CATBaseUnknown (System Framework).
//
//===========================================================================


// Needed to derive from CATIGenericFactory
#include <CATIGenericFactory.h> 

// Global Unique IDentifier defined in .cpp 
extern IID IID_CAAIAfrGeoCreationWkbFactory;

class CAAIAfrGeoCreationWkbFactory : public CATIGenericFactory
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public:
};


#endif
