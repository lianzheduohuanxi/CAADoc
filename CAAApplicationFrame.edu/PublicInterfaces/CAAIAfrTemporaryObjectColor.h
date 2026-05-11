#ifndef CAAIAfrTemporaryObjectColor_h
#define CAAIAfrTemporaryObjectColor_h

// COPYRIGHT DASSAULT SYSTEMES 2003

//
//===========================================================================
// Interface implemented by the UI Active object of the CAAGeometry 
// document. 
// 
//===========================================================================
//

#include <CATBaseUnknown.h>       //Needed to derive from 

// Local Framework
#include "CAAAfrCustCommandHdrModel.h"  //Needed to export the IID

// Global Unique IDentifier defined in .cpp 
// exported by CAAAfrCustomizedCommandHeader
extern IID ExportedByCAAAfrCustCommandHdrModel IID_CAAIAfrTemporaryObjectColor;

class ExportedByCAAAfrCustCommandHdrModel CAAIAfrTemporaryObjectColor: public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public:

      //
      // Returns the current color associated with the UI active object
      //
      virtual HRESULT GetCurrentColor(int & oRed, int & oGreen, int & oBlue) const = 0 ;
      virtual HRESULT SetCurrentColor(int & oRed, int & oGreen, int & oBlue) = 0 ;
};


#endif
