// COPYRIGHT DASSAULT SYSTEMES  1994 2000

//Local Framework
#include "CAALifMyPublisher.h"

// ObjectSpecsModeler 
#include "CATLISTV_CATISpecObject.h"
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"


//LiteralFeatures
#include "CATIParmPublisher.h"


// ================================================================
// 
// ABSTRACT
// --------
// 
// This class defines the CAAMyPublisher code extension which implements CATIParmPublisher
// It derives from CATParmPublisherAdapter and redefine the GetDirectChildren and 
// CompAttrKey methods.
// Any object intended to be added parameters and relations and benefit from the f(x) 
// capabilities must implement the CATIParmPublisher interface.
// The LiteralFeatures framework provides you with the CATParmPublisherAdapter adapter you can extend
// to redefine the GetDirectChildren and GetAllChildren methods.
//
// ===========================================================================
//  Usage:
//  ------
//  Type  CAALifPublishMain
//  
//===========================================================================
//  Inheritance:
//  ------------
//         CATParmPublisherAdapter
//
//===========================================================================

#include "TIE_CATIParmPublisher.h"
TIE_CATIParmPublisher(CAALifMyPublisher);

CATImplementClass(CAALifMyPublisher,CodeExtension,CATBaseUnknown,CAALifSimpleFeature);

CAALifMyPublisher::CAALifMyPublisher()
{
}

CAALifMyPublisher::~CAALifMyPublisher()
{
}

CAALifMyPublisher::CAALifMyPublisher(const CAALifMyPublisher& iRel)
{
}

// add a feature as a component in the "components" attributes which holds a tk_list(tk_component). 
// if the feature does not hold this attribute, nothing is done. 
void CAALifMyPublisher::Append  (const CATISpecObject_var & iKBwareObject ) 
{
    CATISpecAttrAccess_var spSak (this);
    CATISpecAttrKey_var spKey = spSak->GetAttrKey("components");
    if (NULL_var != spKey) 
    { 
        spSak->SetSpecObject(spKey,iKBwareObject);
        spKey->Release();
    }
}


// remove a feature
void CAALifMyPublisher::RemoveChild  (const CATISpecObject_var & iKBwareObject ) 
{
    CATISpecAttrAccess_var spSak (this);	
    CATISpecAttrKey_var spKey = spSak->GetAttrKey("components");
    if (NULL_var != spKey) 
    { 
        spSak->RemoveSpecObject(spKey,iKBwareObject);
        spKey->Release();
    }
}

// The default CATCkeDescendants::GetChildren method is overriden to enable the addition
// of user parameters and relations to the "LifFeatureLength" feature
void CAALifMyPublisher::GetDirectChildren (CATClassId iIntfName,
                                           CATListValCATISpecObject_var &oLst) 
{
    // Retrieve the CATISpecObject from the attribute key
    CATISpecAttrAccess_var spSpecAccess (this);
    CATISpecAttrKey_var spSpecKey = spSpecAccess->GetAttrKey("LifFeatureLength");
    if (NULL_var != spSpecKey) 
        spSpecKey->Release();
    
    CATISpecObject_var spMySpecParam = spSpecAccess->GetSpecObject(spSpecKey);
    if (NULL_var != spMySpecParam) 
        spMySpecParam->Release();
    
    // Determine whether the retrieved CATISpecObject supports
    // the interface specified in the argument
    CATBaseUnknown* pAsked=NULL;
    pAsked = spMySpecParam->QueryInterface(iIntfName);
    if ( NULL != pAsked ) 
    {
        pAsked->Release();
        
        // Add the CATISpecObject which supports the iIntfName interface
        // to the list specified in the second (output) argument
        oLst.Append(spMySpecParam);
    }
    
    // Then we add the objects that had been appended
    spSpecKey =  spSpecAccess->GetAttrKey("components");
    if (NULL_var != spSpecKey)
    {
        spSpecKey->Release();
        
        if (spSpecAccess->TestAttributeValue(spSpecKey) &&  spSpecAccess->GetListSize(spSpecKey) != 0) 
        {
            // we get the list of objects implementing iIntfName
            CATListValCATInterfaceObject_var* plis = spSpecAccess->ListSpecObjects(spSpecKey,iIntfName);
            if ( NULL != plis )
            {
                int size = plis->Size();
                for (int i=1; i <= size; i++)
                {
                    CATISpecObject_var spec = (*plis)[i];
                    if (spec != NULL_var) oLst.Append (spec);
                    
                }
                delete plis;
            } 
        }
    }
    
    return;
}


// scan all children (recursive) 
void CAALifMyPublisher::GetAllChildren (CATClassId iIntfName,
                                        CATListValCATISpecObject_var &oLst)  
{
    CATISpecAttrAccess_var spSpecAccess (this);
    CATISpecAttrKey_var spSpecKey = spSpecAccess->GetAttrKey("components");
    CATIParmPublisher_var des = NULL_var;
    
    // first we add the direct children
    GetDirectChildren (iIntfName,oLst);
    
    if (NULL_var != spSpecKey)
    {
        if (spSpecAccess->TestAttributeValue(spSpecKey) &&  spSpecAccess->GetListSize(spSpecKey) != 0) 
        {
            //get the list of objects implementing CATIParmPublisher inside the list "components".
            CATListValCATInterfaceObject_var* plis = spSpecAccess->ListSpecObjects(spSpecKey,CATIParmPublisher::ClassName());
            if ( plis != NULL )
            {
                int size = plis->Size();
                for (int i=1; i <= size; i++)
                {
                    des = (*plis)[i];
                    if (!!des)
                    {   
                        // for each one call GetAllChildren
                        des->GetAllChildren (iIntfName,oLst);
                    }
                }
                delete plis;
            } 
        }
        spSpecKey->Release();
        
    }	
    return;
}


boolean CAALifMyPublisher::AllowUserAppend ( ) const
{
    return FALSE;
}

CATIContainer_var CAALifMyPublisher::GetContainer()
{
    CATIContainer_var container;
    CATISpecObject_var spec(this);
    if (!!spec)
        container = spec->GetFeatContainer();
    return container;
}





void CAALifMyPublisher::VisitChildren( CATIVisitor* iVisitor,
                                      const int iRecursively)
{
    
    HRESULT hr = E_FAIL;
    if (!iVisitor)
        return;
    
    
    //Trigger the visitor on the parameter under the attribute "LifFeatureLength.
    CATISpecAttrAccess_var spSpecAccess (this);
    CATISpecAttrKey_var spSpecKey = spSpecAccess->GetAttrKey("LifFeatureLength");
    if( NULL_var != spSpecKey )
      {
        CATISpecObject_var spMySpecParam = spSpecAccess->GetSpecObject(spSpecKey);
        if (NULL_var != spMySpecParam) 
          spMySpecParam->Release();
    
        iVisitor->Visit(spMySpecParam);
        spSpecKey->Release();
      }


    
    //Next trigger the visitor on each member of the list "components".
    spSpecKey =  spSpecAccess->GetAttrKey("components");
    CATLISTV(CATBaseUnknown_var) *components = NULL;

    CATIParmPublisher_var des = NULL_var;
        
    if (NULL_var != spSpecKey)
    {
        if (spSpecAccess->TestAttributeValue(spSpecKey) &&  spSpecAccess->GetListSize(spSpecKey) != 0) 
        {
            // we get the list of objects implementing iIntfName
            CATListValCATInterfaceObject_var* plis = spSpecAccess->ListSpecObjects(spSpecKey, CATISpecObject::ClassName());
            if ( plis != NULL )
            {
                //we visit each object of the list.
                int size = plis->Size();
                for (int i=1; i <= size; i++)
                {
                    iVisitor->Visit( (*plis)[i] );
                }
                delete plis;
            } 

            if(iRecursively)
            {
                plis = spSpecAccess->ListSpecObjects(spSpecKey, CATIParmPublisher::ClassName());
                if ( plis != NULL )
                {
                    //we recursively launch visitchildren.
                    int size = plis->Size();
                    for (int i=1; i <= size; i++)
                    {
                        CATIParmPublisher_var publisher = (*plis)[i];

                        //useless test but mkCheckSource will produce an error here.
                        if(publisher != NULL_var)
                            publisher->VisitChildren( iVisitor, iRecursively );
                    }
                    delete plis;
                }
            }
        }
        spSpecKey->Release();
    }	
    return;
}




