// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CAAAniExportVBExt.h
// Provide implementation to interface CATIVBExtension
//
//===================================================================

#ifndef CAAAniExportVBExt_H
#define CAAAniExportVBExt_H

#include "CATBaseObject.h"
#include "CATBSTR.h"
class CATBaseDispatch ;
class CATIAAnalysisCase;
//-----------------------------------------------------------------------

/**
 * Class Object modeler implementation class.
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see System.CATIVBExtension
 *  </ol>
 * Using this prefered syntax will enable mkdoc to document your class.
 */
class CAAAniExportVBExt: public CATBaseObject
{
  CATDeclareClass;

  public:

    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAAniExportVBExt ();
    virtual ~CAAAniExportVBExt ();

//CATIVBExtension
	  HRESULT GetObjects (CATBaseUnknown *  iFrom , CATBaseDispatch *& oDisp) const ;
//CAAIAniExport
    HRESULT __stdcall Export(CATIAAnalysisCase * ipiCase, const CATBSTR & iFullFileName);

  private:

    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAAniExportVBExt (CAAAniExportVBExt &);
    CAAAniExportVBExt& operator=(CAAAniExportVBExt&);

};

//-----------------------------------------------------------------------
class CAAAniExportCreateExt: public CATBaseUnknown
{
  CATDeclareClass;

  public:

     CAAAniExportCreateExt ();
     virtual ~CAAAniExportCreateExt ();

     HRESULT __stdcall CreateInstance (void ** oPPV) ;

  private:
  
    CAAAniExportCreateExt (CAAAniExportCreateExt &);
    CAAAniExportCreateExt& operator=(CAAAniExportCreateExt&);
};

#endif










