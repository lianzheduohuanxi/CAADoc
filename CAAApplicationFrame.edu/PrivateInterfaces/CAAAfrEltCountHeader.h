#ifndef CAAAfrEltCountHeader_h
#define CAAAfrEltCountHeader_h

// COPYRIGHT DASSAULT SYSTEMES 2003

//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//  It is a command header with a customized representation:
//     - menu bar       : nothing 
//     - toolbar        : Editors to display the count of point and line
//     - contextual menu: nothing
//
//  This class is defined has a component. It implements:
//    - CATIAfrCommandHeaderRep in the CAAEAfrCommandHeaderRepForEltCount class.
//       -> to define the representation in toolbar
//
//  An instance of this component is created in the CAAEAfrPaletteOptions class
//  which is an implementation of the CATIAfrPaletteOptions interface.
//
//===========================================================================

//ApplicationFrame framework
#include "CATAfrDialogCommandHeader.h"

#include "CAAAfrCustomizedCommandHeader.h"

class ExportedByCAAAfrCustomizedCommandHeader CAAAfrEltCountHeader : public CATAfrDialogCommandHeader
{
  // Used in conjunction with CATImplementHeaderResources in the .cpp file
  CATDeclareHeaderResources;

  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass ;

  public:
   
    CAAAfrEltCountHeader(const CATString & iHeaderName);

    virtual ~CAAAfrEltCountHeader();

    // Clone
    // -----
    // This method 
    // Replaces (and uses) the copy constructor 
    // 
    CATCommandHeader * Clone() ;
      
  private:

    // Used by the Clone method 
    CAAAfrEltCountHeader(CATCommandHeader *iHeaderToCopy);

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrEltCountHeader(const CAAAfrEltCountHeader &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrEltCountHeader & operator = (const CAAAfrEltCountHeader &iObjectToCopy);

};

#endif

