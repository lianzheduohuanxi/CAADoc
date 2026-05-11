// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserOperationWithMATPComputation.h
//
//===================================================================
#ifndef CAAESmiUserOperationWithMATPComputation_H
#define CAAESmiUserOperationWithMATPComputation_H

#include "CATIMfgComputeToolPathCustom.h"
#include "CATGeometry.h"

class CATIContainer_var;
class CATIMfgToolPath_var;
class CATIMfgTPMultipleMotion_var;
class CATMathBox;

class CAAESmiUserOperationWithMATPComputation: public CATIMfgComputeToolPathCustom
{
  CATDeclareClass;

  public:

	 // Standard constructors and destructors for an implementation class
     CAAESmiUserOperationWithMATPComputation ();
     virtual ~CAAESmiUserOperationWithMATPComputation ();

	 // Computes the tool path of the current user operation.
     HRESULT ComputeToolPath (const CATIContainer_var& iContainer, CATIMfgToolPath_var& oTP);


  private:
  
	 // The copy constructor and the equal operator must not be implemented
     CAAESmiUserOperationWithMATPComputation (CAAESmiUserOperationWithMATPComputation &);
     CAAESmiUserOperationWithMATPComputation& operator=(CAAESmiUserOperationWithMATPComputation&);

	 // Computes the bounding box of a list of geometric elements
     HRESULT GetBoundingBox(CATLISTP(CATGeometry) iGeometricElements,
							CATMathBox & oBBox);

	 // Creates a tool path describing a bounding box
	 HRESULT AddTPMotion(const CATIMfgTPMultipleMotion_var & iMultipleMotion,
						 const CATMathBox & iBBox );

};

#endif
