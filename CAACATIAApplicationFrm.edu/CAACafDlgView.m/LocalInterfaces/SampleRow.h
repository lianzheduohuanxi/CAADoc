// COPYRIGHT DASSAULT SYSTEMES 2007
#ifndef SampleRow_H
#define SampleRow_H

#include "CATBaseUnknown.h"  
#include "CATUnicodeString.h"  
#include "CATListOfCATUnicodeString.h"  

class SampleRow : public CATBaseUnknown
{
  CATDeclareClass; //allow to call IsAKindOf( SampleRow::ClassName() )

  public:
    // Contructs the document from an application and a title.
    SampleRow(int id);

    //destructor
    virtual ~SampleRow();

    void SetDatas(const CATListOfCATUnicodeString &idatas);
    void ClearDatas();

    int Size();

    int _id;
    CATListOfCATUnicodeString _datas;

  private:
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    SampleRow();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    SampleRow(const SampleRow &iObjectToCopy);
};
#endif
