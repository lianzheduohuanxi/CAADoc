// COPYRIGHT DASSAULT SYSTEMES 2007
//======================================================================================
//
// CAAEMmrMultiMeasure.cpp
// Provide implementation to interface
//      CAAIMmrMultiMeasure
//======================================================================================

// Local Framework
#include "CAAEMmrMultiMeasure.h"

#include "CATIDescendants.h"
#include "CATICkeParm.h"

// System Framework
#include "CATBoolean.h"

// MecModInterfaces Framework
#include "CATIBRepAccess.h"
#include "CATIFeaturize.h"
#include "CATIGeometricalElement.h"

// ObjectSpecsModeler Framework
#include "CATBaseUnknown.h"     
#include "CATISpecObject.h"     // needed to manage/query features
#include "CATISpecAttrAccess.h" // needed to access feature attributes
#include "CATISpecAttrKey.h"    // needed to access to the feature attribute values

#include "iostream.h"

CATImplementClass (CAAEMmrMultiMeasure , 
                   DataExtension       ,    
                   CATBaseUnknown      ,
                   CAAMmrMultiMeasure);

//-------------------------------------------------------------------------------------
// CAAEMmrMultiMeasure : constructor
//-------------------------------------------------------------------------------------
CAAEMmrMultiMeasure::CAAEMmrMultiMeasure():
CATBaseUnknown()
{
}

//-------------------------------------------------------------------------------------
// CAAEMmrMultiMeasure : destructor
//-------------------------------------------------------------------------------------
CAAEMmrMultiMeasure::~CAAEMmrMultiMeasure()
{
}

// Tie the implementation to its interface
// ---------------------------------------

#include "TIE_CAAIMmrMultiMeasure.h" // needed to tie the implementation to its interface
TIE_CAAIMmrMultiMeasure( CAAEMmrMultiMeasure);

// To declare that CombinedCurve implements CAAIMmrMultiMeasure, insert 
// the following line in the interface dictionary:
//
// MmrMultiMeasure  CAAIMmrMultiMeasure  libCAAMmrMultiMeasure


//-------------------------------------------------------------------------------------
// Implements CAAIMmrMultiMeasure::SetGeomFeature
//-------------------------------------------------------------------------------------

HRESULT CAAEMmrMultiMeasure::SetInputGeomFeature (CATBaseUnknown * ipGeomFeature )
{ 
  // Sets the geom feature - The Feature to measure.
  // This geom feature will be the input for computing the length, area and volum, if it is possible.
  
  if(ipGeomFeature == NULL)
    return E_FAIL;
  
  CATISpecObject *pSpecOnThis = NULL;
  HRESULT rc = QueryInterface(IID_CATISpecObject, (void**) & pSpecOnThis);
  if (SUCCEEDED(rc) && pSpecOnThis != NULL)
  {
    // Gets a pointer on CATISpecAttrAccess 
    CATISpecAttrAccess *piSpecAttrAccessOnMmrMultiMeasure = NULL; 
    rc = QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnMmrMultiMeasure);
    if (SUCCEEDED(rc)) 
    { 
      // Gets pointers on the geom feature attributes and BRepCase attributes
      CATISpecAttrKey *piKeyOnInputGeomFeature = NULL;
      CATISpecAttrKey *piKeyOnInputGeomFeatureInBRepCase = NULL;

      piKeyOnInputGeomFeature = piSpecAttrAccessOnMmrMultiMeasure -> GetAttrKey("FeatureToMeasure");
      piKeyOnInputGeomFeatureInBRepCase = piSpecAttrAccessOnMmrMultiMeasure -> GetAttrKey("BRepFeatureToMeasure");

      if(piKeyOnInputGeomFeature != NULL && piKeyOnInputGeomFeatureInBRepCase != NULL)
      {
        CATISpecObject *pSpecGeomFeature = NULL;
        rc = ipGeomFeature -> QueryInterface(IID_CATISpecObject, (void**) &pSpecGeomFeature);

        if(SUCCEEDED(rc) && pSpecGeomFeature!= NULL)
        {
          CATIGeometricalElement* pGeometricalElementOnInputFeature = NULL;
          rc = pSpecGeomFeature -> QueryInterface(IID_CATIGeometricalElement, (void**) &pGeometricalElementOnInputFeature);
          if (SUCCEEDED(rc) && pGeometricalElementOnInputFeature != NULL)
          {
            // SpecObject Case : We only need to value the "SpecObject Attribute"
            if(piSpecAttrAccessOnMmrMultiMeasure -> TestAttributeValue(piKeyOnInputGeomFeatureInBRepCase) == TRUE)
            {
              //Unset BRep Case Attribute : We are in SpecObjectCase.
              piSpecAttrAccessOnMmrMultiMeasure -> UnsetAttributeValue(piKeyOnInputGeomFeatureInBRepCase);
            }
            piSpecAttrAccessOnMmrMultiMeasure  -> SetSpecObject(piKeyOnInputGeomFeature, pSpecGeomFeature);

            pGeometricalElementOnInputFeature -> Release();
            pGeometricalElementOnInputFeature = NULL;

            rc = S_OK;
          }
          pSpecGeomFeature -> Release();
          pSpecGeomFeature = NULL;
        }
        else
        {
          // ipGeomFeature is a BRepAccess? 
          CATIBRepAccess *pBRepAccess = NULL;

          rc = ipGeomFeature -> QueryInterface(IID_CATIBRepAccess, (void**) & pBRepAccess);
          if(SUCCEEDED(rc) && pBRepAccess != NULL)
          {
            // 1] Featurize BRepAccess
            //    Don't forget : BRepAccess are not persistant 
            //    ---> Featurize it to keep it in the model ! 
            CATIFeaturize* pFeaturizeBRep = NULL;
            rc = pBRepAccess -> QueryInterface(IID_CATIFeaturize, (void**) & pFeaturizeBRep);
            if (SUCCEEDED(rc) && pFeaturizeBRep!= NULL)
            {
              CATISpecObject_var hFeatureBRep = NULL_var;
              // Featurize(R) to keep (R)elimited surface in order to compute the real measure
              hFeatureBRep = pFeaturizeBRep -> FeaturizeR(MfSelectingFeatureSupport);

              if(!!hFeatureBRep)
              {
                // 2] unset attributes
                if(piSpecAttrAccessOnMmrMultiMeasure -> TestAttributeValue(piKeyOnInputGeomFeature) == TRUE)
                {
                  piSpecAttrAccessOnMmrMultiMeasure -> UnsetAttributeValue(piKeyOnInputGeomFeature);
                }
                if(piSpecAttrAccessOnMmrMultiMeasure -> TestAttributeValue(piKeyOnInputGeomFeatureInBRepCase) == TRUE)
                {
                  // Deletes the former aggregated Feature BRep
                  piSpecAttrAccessOnMmrMultiMeasure -> UnsetAttributeValue(piKeyOnInputGeomFeatureInBRepCase);
                }
                //3] Aggregate hFeatureBRep in piKeyOnInputGeomFeatureInBRepCase
                piSpecAttrAccessOnMmrMultiMeasure -> SetSpecObject(piKeyOnInputGeomFeatureInBRepCase, hFeatureBRep);

                //4] Reroute Attribute...
                piSpecAttrAccessOnMmrMultiMeasure -> SetSpecAttribute(piKeyOnInputGeomFeature, 
                                                                      pSpecOnThis, 
                                                                      piKeyOnInputGeomFeatureInBRepCase, 
                                                                      0);
                rc = S_OK;
              }
              pFeaturizeBRep -> Release();
              pFeaturizeBRep = NULL;
            }                            
            pBRepAccess -> Release();
            pBRepAccess = NULL;
          }
        }
        piKeyOnInputGeomFeature -> Release(); //Release piKeyOnInputGeomFeature 
        piKeyOnInputGeomFeature = NULL;

        piKeyOnInputGeomFeatureInBRepCase -> Release(); //Release piKeyOnInputGeomFeature 
        piKeyOnInputGeomFeatureInBRepCase = NULL;
      }
      else
        rc = E_FAIL;

      piSpecAttrAccessOnMmrMultiMeasure -> Release();
      piSpecAttrAccessOnMmrMultiMeasure = NULL ;
    }
    pSpecOnThis -> Release();
    pSpecOnThis = NULL;
  }
  return rc ;
}

//-------------------------------------------------------------------------------------
// Implements CAAIMmrMultiMeasure::GetGeomFeature 
//-------------------------------------------------------------------------------------

HRESULT CAAEMmrMultiMeasure::GetGeomFeature (CATISpecObject **ioGeomFeature )
{
	cout <<" CAAEMmrMultiMeasure::GetGeomFeature" << endl ;

  HRESULT rc = E_FAIL;

  // Gets a pointer on CATISpecAttrAccess
  CATISpecAttrAccess *piSpecAttrAccessOnMmrMultiMeasure = NULL;
  rc = QueryInterface( IID_CATISpecAttrAccess , (void**) &piSpecAttrAccessOnMmrMultiMeasure );
  if ( SUCCEEDED(rc) && piSpecAttrAccessOnMmrMultiMeasure != NULL)
  {
    CATISpecAttrKey *piKeyOnGeomFeature = NULL;    
    piKeyOnGeomFeature = piSpecAttrAccessOnMmrMultiMeasure -> GetAttrKey("FeatureToMeasure");

    rc = E_FAIL;
    
    if(piKeyOnGeomFeature!= NULL)
    {
      //Get The GeomFeature associated to the 3DMmrMultiMeasure.
      *ioGeomFeature = piSpecAttrAccessOnMmrMultiMeasure -> GetSpecObject(piKeyOnGeomFeature);
      if ( NULL != *ioGeomFeature )
      {
        rc = S_OK ;
           cout <<" CAAEMmrMultiMeasure::GetGeomFeature OK" << endl ;
      } 
      piKeyOnGeomFeature -> Release();
      piKeyOnGeomFeature = NULL;
    }
    piSpecAttrAccessOnMmrMultiMeasure ->Release();
    piSpecAttrAccessOnMmrMultiMeasure = NULL ;
  }
  
  return rc ;
}

//-------------------------------------------------------------------------------------
// Implements CAAIMmrMultiMeasure::GetLengthParameter 
//-------------------------------------------------------------------------------------

HRESULT CAAEMmrMultiMeasure::GetLengthParameter (CATICkeParm_var &oLengthParm) 
{
	cout <<" CAAEMmrMultiMeasure::GetLengthParameter" << endl ;

	CATIDescendants * pDescendantsOnMmrMultiMeasure = NULL;
    
    HRESULT rc = QueryInterface( IID_CATIDescendants, (void**) &pDescendantsOnMmrMultiMeasure);
    if(SUCCEEDED(rc))
    {
      CATListValCATISpecObject_var    hListOfAggregatedParameter      ;
      pDescendantsOnMmrMultiMeasure -> GetDirectChildren ("CATICkeParm",hListOfAggregatedParameter);

      if(0 != hListOfAggregatedParameter.Size())
      {
  		CATBoolean bFoundParameter = FALSE; 
		int i = 1;
		while ((i <= hListOfAggregatedParameter.Size()) && (FALSE == bFoundParameter))
        {
          CATICkeParm_var spParm = hListOfAggregatedParameter[i];
          if(!!spParm && (spParm -> RelativeName(this) == CATUnicodeString("`Computed Length`")))
		  {
			  oLengthParm = spParm;
			  bFoundParameter = TRUE;
		  }
		  i++;
        }
 
		if (FALSE == bFoundParameter)
			rc = E_FAIL;
      
	  } else
		  rc = E_FAIL;

      pDescendantsOnMmrMultiMeasure -> Release();
      pDescendantsOnMmrMultiMeasure = NULL;
    }

	return rc ;
}
//-------------------------------------------------------------------------------------
// Implements CAAIMmrMultiMeasure::GetWetAreaParameter 
//-------------------------------------------------------------------------------------

HRESULT CAAEMmrMultiMeasure::GetWetAreaParameter (CATICkeParm_var &oWetAreaParm) 
{
	CATIDescendants * pDescendantsOnMmrMultiMeasure = NULL;
    
    HRESULT rc = QueryInterface( IID_CATIDescendants, (void**) &pDescendantsOnMmrMultiMeasure);
    if(SUCCEEDED(rc))
    {
      CATListValCATISpecObject_var    hListOfAggregatedParameter      ;
      pDescendantsOnMmrMultiMeasure -> GetDirectChildren ("CATICkeParm",hListOfAggregatedParameter);

      if(0 != hListOfAggregatedParameter.Size())
      {
  		CATBoolean bFoundParameter = FALSE; 
		int i = 1;
		while ((i <= hListOfAggregatedParameter.Size()) && (FALSE == bFoundParameter))
        {
          CATICkeParm_var spParm = hListOfAggregatedParameter[i];
          if(!!spParm && (spParm -> RelativeName(this) == CATUnicodeString("`Computed WetArea`")))
		  {
			  oWetAreaParm = spParm; 
			  bFoundParameter = TRUE;
		  }
		  i++;
        }

		if (FALSE == bFoundParameter)
			rc = E_FAIL;

      } else
		  rc = E_FAIL;

      pDescendantsOnMmrMultiMeasure -> Release();
      pDescendantsOnMmrMultiMeasure = NULL;
    }
	return rc ;
}
//-------------------------------------------------------------------------------------
// Implements CAAIMmrMultiMeasure::GetVolumeParameter 
//-------------------------------------------------------------------------------------

HRESULT CAAEMmrMultiMeasure::GetVolumeParameter (CATICkeParm_var &oVolumeParm) 
{
	HRESULT rc = E_FAIL;
	CATIDescendants * pDescendantsOnMmrMultiMeasure = NULL;
    
    rc = QueryInterface( IID_CATIDescendants, (void**) &pDescendantsOnMmrMultiMeasure);
    if(SUCCEEDED(rc))
    {
      CATListValCATISpecObject_var    hListOfAggregatedParameter      ;
      pDescendantsOnMmrMultiMeasure -> GetDirectChildren ("CATICkeParm",hListOfAggregatedParameter);

      if(0 != hListOfAggregatedParameter.Size())
      {
		CATBoolean bFoundParameter = FALSE; 
		int i = 1;
		while ((i <= hListOfAggregatedParameter.Size()) && (FALSE == bFoundParameter))
        {
          CATICkeParm_var spParm = hListOfAggregatedParameter[i];
          if(!!spParm && (spParm -> RelativeName(this) == CATUnicodeString("`Computed Volume`")))
		  {
			  oVolumeParm = spParm;
			  bFoundParameter = TRUE;
		  } 
			i++;
		}

		if (FALSE == bFoundParameter)
			rc = E_FAIL;

       } else
		  rc = E_FAIL;
	  
      pDescendantsOnMmrMultiMeasure -> Release();
      pDescendantsOnMmrMultiMeasure = NULL;
    }

	return rc ; 
}

