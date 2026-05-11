# COPYRIGHT DASSAULT SYSTEMES 2006
#======================================================================
# Imakefile for module TestSSOCAA.m
#======================================================================
#
#  Jan 2006  Creation: smq
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
LINK_WITH = JS0GROUP JS0FM DI0PANV2 CATApplicationFrame DI0STATE \
PLMSSOCAAClient

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
#
OS = win_b64
#

