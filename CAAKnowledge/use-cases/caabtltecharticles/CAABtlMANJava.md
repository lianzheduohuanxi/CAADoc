---
title: "mkmk and Java"
category: "use-case"
module: "CAABtlTechArticles"
tags: []
source_file: "Doc/online/CAABtlTechArticles/CAABtlMANJava.md"
converted: "2026-05-11T17:33:46.103916"
---

    
    
    
    
    
    
    	
    		
    		RADE
    		
    		| 
    		Multi-Workspace Application Builder
    		
    		| 
    		mkmk and Java
    		_How mkmk organize Java modules_
    		
    	  
    
    	
    		Technical Article
    	  
    
    
    
    
    * * *
    
    
    
    
    	
    		
    		Abstract
    		Distinction is being made to separate client code from server code inside 
    		the run time view.
    		The proposal idea is to separate client run time view from server run 
    		time view. Java modules will be segregated in three categories: common modules, 
    		client modules and server modules.
    		
    
    
    			
        * Client modules will contain code used only by client applications 
        			(UI specific code for example) 
    
    			
        * Server modules will contain code used only by server application 
        			(JDialog controllers, CATServlet code, etc.) 
    
    			
        * Common modules will contain code used by both the client and server 
        			(Trace tools for example) 
    
    		
    
    		The type of Java modules will be specified in the Imakefile.mk by using 
    		the new keyword TYPE. Possible values are CLIENT, SERVER or COMMON. A module 
    		without a TYPE specified will be automatically typed as CLIENT.
    		Java modules are segregated in three categories: Client, Server and Common. 
    		To do this, a new key word TYPE is inserted in JAVA modules Imakefile.mk.
    		
    
    
    			
        * TYPE = CLIENT**(default value if TYPE is not specified)**
        			
    
    			
        * TYPE = COMMON 
    
    			
        * TYPE = SERVER 
    
    		
    
    		Hence, Mkmk build tools will generate three run time views: a common, 
    		a client and a server run time views. Client applications will have to concatenate 
    		the common and client run time view in their classpath while server applications 
    		will have to concatenate the common and server run time view.
    		
    
    
    			
        * Architecture rules
        			
        				
            * LINK_WITH directive 
    
    				
            * 
          				Additional 
          				build rules implied by this architecture 
    
    				
            * CORBA Modules 
    
    			
    			
    
    			
        * Application impacts 
    
    			
        * Client, Common and 
        			Server frameworks 
    
    			
        * Support of the 
        			Java compiler
        			
        				
            * Specifics compilers options
          				
    
    				
            * Compilers access 
    
    			
    			
    
    		
    
    		
    	  
    ---  
    
    
    [Top]
    Architecture rules
     
    
    	
    		BUILT_OBJECT_TYPE = JAVA and TYPE unspecified
    		| /Workspace/$MkmkOS_Builtime/docs/java
    	  
    
    	
    		BUILT_OBJECT_TYPE = JAVA CLIENT
    		| /Workspace/$MkmkOS_Builtime/docs/java
    	  
    
    	
    		BUILT_OBJECT_TYPE = JAVA and TYPE = CLIENT
    		| /Workspace/$MkmkOS_Builtime/docs/java
    	  
    
    	
    		BUILT_OBJECT_TYPE = JAVA COMMON
    		| /Workspace/$MkmkOS_Builtime/docs/java AND /Workspace/$MkmkOS_Builtime/docs/javaserver
    	  
    
    	
    		BUILT_OBJECT_TYPE = JAVA and TYPE = COMMON
    		| /Workspace/$MkmkOS_Builtime/docs/java AND /Workspace/$MkmkOS_Builtime/docs/javaserver
    	  
    
    	
    		BUILT_OBJECT_TYPE = JAVA SERVER
    		| /Workspace/$MkmkOS_Builtime/docs/javaserver
    	  
    
    	
    		BUILT_OBJECT_TYPE = JAVA and TYPE = SERVER
    		| /Workspace/$MkmkOS_Builtime/docs/javaserver
    	  
    
    
    LINK_WITH directive
    The Client/Server architecture implies some restrictions to the relations between 
    Java modules at build time. In fact, Server and Client modules cannot be mixed, 
    then mkmk will check the LINK_WITH directives from Imakefile.mk files.
    Here are the authorized and forbidden relations between Java modules:
    
    	
    		Authorized LINK_WITH are:
    		
    
    
    			
        * CLIENT / CLIENT 
    
    			
        * CLIENT / COMMON 
    
    			
        * SERVER / SERVER 
    
    			
        * SERVER / COMMON 
    
    			
        * COMMON / COMMON 
    
    		
    
    		
    		| Forbidden LINK_WITH are:
    		
    
    
    			
        * SERVER / CLIENT 
    
    			
        * CLIENT / SERVER 
    
    			
        * COMMON / CLIENT 
    
    			
        * COMMON / SERVER 
    
    		
    
    		
    	  
    
    
    Additional 
    build rules implied by this architecture
    
    
    
    	
        * Java modules COMMON will be built into /WS/$MkmkOS_Builtime/docs/**java** 
        	and copied into /WS/$MkmkOS_Builtime/docs/**javaserver**. 
    
    	
        * Java modules COMMON EXTERNAL (ie: .mjext) will be copied into /WS/$MkmkOS_Builtime/docs/**javacommon**.
        	
    
    	
        * Modules where BUILT_OBJECT_TYPE = PACK can only have Java client or Java 
        	common in LINK_WITH. 
    
    
    
    CORBA Modules
    Modules where BUILT_OBJECT_TYPE = CORBA are automatically typed as CLIENT.
    The JAVA part of those modules will be generated in: /Workspace/$MkmkOS_Builtime/docs/**java**.
    The target directory modification for CORBA modules is managed by mkmk without 
    Imakefile.mk modification. Client/Server paradigm, which already exists for CORBA 
    modules, is not related to the JAVA module TYPE (CORBA client code can be used by 
    a server in order to communication to an out-process CORBA component).
    [Top]
    Application impacts
    Since Java code is now separated in at least two run time views (common+client 
    for client applications and common+server for server applications), application 
    will have to update their classpaths in order to concatenate two run time views 
    instead actually of one.
    Client, Common and Server 
    frameworks
    Even if not mandatory by this architecture it should be advised to also have 
    Client frameworks only containing Client JAVA modules, same thing being done for 
    Common and Server framework. This can greatly simplify packaging and avoid having 
    client application CDRom containing server code that will be installed at the same 
    time.
    [Top]
    Support of the Java compiler
    Specifics compilers options
    It is possible to set some local Java compiler options in the Imakefile.mk with 
    the keyword LOCAL_JAVA_FLAGS. Those options are used for all compiler levels.
    Compilers access
    The profile mkmk will detect the JDK and export the Java6ROOT_PATH environment 
    variable. This variable can be overwritten by setting _Java6ROOT_PATH (note the 
    leading underscore) prior to launch mkmk profile.
    [Top]
    
    
    * * *
    
    
    
    History
    
    	
    		Version: **1** [Jun 2003]
    		| Document created
    	  
    
    	
    		[Top]
    	  
    
    
    
    
    * * *
    
    
    
    _Copyright  2000, Dassault Systmes. All rights reserved._
    
    
    
    
    
