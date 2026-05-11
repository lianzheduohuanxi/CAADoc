// COPYRIGHT DASSAULT SYSTEMES  2002
//
// The steps are the following:
//
//   1- Displaying its name and its type ( family,chapter, external or not)
//   2- Displaying its keywords and theirs default value
//   3- Displaying its persistent queries count
//   4- Retrieving its descriptions
//      4-1 Displaying the Name of the description
//      4-2 Displaying the value of each keyword
//      4-3 Analysing the referenced object
//          4-3-1 The referenced object is a chapter 
//                chapter or family ?
//                external or not ?
//                go step 1 with the sub chapter
//          4-3-2 The referenced object is not a chapter
//                retrieving its type (document, feature, description)
//                retrieving its name
//                processing the document case
//                processing the description case
//
//==========================================================================

// ComponentsCatalogsInterfaces Framework
#include "CATICatalogChapter.h" 
#include "CATICatalogQueryResult.h" 
#include "CATListValCATICatalogDescription_var.h"
#include "CATICatalogDescription.h"
#include "CATListValCATICatalogKeyword_var.h"
#include "CATListValCATICatalogPersistentQuery_var.h"
#include "CATICatalogKeyword.h"

// ObjectSpecModeler Framework
#include "CATISpecObject.h"

// ObjectModelerBase Framework
#include "CATIAlias.h"
#include "CATInit.h"
#include "CATILinkableObject.h"

// Standard C++ library
#include "iostream.h"

HRESULT CAABrowsingChapter(CATICatalogChapter * pICatalogChapter, 
                           const CATUnicodeString & ChapterType, 
                           int MoveTxt)
                           
{   
    HRESULT rc = E_FAIL ;

    if ( pICatalogChapter == NULL )
    {
        return rc ;
    }
    rc = S_OK ;

    CATUnicodeString text =" " ;
    CATUnicodeString tiret ="-" ;
    CATUnicodeString SpaceChapter(tiret,MoveTxt);
    CATUnicodeString SpaceChapterContents(text,MoveTxt+3);
    CATUnicodeString SpaceDescContents(text,MoveTxt+6);

    // 1- Displaying the name of the current chapter
    CATUnicodeString ChapterName ;
    ChapterName = pICatalogChapter->GetChapterName();
    cout << SpaceChapter.CastToCharPtr() << ChapterName.CastToCharPtr() ;
    cout << " (" << ChapterType.CastToCharPtr() << ")" << endl;
    
    // 2- Displaying the keywords and their default value for the current chapter
    CATListValCATICatalogKeyword_var * pListKeyword = NULL ;
    rc = pICatalogChapter->ListKeywords(pListKeyword);
    int SizeKWList = 0 ;
    if ( SUCCEEDED(rc) && (NULL != pListKeyword) )
    {
        SizeKWList = pListKeyword->Size();
        cout << SpaceChapterContents.CastToCharPtr() << "Keyword(s): " <<SizeKWList << endl;

        for ( int i=1 ; i<= SizeKWList; i++)
        {
            CATICatalogKeyword_var CurrentKeyword ((*pListKeyword)[i]);
            if ( NULL_var != CurrentKeyword )
            {
               // Its Name
               CATUnicodeString KWName = CurrentKeyword->GetKeywordName();
        
               // Hidden or not ?
               if  ( TRUE == CurrentKeyword->GetHidden() )
               {
                   KWName += "(*)";
               }
               cout <<SpaceChapterContents.CastToCharPtr()<< "   " << KWName.CastToCharPtr() ;

               // Its type
               CATICkeType * pType = CurrentKeyword->GetKeywordType();
               if ( NULL != pType )
               {
                  cout <<"; Type kwd= "<< pType->Show().CastToCharPtr() ;
                  
                  pType->Release();
                  pType = NULL ;
               }

               // Its unit
               CATICkeUnit * pUnit = CurrentKeyword->GetKeywordUnit();
               if ( NULL != pUnit )
               {
                  cout <<"; Unit kwd= "<< pUnit->Symbol().CastToCharPtr() ;

                  pUnit->Release();
                  pUnit = NULL ;
               }

               // Default value
               CATUnicodeString DefaultValue ;
               CATBoolean IsDefaultValue = pICatalogChapter->GetDefaultValue(KWName,DefaultValue);
 
               if ( FALSE == IsDefaultValue  ) DefaultValue = "Unset" ;
               cout <<"; Default value= "<< DefaultValue.CastToCharPtr() << endl;
            }
        }
    }
    cout << endl;
    
    // 3- Verifying the Persistent Queries count
    CATListValCATICatalogPersistentQuery_var * pListPersistentQuery = NULL ;
    rc = pICatalogChapter->ListPersistentQuery(pListPersistentQuery);

    if ( SUCCEEDED(rc) && (NULL !=pListPersistentQuery) )
    {
       int NbPQ = pListPersistentQuery->Size();
       cout << SpaceChapterContents.CastToCharPtr() ;
       cout <<"Nb Pesistent Query=" <<NbPQ << endl;
       for ( int i= 1 ; i <= NbPQ ; i++ )
       {
           CATICatalogPersistentQuery_var CurrentPQ ((*pListPersistentQuery)[i]);
           if ( NULL_var != CurrentPQ )
           {
               CATICatalogChapter * piFilterChapter = NULL;
               // Retrieving the root chapter of the filtered catalog
               rc = CurrentPQ->GetResolutionChapter(piFilterChapter,1);
               if ( SUCCEEDED(rc) )
               {
                   cout <<SpaceChapterContents.CastToCharPtr() ;
                   cout <<"Filtered Chapter" << piFilterChapter->GetChapterName().CastToCharPtr() << endl;

                   piFilterChapter->Release();
                   piFilterChapter = NULL ;
               }
               // Retrieving the expression
               CATUnicodeString Expression ;
               rc = CurrentPQ->GetExpression(Expression);
               if ( SUCCEEDED(rc) )
               {
                   cout <<SpaceChapterContents.CastToCharPtr() ;
                   cout <<"Expression" << Expression.CastToCharPtr() << endl;
               }
           }
       }
       delete pListPersistentQuery ;
       pListPersistentQuery = NULL ;
    }
 
    // 4- Retrieving the description list
    CATListValCATICatalogDescription_var * pListDescription = NULL ;
    rc = pICatalogChapter->ListDescriptions(pListDescription);
    if ( SUCCEEDED(rc) && (NULL != pListDescription) )
    {
      int SizeDescList = pListDescription->Size();

      // Verification
      int NbDesc = 0;
      rc = pICatalogChapter->GetNumberOfDescriptions(NbDesc);
      if ( SUCCEEDED(rc) && (NbDesc == SizeDescList) )
      { 
        for ( int i= 1 ; i<=SizeDescList ;i++)
        {
            CATICatalogDescription_var CurrentDescription ((*pListDescription)[i]);

            if ( NULL_var != CurrentDescription )
            {
               // 4-1 Displaying the Name of the description
               // ------------------------------------------
               CATUnicodeString DescriptionName ;
               rc = CurrentDescription->GetName(DescriptionName) ;
               if ( SUCCEEDED(rc) )
               {
                  cout <<SpaceChapterContents.CastToCharPtr() <<"Description's name= " ;
                  cout << DescriptionName.CastToCharPtr() << endl;
               }

               // 4-2 Displaying the value of each keyword 
               // ----------------------------------------
               cout <<SpaceDescContents.CastToCharPtr() <<"Chapter's keyword value " << endl;
               for ( int j= 1 ; j <= SizeKWList ; j++ )
                {
                  CATICatalogKeyword_var CurrentKeyword ((*pListKeyword)[j]);
                  CATUnicodeString value ;
                   
                  CATUnicodeString KWName = CurrentKeyword->GetKeywordName();
                  rc = CurrentDescription->GetValue(KWName,value); 

                  cout << SpaceDescContents.CastToCharPtr() ;
                  cout << "   " << KWName.CastToCharPtr() ;
                  if ( SUCCEEDED(rc) )
                  {
                     cout << "= " << value.CastToCharPtr() << endl;
                  }else 
                  {
                     cout << "= Unset" << endl;
                     rc = S_OK ;
                  }
                }

                // 4-3 Analysing the referenced object 
                // -----------------------------------
                CATBaseUnknown * pReferencedObject = NULL ;
                rc = CurrentDescription->GetObject(pReferencedObject);

                if ( SUCCEEDED(rc)  && ( NULL != pReferencedObject) )
                {
                   if ( CurrentDescription->IsObjectASubchapter() )
                   {

                      // Retrieving the pointed chapter 
                      CATICatalogChapter * pChapter = NULL ;
                      pChapter = CurrentDescription->GetSubChapter();

                      if ( NULL != pChapter )
                      {
                         // Verifications
                         CATICatalogQueryResult * pICatalogQueryResult = NULL ;
                         rc = pReferencedObject->QueryInterface(IID_CATICatalogQueryResult,
                                               (void **) & pICatalogQueryResult);
                         if ( SUCCEEDED(rc) )
                         {
                            CATICatalogChapter * pIChapter = NULL ;
                            rc = pICatalogQueryResult->GetChapter(pIChapter);
                            if ( SUCCEEDED(rc) )
                            {
                               if ( pIChapter->GetChapterName() != 
                                    pChapter->GetChapterName() )
                               {
                                  cout <<" Error " << endl;
                                  rc = E_FAIL ;
                               }
                               pIChapter->Release();
                               pIChapter = NULL ;
                            }
                            pICatalogQueryResult->Release();
                            pICatalogQueryResult = NULL ;
                         }

                         // chapter or family ?
                         CATUnicodeString sTypeOfChapter ;
                         sTypeOfChapter = "Chapter" ;

                         CATBoolean EndChapter ;
                         EndChapter = pChapter->KindIsEndChapter() ;
                         if ( TRUE == EndChapter )
                         {
                            sTypeOfChapter = "Family" ; 
                         }

                         CATILinkableObject * pLinkObjectOnChapter = NULL ;
                         rc = pChapter->QueryInterface(IID_CATILinkableObject,
                                               (void **) & pLinkObjectOnChapter);

                         // External or not ?
                         if ( SUCCEEDED(rc) )
                         {  
                            CATILinkableObject * pLinkObjectOnDescription = NULL ;
                            rc = CurrentDescription->QueryInterface(IID_CATILinkableObject,
                                                    (void **) & pLinkObjectOnDescription);
                            if ( SUCCEEDED(rc) )
                            {
                                  CATDocument *pDocOnDescription    = pLinkObjectOnDescription->GetDocument();
                                  CATDocument *pDocOnPointedChapter = pLinkObjectOnChapter->GetDocument();
                                  if ( pDocOnDescription != pDocOnPointedChapter )
                                  {
                                   // pointed chapter is external for those which contains the
                                   // current dscription
                                   sTypeOfChapter = "External " + sTypeOfChapter ;
                                  }
                                  pLinkObjectOnDescription->Release();
                                  pLinkObjectOnDescription = NULL ;
                            }

                            pLinkObjectOnChapter->Release();
                            pLinkObjectOnChapter = NULL ;

                            // recursivity
                            ::CAABrowsingChapter(pChapter,
                                              sTypeOfChapter,
                                              MoveTxt+6) ;

                         }
                         pChapter->Release();
                         pChapter = NULL ;
                     }

                   }else
                   {
                      // 4-3-2 The referenced object is not a chapter  
                      // --------------------------------------------

                      CATUnicodeString sTypeOfTheDescription ;
                      CATICatalogDescription::CATCatalogDescriptionType TypeOfTheDescription ;
                      CurrentDescription->GetDescriptionType(TypeOfTheDescription);
                  
                      if      (TypeOfTheDescription == CATICatalogDescription::CATCatalogFeature)
                         sTypeOfTheDescription = "Feature";
                      else if (TypeOfTheDescription == CATICatalogDescription::CATCatalogDescription)
                         sTypeOfTheDescription = "Description";
                      else if (TypeOfTheDescription == CATICatalogDescription::CATCatalogDocument)
                         sTypeOfTheDescription = "Document";

                      cout <<SpaceDescContents.CastToCharPtr() <<"Referenced Object's Type= " ;
                      cout << sTypeOfTheDescription.CastToCharPtr() << endl;

                      // Displaying its name
                      CATIAlias * pIAlias = NULL ;
                      rc = pReferencedObject->QueryInterface(IID_CATIAlias,
                                               (void **) & pIAlias);

                      if ( SUCCEEDED(rc) )
                      {
                        CATUnicodeString Identifier;
                        Identifier = pIAlias->GetAlias() ;
                        cout << SpaceDescContents.CastToCharPtr() ;
                        cout <<"Referenced Object's Name= " ;
                        cout <<Identifier.CastToCharPtr() << endl;

                        pIAlias->Release();
                        pIAlias = NULL ;
                      }

                      // Processing the Document case
                      if ( TypeOfTheDescription == CATICatalogDescription::CATCatalogDocument) 
                      {
                         CATInit * pIInitOnPointedDesc = NULL ;
                         rc = pReferencedObject->QueryInterface(IID_CATInit,
                                                  (void**) &pIInitOnPointedDesc);
                         if ( SUCCEEDED(rc) )
                         {
                            pIInitOnPointedDesc->Release();
                            pIInitOnPointedDesc = NULL ;

                            int value ; 
                            CurrentDescription->IsResolvedObjectComputed(value) ;
                            cout << SpaceDescContents.CastToCharPtr() ;
                            if ( value == 1 )
                            {
                               cout <<"Resolved Part configuration" << endl;
                            }else
                            {
                               cout <<"Part configuration" << endl;
                            }
                         }

                      }

                      // Processing the Description case
                      if ( TypeOfTheDescription == CATICatalogDescription::CATCatalogDescription )
                      {
                         CATICatalogDescription * pIPointedDesc = NULL ;
                         rc = pReferencedObject->QueryInterface(IID_CATICatalogDescription,
                                                  (void**) &pIPointedDesc);
                         if ( SUCCEEDED(rc) )
                         {
 
                             CATICatalogChapter * pExternalChapter = NULL ;
                             rc = pIPointedDesc->GetChapter(pExternalChapter);
                             if ( SUCCEEDED(rc) )
                             {
                                CATUnicodeString ChapterName ;
                                ChapterName = pExternalChapter->GetChapterName();
                                cout <<SpaceDescContents.CastToCharPtr() ;
                                cout <<"Name of its external chapter:" ;
                                cout <<ChapterName.CastToCharPtr() << endl;

                                pExternalChapter->Release();
                                pExternalChapter = NULL ;
                             }
                             pIPointedDesc->Release();
                             pIPointedDesc = NULL ;
                         }
                      }
                   }  
                   pReferencedObject->Release();
                   pReferencedObject = NULL ;
                }
            }
        }
      }
      delete pListDescription ;
      pListDescription = NULL ;
    }

    if ( NULL != pListKeyword )
    {
       delete pListKeyword ;
       pListKeyword = NULL ;
    }

    return rc ;
}
