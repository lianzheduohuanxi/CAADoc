#ifndef CAAIDlgDataRequest_H
#define CAAIDlgDataRequest_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface implemented by of the CAADlgBBEditorMessage class message. 
//  This interface allows to retrieve data contained in the message. 
//
//===========================================================================

//System Framework
#include "CATBaseUnknown.h"   // Needed to derive from 

// Local framework
#include "CAADlgBBMessageInt.h"  // Needed to export the IID and the class

extern ExportedByCAADlgBBMessageInt IID IID_CAAIDlgDataRequest ;

class ExportedByCAADlgBBMessageInt CAAIDlgDataRequest : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :

      // Retrieves the text of the message
      //
      virtual HRESULT GetData(char  ** oText) = 0 ;

	  virtual HRESULT SetData(const char *iText) = 0 ;
 

};
#endif
