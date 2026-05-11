# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAAAfrGeoCreationWbench.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH=  CATApplicationFrame   \
            CATObjectModelerBase  \
            JS0GROUP        \
            CAAAfrGeometryWshop
