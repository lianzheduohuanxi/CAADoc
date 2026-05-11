# COPYRIGHT DASSAULT SYSTEMES 2002
#======================================================================
# Imakefile for module CAASmiUserOperationGeomUI.m
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES =
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES) JS0FM JS0GROUP CATCGMGeoMath\
								   DI0PANV2 AC0SPBAS AD0XXBAS \
								   YP00IMPL AS0STARTUP CD0EDIT \
								   CATViz CATVisualization \
								   CATDialogEngine \
								   CATManufacturingInterfaces \
								   CAASmiUserMachFeature \
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
