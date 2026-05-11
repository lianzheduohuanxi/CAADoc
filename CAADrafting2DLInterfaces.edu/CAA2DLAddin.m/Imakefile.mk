// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// Imakefile for code module CAA2DLAddin.m
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Fev. 2007  Creation
//=============================================================================
BUILT_OBJECT_TYPE=SHARED LIBRARY
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = 
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES)\
            JS0CORBA \
            CATApplicationFrame \
            Drafting2DLItfCPP
            

# System dependant variables
#
OS = AIX
#
OS = HP-UX
#
OS = IRIX
#
OS = SunOS
#
OS = Windows_NT


