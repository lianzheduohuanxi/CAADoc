// COPYRIGHT DASSAULT SYSTEMES 2007

#include "SampleRow.h" 

CATImplementClass(SampleRow, Implementation, CATBaseUnknown, CATNull); 

//-------------------------------------------------------------------------------
SampleRow::SampleRow(int id):_id(id)
{
}

//-------------------------------------------------------------------------------
SampleRow::~SampleRow()
{
}

//-------------------------------------------------------------------------------
void SampleRow::SetDatas(const CATListOfCATUnicodeString &idatas)
{
  int nbDatas = idatas.Size();
  if (nbDatas <= 0)
    return;

  _datas.RemoveAll();
  for (int i = 1; i <= nbDatas; i++)
    _datas.Append(idatas[i]);
}

//-------------------------------------------------------------------------------
void SampleRow::ClearDatas()
{
  _datas.RemoveAll();
}

//-------------------------------------------------------------------------------
int SampleRow::Size()
{
  return _datas.Size();
}
