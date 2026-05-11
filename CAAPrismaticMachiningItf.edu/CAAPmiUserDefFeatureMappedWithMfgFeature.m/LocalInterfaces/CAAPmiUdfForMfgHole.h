/* -*-c++-*- */
#ifndef CAAPmiUdfForMfgHole_h
#define CAAPmiUdfForMfgHole_h
// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
// ===================================================================
//
// CAAPmiUdfForMfgHole: implementation of the CATIMfgDesignHole interface
// for the User Defined Features 
// ===================================================================

#include "CATBaseUnknown.h"
#include "CATICkeParm.h"
#include "CATString.h"

class CAAPmiUdfForMfgHole : public CATBaseUnknown
{
  CATDeclareClass;

  public:
 
    CAAPmiUdfForMfgHole();
    virtual ~CAAPmiUdfForMfgHole();

    virtual HRESULT GetDiameter  (CATICkeParm_var &oDiameter);
    virtual HRESULT GetDepth     (CATICkeParm_var &oDepth);

    virtual HRESULT GetOrigin    (double& oX, double& oY, double& oZ);
    virtual HRESULT GetDirection (double& oX, double& oY, double& oZ);

    virtual HRESULT get_Parameter (const CATString &iParameterName, double &oParameter);
    virtual HRESULT get_Parameter (const CATString &iParameterName, int &oParameter);

  private:

    // No use of Copy Constructor and = operator
    CAAPmiUdfForMfgHole (CAAPmiUdfForMfgHole &);

    CAAPmiUdfForMfgHole& operator=(CAAPmiUdfForMfgHole&);

};
#endif

