# COPYRIGHT DASSAULT SYSTEMES 2007
#======================================================================
# Imakefile for module CAAEnoviaV5SaveCmd.m
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 

LINK_WITH = JS0CORBA DI0STATE JS0FM DI0PANV2 CD0FRAME AS0STARTUP \
            AD0XXBAS CATPDMBaseEnoviaV5CAA CATPDMBaseItfCPP

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

