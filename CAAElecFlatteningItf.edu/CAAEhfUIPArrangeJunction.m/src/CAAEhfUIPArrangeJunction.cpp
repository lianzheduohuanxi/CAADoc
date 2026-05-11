/**
 * @fullreview JNT GLY 07:03:02
 */	

// --------------------------------------------------------
// COPYRIGHT Dassault Systemes 2007
//===================================================================
//
//
// Usage notes: Test of the CAA interface in Ehf
//
//===================================================================
//
//  February 2007   JNT
//===================================================================

#include "CAAEhfUIPArrangeJunction.h"

// --- Mathematics Framework ---
#include "CATMathVector.h"
#include "CATMathLine.h"
#include "CATMathPoint.h"
#include "CATMathPlane.h"
#include "CATMathConstant.h" //For CATDegreeToRadian etc.
#include "CATMathTransformation.h"

// --- ElecFlatteningItf Framework ---
#include "TIE_CATIEhfUIPArrangeJunction.h"

/* 
** Return Value   = S_OK : On Successful Completion of the Sample Code 
**                = E_FAIL : On all other cases
*/


TIE_CATIEhfUIPArrangeJunction( CAAEhfUIPArrangeJunction );

CATImplementClass( CAAEhfUIPArrangeJunction,      // Implementation class
                   CodeExtension,                 // Implementation style
                   CATBaseUnknown,                // Useless on extensions
                   CAAEhfArrangeJunction );       // Component extended by this class

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
CAAEhfUIPArrangeJunction::CAAEhfUIPArrangeJunction()
{
  
}

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
CAAEhfUIPArrangeJunction::~CAAEhfUIPArrangeJunction()
{
  
}

// ---------------------------------------------------------------------------
// CAAEhfUIPArrangeJunction::RetrieveUserDirection
// ---------------------------------------------------------------------------
HRESULT CAAEhfUIPArrangeJunction::RetrieveUserDirection(const CATListPtrCATBaseUnknown & iListOfBundleSegmentExtremity,
                                                        const CATMathPlane             & iFlatteningPlane,
                                                        CATLISTP(CATMathVector)        & ioListOfDirections)
{

  HRESULT               retCode = E_FAIL;
  
  CATMathVector         * pVector       = NULL;
  CATMathLine           * pRotationAxis = NULL;
  CATMathTransformation * pRotation     = NULL;//Used in for loop

  CATMathVector RefVector;
  CATMathVector Normal;
  CATMathPoint  Origin;

  int NbVectors = 0;
  int NbExtremities = 0;
  int Index = 0;
  double Angle = 0.0;

  //Check
  NbVectors = ioListOfDirections.Size();
  NbExtremities = iListOfBundleSegmentExtremity.Size();

  if (( 2 > NbVectors ) || ( 2 > NbExtremities ))
  {   
    retCode = E_FAIL; 
    goto EscapeWay;
  }

  //Get the normal vector and the origin of the flattening plane
  iFlatteningPlane.GetNormal(Normal);
  iFlatteningPlane.GetOrigin(Origin);

  // Get the rotation axis
  pRotationAxis = new CATMathLine(Origin,Normal);
  if (NULL == pRotationAxis)
  {
    retCode = E_FAIL; 
    goto EscapeWay;
  }
  
  // The first vector is the reference vector of the fixed branch.
  RefVector = *(ioListOfDirections[1]);

  
  // Empty the List Of Directions	
    
  for (Index = 1; Index <= NbVectors; Index++)
  {
     delete ioListOfDirections[Index];
     ioListOfDirections[Index] = NULL;
  }

  ioListOfDirections.RemoveAll();


  
  // Fill with pRefVector: 	
  pVector = new CATMathVector(RefVector);
  if (NULL == pVector)
  {
    retCode = E_FAIL; 
    goto EscapeWay;
  }
  ioListOfDirections.Append(pVector) ;
  pVector = NULL;

  
  //For all other vectors, a rotation of 15 degrees is computed.

  for (Index = 2; Index <= NbVectors; Index++)
  {

	  // Get the transformation
	  Angle = 15 * (Index-1);


	  //Convert into Radians, because, CATMathTransfo need Radian
      Angle = Angle * CATDegreeToRadian ;
      pRotation = new CATMathTransformation(Angle, *pRotationAxis) ;
      if (NULL == pRotation)
      {
        retCode = E_FAIL; 
        goto EscapeWay;
      }

	  // Retrieve the new vector rotated.
	  pVector = new CATMathVector ((*pRotation) * RefVector);
	  if (NULL == pVector)
      {
        retCode = E_FAIL; 
        goto EscapeWay;
      }
      pVector->Normalize() ;

	
	  // Append the new vector rotated.
      ioListOfDirections.Append(pVector) ;


	  // Delete the pointer on the transformation
	  delete pRotation;
      pRotation = NULL;
	}
    retCode = S_OK;


EscapeWay:

  // Clean Up
  //ReleasePtr

  if (NULL != pRotationAxis)
  {
    delete pRotationAxis;
    pRotationAxis = NULL;
  }

  if( FAILED(retCode) )
  {
    NbVectors = ioListOfDirections.Size();
  	for (Index = 1; Index <= NbVectors; Index++)
  	{
      delete ioListOfDirections[Index];
      ioListOfDirections[Index] = NULL;
  	}
  }

  return retCode;
}



