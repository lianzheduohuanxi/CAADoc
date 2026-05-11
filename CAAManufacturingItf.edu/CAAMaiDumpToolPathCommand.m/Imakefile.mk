# COPYRIGHT DASSAULT SYSTEMES 2001
#======================================================================
# Imakefile for module CAAMaiDumpToolPath.m 
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = JS0FM JS0GROUP AD0XXBAS \
DI0STATE AC0SPBAS\
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES) CATManufacturingInterfaces CATMathStream\
		CATViz CATVisualization ProcessInterfaces Mathematics CATApplicationFrame

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
