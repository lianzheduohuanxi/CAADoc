// COPYRIGHT DASSAULT SYSTEMES 2003

// local framework
#include "CAAAfrEltCountHeader.h"

// Standard library
#include <iostream.h>

//-----------------------------------------------------------------------------
// To declare that the class is a component main class which OM derives from
// the CATAfrDialogCommandHeader component
//
CATImplementClass(CAAAfrEltCountHeader, 
                  Implementation,
                  CATAfrDialogCommandHeader, 
                  CATNull);

//-----------------------------------------------------------------------
// Resource file definition 
//
CATImplementHeaderResources(CAAAfrEltCountHeader, // Command header class name
			    CATAfrDialogCommandHeader,   // Its base class
			    CAAAfrEltCountHeader);            // Resource file name 

//-----------------------------------------------------------------------

CAAAfrEltCountHeader::CAAAfrEltCountHeader(const CATString & iHeaderName) : 
    CATAfrDialogCommandHeader(iHeaderName)
{
   cout <<" CAAAfrEltCountHeader::CAAAfrEltCountHeader" << endl;
}

CAAAfrEltCountHeader::~CAAAfrEltCountHeader()
{
    cout <<" CAAAfrEltCountHeader::~CAAAfrEltCountHeader" << endl;
}

//-----------------------------------------------------------------------

CATCommandHeader * CAAAfrEltCountHeader::Clone ()                                  
{ 
    cout <<" CAAAfrEltCountHeader::Clone" << endl;

    return new CAAAfrEltCountHeader(this); 
}   

//-----------------------------------------------------------------------

CAAAfrEltCountHeader::CAAAfrEltCountHeader(CATCommandHeader * iHeaderToCopy):
                          CATAfrDialogCommandHeader(iHeaderToCopy)
{
   cout << " CAAAfrEltCountHeader Copy const " << endl ;
}	                  


