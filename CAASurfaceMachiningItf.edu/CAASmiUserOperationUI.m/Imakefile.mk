# COPYRIGHT DASSAULT SYSTEMES 2002
#======================================================================
# Imakefile for module CAASmiUserOperationUI.m
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES =
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES) JS0FM JS0GROUP \
								   DI0PANV2 \
								   CATLiteralFeatures KnowledgeItf \
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
