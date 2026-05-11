// COPYRIGHT DASSAULT SYSTEMES 2007
#ifndef CATLISTOFSampleCell_H
#define CATLISTOFSampleCell_H

#include "SampleCell.h"

//Clean  previous  funtions  requests
#include <CATLISTV_Clean.h>

//Require  needed  functions
#define CATLISTV_Append
#define CATLISTV_RemoveValue
#define CATLISTV_RemoveAll
#define CATLISTV_Locate
#define CATLISTV_Size

//Get  Macros
#include <CATLISTV_Declare.h>

//Generate  interface  of  collection-class  (funtions  declarations)
CATLISTV_DECLARE (SampleCell)
typedef class CATLISTV (SampleCell) CATListOfSampleCell;

#endif
