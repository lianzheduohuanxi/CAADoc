// COPYRIGHT DASSAULT SYSTEMES 2003

// local framework
#include "CAAAfrComboColorHeader.h"

// Standard library
#include <iostream.h>

//-----------------------------------------------------------------------------
// To declare that the class is a component main class which OM derives from
// CATAfrDialogCommandHeader 
//
CATImplementClass(CAAAfrComboColorHeader, 
                  Implementation,
                  CATAfrDialogCommandHeader, 
                  CATNull);

//-----------------------------------------------------------------------
// Resource file definition 
//
CATImplementHeaderResources(CAAAfrComboColorHeader, // Command header class name
			    CATAfrDialogCommandHeader,          // Its base class
			    CAAAfrComboColorHeader);            // Resource file name 

//-----------------------------------------------------------------------

CAAAfrComboColorHeader::CAAAfrComboColorHeader(const CATString & iHeaderName) : 
    CATAfrDialogCommandHeader(iHeaderName)
{
   cout <<" CAAAfrComboColorHeader::CAAAfrComboColorHeader" << endl;
}

CAAAfrComboColorHeader::~CAAAfrComboColorHeader()
{
    cout <<" CAAAfrComboColorHeader::~CAAAfrComboColorHeader" << endl;
}

//-----------------------------------------------------------------------

CATCommandHeader * CAAAfrComboColorHeader::Clone ()                                  
{ 
    cout <<" CAAAfrComboColorHeader::Clone" << endl;

    return new CAAAfrComboColorHeader(this); 
}   

//-----------------------------------------------------------------------

CAAAfrComboColorHeader::CAAAfrComboColorHeader(CATCommandHeader * iHeaderToCopy):
                          CATAfrDialogCommandHeader(iHeaderToCopy)
{
   cout << " CAAAfrComboColorHeader Copy const " << endl ;
}	                  

