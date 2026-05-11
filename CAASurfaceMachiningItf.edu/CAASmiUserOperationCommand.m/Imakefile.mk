# COPYRIGHT DASSAULT SYSTEMES 2002
#======================================================================
# Imakefile for module CAASmiCreateUserActivityCommand.m 
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES =
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES)  JS0FM JS0GROUP \
									AD0XXBAS CD0FRAME DI0PANV2 \
									DI0STATE AC0SPBAS \
									ProcessInterfaces \
									CATManufacturingInterfaces \
									CATSurfaceMachiningInterfaces

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
