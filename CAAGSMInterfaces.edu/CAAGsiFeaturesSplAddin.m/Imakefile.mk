#@ autoformat 06:09:14
#======================================================================
# COPYRIGHT Dassault Systemes 2006
#======================================================================
# Imakefile for module CAAGsiFeaturesSplAddin
#======================================================================
# SHARED LIBRARY 
BUILT_OBJECT_TYPE=SHARED LIBRARY 

LINK_WITH_V5_ONLY=
LINK_WITH_V6_ONLY=
 
WIZARD_LINK_MODULES = \
    CATGitInterfaces               \ # GSMInterfaces                  CATGitInterfaces
    PartInterfacesUUID             \ # PartInterfaces                 PartInterfacesUUID
    JS0GROUP                       \ # System                         JS0GROUP
#

LINK_WITH = \
    $(LINK_WITH_V5_ONLY)           \
    $(LINK_WITH_V6_ONLY)           \
    $(WIZARD_LINK_MODULES)         \
    CATApplicationFrame            \ # ApplicationFrame               CATApplicationFrame
    CATGitInterfaces               \ # GSMInterfaces                  CATGitInterfaces
    CATGSMUseItf                   \ # CATGSMUseItf
#

OS = COMMON
#if defined(R201)
LINK_WITH_V6_ONLY= \
#
#else
#if defined(CATIAV5R21)
LINK_WITH_V5_ONLY= \
#
#endif
#endif
