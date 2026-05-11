#ifndef CAAEAfrInitDocument_H
#define CAAEAfrInitDocument_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document type (CAAGeometry) with its own workshop
//  and commands.
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAGeom Late Type. 
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
#include "CATBoolean.h"       // For the Init method


class CAAEAfrInitDocument: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEAfrInitDocument();
    virtual ~CAAEAfrInitDocument();

    // CATIInit     
    void                     Init (CATBoolean iDestroyExistingData);
    virtual CATBaseUnknown * GetRootContainer(const CATIdent interfaceID);


  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrInitDocument(const CAAEAfrInitDocument &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrInitDocument & operator = (const CAAEAfrInitDocument &iObjectToCopy);

  private:

    // Geometrical container which contains the UI activable object 
    // And all objects created in the workshop actived by this UI object
    //
    CATBaseUnknown  * _pGeomCont ;
     
};
#endif
