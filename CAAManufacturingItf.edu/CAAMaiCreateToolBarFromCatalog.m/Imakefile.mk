# COPYRIGHT Dassault Systemes 2007
#======================================================================
# Imakefile for module MfgTstToolBarFromCatalog.m
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = JS0GROUP \
JS0GROUP 
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES)	JS0FM				\
						CATApplicationFrame			\
						CATManufacturingInterfaces

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
