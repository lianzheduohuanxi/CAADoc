#ifndef CAAPriEMechanicalCCP_H
#define CAAPriEMechanicalCCP_H

// COPYRIGHT DASSAULT SYSTEMES 2002
// All right reserved

//==========================================================================
//  Sample code for : Part Interfaces
//  Mission         : Implement interface CATIMechanicalCCP
//									
//	
//  Type            : shared library
//  Inputs          : 
//  Outputs         :
//	 
//  Illustrates     : methods implementation to allow Mechanical 
//                  : Design Form Feature to be pasted
//										
// Abstract of the sample	:
// ------------------------
//		
//  In this sample we have implemented the mandatory methods to allow 
//  User Pad to be pasted
//  
//  GiveMeYourFavoriteSpecifications method returns the sketch associated to the
//  profile
//  
//  IsElementValidForPaste returns 1 if the path element represents a sketch
//
//  CanBeDeleted returns 1 and indicates that the UserPad can be deleted
//  CanBeCopied returns 1 and indicates that the UserPad can be copied
//
//==========================================================================


#include "CATLISTV_CATISpecObject.h" // needed to return the sketch associated 
                                     // to the UserPad

class CATPathElement;
class CATMathPoint;
class CATMathDirection;

class CAAPriEMechanicalCCP : public CATBaseUnknown
{

  CATDeclareClass;

  public:

    // constructor
    CAAPriEMechanicalCCP();

    // destructor
    virtual ~CAAPriEMechanicalCCP();
    
		// returns the sketch associated to the profile of the UserPad
    virtual CATLISTV(CATISpecObject_var) GiveMeYourFavoriteSpecifications() const;

		// returns 1 if the element is valid
    virtual int IsElementValidForPaste(CATPathElement* path) const;

		// returns the anchor point of the sketch
    virtual CATMathPoint GetAnchorPoint() const ;

    // returns the normal of the sketch
    virtual CATMathDirection GetReferenceNormal() const;

    // returns 1
    virtual int CanBeDeleted(const CATLISTV(CATISpecObject_var) &List) const;

    // returns 1
    virtual int CanBeCopied() const;

  private:
    // Copy constructor not implemented
    // Set as private to prevent from compiler automatic creation as public
    CAAPriEMechanicalCCP(const CAAPriEMechanicalCCP&);
};
#endif // CAAPriECCP_H
