#ifndef CAAIAfrMRUManagement_h
#define CAAIAfrMRUManagement_h

// COPYRIGHT DASSAULT SYSTEMES 2003

//
//===========================================================================
// 
// 
//===========================================================================
//System Framework
#include <CATBaseUnknown.h>       //Needed to derive from 
class CATUnicodeString ;
#include <CATListOfCATUnicodeString.h>   

// Local Framework
#include "CAAAfrCustCommandHdrModel.h"  //Needed to export the IID

// Global Unique IDentifier defined in .cpp 
// exported by CAAAfrCustomizedCommandHeader
extern IID ExportedByCAAAfrCustCommandHdrModel IID_CAAIAfrMRUManagement;

class ExportedByCAAAfrCustCommandHdrModel CAAIAfrMRUManagement: public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public:

      //
      // Adds a new item 
      //
      virtual HRESULT AddElement(CATUnicodeString &iNewElement)  = 0 ;

      //
      // Retrieves the list of items 
      //
      virtual HRESULT GetElementList(CATListOfCATUnicodeString &ElementList) const = 0 ;

      //
      // Selects an element of the list 
      //
      virtual HRESULT SelectElement(int iPosition) = 0 ;

};


#endif
