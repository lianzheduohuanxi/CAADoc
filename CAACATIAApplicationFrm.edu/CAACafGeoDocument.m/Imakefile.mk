# COPYRIGHT DASSAULT SYSTEMES 2000
#======================================================================
# Imakefile for module CAACafGeoDocument.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH=  CATApplicationFrame   \
            CATIAApplicationFrame \
            CATObjectModelerBase  \
            CATVisualization CATViz     \
            CAASysGeoModelInf     \
            JS0FM JS0GROUP \
            DI0PANV2
