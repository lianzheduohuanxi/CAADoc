# COPYRIGHT DASSAULT SYSTEMES 2004
#======================================================================
# Imakefile for module CATEhiFLEXImpl.m
#======================================================================
#
#  Dec 2004  Creation: axc
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = JS0GROUP \
JS0FM JS0GROUP ElecHarnessItfUUID 
# END WIZARD EDITION ZONE

LINK_WITH = $(WIZARD_LINK_MODULES)\
			CATEhiInterfaces CATElectricalInterfaces AS0STARTUP

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
