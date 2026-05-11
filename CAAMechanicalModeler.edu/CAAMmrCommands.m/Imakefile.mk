# COPYRIGHT DASSAULT SYSTEMES 2009
#======================================================================
# Imakefile for module CAAMmrCommands.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH=  CATMathematics   \
            JS0FM JS0GROUP   \
            DI0PANV2 JS0CORBA    CATOMY \ 
            AD0XXBAS \
            CATMecModUseItf CATMecModLiveUseItf \
            CATDialogEngine \
            CATMecModInterfaces CATVisualization
