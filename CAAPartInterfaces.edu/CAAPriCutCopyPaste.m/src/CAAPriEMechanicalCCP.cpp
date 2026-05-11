/**
* @quickReview SQA 06:05:03 ZMK - R17GA - KO in Doc check Mode- CATIMechanicalCCP implemented for CAAPriPatternPad for sketch updation 
* @quickReview BAG 04:02:25
* @quickReview sqa 04:01:09
* @quickReview frn 03:06:26
*/
// Copyright © 1994-2000 Dassault Systèmes.
// All right reserved



// Local Framework
#include "CAAPriEMechanicalCCP.h"

// PartInterfaces Framework
#include "CATIPrtProfile.h"              // needed to access the profile attribute
// of the User Pad / Pattern Pad

// SketcherInterfaces Framework
#include "CATISketch.h"                  // needed to find a sketch in a path element

// MecModInterfaces Framework
#include "CATIPrtPart.h"                 // needed to check validity of pasted element

// Visualization Framework
#include "CATPathElement.h"              // needed to check validity of pasted element

// Mathematics Framework
#include "CATPlane.h"                    // needed to check validity of pasted element
#include "CATMathPoint.h"                // needed to define anchor point
#include "CATMathDirection.h"            // needed to define the normal of the feature

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"              // needed to manage the profile
#include "CATISpecAttrAccess.h"					 // needed to access Userpad / PatternPad attributes
#include "CATISpecAttrKey.h"						 // needed to access Userpad / PatternPad attribute keys


// To declare that the class 
// is a DataExtension of (late type) CAAPriUserPad and CAAPriPatternPad
CATBeginImplementClass(CAAPriEMechanicalCCP, DataExtension, CATBaseUnknown, CAAPriUserPad);
CATAddClassExtension(CAAPriPatternPad); 
CATEndImplementClass(CAAPriEMechanicalCCP);

#include "TIE_CATIMechanicalCCP.h" // needed to tie the implementation to its interface
TIE_CATIMechanicalCCP(CAAPriEMechanicalCCP);

// To declare that UserPad implements CATIMechanicalCCP, insert 
// the following line in the interface dictionary:
//
// CAAPriUserPad  CATIMechanicalCCP  libCAAPriCutCopyPaste

// To declare that PatternPad implements CATIMechanicalCCP, insert 
// the following line in the interface dictionary:
//
// CAAPriPatternPad  CATIMechanicalCCP  libCAAPriCutCopyPaste


//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
CAAPriEMechanicalCCP::CAAPriEMechanicalCCP()
{
}


//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
CAAPriEMechanicalCCP::~CAAPriEMechanicalCCP()
{
}


//-------------------------------------------------------------------------
// GiveMeYourFavoriteSpecifications
// The purpose of this method is to return the major specifications
// of a feature: that is the specifications that have to be copied
// with the feature to have an independant copy.
// In the case of the UserPad / PatternPad, the favorite specification is the input
// sketch. This sketch is found through the Profile attribute.
//-------------------------------------------------------------------------
CATLISTV(CATISpecObject_var) CAAPriEMechanicalCCP::GiveMeYourFavoriteSpecifications() const
{

  // Retrieves the Profile attribute of the UserPad / PatternPad feature.
  //

  CATLISTV(CATISpecObject_var) listSpec;

  CATISpecObject *piUserPad = NULL;
  HRESULT rc = ((CATBaseUnknown*)this)->QueryInterface( IID_CATISpecObject , ( void** ) &piUserPad );
  if( FAILED(rc) )
    return listSpec;

  CATISpecAttrAccess * piSpecAttrAccessOnUserPad = NULL; 
  rc = piUserPad->QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnUserPad);

  if ( SUCCEEDED(rc) ) 
  { 
    // Gets a pointer on the Profile attribute key
    CATISpecAttrKey * piSpecAttrKeyOnProfile = NULL;    
    piSpecAttrKeyOnProfile = piSpecAttrAccessOnUserPad->GetAttrKey("Profile");

    if ( NULL != piSpecAttrKeyOnProfile )
    {
      CATISpecObject_var spProfile = piSpecAttrAccessOnUserPad->GetSpecObject(piSpecAttrKeyOnProfile);

      piSpecAttrKeyOnProfile->Release();
      piSpecAttrKeyOnProfile = NULL ;

      if(NULL_var != spProfile)
      {
        spProfile->Release();

        // Retrieves the sketch associated with the profile
        // The sketch is added in the returned list
        //
        CATIPrtProfile_var spPrtProfileOnProfile(spProfile);
        if (NULL_var != spPrtProfileOnProfile)
        {
          CATISpecObject_var spElt = NULL_var;
          spPrtProfileOnProfile->GetElement(1, spElt);
          if (NULL_var != spElt)
          {
            listSpec.Append(spElt);
          }
        }
      }
    }

    piSpecAttrAccessOnUserPad->Release();
    piSpecAttrAccessOnUserPad = NULL;

  }

  piUserPad->Release();
  piUserPad = NULL;

  return listSpec;
}

//-------------------------------------------------------------------------
// IsElementValidForPaste
// The purpose of this method is to accept or refuse to paste on the given
// path element.
// In the UserPad / PatternPad case, the paste is accepted if the path element contains
// a sketch.
//-------------------------------------------------------------------------
int CAAPriEMechanicalCCP::IsElementValidForPaste(CATPathElement* ispPath) const 
{

  // return value: the paste is not valid yet.
  //
  int valid = 0;

  if(!ispPath)
    return valid;

  // checking there is a sketch in the path element
  //
  CATBaseUnknown *spSketchOnElt = ispPath->FindElement(IID_CATISketch);
  if( NULL != spSketchOnElt )
  {
    spSketchOnElt->Release();
    valid = 1;
  }
  return valid; 
}


//-------------------------------------------------------------------------
// GetAnchorPoint
// The purpose of this method is to give information about the absolute
// position of the result of the feature.
// In the case of the UserPad / PatternPad, the anchor point is the one of the referenced
// sketch.
//-------------------------------------------------------------------------
CATMathPoint CAAPriEMechanicalCCP::GetAnchorPoint() const 
{

  // Retrieves the Profile attribute of the UserPad / PatternPad feature.
  //

  CATMathPoint anchorPoint;

  CATISpecObject * piUserPad = NULL;
  HRESULT rc = ((CATBaseUnknown*)this)->QueryInterface( IID_CATISpecObject , ( void** ) &piUserPad );
  if( FAILED(rc) )
    return anchorPoint;

  CATISpecAttrAccess * piSpecAttrAccessOnUserPad = NULL; 
  rc = piUserPad->QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnUserPad);

  if ( SUCCEEDED(rc) ) 
  { 
    // Gets a pointer on the Profile attribute
    CATISpecAttrKey * piSpecAttrKeyOnProfile = NULL;    
    piSpecAttrKeyOnProfile = piSpecAttrAccessOnUserPad->GetAttrKey("Profile");

    if ( NULL != piSpecAttrKeyOnProfile )
    {
      CATISpecObject_var spProfile = piSpecAttrAccessOnUserPad->GetSpecObject(piSpecAttrKeyOnProfile);

      piSpecAttrKeyOnProfile->Release();
      piSpecAttrKeyOnProfile = NULL ;

      if(NULL_var != spProfile)
      {
        spProfile->Release();

        // Retrieves the sketch associated with the profile
        // The sketch is added in the returned list
        //
        CATIPrtProfile_var spPrtProfileOnProfile(spProfile);
        if (NULL_var != spPrtProfileOnProfile)
        {
          int nbElt = spPrtProfileOnProfile->GetElementCount();
          if (1 == nbElt)
          {
            // Retrieves the sketch associated to the profile
            //
            CATISpecObject_var spElt;
            spPrtProfileOnProfile->GetElement(1, spElt);
            CATIMechanicalCCP_var spCCPOnElt(spElt);
            if (NULL_var != spCCPOnElt)
            {
              // Delegates GetAnchorPoint to the sketch
              //
              anchorPoint = spCCPOnElt->GetAnchorPoint();
            }
          }
        }
      }
    }

    piSpecAttrAccessOnUserPad->Release();
    piSpecAttrAccessOnUserPad = NULL;

  }

  piUserPad->Release();
  piUserPad = NULL;

  return anchorPoint;
}


//-------------------------------------------------------------------------
// GetReferenceNormal
// The purpose of this method is to give information about the absolute
// normal of the result of the feature.
// In the case of the UserPad / Pattern Pad, the reference normal is the one of the
// referenced sketch
//-------------------------------------------------------------------------
CATMathDirection CAAPriEMechanicalCCP::GetReferenceNormal() const
{

  // Retrieves the Profile attribute of the UserPad / PatternPad feature.
  //

  CATMathDirection normal;


  CATISpecObject *piUserPad = NULL;
  HRESULT rc = ((CATBaseUnknown*)this)->QueryInterface( IID_CATISpecObject , ( void** ) &piUserPad );
  if( FAILED(rc) )
    return normal;  

  CATISpecAttrAccess * piSpecAttrAccessOnUserPad = NULL; 
  rc = piUserPad->QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnUserPad);

  if ( SUCCEEDED(rc) ) 
  { 
    // Gets a pointer on the Profile attribute
    CATISpecAttrKey * piSpecAttrKeyOnProfile = NULL;    
    piSpecAttrKeyOnProfile = piSpecAttrAccessOnUserPad->GetAttrKey("Profile");

    if ( NULL != piSpecAttrKeyOnProfile )
    {
      CATISpecObject_var spProfile = piSpecAttrAccessOnUserPad->GetSpecObject(piSpecAttrKeyOnProfile);

      piSpecAttrKeyOnProfile->Release();
      piSpecAttrKeyOnProfile = NULL ;

      if(NULL_var != spProfile)
      {
        spProfile->Release();

        // Retrieves the sketch associated with the profile
        // The sketch is added in the returned list
        //
        CATIPrtProfile_var spPrtProfileOnProfile(spProfile);
        if (NULL_var != spPrtProfileOnProfile)
        {
          int nbElt = spPrtProfileOnProfile->GetElementCount();
          if (1 == nbElt)
          {
            CATISpecObject_var spElt;
            spPrtProfileOnProfile->GetElement(1, spElt);
            CATIMechanicalCCP_var spCCPOnElt(spElt);
            if (spCCPOnElt != NULL_var)
            {
              // Delegates GetReferenceNormal to the sketch
              //
              normal = spCCPOnElt->GetReferenceNormal();
            }
          }
        }
      }
    }

    piSpecAttrAccessOnUserPad->Release();
    piSpecAttrAccessOnUserPad = NULL;

  }

  piUserPad->Release();
  piUserPad = NULL;

  return normal;
}


//-------------------------------------------------------------------------
// CanBeDeleted
// The purpose of this method is to accept to cut the feature.
// In the case of the UserPad / PatternPad, the cut is always available.
//-------------------------------------------------------------------------
int CAAPriEMechanicalCCP::CanBeDeleted(const CATListValCATISpecObject_var &List) const 
{
  return 1;
}


//-------------------------------------------------------------------------
// CanBeCopied
// The purpose of this method is to accept to copy the feature.
// In the case of the UserPad / PatternPad, the copy is always available.
//-------------------------------------------------------------------------
int CAAPriEMechanicalCCP::CanBeCopied() const 
{
  return 1;
}


CAAPriEMechanicalCCP::CAAPriEMechanicalCCP(const CAAPriEMechanicalCCP&)
{
};
