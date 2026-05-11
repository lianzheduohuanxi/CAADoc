#ifndef CAAEAfrUIActivateRootObject_H
#define CAAEAfrUIActivateRootObject_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document type (CAASample).
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the root object of the document.
//  It implements the CATIUIActivate interface in order to associate a
//  workshop with the document.
//  It derives from the CATExtIUIActivate adapter which provides most of
//  the implementation.
//
//  Illustrates:
//    - implementation of the CATIUIActivate interface to associate a
//      workshop with a document.
//
//
//===========================================================================
//  Usage:
//  ------
//  Launch CATIA V5, File/New. Choose the Geometry document.
//  The Geometry workshop is loaded.  
//  
//===========================================================================
//  Inheritance:
//  ------------
//        CATExtIUIActivate ( ApplicationFrame Framework )     
//           CATBaseUnknown    (System Framework).
//
//===========================================================================
//  Main Method:
//  ------------
//
//  GetWorkshop : returns the workshop name       
//  GetDefaultCommand : returns the name of the default command.
//
//===========================================================================

// ApplicationFrame framework
#include "CATExtIUIActivate.h"   // Needed to derive from CATExtIUIActivate
// System Framework
#include "CATString.h"           // Needed by GetWorkshop,GetDefaultCommand 


class CAAEAfrUIActivateRootObject: public CATExtIUIActivate
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;

  public:

    CAAEAfrUIActivateRootObject();
    virtual ~CAAEAfrUIActivateRootObject();
 
    // GetWorkshop
    // ------------
    // Returns the workshop identifier.
    //
    // This identifier is the name of class which implements CATIWorkshop 
    
    CATString & GetWorkshop() ;
    
    // GetDefaultCommand
    // ------------------
    // Returns the command header identifier of the default command.
    //
    // The default command is the one that is made active whenever the object which 
    // implements CATIUIActivate becomes UIActive.
    
    CATString & GetDefaultCommand() ;

  private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrUIActivateRootObject(const CAAEAfrUIActivateRootObject &iObjectToCopy);
  
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrUIActivateRootObject & operator = (const CAAEAfrUIActivateRootObject &iObjectToCopy);
  
  private : 

    CATString  _WorkshopName ;
    CATString  _DefaultCommandName ;

};
#endif
