/* -*-c++-*- */
#ifndef CAAEOmbExportTypeData_H
#define CAAEOmbExportTypeData_H

//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//===================================================================

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
// Implement interface ObjectModelerBase.CATIExportTypeManager
// for object CATProduct to OmbExportType
// 
//
//===========================================================================


#include "CATBaseUnknown.h" // To derive from

class CATDocument;
#include "CATUnicodeString.h"

class CAAEOmbExportTypeData : public CATBaseUnknown
{
    // Used in conjunction with CATImplementClass in the .cpp file 
    CATDeclareClass;

public:

    CAAEOmbExportTypeData();
    virtual ~CAAEOmbExportTypeData();


    // CATIExportTypeManager Methods
    //-------------------------------
    virtual HRESULT ExportData ( CATDocument      * ipDoc,
                                 CATUnicodeString   iPath ) ;

	virtual HRESULT ExportData ( CATUnicodeString iToExportPath,
                                 CATUnicodeString iExportedPath ) ;

private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEOmbExportTypeData(const CAAEOmbExportTypeData &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEOmbExportTypeData & operator = (const CAAEOmbExportTypeData &iObjectToCopy);
};

#endif


