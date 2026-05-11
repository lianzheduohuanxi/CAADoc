// COPYRIGHT DASSAULT SYSTEMES 2012
//==========================================================================
// This file contains the method to extract from the geometry from the part
//==========================================================================

// MecModInterfaces Framework in V5
// CATMecModLiveUseItf Framework in V6
#include "CATIPartRequest.h"

// CATMecModLiveUseItf Framework 
#include "CATIMmiUseBodyContent.h"

// ObjectModelerBase Framework
#include "CATIAlias.h"      // to retrieve a specific body 

// Local Framework
#include "CAAV5V6MmrGetGeometry.h"      // to retrieve a specific element

//System Frameworks
#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include "CATLISTV_CATBaseUnknown.h"

// C++ Standard library
#include "iostream.h"


HRESULT CAAV5V6MmrGetGeometry(CATIPartRequest_var ispModelPart, const CATUnicodeString iInputName,
				 CATBaseUnknown ** oInput)
{
  HRESULT rc = E_FAIL ;
  CATBoolean found = FALSE ;	

  if ( (NULL != oInput) && ( NULL_var != ispModelPart) )
  {   
	  *oInput = NULL ;

	  // Retrieves all root bodies , all GS and all root OGS ( it does not retrieve ALL bodies below the Part)
	  CATListValCATBaseUnknown_var pListBodies  ;
	  rc = ispModelPart->GetAllBodies("",pListBodies);
	  if ( SUCCEEDED(rc) )
	  {
		  int iBodies =1 ;	  
		  int nbbodies = pListBodies.Size();

		  while ( (FALSE == found) && (iBodies <= nbbodies) )
		  {
			  CATIAlias_var spAliasBody = pListBodies[iBodies] ;
			  if ( NULL_var != spAliasBody )
			  {
				  CATUnicodeString currentbodyname = spAliasBody->GetAlias();

				  if ( iInputName == currentbodyname )
				  {
					  // We have found a body
					  found = TRUE ;
					  rc = spAliasBody->QueryInterface(IID_CATBaseUnknown,(void**)&(*oInput));
				  }else
				  {
					  // Research in the body
					  CATIMmiUseBodyContent_var spUseBodyContentOnBody = spAliasBody ;
					  if ( spUseBodyContentOnBody != NULL_var )
					  {
						  // Retrieve all geometrical element in the body 
						  CATListValCATBaseUnknown_var ListFeatureInsideCurrentBody;
                          spUseBodyContentOnBody->GetMechanicalFeatures(ListFeatureInsideCurrentBody) ;
						  int nbchild = ListFeatureInsideCurrentBody.Size() ;

						  int iChild=1 ;
						  while (  (FALSE == found) && (iChild <= nbchild) )
						  {
							  CATIAlias_var spChild = ListFeatureInsideCurrentBody[iChild] ;
							  if ( NULL_var != spChild )
							  {
								  CATUnicodeString currentchildname = spChild->GetAlias();

								  if ( iInputName == currentchildname )
								  {
									  // we have found a child of a body
									  found = TRUE ;
									  rc = spChild->QueryInterface(IID_CATBaseUnknown,(void**)&(*oInput));
								  }
							  }
							  iChild++ ;
						  }
					  }
				  }
			  }
			  iBodies ++ ;               
		  }
	  }

  }

  if ( TRUE == found )
  {
     rc =S_OK ;
  }
  else 
	 rc = E_FAIL;

  return rc ;
}

