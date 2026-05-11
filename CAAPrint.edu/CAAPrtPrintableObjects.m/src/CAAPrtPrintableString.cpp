// COPYRIGHT DASSAULT SYSTEMES 1999

// local framework
#include "CAAPrtPrintableString.h"   // Header of the current class
#include "CAAPrtStringImage.h"       // The class of the image to print

// System framework
#include "CATUnicodeString.h"        // The string class

// Print framework
#include "TIE_CATIPrintable.h"
  
// To create the TIE object
TIE_CATIPrintable(CAAPrtPrintableString); 

// To declare that the class is a component main class 
CATImplementClass(CAAPrtPrintableString,Implementation,CATBaseUnknown, CATNull);

// To declare that CAAPrtPrintableString implements CATIPrintable, insert 
// the following line in the interface dictionary:
//
// CATPrtPrintableString   CATIPrintable  libCAAPrtPrintableObjects
//

/*---------------------------------------------------------------------------*/
CAAPrtPrintableString::CAAPrtPrintableString(const CATUnicodeString & iString):
_String(iString)
{
}

/*---------------------------------------------------------------------------*/
CAAPrtPrintableString::~CAAPrtPrintableString()
{
}

/*---------------------------------------------------------------------------*/
CATPrintImage * CAAPrtPrintableString::CreatePrintableImage(void)
{
  return new CAAPrtStringImage(_String);
}
