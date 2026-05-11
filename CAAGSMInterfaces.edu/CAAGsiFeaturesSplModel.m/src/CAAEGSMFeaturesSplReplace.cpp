// COPYRIGHT Dassault Systemes 2006
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------
// 
// CAAEGSMFeaturesSplReplace.cpp
// Provide implementation to interface
//    CATIReplace
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//June 2006 : Creation CAA Sample 
//===================================================================

// Local Framework
// MINC 
#include "CATLISTV_CATBaseUnknown.h"

#include "CAAEGSMFeaturesSplReplace.h"

// System Framework
#include "CATErrorMacros.h"               // To manage Try/Catch

// Visualization Framework
#include "CATIVisProperties.h"            // To manage Hide/Show of a Feature
#include "CATVisPropertiesValues.h"               
#include "CATPathElement.h"               // To handle Selection path

// ObjectModelerBase Framework
#include "CATIRedrawEvent.h"              // To handle the Redraw in the Tree Representation
#include "CATIDescendants.h"  

// ObjectSpecsModeler Framework

#include "CATIContainer.h"             
#include "CATISpecObject.h"               // To handle feature, update it
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"
#include "LifeCycleObject.h"

//include LiteralFeatures
#include "CATICkeParm.h"
#include "CATICkeType.h"
#include "CATIParmDictionary.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeRelation.h"
#include "CATICkeParmFactory.h"
#include "CATIParmPublisher.h"

// InteractiveInterfaces Framework 
#include "CATIOrientationFlag.h"          // To handle inversion state of a Feature

// MechanicalModeler Framework
#include "CATIFeaturize.h"                // On the fly featurization of Selection Objects 
#include "CATIMfBRep.h"  

// GSMInterfaces Framework
#include "CATIPrtContainer.h"               // To create Inversion Feature 
#include "CATIPrtPart.h"               // To create Inversion Feature 
#include "CATIGSMTool.h"               // To create Inversion Feature 
#include "CATIGSMFactory.h"               // To create Inversion Feature 
#include "CATIGSMInverse.h"               // To handle Inversion Feature 
#include "CATIInputDescription.h"          // To handle Inversion Feature 

#include "CATIModelEvents.h"
#include "CATModify.h"

// V5R17 
#include "CATIGSMAttributes.h"

// #define DEBUG_REPLACE
#ifdef DEBUG_REPLACE
#include "iostream.h"
#endif 

//-----------------------------------------------------------------------------

CATBeginImplementClass(CAAEGSMFeaturesSplReplace,DataExtension, CATSpecReplaceExt ,CAASewSkinBasic);
CATAddExtendedImplementation(CAACircleSweepTg);
CATEndImplementClass(CAAEGSMFeaturesSplReplace);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIReplace, CAAEGSMFeaturesSplReplace);



// 
//
//-----------------------------------------------------------------------------

CAAEGSMFeaturesSplReplace::CAAEGSMFeaturesSplReplace():CATSpecReplaceExt()
{
#ifdef DEBUG_REPLACE 
	cout <<"CAAEGSMFeaturesSplReplace::CAAEGSMFeaturesSplReplace" << endl;
#endif 
}

//-----------------------------------------------------------------------------

CAAEGSMFeaturesSplReplace::~CAAEGSMFeaturesSplReplace ()
{
#ifdef DEBUG_REPLACE 
	 cout <<"CAAEGSMFeaturesSplReplace::~CAAEGSMFeaturesSplReplace" << endl;
#endif 
}


// *** CATIReplace Implementation 
//-----------------------------------------------------------------------------
// IsElementValidForReplace
//-----------------------------------------------------------------------------

HRESULT
CAAEGSMFeaturesSplReplace::IsElementValidForReplace(const CATUnicodeString& iNameOfRole,
                                                     const CATBaseUnknown_var& iElement,
                                                     CATUnicodeString& oMessage, 
                                                     int& oElementValidity, 
                                                     const CATBaseUnknown_var& iOldValue)
{
#ifdef DEBUG_REPLACE 
   cout <<"CAAEGSMFeaturesSplReplace::IsElementValidForReplace"<< iNameOfRole << endl;
#endif 
  
   HRESULT rc = S_OK;

   oElementValidity=0;

   // The default implementation calls the CATIAttrBehavior interface
   // ----------------------------------------------------------------------------------------------------------
   rc = CATSpecReplaceExt::IsElementValidForReplace(iNameOfRole,iElement,oMessage,oElementValidity,iOldValue);
 

   // Specific / Implement for litterals 
   // ----------------------------------------------------------------------------------------------------------
	
   // Check Type consistency 
   CATICkeParm_var newparm = iElement;
   if (!!newparm)
   {
	   
	   CATICkeType_var newtype = newparm->Type();

	   // Identify Types  
	   CATIParmDictionary_var ParmDic = CATCkeGlobalFunctions::GetParmDictionary();
	   
	   // cas de la geometrie qui adhere a CATICkeParm (datum value par formule)
	   //if(!(!!newtype && newtype->IsaKindOf(CATParmDictionary::FeatureType)==CATCke::True && oElementValidity==1))
	   if(!(!!newtype && newtype->IsaKindOf(ParmDic->GetFeatureType())==CATCke::True && oElementValidity==1))
	   {
		   if (!!iOldValue)
		   {
			   oElementValidity=0;
			   CATICkeParm_var oldparm = iOldValue;
			   CATICkeParm_var newparm = iElement;
			   if (!!oldparm && !!newparm)
			   {
				   CATICkeType_var oldtype = oldparm->Type();
				   CATICkeType_var newtype = newparm->Type();
				   if (oldtype==newtype)
					   oElementValidity=1;
			   }
		   }
		   else
		   {
			   oElementValidity=0;
			   if ((iNameOfRole.SearchSubString("Ratio")!=-1)
				   ||(iNameOfRole.SearchSubString("Precis")!=-1)
				   ||(iNameOfRole.SearchSubString("Norme")!=-1))
				   if (newtype==ParmDic->GetRealType())
					   oElementValidity=1;
			   if (iNameOfRole.SearchSubString("Ang")!=-1)
				   if (newtype==ParmDic->GetAngleType())
					   oElementValidity=1;
			   if ((iNameOfRole.SearchSubString("Length")!=-1)
				   ||(iNameOfRole.SearchSubString("Long")!=-1)
				   ||(iNameOfRole.SearchSubString("Values")!=-1)
				   ||(iNameOfRole.SearchSubString("Radius")!=-1)
				   ||(iNameOfRole.SearchSubString("Distance")!=-1))
				   if (newtype==ParmDic->GetLengthType())
					   oElementValidity=1;
		   }
	   }
   }
#ifdef DEBUG_REPLACE 
   cout <<"CAAEGSMFeaturesSplReplace::IsElementValidForReplace  =  "<<oElementValidity << endl;
#endif 

   // Exit 
   return rc ;
}


//-----------------------------------------------------------------------------
// Replace
//-----------------------------------------------------------------------------
HRESULT
CAAEGSMFeaturesSplReplace::Replace(const CATUnicodeString& iNameOfRole,
								   CATBaseUnknown_var& ispNewElement,
								   const CATBaseUnknown_var& ispOldValue)
{
	HRESULT rc = E_FAIL;

#ifdef DEBUG_REPLACE 
	cout <<"CAAEGSMFeaturesSplReplace::Replace" << endl;
#endif 

	CATISpecObject_var spCurrent = this;
	CATISpecObject_var spNewSpec = ispNewElement;
	CATBaseUnknown_var spForReplace = ispNewElement;
	CATISpecObject_var spSpecOldValue  = ispOldValue; 

#ifdef DEBUG_REPLACE 
	cout <<"(CAAEGSMFeaturesSplReplace::Replace) ==== heck Replace HimSelf " << endl;
#endif 
	// ----------------------------------------------------------------------------------
	// Avoid replaceing by himself 
	// ----------------------------------------------------------------------------------
	// Tests to enhance performance in case of replacing an element by itself
	// We want to avoid the Replace of a Feature by itself, but we have 
	// to be cautious with the orientation associated with the input element.
	if ((NULL_var != ispNewElement) && (ispNewElement == ispOldValue))
	{
		// Get the Inversion Management interface
		CATIOrientationFlag_var spInvertFlag = ispNewElement;

		// If the NewElement is not inversed and that the Old one is 
		// equal to the new one, we don't do the Replace
		if (NULL_var != spInvertFlag && !spInvertFlag->IsInversed())
			return S_OK;

		// If the new element doesn't support inversion flag management,
		// the orientation doesn't matter for this element, so the Replace
		// is not necessary, we don't do the Replace
		if (NULL_var == spInvertFlag)
			return S_OK;
	}

	// Tests that input Element is different from this, if it is the 
	// case we are trying to Replace an input of this by this, this is 
	// a basic test to avoid cycle in between Feature. 
	if ((NULL_var != spForReplace) && (spForReplace==spCurrent))
	{
		return E_FAIL;
	}

	// ----------------------------------------------------------------------------------
	// Replace for aggregated Litterals 
	// ----------------------------------------------------------------------------------

	// Specific operation for literal features
	//-------------------------------------------------------
	// Replacing a literal by another leads to an 'equality' formula creation
	// to valuate the literal 'to be replaced'; if the new spec is not a literal
	// nothing is changed from standard operation
	//
   // Identify Types  
   CATIParmDictionary_var ParmDic = CATCkeGlobalFunctions::GetParmDictionary();


	CATICkeParm_var spIOldLitt(ispOldValue);
	if (!!spIOldLitt)  {
#ifdef DEBUG_REPLACE 
	cout <<"(CAAEGSMFeaturesSplReplace::Replace) ==== Replace litteral  " << endl;
#endif 

		CATICkeType_var oldtype = spIOldLitt->Type();
		if(!!oldtype && !(oldtype->IsaKindOf(ParmDic->GetFeatureType())==CATCke::True))
		{

			CATICkeParm_var spINewLitt(ispNewElement);
			if (!!spINewLitt)
			{
				CATICkeType_var newtype = spINewLitt->Type();
				if(!!newtype && !(newtype->IsaKindOf(ParmDic->GetFeatureType())==CATCke::True))
				{
					// Old Litteral Used to handle a formula ? 
					CATICkeRelation_var OldRelation = spIOldLitt -> Relation();
					if (!!OldRelation)   {
						OldRelation -> Desactivate();
					}

					// Get Root ParmPublisher 
					CATIParmPublisher_var spRootPublisher;  
					CATIContainer_var  spCont ;
					if (!!spSpecOldValue)  {    
						spCont = spSpecOldValue -> GetFeatContainer();

						CATIPrtContainer* piPrtContainer = NULL;
						rc = spCont ->QueryInterface(IID_CATIPrtContainer, (void**) &piPrtContainer);
						if (SUCCEEDED(rc)) 
						{
							CATIPrtPart_var spPrtPart = piPrtContainer->GetPart();
							piPrtContainer->Release();    piPrtContainer = NULL;			
							if( spPrtPart  != NULL_var ){ 
								CATIParmPublisher * piPublish = NULL; 
								rc = spPrtPart->QueryInterface(IID_CATIParmPublisher,  (void**) &piPublish);
								spRootPublisher = piPublish; 
								if (piPublish) piPublish-> Release(); piPublish =NULL;  
							} 

						}
					}

					// Equality formula creation
					CATICkeParmFactory_var CkeFac = spCont ;
					if (CkeFac != NULL_var && spRootPublisher != NULL_var   ) 
					{
						CATISpecObject_var spRelationSet = 
							CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Relation,spRootPublisher,CATCke::True);
						if (!!spRelationSet)
						{
							// Create Relation 
							CATCkeListOf(Parm) ListeInputs;
							ListeInputs.Append(spINewLitt);
							CATICkeRelation_var RelationSurLitteral = CkeFac -> CreateFormula("", "", "", spIOldLitt, &ListeInputs, "a1", NULL_var, CATCke::False);

							// Insert Relation
							// It is important (but not necessary) to aggregate those parameters especially in part context
							CATIParmPublisher_var spParmPublisher = spRelationSet;
							if (!!spParmPublisher)
								spParmPublisher->Append(RelationSurLitteral);
						}
					}

					// 
					// If a formula already existed, it is deleted
					// NB: a CATKweServices::RemoveFromCurrentRelationSet method
					// should be soon available. To be followed...
					if (!!OldRelation)
					{
						CATISpecObject_var SpecOldRelation(OldRelation);
						CATISpecObject_var SpecRelationSet;
						if (!!SpecOldRelation 	)	{
							SpecRelationSet = SpecOldRelation -> GetFather();
							if (SpecRelationSet != NULL_var) 	{
								CATIParmPublisher_var PPRelSet(SpecRelationSet);
								if (!!PPRelSet)		{
									PPRelSet -> RemoveChild(SpecOldRelation);
								}
								SpecRelationSet -> Release();
							}
						}
					}
				}
			}
		}
	}


	// ----------------------------------------------------------------------------------
	// Key corresponding to the Input to replace 
	// ----------------------------------------------------------------------------------
#ifdef DEBUG_REPLACE 
	cout <<"(CAAEGSMFeaturesSplReplace::Replace) ==== Get hKey to replace" << iNameOfRole << endl;
#endif 

	// We retrieve the old BRep feature on 'this' feature from
	// 1) the BRep given as old element
	// 2) the given old BRep feature (which might not be on
	// 'this' in PowerCopy scenarii)
	//-----------------------------------------------------------
	CATISpecAttrAccess_var spCurrentObjAttrAccess(GetImpl());
	CATISpecAttrKey_var hKey;
	if (!!spCurrentObjAttrAccess)
	{
		hKey = spCurrentObjAttrAccess -> GetAttrKey(iNameOfRole);
		if (NULL_var != hKey)
			hKey -> Release();
	}

	// ----------------------------------------------------------------------------------
	// Preparation for BRep = Case old value is A BRep - To be manage correctly 
	// ----------------------------------------------------------------------------------

	CATIMfBRep_var     spMfBRepOldValue  (ispOldValue);
	// Test to restore when powercopy works properly
	//   if (!spSpecOldValue && !spIOldLitt && !!hKey)

	if ( (!spSpecOldValue || !!spMfBRepOldValue) && !spIOldLitt && !!hKey)
	{
#ifdef DEBUG_REPLACE 
	cout <<"(CAAEGSMFeaturesSplReplace::Replace) ==== Check  BRep " << endl;
#endif 
 

		// We have a selection element and we must retrieve the corresponding BRep feature
		// (especially for RemoveAnInput)

		if (hKey -> GetType() == tk_list)
		{
			CATListValCATBaseUnknown_var * liste = spCurrentObjAttrAccess -> ListSpecObjects(hKey);
			if (liste)
			{
				int iSize = liste -> Size();
				for (int jj=1 ; jj<=iSize ; jj++)
				{
					CATIMfBRep_var brepFtr = (*liste)[jj];
					if (!!brepFtr && brepFtr -> IsSame(ispOldValue) == 1)
					{
						spSpecOldValue = brepFtr;
						break;
					}
				}
				delete liste;
			}
		}
		else
		{
			CATISpecObject_var ItfSpec = spCurrentObjAttrAccess -> GetSpecObject(hKey);
			if (NULL_var != ItfSpec) ItfSpec -> Release();
			CATIMfBRep_var brepFtr(ItfSpec);
			if (!!brepFtr && brepFtr -> IsSame(ispOldValue) == 1)
			{
				spSpecOldValue = ItfSpec;
			}
		}

	}
	// ----------------------------------------------------------------------------------
	// Featurized And Invert 
	// ----------------------------------------------------------------------------------

	//Featurization on the fly
	//-------------------------------------
	if (NULL_var == spNewSpec)
	{
#ifdef DEBUG_REPLACE 
	cout <<"(CAAEGSMFeaturesSplReplace::Replace) ====  BRep - Featurize " << endl;
#endif 
		CATISpecObject_var spElem = ExtractFeature(ispNewElement);
		spForReplace = spElem;
	}

	//Inversion of the Feature if no inversion still exists
	//-----------------------------------------------------
#ifdef DEBUG_REPLACE 
	cout <<"(CAAEGSMFeaturesSplReplace::Replace) ====  Check Invert " << endl;
#endif 
	spForReplace = InvertFeature(ispNewElement,spForReplace);



    //Check if ispOldValue  is absorbed
	//-----------------------------------------------------
	// spCurrent : Ist it Modification feature ?
	int  OldFeatAbsorbed=0;
	CATIInputDescription::FeatureType iTypeOfCurrent=CATIInputDescription::FeatureType_Creation;
	CATIInputDescription_var InputDes(spCurrent);
	if(!!InputDes)
	{
		rc = InputDes -> GetFeatureType(iTypeOfCurrent); 
#ifdef DEBUG_REPLACE 
		cout <<"(CAAEGSMFeaturesSplReplace::Replace) ==== TypeOfFeature  " << iTypeOfCurrent << endl;
#endif 
	}

	// spCurrent : Modification feature , Ist it inserted in linear body tool ?
	if ( iTypeOfCurrent == CATIInputDescription::FeatureType_Modification){

#ifdef DEBUG_REPLACE 
		cout <<"(CAAEGSMFeaturesSplReplace::Replace) Modification Feature "<< endl;
#endif 
		// Absorbent Set ? 
		int IsAnAbsorbentSet = -1 ;
		CATISpecObject_var spFather = spCurrent->GetFather();
		if ( NULL_var  != spFather ){
			spFather -> Release();
			CATIGSMTool *piGSMToolFather = NULL;
			HRESULT rc =spFather->QueryInterface ( IID_CATIGSMTool, (void**) &piGSMToolFather);
			if ( SUCCEEDED(rc) ) { 
				// Type Of Tool 
				piGSMToolFather->GetType(IsAnAbsorbentSet) ;
				piGSMToolFather->Release() ; piGSMToolFather=NULL; 
			}
		}
#ifdef DEBUG_REPLACE 
		cout <<"(CAAEGSMFeaturesSplReplace::Replace) IsAnAbsorbentSet ?"<<IsAnAbsorbentSet<< endl;
#endif 

		// Is Old Spec input among modified inputs of spCurrent 
		if (IsAnAbsorbentSet) { 
			CATListValCATBaseUnknown_var lAbsorbedFeatures;     
			rc = InputDes->GetListOfModifiedFeatures(lAbsorbedFeatures);
			if (SUCCEEDED(rc )) {
				int nNbAbsorbed = lAbsorbedFeatures.Size();
				for (int nAbsorbed = 1; nAbsorbed <= nNbAbsorbed; nAbsorbed++){
					if (ispOldValue == lAbsorbedFeatures[nAbsorbed]){ 
						 OldFeatAbsorbed=1;
						 break; 
					}
				}
			}
		}
#ifdef DEBUG_REPLACE 
		cout <<"(CAAEGSMFeaturesSplReplace::Replace) OldFeatAbsorbed ?"<<OldFeatAbsorbed<< endl;
#endif 

	}


	// ----------------------------------------------------------------------------------
	// Update Spec Input 
	// ----------------------------------------------------------------------------------
	CATIGSMAttributes_var spGsdSpecAttr (spCurrent) ; 
    if (NULL_var != spGsdSpecAttr) {
		if (!! spSpecOldValue){
			rc = spGsdSpecAttr -> RemoveAttrSpecObject (hKey,spSpecOldValue);
		}
		rc = spGsdSpecAttr -> SetAttrSpecObject(hKey,spForReplace);
	}

	//Send Visu event for main input change
	// --------------------------------------------------------
	if(OldFeatAbsorbed ) {
		
		if ( iTypeOfCurrent == CATIInputDescription::FeatureType_Modification){
#ifdef DEBUG_REPLACE 
			cout <<"(CAAEGSMFeaturesSplReplace::Replace) Refresh Visu "<<endl;
#endif 

			// Refresh Visu Tool 
			// - Allow correct re-display of old input , previously absorbed in current OGS 
			AppendVisu (spCurrent);
		}
	}
	
	// Safety :
	//-----------------------------------------------------------
	// In case of error in Spec  Modeler Replace : We may have created a BRep that is not agggrgated 
	// Need Any way to remove non aggregated BRep Feature :  Clean up non-aggregated brep
	if(!!spForReplace)
	{
		CATISpecObject_var SpecExtractedFeature=spForReplace;
		if(!!SpecExtractedFeature)
		{
			CATISpecObject_var father = SpecExtractedFeature->GetFather();
			if (father!=NULL_var)
			{
				father->Release();
			}
			else
			{
				LifeCycleObject_var ItfLife(SpecExtractedFeature);
				if (!!ItfLife) ItfLife -> remove();
			}
		}
	}


	// ----------------------------------------------------------------------------------
	//Update Representation
	// ----------------------------------------------------------------------------------
#ifdef DEBUG_REPLACE 
	cout <<"(CAAEGSMFeaturesSplReplace::Replace) ====  Check Visu : Redraw  " << endl;
#endif 
	CATIRedrawEvent_var spEvent(spCurrent);
	if (NULL_var != spEvent) {
		spEvent->Redraw();
	}

	return rc;
}
// *** End of CATIReplace Implementation 

//------------------------------------------------------------------------
// Extract Feature = Featurized a selected BREP feature for replace  
//------------------------------------------------------------------------
CATISpecObject_var
CAAEGSMFeaturesSplReplace::ExtractFeature(const CATBaseUnknown_var& ispSelectedObject)
{
#ifdef DEBUG_REPLACE 
	cout <<"CAAEGSMFeaturesSplReplace::ExtractFeature" << endl;
#endif 

	CATISpecObject_var spNewValue = ispSelectedObject;

	if (NULL_var == spNewValue)
	{
		// Selected Object conversion into an equivalent feature
      CATIFeaturize_var spToFeaturize = ispSelectedObject;
      if (NULL_var != spToFeaturize)
      {
         // We create a Feature that will have the representation (Result) of the 
         // selected object that will be a Relimited one. The selected object is a non-
         // persistent object, with this conversion we make it persistent and associative.
         // This feature will be aggregated in the Replace method, we just have to update it
         // before calling this method.
         spNewValue = spToFeaturize->FeaturizeR(MfPermanentBody | 
                                                MfLastFeatureSupport | 
                                                MfRelimitedFeaturization);
         //Update of the New Feature
         CATTry
         {
            spNewValue->Update();
         }
         CATCatch(CATError,error)
         {
             ::Flush(error);
         }
         CATEndTry    
      }
   }

   return spNewValue; 
}

//------------------------------------------------------------------------
// Invert Feature = Insert GSDInversee if asked by Generic replace interactive component 
//------------------------------------------------------------------------
CATISpecObject_var CAAEGSMFeaturesSplReplace::InvertFeature(const CATBaseUnknown_var& ispSelectedObject, const CATISpecObject_var& ispCurrentSpec)
{
#ifdef DEBUG_REPLACE 
   cout <<"CAAEGSMFeaturesSplReplace::InvertFeature" << endl;
#endif 

   CATISpecObject_var spToReturn = ispCurrentSpec;

   //We check that the feature is not inversed
   CATIOrientationFlag_var spInvertFlag = ispSelectedObject;
   if (NULL_var != spInvertFlag && spInvertFlag->IsInversed())
   {
      //We check first if the feature is an inversion
      CATIGSMInverse_var spInverse = ispCurrentSpec;
      if (NULL_var != spInverse)
      {
         //We retrieve inversion Parent
         spToReturn = spInverse->GetElem();
      }
      else
      {
          //Inversion Creation
          //------------------
          CATISpecObject_var spSpec(this);
          CATISpecObject_var spInverse = NULL_var;
          CATIContainer_var  spFeatCont= spSpec -> GetFeatContainer();
          
          //We check that no inversion still exist on this feature
          //We First get the pointing attributes, owned by a GSMInverse feature  
          
          /*
          CATListValCATISpecAttribute_var * aListAtt = ispCurrentSpec->InverseAttrLink("CATIGSMInverse"); 
          */
          CATISpecAttrAccess_var spAttrAccessOnCurrentSpec = ispCurrentSpec;
          CATListValCATBaseUnknown_var * pListPointingObject = spAttrAccessOnCurrentSpec->ListPointingObjects(IID_CATIGSMInverse);
          if (NULL != pListPointingObject)
          {
              int size = pListPointingObject -> Size();
              for (int i = 1; i<= size; i++)
              {
                  CATISpecObject_var spOwner =  (*pListPointingObject)[i];
                  if ( NULL_var != spOwner )
                  {
                      // if the feature is created in the same Container of Feature
                      // then we store the Inverse feature and exit the loop.
                      CATIContainer_var spFeatContForOwner = spOwner->GetFeatContainer() ;
                      if ( spFeatContForOwner == spFeatCont)
                      {
                          // We have found a valid Inverse Feature, we step out of this loop
                          // and we won't need an inversion creation. 
                          spInverse = spOwner;
                          break;
                      }
                  }
              }
              delete pListPointingObject;
              pListPointingObject = NULL;
          }
          
          
          // Finally we create the inversion
          // If no inversion was found above.
          if (NULL_var == spInverse)
          {
              CATIGSMFactory * pIFactoryOnFeatCont = NULL ;   
              HRESULT rc = spFeatCont->QueryInterface(IID_CATIGSMFactory,(void**)&pIFactoryOnFeatCont);
              if ( SUCCEEDED(rc) )
              {
                  spInverse = pIFactoryOnFeatCont -> CreateInverse(ispCurrentSpec);
                  if (NULL_var != spInverse)
                  {
					  /*
                      //Hide the inversion
                      CATIVisProperties *pVisuSpec = NULL;
                      rc = spInverse->QueryInterface(IID_CATIVisProperties,(void**)&pVisuSpec);
                      if( SUCCEEDED(rc) )
                      {
                          CATVisPropertiesValues MyProp ;
                          MyProp.SetShowAttr(CATNoShowAttr);
                          pVisuSpec -> SetPropertiesAtt(MyProp,CATVPShow,CATVPGlobalType);
                          pVisuSpec -> Release();
                          pVisuSpec = NULL ;
                      }
                      */ 
                      // Aggregation of the inversion to me
                      CATIDescendants_var spDesc = spSpec;
                      if (NULL_var != spDesc)
                      {
                          spDesc -> Append(spInverse);
                      }
                      
                      //Update the inversion
                      CATISpecObject_var spObject = spInverse;
                      if (NULL_var != spObject)
                      {
                          CATTry
                          {
                              spObject->Update();
                          }
                          CATCatch(CATError,error)
                          {
                              Flush(error);
                          }
                          CATEndTry    
                      }
                  }
                  
                  pIFactoryOnFeatCont->Release();
                  pIFactoryOnFeatCont = NULL ;
              }
          }
          spToReturn = spInverse;
      }
   }
   return spToReturn;
}


// Refresh Visu / Event send to the tool father 
// --------------------------------------------------------------
void CAAEGSMFeaturesSplReplace::AppendVisu(CATISpecObject_var spSpec )
{
#ifdef DEBUG_REPLACE 
	cout <<"(AppendVisu) ==== spSpec " <<  spSpec -> GetName() << endl;
#endif 
	CATISpecObject_var spFather  = spSpec ->GetFather();
	if ( NULL_var  != spFather )
	{
		spFather -> Release();
		CATIGSMTool *piGSMToolFather = NULL;
		HRESULT rc =spFather->QueryInterface ( IID_CATIGSMTool, (void**) &piGSMToolFather);
		if ( SUCCEEDED(rc) ) { 

			// Event set to father tool in order to refresh visualization
			CATIModelEvents_var IME(piGSMToolFather);
			if(NULL_var != IME) {
				CATModify info(piGSMToolFather->GetImpl());
				IME->Dispatch(info);
			}
			piGSMToolFather->Release() ; piGSMToolFather=NULL; 
		}
		else {
			AppendVisu( spFather);
		}
	}   
}


