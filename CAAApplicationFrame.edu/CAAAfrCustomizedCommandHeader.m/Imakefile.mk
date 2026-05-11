# COPYRIGHT DASSAULT SYSTEMES 2002
#======================================================================
# Imakefile for module CAAMmrCATMmuDebugCAAAddin.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
LINK_WITH=CATApplicationFrame  DI0PANV2 \
          JS0GROUP JS0FM  CATVisualization\
		  CAAAfrCustCommandHdrModel CAASysGeoModelInf
