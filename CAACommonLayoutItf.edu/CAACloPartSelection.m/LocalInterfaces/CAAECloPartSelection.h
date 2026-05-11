#ifndef CAAECloPartSelection_H
#define CAAECloPartSelection_H

#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"
#include "CATECloPartSelectionAdapter.h"

class CATIUnknownList;
class CATListValCATUnicodeString;

//-----------------------------------------------------------------------

/**
 * Interface to calculate the weld offset 
 */
class CAAECloPartSelection: public CATECloPartSelectionAdapter
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors
  // -------------------------------------
     CAAECloPartSelection ();
     virtual ~CAAECloPartSelection ();


    /**
  * Interrupt the part place process before catalog part selection and override or modify the selection process.
  * 
  * @param iuStandard 
  *   input: The standard  
  * @param iuSpec
  *   input: The material specification ( NULL is non-spec)
  * @param iuPartType
  *   input: part type of the parts 
  * @param iLFilterParameters
  *   input: The list of parameters used in the search. (this could be all the parameters used, 
  *          or only the ones that actually match keywords.)
  * @param iLSortParameters
  *   input: A list of parameters used to sort the results of the search. 
  *          The list is sort by descriptions that best match parameters in this list.
  *          (this could be all the parameters used, or only the ones that actually match keywords.)
  * @param iListDescription
  *   input: list of the catalog descriptions available for selection
  * @param iLParameters
  *   input: list of paramaters used by part placement
  * @param oListDescription
  *   output: list of catalog descriptions to be displayed for user selection
  * @return
  *   A boolean value.
  *   <br><b>Legal values</b>:
  *   <dl>
  *     <dt>SUCCEEDED</dt>
  *     <dt>FAILED</dt>
  *   </dl>
  */
  virtual HRESULT FilterPartSelection (  
                                            const CATUnicodeString& iuStandard,
                                            const CATUnicodeString& iuSpec,
                                            const CATUnicodeString& iuPartType,
                                            const CATIUnknownList *iLFilterParameters,
                                            const CATIUnknownList *iLSortParameters,
                                            const CATIUnknownList *iListDescription,
                                            CATIUnknownList*& oListDescription);

   /**
    * Method called by part placement UI to determine if a call to RefinePartSelection is needed.
    * 
    * @param iuApplicationContext 
    *   input: The application currently being used (e.g. CATPiping, CATTubing)  
    * @param iuStandard 
    *   input: The standard  
    * @param iuSpec
    *   input: The material specification ( NULL is non-spec)
    * @param iuPartType
    *   input: part type of the parts 
    * @param oiActivate
    *   output: flag to determine external program use. 1: Activate external program. 0: Do not activate.
    * @return
    *   A boolean value.
    *   <br><b>Legal values</b>:
    *   <dl>
    *     <dt>SUCCEEDED</dt>
    *     <dt>FAILED</dt>
    *   </dl>
    */

    virtual HRESULT IsExternalProgramNeeded  ( 
                                          const CATUnicodeString &iuApplicationContext,
                                          const CATUnicodeString &iuStandard,
                                          const CATUnicodeString &iuSpec,
                                          const CATUnicodeString &iuPartType,
                                          int &oiActivate
                                          );

   /**
    * Provide an supplemental part selection available from the part placement panel after the part placement engine selection has taken place.
    * 
    * @param iuApplicationContext 
    *   input: The application currently being used (e.g. CATPiping, CATTubing)  
    * @param iuStandard 
    *   input: The standard  
    * @param iuSpec
    *   input: The material specification ( NULL is non-spec)
    * @param iuPartType
    *   input: part type of the parts 
    * @param iLEnvironmentParameters
    *   input: A list of parameters from by the parent product under which the part will be placed. 
    * @param iLFilterParameters
    *   input: The list of parameters used in the search. (this could be all the parameters used, 
    *          or only the ones that actually match keywords.)
    * @param iLSortParameters
    *   input: A list of parameters used to sort the results of the search. 
    *          The list is sort by descriptions that best match parameters in this list.
    *          (this could be all the parameters used, or only the ones that actually match keywords.)
    * @param iListDescription
    *   input: list of the catalog descriptions available for selection
    * @param iPartChapter
    *   input: chapter that the part placement engine searched.
    * @param opListPartNumbersFound
    *   output: list of part numbers found by this method.
    * @return
    *   A boolean value.
    *   <br><b>Legal values</b>:
    *   <dl>
    *     <dt>SUCCEEDED</dt>
    *     <dt>FAILED</dt>
    *   </dl>
    */

    virtual HRESULT RefinePartSelection ( 
                                          const CATUnicodeString &iuApplicationContext,
                                          const CATUnicodeString &iuStandard,
                                          const CATUnicodeString &iuSpec,
                                          const CATUnicodeString &iuPartType,
                                          const CATIUnknownList *iLEnvironmentParameters,
                                          const CATIUnknownList *iLFilterParameters,
                                          const CATIUnknownList *iLSortParameters,
                                          const IUnknown *ipiCatalogObjectToBeSearched,
                                          CATListValCATUnicodeString &opListPartNumbersFound 
                                          );

};

//-----------------------------------------------------------------------

#endif
