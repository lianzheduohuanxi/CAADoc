// COPYRIGHT DASSAULT SYSTEMES 2007
#ifndef SampleCell_H
#define SampleCell_H

#include "CATBaseUnknown.h"
#include "CATString.h"

class SampleCell : public CATBaseUnknown
{
  CATDeclareClass; //allow to call IsAKindOf( SampleCell::ClassName() )

  public:
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    SampleCell();

    // Contructs the document from an application and a title.
    SampleCell(CATBaseUnknown_var iRow, const CATString &iCol);

    //destructor
    virtual ~SampleCell();

    //Compare operator
    int operator==(const SampleCell &iObjectToCompare) const;
    int operator!=(const SampleCell &iObjectToCompare) const;

    CATBaseUnknown_var &GetRow();
    CATString &GetColumn();

    CATBaseUnknown_var _iRow;
    CATString _iCol;
};
#endif
