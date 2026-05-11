// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserOperationTPComputation.h
//
//===================================================================
#ifndef CAAESmiUserOperationTPComputation_H
#define CAAESmiUserOperationTPComputation_H

#include "CATIMfgComputeToolPathCustom.h"
class CATIContainer_var;
class CATIMfgToolPath_var;
class CATCurve;
#include "CATLISTV_CATMathPoint.h"

class CAAESmiUserOperationTPComputation: public CATIMfgComputeToolPathCustom
{
  CATDeclareClass;

  public:

	 // Standard constructors and destructors for an implementation class
     CAAESmiUserOperationTPComputation ();
     virtual ~CAAESmiUserOperationTPComputation ();

	 // Compute the tool path of the current operation.
     HRESULT ComputeToolPath (const CATIContainer_var& iContainer, CATIMfgToolPath_var& oTP);


  private:
  
	 // The copy constructor and the equal operator must not be implemented
     CAAESmiUserOperationTPComputation (CAAESmiUserOperationTPComputation &);
     CAAESmiUserOperationTPComputation& operator=(CAAESmiUserOperationTPComputation&);

	 // Computes discretized points on the curve iCurve.
     HRESULT TessellateGeometry(CATCurve * const iCurve, const double iStep,
							 CATLISTV(CATMathPoint) & oPointsList);


};

#endif
