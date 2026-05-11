# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAACafEditTextureProp.m
#======================================================================
BUILT_OBJECT_TYPE=SHARED LIBRARY

LINK_WITH= JS0FM JS0GROUP \
          DI0PANV2 \
		  CATIAApplicationFrame CATVisualization CATViz\
		  CATObjectModelerBase \
		  CAASysGeoModelInf 
