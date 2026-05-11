#ifndef CAASysSprocketsImpl_h
#define CAASysSprocketsImpl_h

// COPYRIGHT DASSAULT SYSTEMES 2002

#include "CATBaseCollection.h"
#include "CATVariant.h"
#include "CATSafeArray.h"
#include "CATListOfCAAIASysSprocket.h"
class CAAIASysSprockets;
class CAAIASysSprocket;

/**
 * Implementation of the CAAIASysSprockets interface
 */
class CAASysSprocketsImpl : public CATBaseCollection {
  public:
    CATDeclareClass;

    /**
     * Destructor.
     */
    virtual ~CAASysSprocketsImpl();


    /**
     * Instantiates a new CAASysSprocketsImpl.
     */
    static HRESULT __stdcall CreateSprockets(
      CAAIASysSprockets*& oCAAIASysSprockets);

    // Partial implementation of the CATIACollection interface
    virtual HRESULT __stdcall get_Name(
      CATBSTR & oNameBSTR);
    virtual HRESULT __stdcall get__NewEnum(
      IUnknown *& oEnumerator);
    virtual HRESULT __stdcall get_Count(
      CATLONG & oCount);

    // Implementation of the CAAIASysSprockets interface
    virtual HRESULT __stdcall Item(
      const CATVariant & iIndex, 
      CAAIASysSprocket *& oSprocket);
    virtual HRESULT __stdcall AddAll(
      const CATSafeArrayVariant & iSprocketArray);
    virtual HRESULT __stdcall ToArray(
      CATSafeArrayVariant & ioArray);

  private:
    /**
     * Constructor.
     */
    CAASysSprocketsImpl();

  private:
    /**
     * A list in which the CAAIASysSprockets are stored internally.
     */
    CATListOfCAAIASysSprocket _sprockets;
};

#endif // CAASysSprocketsImpl_h
