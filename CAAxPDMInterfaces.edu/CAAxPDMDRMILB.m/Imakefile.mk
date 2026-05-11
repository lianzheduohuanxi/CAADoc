# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAASysUExitIO.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH= JS0GROUP  JS0FILEEXIT SystemUUID DI0PANV2 CATDlgStandard CATApplicationFrame  JS0FM CATxPDMInterfaces CATInteractiveInterfaces
