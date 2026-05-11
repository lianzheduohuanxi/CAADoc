#ifndef CAAEAfrInit_H
#define CAAEAfrInit_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document type CAASample.
//         
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Class which implements the CATInit interface of a new document
//  type (CAASample)
//  It is a data extension of a late type (CAADoc) which is the document 
//  suffix. 
//
//===========================================================================
//  Usage:
//  ------
//  Launch CATIA V5, File/New In the Dialog Box the new document type  
//  appears.
//  
//===========================================================================
//  Inheritance:
//  ------------
//         CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  Init
//  GetRootContainer
//
//===========================================================================

// System framework
#include "CATBaseUnknown.h"   // Needed to derive from CATBaseUnknown
#include "CATBoolean.h"       // For the Init Method


class CAAEAfrInit: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEAfrInit();
    virtual ~CAAEAfrInit();

    // CATIInit     
    void                     Init (CATBoolean iDestroyExistingData);
    virtual CATBaseUnknown * GetRootContainer(const CATIdent interfaceID);


  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrInit(const CAAEAfrInit &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrInit & operator = (const CAAEAfrInit &iObjectToCopy);

  private:

    // Geometrical container which contains the UI activable object 
    // and all objects created in the workshop actived by this UI object
    //
    CATBaseUnknown  * _pSampContainer ;
     
};
#endif
