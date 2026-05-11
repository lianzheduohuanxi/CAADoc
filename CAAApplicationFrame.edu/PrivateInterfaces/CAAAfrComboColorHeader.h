#ifndef CAAAfrComboColorHeader_h
#define CAAAfrComboColorHeader_h

// COPYRIGHT DASSAULT SYSTEMES 2003

//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//  It is a command header with a customized representation:
//     - menu bar       : nothing
//     - toolbar        : a combo of colors 
//     - contextual menu: nothing
//
//  This class is defined has a component. It implements:
//    - CATIAfrCommandHeaderRep in the CAAEAfrCommandHeaderRepForComboColor class.
//       -> to define the combo representation (only in toolbar) 
// 
//  An instance of this component is created in the CAAAfrGeoChartWindowAdn class
//  which is an implementation of the CAAIAfrGeometryWksAddin interface.
//
//===========================================================================

//ApplicationFrame framework
#include "CATAfrDialogCommandHeader.h"

#include "CAAAfrCustomizedCommandHeader.h"

class ExportedByCAAAfrCustomizedCommandHeader CAAAfrComboColorHeader : public CATAfrDialogCommandHeader
{
  // Used in conjunction with CATImplementHeaderResources in the .cpp file
  CATDeclareHeaderResources;

  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass ;

  public:
   
    CAAAfrComboColorHeader(const CATString & iHeaderName);

    virtual ~CAAAfrComboColorHeader();

    // Clone
    // -----
    // This method 
    // Replaces (and uses) the copy constructor 
    // 
    CATCommandHeader * Clone() ;
      
  private:

    // Used by the Clone method 
    CAAAfrComboColorHeader(CATCommandHeader *iHeaderToCopy);

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrComboColorHeader(const CAAAfrComboColorHeader &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrComboColorHeader & operator = (const CAAAfrComboColorHeader &iObjectToCopy);

};

#endif


