---
title: "
      Consuming the ENOPosApplicationBinderImpl CAA Web Service
    "
category: "use case"
module: "CAAPLMSecUseCases"
tags: ["CAAENOPosApplicationBinderImplClient", "CAAWebServices", "CAAJAXRPCHTTPSessionHandler", "CAAENOPosApplicationBinderImplUseCase", "CAAENOPosApplicationBinderImplWrapper", "CAAPLMSecurity", "CAAENOPosAppBinderImplAxis1_3Client"]
source_file: "Doc/online/CAAPLMSecUseCases/CAAENOPosAppBinderAxisClient.md"
converted: "2026-05-11T17:33:45.558180"
---
#  CAA Web Services Home 

| 
##   

| 
###  Consuming the ENOPosApplicationBinderImpl CAA Web Service 

_Using the ENOPosApplicationBinderImpl CAA Web service in order to log on to ENOVIA LCA V5_  
---|---|---  
Use Case   
  
* * *
###  Abstract 

This article discusses the **CAAENOPosAppBinderImplAxis1_3Client** use case. It describes how to use the Java client binding that can be generated using the Axis WSDL2Java emitter in order to consume the **ENOPosApplicationBinderImpl CAA Web service**. It provides a sample usage scenario that demonstrates how to manage a session with an ENOVIA LCA V5 system. 

  * **What You Will Learn With This Use Case**
  * **The CAAENOPosAppBinderImplAxis1_3Client Use Case**
    * What Does CAAENOPosAppBinderImplAxis1_3Client Do
    * Where To Find the CAAENOPosAppBinderImplAxis1_3Client Code
    * How to Launch CAAENOPosAppBinderImplAxis1_3Client
  * **Step-by-step**
  * **In Short**
  * **References**

  
---  
  
* * *
###  What You Will Learn With This Use Case 

This use case demonstrates how to write a client application that consumes the ENOPosApplicationBinderImpl CAA Web service. It helps you to: 

  * Generate the Java client binding for the ENOPosApplicationBinderImpl CAA Web service, 
  * Write a wrapper class that instantiates the generated proxy, configures it, and uses it to remotely invoke methods on the CAA Web service, 
  * Write a class that demonstrates a sample usage scenario for the ENOPosApplicationBinderImpl CAA Web service, using the wrapper class mentioned above. 

This article also provides guidances on how to build and run the sample client application using **IRAD (IBM Rational Application Developer) 6.0** , although any other Java IDE (Integrated Development Environment) or stand-alone JDK/JRE (Java Development Kit/Java Runtime Environment) could be used for that purpose. 

[Top] 
###  The CAAENOPosAppBinderImplAxis1_3Client Use Case 

CAAENOPosAppBinderImplAxis1_3Client is a use case of the CAAPLMSecurity.edu framework that illustrates the ENOPosApplicationBinderImpl CAA Web service capabilities. 

[Top] 
####  What Does CAAENOPosAppBinderImplAxis1_3Client Do 

The sample usage scenario delivered with this use case contains the following steps: 

  * Retrieve the contexts (or roles) available for a user specified in parameter, and then display the results to the standard output, 
  * Select the first context available from the result list and use it to log on to ENOVIA LCA V5, 
  * Log out from ENOVIA LCA V5 and terminate the opened session. 

[Top] 
####  Where To Find the CAAENOPosAppBinderImplAxis1_3Client Code 

The CAAENOPosAppBinderImplAxis1_3Client use case is made of several classes located in the **CAAENOPosAppBinderImplAxis1_3Client.mj** module of the **CAAPLMSecurity.edu** framework: 

**Windows** : `_< Install>_\CAAPLMSecurity.edu\CAAENOPosAppBinderImplAxis1_3Client.mj\src`  
**Unix** : `_< Install>_/CAAPLMSecurity.edu/CAAENOPosAppBinderImplAxis1_3Client.mj/src`  
---  
  
  * `_< Install>_`: the directory where the CAA CD-ROM is installed. 

The sample Java resources generated using the Axis WSDL2Java emitter are delivered in the following directory (**Windows**): 

`_< Source>_\_< Output-package>_\CATServiceExceptionType.java  
_< Source>_\_< Output-package>_\ENOPosApplicationBinderImpl.java  
_< Source>_\_< Output-package>_\ENOPosApplicationBinderImplLocator.java  
_< Source>_\_< Output-package>_\IApplicationBinder.java  
_< Source>_\_< Output-package>_\IApplicationBinderBindingStub.java  
_< Source>_\_< Output-package>_\Identifier.java  
_< Source>_\_< Output-package>_\SessionToken.java  
_< Source>_\_< Output-package>_\Status.java  
_< Source>_\_< Output-package>_\holders\SessionTokenHolder.java  
_< Source>_\_< Output-package>_\holders\StringArrayTypeHolder.java`  
---  
  
  * `_< Source>_`: `_< Install>_\CAAPLMSecurity.edu\CAAENOPosAppBinderImplAxis1_3Client.mj\src`, 
  * `_< Install>_`: same as above, 
  * `_< Output-package>_`: com\dassault_systemes\caaplmsecurity\caaenoposappbinderaxis1_3client\generated (based on the output package value specified when using the WSDL2Java emitter). 

The CAAENOPosAppBinderImplAxis1_3Client module contains the other following resources:

`_< Source>_\_< Root-package>_\CAAENOPosApplicationBinderImplClient.java  
_< Source>_\_< Root-package>_\CAAENOPosApplicationBinderImplUseCase.java  
_< Source>_\_< Root-package>_\CAAENOPosApplicationBinderImplWrapper.java`  
---  
  
  * `_< Source>_`: same as above, 
  * `_< Root-package>_`: com\dassault_systemes\caaplmsecurity\caaenoposappbinderaxis1_3client. 

The **CAAENOPosApplicationBinderImplWrapper** class describes how to configure the generated proxy and how to invoke its methods. The **CAAENOPosApplicationBinderImplUseCase** class demonstrates a sample use case scenario of the ENOPosApplicationBinderImpl CAA Web service. The **CAAENOPosApplicationBinderImplClient** class contains the main program. It parses the command line inputs and starts up the use case. 

This use case has a dependency on the **CustomSessionHandler** class which is available in the **CAAJAXRPCHTTPSessionHandler.mj** module of the **CAAWebServices.edu** framework. Please refer to [1] for details on HTTP session management and where to find the related class. 

[Top] 
####  How to Launch CAAENOPosAppBinderImplAxis1_3Client 

To launch the CAAENOPosAppBinderImplAxis1_3Client use case, you will need to set up a buildtime environment, build the code along with its prerequisites, set up a runtime configuration and then execute the use case. You can see [2] for details on how to perform these steps within the IRAD 6 environment. 

The sample usage scenario delivered within this use case consists of a class declaring a main method that takes several options as parameters, as described below: 

`-w _< URI>_ -e _< ENOVIA username>_ -u _< Basic Authentication username>_ -p _< Basic Authentication password>_`  
---  
  
  * `_< URI>_`: is the root URI of the Web application where the ENOPosApplicationBinderImpl CAA Web service is deployed, 
  * `_< ENOVIA username>_`: is a valid username declared in the ENOVIA P&O database, 
  * `_< Basic Authentication Username>_ and _< Basic Authentication Password>_`: are a valid set of credentials for authentication on the remote Web server. 

Here follows a sample command, to be updated with your own environment configuration: 

`-w http://stophe1dsy.dsy.ds:9080/B17 -e cjk -u wpsadmin -p wpsadmin`  
---  
  
[Top] 
###  Step-by-step 

The following section first explains how to generate the Java client binding for the ENOPosApplicationBinderImpl CAA Web service demonstrated. The remaining sections then describe the code that must be written in order to consume this Web service: 

  1. Creating the Java Client Binding
  2. Instantiating and Configuring the Generated Proxy
  3. Retrieving User Contexts
  4. Logging On To ENOVIA LCA V5
  5. Logging Out From ENOVIA LCA V5
  6. Sample Usage Scenario

[Top] 
####  Creating the Java Client Binding 

Please refer to [3] for details on how to generate the Java client binding using the Axis WSDL2Java emitter. 

Here follows a sample command in order to generate the Java client binding for the ENOPosApplicationBinderImpl CAA Web service: 

`%JDK_HOME%\bin\java org.apache.axis.wsdl.WSDL2Java -o C/CAAPLMSecurity\src -p com.dassault_systemes.caaplmsecurity.caaenoposappbinderaxis1_3client.generated http://karindsy.dsy.ds:9080/B17/wsdl?service=urn:com:dassault_systemes:ENOPosWS:ENOPosAppliBinder:ENOPosApplicationBinderImpl`  
---  
  
The server name, port, and context root URI information must be updated to match the server where the CAA Web service has been deployed. The list of generated resources is available from the above section: "Where To Find the CAAENOPosAppBinderImplAxis1_3Client Code". 

[Top] 
####  Instantiating and Configuring the Generated Proxy 

In order to be able to consume the ENOPosApplicationBinderImpl CAA Web service implementation that has been deployed on a target server, you first need to retrieve an instance of the `IApplicationBinderBindingStub` generated class (also referred to as the **proxy**). It is a common best practice to manipulate an instance through its related interface whenever available. The WSDL2Java emitter produces an interface that is implemented by the `IApplicationBinderBindingStub` class: `IApplicationBinder`. It describes the available methods for the remote CAA Web service. 

![Warning](../CAAIcons/images/warning.gif)   Although the `IApplicationBinderBindingStub` class can be directly instantiated using its own set of constructors, the Axis User's Guide recommends to discard this approach. Instead, the recommended approach is to use another generated class for that purpose: `ENOPosApplicationBinderImplLocator`. It implements the `ENOPosApplicationBinderImpl` interface. 

The following code describes how to instantiate the generated proxy. Such proxy is used in order to marshall method calls and objects to SOAP requests, and to unmarshall SOAP responses to objects. This proxy must be configured in order to manage authentication on the remote Web server, timeout, and session management. Maintaining the HTTP session state is mandatory when consuming ENOVIA LCA V5 CAA Web services. 

`**public class** CAAENOPosApplicationBinderImplWrapper {  
  **private** String SERVICE_ID = "urn!com!dassault_systemes!ENOPosWS!ENOPosAppliBinder!ENOPosApplicationBinderImpl";  
  **private** IApplicationBinder proxy = **null** ;  
  
  **public** CAAENOPosApplicationBinderImplWrapper(  
    String clientId,  
    String uri,  
    String credUser,  
    String credPwd,  
    **int** timeOut) {  
    // Compute the SOAP endpoint URI value that bounds to the deployed  
    // implementation of the ENOPosApplicationBinderImpl CAA Web service  
    String endpoint = uri + "servicerouter?service=" + SERVICE_ID;  
  
    // Retrieve proxy instance  
    ENOPosApplicationBinderImplLocator locator = **new** ENOPosApplicationBinderImplLocator();  
    try {  
      proxy = locator.getENOPosApplicationBinderImplPort(**new** URL(endpoint));  
    } **catch** (MalformedURLException e) {  
      ...  
    } **catch** (ServiceException e) {  
      ...  
    }  
  
    // Required for HTTP session state management **(1)**  
    ((IApplicationBinderBindingStub) proxy).setMaintainSession(**true**);  
    **if** (clientId != **null**) {  
  
      // Required to maintain HTTP session state accross services **(2)**  
      HandlerInfo info = **new** HandlerInfo();  
      info.setHandlerClass(CustomSessionHandler.**class**);  
      Map handlerConfig = **new** HashMap();  
      handlerConfig.put(CustomSessionHandler.CLIENT_ID, clientId);  
      info.setHandlerConfig(handlerConfig);  
  
      HandlerRegistry registry = locator.getHandlerRegistry();  
      String portName = locator.getENOPosApplicationBinderImplPortWSDDServiceName();  
      QName name = **new** QName(portName);  
      List chain = registry.getHandlerChain(name);  
      chain.add(info);  
    }  
  
    // Required for the Basic Authentication mechanism **(3)**  
    **if** (credUser != **null** && credUser != **null**) {  
      ((IApplicationBinderBindingStub) proxy).setUsername(credUser);  
      ((IApplicationBinderBindingStub) proxy).setPassword(credPwd);  
    }  
  
    // Increase the default client time-out **(4)**  
    ((IApplicationBinderBindingStub) proxy).setTimeout(timeOut);  
}`  
---  
  
**(1)** : in order to maintain the HTTP session state between successive calls performed using the same proxy instance, the `setMaintainSession` method must be used. This is mandatory in the context of ENOVIA LCA V5 CAA Web services,  
**(2)** : in order to maintain the HTTP session state between successive calls performed using distinct proxy instances, a JAX-RPC custom handler must be configured on the proxy. This is mandatory in the context of ENOVIA LCA V5 CAA Web services. You can refer to [1] for details,  
**(3)** : when security is enabled, it is mandatory to set the `username` and `password` attributes on the generated proxy. The values specified must match a valid set of credentials for the Basic Authentication mechanism,  
**(4)** : the default timeout value can be increased in order to avoid potential issues at runtime, such as losing the HTTP connection before receiving the SOAP responses. The sample value specified in the code is in milliseconds.  

[Top] 
####  Retrieving User Contexts 

In order to log on to ENOVIA LCA V5, you must first retrieve the contexts associated with a given user declared in the P&O (People & Organization) database. This can be achieved using the following method, which is available through the generated `IApplicationBinder` proxy interface: 

`**public** Status getUserContexts(String iUserName, StringArrayTypeHolder oUserContexts)  
  **throws** RemoteException, CATServiceExceptionType`  
---  
  
This method accepts the following parameters: 

`[in] iUserName` |    The name of a user declared in the P&O database   
---|---  
`[in/out] oUserContexts` |    The list of contexts allowed for the specified user (for example VPMDESIGNER.VPM.DEFAULT)   
  
The following code demonstrates the use of the `getUserContexts` method: 

`**public class** CAAENOPosApplicationBinderImplWrapper {  
  ...  
  **public** String[] getUserContexts(String username) **throws** Exception {  
    ...  
    // Holder instance used as in/out parameter  
    StringArrayTypeHolder contextsHolder = new StringArrayTypeHolder();  
    **try** {  
      **Status status = proxy.getUserContexts(username, contextsHolder);**  
      System.out.println("Status: " + status.getStatus());  
    } **catch** (CATServiceExceptionType e) {  
      throw e;  
    } **catch** (Throwable t) {  
      **throw new** Exception("Failed to get user contexts", t);  
    }  
  
    **if** (contextsHolder == **null** || contextsHolder.value == **null**) {  
      **throw new** Exception("Failed to get user contexts");  
    }  
  
    **return** contextsHolder.value;  
  }  
}`  
---  
  
[Top] 
####  Logging On To ENOVIA LCA V5 

You can then log on to ENOVIA LCA V5 with one of the contexts available for the user specified using the following method: 

`**public** Status bindToApplication(String iSelectedUserContext, SessionTokenHolder oSessionId)  
  **throws** RemoteException, CATServiceExceptionType`  
---  
  
This method accepts the following parameters: 

`[in] iSelectedUserContext` |    The context to use in order to log on to ENOVIA LCA V5   
---|---  
`[in/out] oSessionId` |    The session identifier, if any (may be null)   
  
The following code demonstrates the use of the `bindToApplication` method: 

`**public class** CAAENOPosApplicationBinderImplWrapper {  
  ...  
  **public** SessionToken login(String context) **throws** Exception {  
    ...  
    // Holder instance used as in/out parameter  
    SessionTokenHolder sessionTokenHolder = **new** SessionTokenHolder();  
    **try** {  
      **Status status = proxy.bindToApplication(context, sessionTokenHolder);**  
      System.out.println("Status: " + status.getStatus());  
    } **catch** (CATServiceExceptionType e) {  
      **throw** e;  
    } **catch** (Throwable t) {  
      **throw new** Exception("Failed to log in", t);  
    }  
  
    SessionToken sessionToken = **null** ;  
    **if** (sessionTokenHolder != **null**) {  
      sessionToken = sessionTokenHolder.value;  
    }  
  
    **return** sessionToken;  
  }  
}`  
---  
  
[Top] 
####  Logging Out From ENOVIA LCA V5 

You can finally log off from ENOVIA LCA V5 and terminate the opened session using the following method: 

`**public** Status releaseFromApplication(SessionToken iSessionId)  
  **throws** RemoteException, CATServiceExceptionType`  
---  
  
The method accepts the following parameters: 

`[in] iSessionId` |   The session identifier retrieved through the call to `bindToApplication`, if any (may be null)   
---|---  
  
The following code demonstrates the use of the `releaseFromApplication` method: 

`**public class** CAAENOPosApplicationBinderImplWrapper {  
  ...  
  **public void** logout(SessionToken sessionToken) **throws** Exception {  
  **try** {  
    **Status status = proxy.releaseFromApplication(sessionToken);**  
    System.out.println("Status: " + status.getStatus());  
  } **catch** (CATServiceExceptionType e) {  
    throw e;  
  } **catch** (Throwable t) {  
    **throw new** Exception("Failed to log out", t);  
  }  
}`  
---  
  
[Top] 
####  Sample Usage Scenario 

The following code depends on the CAAENOPosApplicationBinderImplWrapper class described above. It demonstrates a sample usage scenario for the ENOPosApplicationBinderImpl CAA Web service: 

`**public class** CAAENOPosApplicationBinderImplUseCase {  
  **private** String uri = **null** ;  
  **private** String credUser = **null** ;  
  **private** String credPwd = **null** ;  
  
  **public** CAAENOPosApplicationBinderImplUseCase(  
    String uri,  
    String credUser,  
    String credPwd) {  
      this.uri = uri;  
      this.credUser = credUser;  
      this.credPwd = credPwd;  
  }  
  
  **public void** runSampleUsageScenario(String enoviaUser) {  
    **try** {  
      // ------------------------------------------------------------  
      // Step 1 - Instantiate and configure the proxy  
      // ------------------------------------------------------------  
  
      String clientId = **new** Long(System.currentTimeMillis()).toString();  
  
      // Instantiate the wrapper client class  
      **CAAENOPosApplicationBinderImplWrapper wrapper =**new** CAAENOPosApplicationBinderImplWrapper(  
        clientId, uri, credUser, credPwd, 360000);**  
  
      // ------------------------------------------------------------  
      // Step 2 - Get and display contexts for the user specified  
      // ------------------------------------------------------------  
  
      **String[] userContexts = wrapper.getUserContexts(enoviaUser);**  
  
      // ------------------------------------------------------------  
      // Step 3 - Log on to ENOVIA with the first available context  
      // ------------------------------------------------------------  
  
      **if** (userContexts.length == 0) {  
        **throw new** Exception("No context found for the user specified");  
      }  
      **SessionToken sessionToken = wrapper.login(userContexts[0]);**  
  
      // ------------------------------------------------------------  
      // Step 4 - Log out from ENOVIA  
      // ------------------------------------------------------------  
  
      **wrapper.logout(sessionToken);**  
      ...  
    } **catch** (CATServiceExceptionType c) {  
      ...  
      System.out.println("\tError code: " + c.getCode());  
      System.out.println("\tError message: " + c.getMessage());  
      **if** (c.getErrorArguments() != **null**) {  
        String[] errorArguments = c.getErrorArguments();  
        System.out.println("\tError arguments: " + errorArguments.length);  
        **for** (**int** i = 0; i < errorArguments.length; i++) {  
          System.out.println("\t\tArgument[" + i + "]: " + errorArguments[i]);  
        }  
      }  
    } **catch** (Exception e) {  
      ...  
    }  
  }  
}`  
---  
  
[Top] 

* * *
###  In Short 

This use case explains how to use the Java client binding generated using the Axis WSDL2Java emitter in order to consume the ENOPosApplicationBinderImpl CAA Web service. It also gives an overview of the available methods: 

  * `getUserContexts`: retrieve the contexts associated with a given user declared in the P&O database, 
  * `bindToApplication`: log on to ENOVIA LCA V5 using a specific context, 
  * `releaseFromApplication`: log off from ENOVIA LCA V5 in order to terminate an opened session. 

[Top] 

* * *
###  References 

[1]  |  [Maintaining the Session State](../CAAWSTechArticles/CAAWSMaintainSessionWithAxis.md)  
---|---  
[2]  |  [Building and Launching a CAA Web Service Use Case](../CAAWSUseCases/CAAWSBuildAndLaunchUsingAxis.md)  
[3]  |  [Generating a Java Client Binding](../CAAWSTechArticles/CAAWSClientUsingAxis.md)  
[Top]   
  
* * *
###  History 

Version: **1** [Apr 2005]  |  Document created   
---|---  
Version: **2** [Jan 2006]  |  Document updated   
[Top]   
  
* * *

_Copyright © 1994-2006, Dassault Systèmes. All rights reserved._
