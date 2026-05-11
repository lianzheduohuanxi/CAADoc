// COPYRIGHT DASSAULT SYSTEMES 1999
//===================================================================
//
// CAAAniCCTools.h
// Header definition of CAAAniCCTools
//===================================================================
#ifndef CAAAniCCTools_H
#define CAAAniCCTools_H

#include "CATISamAnalysisSet.h"
#include "CATAnalysisExplicitSet.h"
//----------------------------------------------------------------------
/**
 * Sample to create a CharacCollector streamed and managed in the Field Model.
 */

class  CAAAniCCTools
{
  public:

/**
 * Create a CharacCollector streamed and managed in the Field Model.
 * @param ispSet           Input feature.
 * @param iExpParent       Field model associated to ispSet. In fact CATISamExplicit::GetExplicitObject.
 */
    static HRESULT ComputeCC(CATISamAnalysisSet_var& ispSet,CATAnalysisExplicitSet & iExpParent);
  private:
    
    CAAAniCCTools();
    static void ReadFile(CATISamAnalysisSet_var& ispSet,char* iName,int iNb	,float *iFvalues);
};
//-----------------------------------------------------------------------

#endif
