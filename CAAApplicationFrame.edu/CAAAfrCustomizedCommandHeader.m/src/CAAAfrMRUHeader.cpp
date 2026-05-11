// COPYRIGHT DASSAULT SYSTEMES 2003

// local framework
#include "CAAAfrMRUHeader.h"

// Standard library
#include <iostream.h>

//-----------------------------------------------------------------------------
// To declare that the class is a component main class 
//
CATImplementClass(CAAAfrMRUHeader, 
                  Implementation,
                  CATAfrDialogCommandHeader, 
                  CATNull);
CATImplementHeaderResources(CAAAfrMRUHeader,
                            CATCommandHeader,
                            CAAAfrMRUHeader);

//-----------------------------------------------------------------------

CAAAfrMRUHeader::CAAAfrMRUHeader(const CATString & iHeaderName) : 
    CATAfrDialogCommandHeader(iHeaderName)
{
   cout <<" CAAAfrMRUHeader::CAAAfrMRUHeader" << endl;
}

CAAAfrMRUHeader::~CAAAfrMRUHeader()
{
    cout <<" CAAAfrMRUHeader::~CAAAfrMRUHeader" << endl;
}

//-----------------------------------------------------------------------

CATCommandHeader * CAAAfrMRUHeader::Clone ()                                  
{ 
    cout <<" CAAAfrMRUHeader::Clone" << endl;

    return new CAAAfrMRUHeader(this); 
}   

//-----------------------------------------------------------------------

CAAAfrMRUHeader::CAAAfrMRUHeader(CATCommandHeader * iHeaderToCopy):
                          CATAfrDialogCommandHeader(iHeaderToCopy)
{
   cout << " CAAAfrMRUHeader Copy const " << endl ;
}	                  


