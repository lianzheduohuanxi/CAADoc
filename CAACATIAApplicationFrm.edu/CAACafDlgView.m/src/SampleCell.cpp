// COPYRIGHT DASSAULT SYSTEMES 2007

#include "SampleCell.h" 

CATImplementClass(SampleCell, Implementation, CATBaseUnknown, CATNull); 

SampleCell::SampleCell():_iRow(NULL_var), _iCol("")
{
}

//-------------------------------------------------------------------------------
SampleCell::SampleCell(CATBaseUnknown_var iRow, const CATString &iCol):_iRow(iRow), _iCol(iCol)
{
}

//-------------------------------------------------------------------------------
SampleCell::~SampleCell()
{
}

//-------------------------------------------------------------------------------
int SampleCell::operator==(const SampleCell &iObjectToCompare) const
{
  if (iObjectToCompare._iRow == _iRow && iObjectToCompare._iCol == _iCol)
    return 1;
  else
    return 0;
}

int SampleCell::operator!=(const SampleCell &iObjectToCompare) const
{
  if (iObjectToCompare._iRow == _iRow && iObjectToCompare._iCol == _iCol)
    return 0;
  else
    return 1;
}


CATBaseUnknown_var &SampleCell::GetRow()
{
  return _iRow;
}

CATString &SampleCell::GetColumn()
{
  return _iCol;
}
