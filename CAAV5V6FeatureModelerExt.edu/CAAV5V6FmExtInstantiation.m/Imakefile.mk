#
# COPYRIGHT DASSAULT SYSTEMES 2000
#

BUILT_OBJECT_TYPE=LOAD MODULE
#BUILT_OBJECT_TYPE=NONE

#if defined (CATIAR214)
LINK_WITH = ObjectModelerSystem CAAV5V6FmExtUtilities FeatureModelerExt \
			JS0CORBA CAAAdpUtilities CATPLMIntegrationAccess \
			CAT3DPhysicalRepItf \
			CATPLMComponentInterfaces  \
	    CATPLMIdentificationAccess  CATOmbLifeCycle CATPLMIntegrationUse \
	    
#elif defined (CATIAV5R23) 

LINK_WITH = CATObjectModelerBase \
            CATObjectSpecsModeler \
			JS0CORBA FeatureModelerExt
			
#endif
 	 

 	 


