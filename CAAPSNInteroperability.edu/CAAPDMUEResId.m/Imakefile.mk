# COPYRIGHT DASSAULT SYSTEMES 2007
#======================================================================
# Imakefile for module CAAPDMUEResId.m
#======================================================================
#
#  Oct 2007  Creation: Code generated manually  VEL
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES =  JS0GROUP CATPDMBaseItfCPP\

# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES)

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
