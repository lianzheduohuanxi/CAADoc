# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAAAfrGeoModel.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH=  CATVisualization  CATViz    \
            CATObjectModelerBase  \
            JS0GROUP              \
            CAASysGeoModelInf     \
            CATApplicationFrame   
