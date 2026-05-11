#ifndef CAAAfrMRUHeader_h
#define CAAAfrMRUHeader_h

// COPYRIGHT DASSAULT SYSTEMES 2003

//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//  It is a command header with a customized representation:
//     - menu bar       : a MRU 
//     - toolbar        : nothing 
//     - contextual menu: nothing
//
//  This class is defined has a component. It implements:
//    - CATIAfrCommandHeaderRep in the CAAEAfrCommandHeaderRepForMRU class.
//       -> to define the MRU representation (only in menubar)
// 
//  An instance of this component is created in the CAAAfrGeneralWksAdn class
//  which is an implementation of the CATIAfrGeneralWksAddin interface.
//
//===========================================================================

//ApplicationFrame framework
#include "CATAfrDialogCommandHeader.h"

#include "CAAAfrCustomizedCommandHeader.h"
class ExportedByCAAAfrCustomizedCommandHeader CAAAfrMRUHeader : public CATAfrDialogCommandHeader
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass ;
  CATDeclareHeaderResources;

  public:
   
    CAAAfrMRUHeader(const CATString & iHeaderName);

    virtual ~CAAAfrMRUHeader();

    // Clone
    // -----
    // This method 
    // Replaces (and uses) the copy constructor 
    // 
    CATCommandHeader * Clone() ;
      
  private:

    // Used by the Clone method 
    CAAAfrMRUHeader(CATCommandHeader *iHeaderToCopy);

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrMRUHeader(const CAAAfrMRUHeader &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrMRUHeader & operator = (const CAAAfrMRUHeader &iObjectToCopy);

};

#endif

