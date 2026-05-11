/* -*-c++-*- */
//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//===================================================================
//
// Class CAAEOmbExportTypeData
//
// Implement interface ObjectModelerBase.CATIExportTypeManager
// for object CATProduct to OmbExportType
//

#include "CAAEOmbExportTypeData.h"

#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATUnicodeString.h"
#include "iostream.h"

//-----------------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATIExportTypeManager.h"
TIE_CATIExportTypeManager( CAAEOmbExportTypeData );

// To declare that the class is a code extension of CATProduct_OmbExportType
//
CATImplementClass( CAAEOmbExportTypeData,
			       CodeExtension,
			       CATBaseUnknown, 
				   CATProduct_OmbExportType );

// 
// To declare that CAAEOmbExportTypeData implements CATIExportTypeManager, insert 
// the following line in the interface dictionary:
//
//    CATProduct_OmbExportType CATIExportTypeManager  libCAAOmbExportType
//
//------------------------------------------------------------------------------------

CAAEOmbExportTypeData::CAAEOmbExportTypeData()
{
}


CAAEOmbExportTypeData::~CAAEOmbExportTypeData()
{
}

HRESULT CAAEOmbExportTypeData::ExportData ( CATDocument *pDoc,
                                            CATUnicodeString path )
{
    cout << "************** Begin ExportData 1" << endl << flush;
	// @CSC-Filter UNER
	HRESULT rc = CATDocumentServices::SaveAs (*pDoc, 
		                                      path);

    return rc;
}

HRESULT CAAEOmbExportTypeData::ExportData ( CATUnicodeString iToExportPath,
                                            CATUnicodeString iExportedPath )
{
    cout << "************** Begin ExportData 2" << endl << flush;
    return E_NOTIMPL;
}

