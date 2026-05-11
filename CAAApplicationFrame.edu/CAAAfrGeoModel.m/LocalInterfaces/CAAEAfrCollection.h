#ifndef CAAEAfrCollection_H
#define CAAEAfrCollection_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CAAISysCollection interface which enables
//  to manages the list of objects of the container in the CAAGeometry Document. 
//  So this extension extens the container.
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  GetNumberOfObjects
//  GetObject
//  AddObject
//  RemoveObject
//
//===========================================================================
// System framework
#include "CATBaseUnknown.h"
#include "CATCollec.h"

// ApplicationFrame framework
class CATLISTP(CATBaseUnknown);

class CAAEAfrCollection : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public :

    CAAEAfrCollection();
    virtual ~CAAEAfrCollection();

    // GetNumberOfObjects
    // -------------------
    // Retrieves the number of object in the Collection.
    // Return E_FAIL if the Collection is empty else S_OK
    //
    virtual HRESULT GetNumberOfObjects(int * oCount);

    // GetObject
    // --------- 
    // Retrieves the iRank object in this Collection.
    // Return E_FAIL if the Collection is iRank is bad else S_OK
    //
    virtual HRESULT GetObject    (int                  iRank,
                                  CATBaseUnknown    ** oObject);
    // AddObject
    // ---------
    // Adds iObject in the Collection, sets link for the display,
    // sets link with the object which has created it (this) and
    // send a notification to prevent that the model contains 
    // somethings
    //
    virtual HRESULT AddObject    (CATBaseUnknown     * iObject);

    // RemoveObject
    // ------------
    // Removes iObject in the Collection, unsets link for the display,
    // unsets link with the object which has created it (this) and
    // send a notification to prevent that the model becomes empty 
    //
    virtual HRESULT RemoveObject (CATBaseUnknown     * iObject);

    // RemoveObject
    // ------------
    // Empties the Collection, unsets link for the display,
    // unsets link with the object which has created it (this)
    //
    virtual HRESULT Empty();

  private :
  
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrCollection(const CAAEAfrCollection &iObjectToCopy);
  
    // Assigment opeartor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrCollection & operator = (const CAAEAfrCollection &iObjectToCopy);
  
  private :

    CATLISTP(CATBaseUnknown) * _pListe;
};

#endif
