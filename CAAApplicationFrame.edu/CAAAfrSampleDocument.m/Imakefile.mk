# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAAAfrSampleDocument.m
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH=  CATApplicationFrame     \
            CATObjectModelerBase    \
            CATVisualization  CATViz      \
            CAASysGeoModelInf       \
            CAAAfrGeoWindows        \
            JS0FM JS0GROUP DI0PANV2
