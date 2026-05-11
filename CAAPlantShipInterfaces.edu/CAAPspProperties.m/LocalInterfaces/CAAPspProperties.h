// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspProperties
//
#ifndef CAAPspProperties_H
#define CAAPspProperties_H

#include "CAAPspBaseEnv.h"

class CATIPspAttribute;
class CATListValCATUnicodeString;
//-----------------------------------------------------------------------------

class CAAPspProperties : public CAAPspBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAPspProperties ();
    virtual ~CAAPspProperties();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //-------------------------------------------------------------------------
    int DoSample (const CATUnicodeString &iFileToBeLoaded);

	private :

		int QueryAttributeValues (CATIPspAttribute* pAttr, CATListValCATUnicodeString* pAttrNameList );

		
};
#endif
