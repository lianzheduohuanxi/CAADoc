// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAArrPathwayRun
//
#ifndef CAAArrPathwayRun_H
#define CAAArrPathwayRun_H

#include "CAAArrBaseEnv.h"
#include "CATIRouSection.h"
#include "CATIArrSegment.h"

class CAAArrPathwayRun : public CAAArrBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAArrPathwayRun ();
    virtual ~CAAArrPathwayRun();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //        iPathToOutputFile - path to save the file in 
    //-------------------------------------------------------------------------
    int DoSample(const CATUnicodeString &iFileToBeLoaded);

  private:
    
    void DisplayRectSection(CATIRouSection_var spRouSect02);
    void DisplayNodeDataForSegment(CATIArrSegment *piArrSegment);

};
#endif
