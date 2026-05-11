# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAAAfrGeometryWshop.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH=  CATApplicationFrame   \
            CATVisualization   CATViz   \
            JS0GROUP        \
            CATObjectModelerBase  \
            CAASysGeoModelInf 
