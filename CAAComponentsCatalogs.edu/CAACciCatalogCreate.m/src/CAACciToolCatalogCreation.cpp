// COPYRIGHT DASSAULT SYSTEMES  2002
//
//   Abstract: This function illustrates how to use the interface of 
//             ComponentsCatalogInterfaces framework to create a catalog.
//             
//             It creates the CAATool.catalog document which contains
//             the following caracteristics:
//             
//             About chapters:
//                - Chapter and sub chapter 
//                - External chapter, it means that the chapter
//                  linked with a chapter comes from an another catalog 
//                - External Family, it means that the family
//                  linked with a chapter comes from an another catalog                
//            
//             About components: (contents of the family's descriptions)
//                - The components are Part documents with or without  
//                  design table (DT) 
//                - Permanent query as used to define components
//                - resolved and unresolved Part with DT
//
//             About Keywords:
//                - There are keywords with or without default value
//                - keyword are valuated 
//                - a keyword is invisible (for the catalog browser)
//                - different kind of keyword (string, integer, length)
//
//             The structure of the CAATool catalog is the following:
//
//             Tools (Root chapter) 
//                Screws ( External chapter from CAAScrew.catalog )
//                Nuts (chapter)
//                   Nuts6SidesFamily (External family from CAANuts6Sides.catalog)
//                   Nuts4SidesFamily (Family)
//                NutsWithFixedSizeHole ( chapter) 
//                   Nuts6SidesHole10Family (Family)
//             
//   Steps :
//    1-  Creating the new document 
//    2-  Filling the document
//
//      2-1 Creating the Tools chapter, the root chapter
//        2-1-1 Creating the chapter
//        2-1-2 Creating the ToolType and Suppliers keywords
//        2-1-3 Setting default value for the Suppliers keyword
//
//      2-2 Retrieving the Screws chapter from the CAAScrew catalog
//        2-2-1 Retrieving the chapter
//        2-2-2 Associating the Screws chapter to the Tools chapter
//        2-2-3 Associating a value to the ToolType keyword
//
//      2-3 Creating the Nuts chapter 
//        2-3-1 Creating the chapter
//        2-3-2 Associating the Nuts chapter to the Tools chapter
//        2-3-3 Associating a value to the ToolType keyword
//        2-3-4 Creating the SideNumber keyword
//
//      2-4 Retrieving the Nuts6SidesFamily end chapter in the CAANuts6Sides catalog 
//        2-4-1 Retrieving the end chapter
//        2-4-2 Associating the Nuts6SidesFamily to the Nuts chapter
//        2-4-3 Associating a value to the SideNumber keyword
//
//      2-5 Creating the Nuts4SidesFamily end chapter 
//        2-5-1 Creating the chapter
//        2-5-2 Associating the Nuts4SidesFamily chapter to the Nuts chapter
//        2-5-3 Associating a value to the SideNumber keyword
//        2-5-4 Adding the CAANuts4Sides Part document which contains a DT 
//
//      2-6 Creating the NutsWithFixedSizeHole chapter
//        2-6-1 Creating the chapter
//        2-6-2 Associating the NutsWithFixedSizeHole chapter to the
//               Tools chapter
//        2-6-3 Associating a value to the ToolType keyword
//
//      2-7 Creating the Nuts6SidesHole10Family end chapter
//        2-7-1 Creating the chapter
//        2-7-2 Associating the Nuts6SidesHole10Family chapter to the 
//               NutsWithFixedSizeHole chapter
//        2-7-3 Creating keyword 
//        2-7-4 Adding persistent query
//        2-7-5 Verifying the descriptions of the Nuts6SidesHole10Family
//
//      2-8 Releasing the pointers
//
//    3-  Saving and closing the document
//
//==========================================================================
// Local Framework
#include "CAACciCatalogDocumentServices.h" // To create, save the new catalog document

// ObjectModelerBase
#include "CATDocumentServices.h"         // Open document
#include "CATDocument.h"

// ComponentsCatalogsInterfaces
#include "CATICatalogChapterFactory.h"
#include "CATICatalogChapter.h"
#include "CATICatalogKeyword.h" 
#include "CATICatalogDescription.h"
#include "CATICatalogPersistentQuery.h"
#include "CATICatalogQueryResult.h"
#include "CATListValCATICatalogDescription_var.h"

// ObjectSpecsModeler
#include "CATLISTV_CATISpecObject.h"

//LiteralFeatures
#include "CATIDesignTable.h"

// System 
#include "CATUnicodeString.h"

// Standard C++ library
#include <iostream.h>

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif

HRESULT CAAToolCatalogCreation(CATUnicodeString & iInputPath, CATUnicodeString & iOutputPath) 
{
    HRESULT rc = E_FAIL ;

    cout <<"Beginning of the CAATool.catalog creation" << endl;

    // ----------------------------------
    // 1- Creating a new catalog document
    // ----------------------------------
    CATDocument * pDocument = NULL ;
    CATICatalogChapterFactory * pICatalogChapterFactory = NULL ;

    rc = ::CAACreateCatalogDocument(&pDocument,&pICatalogChapterFactory);

    // ------------------------
    // 2- Filling the document
    // ------------------------
    if ( SUCCEEDED(rc) && ( NULL != pICatalogChapterFactory) )
    {        
       // 2-1 Creating the Tools chapter, the root chapter
       // ----------------------------------------------------
       CATICatalogChapter * piToolChapter = NULL ;

       // 2-1-1 Creating the chapter
       CATUnicodeString ChapterName = "Tools" ;
       CATBoolean IsEndChapter = FALSE ;
       rc = pICatalogChapterFactory->CreateChapter(ChapterName,IsEndChapter,piToolChapter);
       if ( SUCCEEDED(rc) )
       {    
          cout <<"   The Tools chapter has been created" << endl;
       }

       // 2-1-2 Creating the ToolType and Suppliers keywords 
       if ( SUCCEEDED(rc) && (NULL != piToolChapter))
       {
          CATICatalogKeyword * piKeyword = NULL ;
          rc = piToolChapter->AddKeyword("ToolType","String",piKeyword);
          if ( SUCCEEDED(rc) )
          {
             piKeyword->Release();
             piKeyword = NULL ;
          }   
          if ( SUCCEEDED(rc) )
          {
             rc = piToolChapter->AddKeyword("Suppliers","String",piKeyword);
             if ( SUCCEEDED(rc) )
             {
                // Suppliers keyword will be invisible in the 
                // catalog browser
                piKeyword->SetHidden(TRUE);  
                piKeyword->Release();
                piKeyword = NULL ;
             }
          }
       }

       // 2-1-3 Setting default value for the Suppliers keyword
       if ( SUCCEEDED(rc) && (NULL != piToolChapter))
       {
          CATUnicodeString Value = "MySupplierA" ;
          rc = piToolChapter->SetDefaultValue("Suppliers",Value);
       }

       // 2-2 Retrieving the Screws chapter from the CAAScrew catalog
       // -----------------------------------------------------------
       if ( SUCCEEDED(rc) && (NULL !=piToolChapter) )
       {

          // 2-2-1 Retrieving the chapter
          CATILinkableObject * piLinkOnChapter = NULL ;
          CATUnicodeString ChapterName = "Screws";
          CATUnicodeString DocumentName = "CAAScrew" ;
          rc = ::CAAFindChapterInCatalog(DocumentName,iOutputPath,ChapterName,IID_CATILinkableObject,
                                              (void**)&piLinkOnChapter);

          // 2-2-2 Associating the Screws chapter to the Tools chapter
          if ( SUCCEEDED(rc) )
          {
             CATICatalogDescription * piDescription = NULL ;
             rc = piToolChapter->AddDescription(piDescription,piLinkOnChapter);
             if ( SUCCEEDED(rc) && ( NULL != piDescription) )
             {
                cout <<"      The Screws chapter has been created" << endl;   

                 // 2-2-3 Associating a value to the ToolType keyword
                rc = piDescription->SetValue("ToolType","Screws");

                piDescription->Release();
                piDescription = NULL ;
             } 

             piLinkOnChapter->Release();
             piLinkOnChapter = NULL ;                    
           }
       }

       // 2-3 Creating the Nuts chapter 
       // ----------------------------- 
       CATICatalogChapter * piNutsChapter = NULL ;

       // 2-3-1 Creating the chapter
       if ( SUCCEEDED(rc) )
       {
          CATUnicodeString ChapterName = "Nuts" ;
          CATBoolean IsEndChapter = FALSE ;

          rc = pICatalogChapterFactory->CreateChapter(ChapterName,IsEndChapter,piNutsChapter);
          if ( SUCCEEDED(rc) )
          {
             cout <<"      The Nuts chapter has been created" << endl;
          }
       }

       // 2-3-2 Associating the Nuts chapter to the Tools chapter
       if (SUCCEEDED(rc) && (NULL != piNutsChapter) && (NULL != piToolChapter) )
       {                  
          CATILinkableObject * pLinkOnChapter = NULL ;
          rc = piNutsChapter->QueryInterface(IID_CATILinkableObject,
                                              (void **) &pLinkOnChapter);     
          if ( SUCCEEDED(rc) )
          {
             CATICatalogDescription * piDescription = NULL ;
             rc = piToolChapter->AddDescription(piDescription,pLinkOnChapter);
             if ( SUCCEEDED(rc) && (NULL != piDescription) )
             {
                // 2-3-3 Associating a value to the ToolType keyword
                rc = piDescription->SetValue("ToolType","Nuts");

                piDescription->Release();
                piDescription = NULL ;
             }

             pLinkOnChapter->Release();
             pLinkOnChapter = NULL ;
          }
       }

       // 2-3-4 Creating the SideNumber keyword
       if ( SUCCEEDED(rc) && (NULL != piNutsChapter) )
       {                  
          CATICatalogKeyword * piKeyword = NULL ;
          rc = piNutsChapter->AddKeyword("SideNumber","Integer",piKeyword);
          if ( SUCCEEDED(rc) )
          {
             piKeyword->Release();
             piKeyword = NULL ;
          }
       }

       // 2-4 Retrieving the Nuts6SidesFamily end chapter (family) in the 
       //     CAANuts6Sides catalog
       // ------------------------------------------------------
        if ( SUCCEEDED(rc) && (NULL != piNutsChapter))
        {
           // 2-4-1 Retrieving the family
           CATILinkableObject * piLinkOnChapter = NULL ;
           CATUnicodeString ChapterName = "Nuts6SidesFamily";
           CATUnicodeString DocumentName = "CAANuts6Sides";
           rc = ::CAAFindChapterInCatalog(DocumentName,iOutputPath,
                                       ChapterName,IID_CATILinkableObject, 
                                           (void**) &piLinkOnChapter);
        
           // 2-4-2 Associating the Nuts6SidesFamily to the Nuts chapter
           if ( SUCCEEDED(rc) )
           {
              CATICatalogDescription * piDescription = NULL ;
              rc = piNutsChapter->AddDescription(piDescription,piLinkOnChapter);
              if ( SUCCEEDED(rc) && (NULL != piDescription) )
              {
                 cout <<"         The Nuts6SidesFamily end chapter has been created" << endl;   
                 
                 // 2-4-3 Associating a value to the SideNumber keyword
                 rc = piDescription->SetValue("SideNumber","6");
                 piDescription->Release();
                 piDescription = NULL ;
              }

              piLinkOnChapter->Release();
              piLinkOnChapter = NULL ;
           }
        }

       // 2-5 Creating the Nuts4SidesFamily end chapter 
       // ----------------------------------------------
       CATICatalogChapter * piNuts4SidesFamily = NULL ;

       // 2-5-1 Creating the chapter
       if ( SUCCEEDED(rc) )
       {
          CATUnicodeString     ChapterName = "Nuts4SidesFamily" ;
          CATBoolean           IsEndChapter = TRUE ;
          rc = pICatalogChapterFactory->CreateChapter(ChapterName,IsEndChapter,piNuts4SidesFamily);

          if ( SUCCEEDED(rc) )
          {
             cout <<"      The Nuts4SidesFamily end chapter has been created" << endl;
          }
       }

       // 2-5-2 Associating the Nuts4SidesFamily chapter to the Nuts chapter
       if ( SUCCEEDED(rc) && (NULL != piNuts4SidesFamily) && (NULL != piNutsChapter) )
       {                    
          CATILinkableObject * pLinkOnFamily = NULL ;
          rc = piNuts4SidesFamily->QueryInterface(IID_CATILinkableObject,
                                              (void **) &pLinkOnFamily);     
          if ( SUCCEEDED(rc) )
          {
             CATICatalogDescription * piDescription = NULL ;
             rc = piNutsChapter->AddDescription(piDescription, pLinkOnFamily);
             if ( SUCCEEDED(rc) && (NULL != piDescription) )
             {
                // 2-5-3 Associating a value to the SideNumber keyword
                rc = piDescription->SetValue("SideNumber","4");

                piDescription->Release();
                piDescription = NULL ;
             }

             pLinkOnFamily->Release();
             pLinkOnFamily = NULL ;
          }
       }

       // 2-5-4 Adding the CAANuts4Sides Part document which contains a DT  
       if ( SUCCEEDED(rc) && (NULL != piNuts4SidesFamily) )
       {
          CATDocument * pCAANuts4SidesDocument = NULL ;
            
          CATUnicodeString ModelDocName = "CAANuts4Sides.CATPart" ;
          ModelDocName = iInputPath + Slash + "CAANuts4Sides.CATPart" ;

          CATIDesignTable * pDesignTable = NULL ;
          rc = ::CAARetrieveDTInPartDocument(ModelDocName,&pDesignTable);
 
          if ( SUCCEEDED(rc) )
          {
             piNuts4SidesFamily->AddFamilyDescriptionsFromDesignTable(pDesignTable);

             pDesignTable->Release();
             pDesignTable= NULL ;
          }

       }

       // 2-6 Creating the NutsWithFixedSizeHole chapter
       // ----------------------------------------------
       CATICatalogChapter * piNutsWithFixedSizeHoleChapter = NULL ;

       // 2-6-1 Creating the chapter
       if ( SUCCEEDED(rc) )
       { 
          CATUnicodeString ChapterName = "NutsWithFixedSizeHole" ;
          CATBoolean IsEndChapter = FALSE ;
          rc = pICatalogChapterFactory->CreateChapter(ChapterName,IsEndChapter,piNutsWithFixedSizeHoleChapter);
          if ( SUCCEEDED(rc) )
          {
             cout <<"      The NutsWithFixedSizeHole chapter has been created" << endl;
          }
       }

       // 2-6-2 Associating the NutsWithFixedSizeHole chapter to the
       //       Tools chapter
       if ( SUCCEEDED(rc) && ( NULL != piToolChapter) )
       {
          CATILinkableObject * pLinkOnChapter = NULL ;
          rc = piNutsWithFixedSizeHoleChapter->QueryInterface(IID_CATILinkableObject,
                                              (void **) &pLinkOnChapter);     
          if ( SUCCEEDED(rc) )
          {
             CATICatalogDescription * piDescription = NULL ;
             rc = piToolChapter->AddDescription(piDescription,pLinkOnChapter);
             if ( SUCCEEDED(rc) && (NULL != piDescription) )
             {  
                // 2-6-3 Associating a value to the ToolType keyword
                rc = piDescription->SetValue("ToolType","Nuts");

                piDescription->Release();
                piDescription = NULL ;
             }

             pLinkOnChapter->Release();
             pLinkOnChapter = NULL ;
          }
       }

       // 2-7 Creating the piNuts6SidesHole10Family end chapter
       // -----------------------------------------------------
       CATICatalogChapter * piNuts6SidesHole10Family = NULL ;  
       
       // 2-7-1 Creating the chapter
       if ( SUCCEEDED(rc) )
       {
          CATUnicodeString     ChapterName = "Nuts6SidesHole10Family" ;
          CATBoolean           IsEndChapter = TRUE ;
          rc = pICatalogChapterFactory->CreateChapter(ChapterName,IsEndChapter,piNuts6SidesHole10Family);

          if ( SUCCEEDED(rc) )
          {
             cout <<"         The Nuts6SidesHole10Family end chapter has been created" << endl;
          }
       }

       // 2-7-2 Associating the new chapter (Nuts6SidesHole10Family) to its 
       //       parent chapter (NutsWithFixedSizeHole)
       //
       if ( SUCCEEDED(rc) && (NULL !=piNuts6SidesHole10Family) 
             && (NULL != piNutsWithFixedSizeHoleChapter) )
       {
          CATILinkableObject * pLinkOnFamily = NULL ;
          rc = piNuts6SidesHole10Family->QueryInterface(IID_CATILinkableObject,
                                              (void **) &pLinkOnFamily);     
          if ( SUCCEEDED(rc) )
          {
             CATICatalogDescription * piDescription = NULL ;
             rc = piNutsWithFixedSizeHoleChapter->AddDescription(piDescription,pLinkOnFamily);     
             if (SUCCEEDED(rc) && (NULL != piDescription) )
             {
                piDescription->Release();
                piDescription = NULL ;
             } 

             pLinkOnFamily->Release();
             pLinkOnFamily = NULL ;
          }
       }

       //2-7-3 Creating keyword 
       //
       CATUnicodeString KWFirstLimit= "PartBody\\Pad.1\\FirstLimit\\Length" ;
       CATUnicodeString KWDiameter= "PartBody\\Hole.1\\Diameter" ;

       CATUnicodeString KWName= "Name" ;

       if ( SUCCEEDED(rc) && (NULL!= piNuts6SidesHole10Family) )
       {
           
          // This keyword is the same as the 
          CATICatalogKeyword * piKeyword = NULL ;
          CATUnicodeString  TypeKW = "String" ;
          rc = piNuts6SidesHole10Family->AddKeyword(KWName,TypeKW,piKeyword);
                                                                               
          if ( SUCCEEDED(rc) )
          {
             piKeyword->Release();
             piKeyword = NULL ;
          } 

       }

       //2-7-4 Adding persistent query  
       //
       if ( SUCCEEDED(rc) && (NULL != piNuts6SidesHole10Family) )
       {
          CATUnicodeString QueryPersistentName ="QueryOn6Sides";
          CATICatalogPersistentQuery * piPersistentQuery = NULL ;
          rc = piNuts6SidesHole10Family->AddPersistentQuery(QueryPersistentName,piPersistentQuery);
          if ( SUCCEEDED(rc) && ( NULL != piPersistentQuery) )
          {
             // a/ Retrieving the root chapter of the CAANuts6Sides catalog
             // Note: A persistent query is always done on a root chapter
             // of a catalog.
             CATICatalogChapter * piChapter = NULL ;
             CATUnicodeString ChapterName = "Nuts6Sides";
             CATUnicodeString DocumentName ="CAANuts6Sides";
             rc = ::CAAFindChapterInCatalog(DocumentName,iOutputPath,ChapterName,
                                         IID_CATICatalogChapter, (void**) &piChapter);
             
             if ( SUCCEEDED(rc) )
             {
                // b/ Associating the root chapter to the current query
                rc = piPersistentQuery->SetResolutionChapter(piChapter);
                if ( SUCCEEDED(rc) )
                {
                   // c/ Creating the expression
                   //
                   CATUnicodeString KW = "\"PartBody\\Hole.1\\Diameter\"";

                   CATUnicodeString Expression ="(x." + KW  + "==10mm)" ;
                  
                   // d/ associating the expression to the persistent query
                   rc = piPersistentQuery->SetExpression(Expression) ; 
                   
                   if ( SUCCEEDED(rc) )
                   {
                       CATICatalogQueryResult * pICatalogQueryResult = NULL ;
                       rc = piPersistentQuery->GetGeneratedQueryResult(pICatalogQueryResult) ;
                       if ( SUCCEEDED(rc) )
                       {
                          if ( pICatalogQueryResult->Size() != 0 )
                          {
                              // The list must be empty
                              rc = E_FAIL ;
                          }
                          pICatalogQueryResult->Release();
                          pICatalogQueryResult = NULL ;                         
                       }

                       CATListValCATICatalogDescription_var * pListExternalDescription  = NULL ;
                       if ( SUCCEEDED(rc) )
                       {
                          // e/ Resolving the query- The descriptions will be saved
                          // in the document
                          //
                          int ResolveMode = 1 ; // ( 1: resolution, 0: simulation)
                          
                          rc = piPersistentQuery->ResolveQuery(ResolveMode,
                                                            pListExternalDescription );

                       }
                       // f/ Displaying the result
                       // Caution: The descriptions returned by the ResolveQuery 
                       // method are descriptions pointing on the another document
                       // So the keywords associated with these descriptions are not
                       // the keywords of the piNuts6SidesHole10Family family
                       // 
                       if ( SUCCEEDED(rc) && ( NULL != pListExternalDescription ) )
                       {
                           int SizeList = pListExternalDescription ->Size();

                           cout <<"            Number of description by the " ;
                           cout << QueryPersistentName.CastToCharPtr() ;
                           cout <<" persistent query= " << SizeList << " :" << endl;
                           
                           int i = 1 ;
                           while ( SUCCEEDED(rc)  && (i <=SizeList) )
                           {
                              CATICatalogDescription_var spDesc = (*pListExternalDescription )[i] ;
                              if ( NULL_var != spDesc )
                              {
                                  CATUnicodeString DescriptionName ;
                                  rc = spDesc->GetName(DescriptionName);
                                  if ( SUCCEEDED(rc) )
                                  {
                                      cout <<"            " << DescriptionName.CastToCharPtr() << endl;
                                      
                                      CATUnicodeString KeywordValue ;
                                      rc = spDesc->GetValue(KWFirstLimit,KeywordValue) ;
                                      if ( rc == S_OK)
                                      {
                                          cout <<"            First Limit value=" << KeywordValue.CastToCharPtr() << endl;
                                      }
                                      rc = spDesc->GetValue(KWDiameter,KeywordValue);
                                      if ( rc == S_OK)
                                      {
                                          cout <<"            Diameter value=" << KeywordValue.CastToCharPtr() << endl;
                                      }
                                      rc = spDesc->GetString("Name", KeywordValue);
                                      if ( rc == S_OK)
                                      {
                                         cout <<" Error the Name keyword is not a keyword" << endl;
                                         rc = E_FAIL ;
                                      }else rc = S_OK ;
                                  }
                              }else rc = E_FAIL ;
                              i++ ;
                           }
                       }
                       if ( NULL != pListExternalDescription  )
                       {
                           delete pListExternalDescription  ;
                           pListExternalDescription  = NULL ;
                       }

                       if ( SUCCEEDED(rc) )
                       {
                          rc = piPersistentQuery->GetGeneratedQueryResult(pICatalogQueryResult) ;
                          if ( SUCCEEDED(rc) )
                          {
                             cout <<"            mode=" << pICatalogQueryResult->GetQueryMode() << endl;
                             if ( 1 == pICatalogQueryResult->GetQueryMode() )
                             {
                                cout <<"            size=" << pICatalogQueryResult->Size() << endl;
                                if ( pICatalogQueryResult->Size() != 2 )
                                {
                                   cout <<" Error the nb description is wrong" << endl;
                                   rc = E_FAIL ;
                                }
                             }else 
                             {
                                 rc = E_FAIL ;
                                 cout <<" The mode must be 1 " << endl;
                             }

                             pICatalogQueryResult->Release();
                             pICatalogQueryResult = NULL ;
                          }
                       }

                   }else cout <<"Error in creating the permanent query" << endl;
                }
                // g/ Releasing the external chapter used for the persistent query
                piChapter->Release();
                piChapter = NULL ;
             }
             piPersistentQuery->Release();
             piPersistentQuery = NULL ;
          }
       }
       //2-7-5 Verifying the descriptions on the Family 
       //
       if ( SUCCEEDED(rc) && (NULL != piNuts6SidesHole10Family) )
       {
           CATListValCATICatalogDescription_var * pListDescription = NULL;
           rc = piNuts6SidesHole10Family->ListDescriptions (pListDescription) ;
           if (SUCCEEDED(rc) && (NULL != pListDescription) )
           {
              cout <<"            Keyword's value for each description of the family:"<<endl;
              int NbDescriptions = pListDescription->Size() ;
              int i=1 ; 
              while ( SUCCEEDED(rc) && ( i <= NbDescriptions) )
              {
                 CATICatalogDescription_var spDesc = (*pListDescription)[i] ;
                 if ( NULL_var != spDesc )
                 {
                   CATUnicodeString KeywordValue;
                   rc = spDesc->GetValue(KWFirstLimit,KeywordValue) ;
                   if ( rc == S_OK)
                   {
                      cout <<" Error the Name keyword is not a keyword" << endl;
                      rc = E_FAIL ;
                   }else rc = S_OK ;

                   rc = spDesc->GetString("Name", KeywordValue);
                   if ( rc == S_OK)
                   {
                      cout <<"            Name value=" << KeywordValue.CastToCharPtr() << endl;
                   }
                 }else rc = E_FAIL ;
                 i++ ;
              }
           }

           if ( NULL != pListDescription)
           {
               delete pListDescription;
               pListDescription=NULL;
           }
       }

       // 2-8 Releasing the pointers
       // --------------------------  
       if ( NULL != piNuts4SidesFamily )
       {
           piNuts4SidesFamily->Release();
           piNuts4SidesFamily = NULL ;
       }

       if ( NULL != piNuts6SidesHole10Family )
       {
          piNuts6SidesHole10Family->Release();
          piNuts6SidesHole10Family = NULL ;
       }
       if ( NULL != piNutsWithFixedSizeHoleChapter )
       {
          piNutsWithFixedSizeHoleChapter->Release();
          piNutsWithFixedSizeHoleChapter = NULL ;
       }
       if ( NULL != piNutsChapter )
       {     
          piNutsChapter->Release();
          piNutsChapter = NULL ;
       }
       if ( NULL != piToolChapter )
       {
          piToolChapter->Release();
          piToolChapter = NULL ;
       }

       pICatalogChapterFactory->Release();
       pICatalogChapterFactory = NULL ;
    }

    // ----------------------------------
    // 3- Saving and closing the document
    // ----------------------------------
    if ( SUCCEEDED(rc) && (NULL != pDocument) )
    {
       CATUnicodeString DocumentName = "CAATool" ;
       rc = ::CAACloseCatalogDocument(DocumentName,*pDocument,iOutputPath);
       pDocument = NULL ;
    }

    cout <<"Ending of the CAATool.catalog creation" << endl << endl;

    return rc ;
}
