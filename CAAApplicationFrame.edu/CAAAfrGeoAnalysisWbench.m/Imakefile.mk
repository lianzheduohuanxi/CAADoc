# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAAAfrGeoAnalysisWbench.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH=  CATApplicationFrame   \
            CATObjectModelerBase \
            JS0GROUP  \
            CAAAfrGeometryWshop
