// COPYRIGHT DASSAULT SYSTEMES 2003

#ifndef CAAAfrEltCountRep_h
#define CAAAfrEltCountRep_h

//===========================================================================
//  Abstract of the class:
//  ----------------------
//  This class is the representation ( a CATCommand ) of the 
//  CAAAfrEltCountHeader in the tool bar.
//
//===========================================================================

// CAASystem.edu Framework
class CAAISysCollection ;

// System Framework
#include "CATAfrCommandHeaderRep.h" // to derive from 
class CATString ;

// Dialog Framework
class CATDialog ;
class CATDlgEditor ;

class CAAAfrEltCountRep : public CATAfrCommandHeaderRep
{

public:
  
  // Constructor
  // -----------
  // iParent kept by the CAAAfrHeaderRep class instance will be
  // the dialog object parent of CATDlgEltCount created by 
  // this class.
  //
  CAAAfrEltCountRep(const CATDialog * iParent, CATString & iCommandName);

  // Destructor
  // ----------
  // The CATDlgEltCount instance created in this class instance must
  // be released.
  //
  virtual ~CAAAfrEltCountRep();

  // Build
  // -----
  // This method  creates the CATDlgEltCount instance 
  // and calls SetCurrentColor to set the current 
  // selected color
  //
  HRESULT Build();

private:

  // ModifiedCB
  // ----------
  // Callback method when the  sends a
  // notification when its list of items is modified.
  // 
  void ModifiedCB(CATCallbackEvent       iEvent, 
                  void            *       , 
                  CATNotification * iNotification, 
                  CATSubscriberData  iData,
		              CATCallback iCallBack);

  // ValuateEditors
  // ---------------
  // This method queries the UIActive object to know the
  // 
  //
  HRESULT ValuateEditors() ;

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAAfrEltCountRep(const CAAAfrEltCountRep &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAAfrEltCountRep & operator = (const CAAAfrEltCountRep &iObjectToCopy);

private:

     // The CATDlgEditor instances created by the Build method
     CATDlgEditor    * _pEdtPoint;
     CATDlgEditor    * _pEdtLine;

     // Object which sends the event when the document is empty or 
     // when the first element is created. 
     CAAISysCollection *      _piSysCollection ;
};

#endif
