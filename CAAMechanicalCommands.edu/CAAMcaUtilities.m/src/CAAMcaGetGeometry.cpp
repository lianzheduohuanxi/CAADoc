// COPYRIGHT DASSAULT SYSTEMES 2001
//==========================================================================
// This file contains the method to extract from the original CATPart the
// geometrie to create the new user feature
// This method is called in the CAAMcaUdfCreation.cpp 
//==========================================================================

//MecModInterfaces Framework
#include "CATIPrtContainer.h"
#include "CATIPartRequest.h"

// ObjectSpecsModeler Framework
#include "CATIDescendants.h"
#include "CATISpecObject.h"
#include "CATIAlias.h"      // to retrieve a specific body 

#include "CATLISTV_CATBaseUnknown.h" 

// Local Framework
#include "CAAMcaGetGeometry.h"      // to retrieve a specific element

#include "iostream.h"


HRESULT CAAMcaGetGeometry(CATISpecObject_var ispModelPart, const CATUnicodeString iInputName,
				 CATBaseUnknown ** oInput)
{
  HRESULT rc = E_FAIL ;
  CATBoolean found = FALSE ;	

  if ( (NULL != oInput) && ( NULL_var != ispModelPart) )
  {   
     *oInput = NULL ;

     CATIPartRequest * pPartAsRequest = NULL ;
     rc = ispModelPart->QueryInterface(IID_CATIPartRequest,(void**)&pPartAsRequest);
     if ( SUCCEEDED(rc) )
     {
        // Retrieves all bodies
        CATListValCATBaseUnknown_var pListBodies  ;
        rc = pPartAsRequest->GetAllBodies("",pListBodies);
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
                   CATIDescendants * pIDescendants = NULL ;
                   rc =  spAliasBody->QueryInterface(IID_CATIDescendants,(void**)&pIDescendants);
		   if ( SUCCEEDED(rc) )
                   {
                      // finds a specific element in the body
		      int iChild=1 ;	  
		      int nbchild = pIDescendants->GetNumberOfChildren() ;

                      while (  (FALSE == found) && (iChild <= nbchild) )
                      {
                         CATIAlias_var spChild = pIDescendants->GetChildAtPosition(iChild) ;
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
					   
                      pIDescendants->Release();
		      pIDescendants = NULL ;
		   }
                 }
              }
              iBodies ++ ;               
           }
        }
        pPartAsRequest->Release();
        pPartAsRequest = NULL ;
     }
  }

  if ( TRUE == found )
  {
     rc =S_OK ;
  }
  return rc ;
}

