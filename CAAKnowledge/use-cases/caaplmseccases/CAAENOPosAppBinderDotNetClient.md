---
title: "
```vbscript
title: "
      Consuming the ENOPosApplicationBinderImpl CAA Web Service
```

    "
```vbscript
title: "
Consuming the ENOPosApplicationBinderImpl CAA Web Service
category: use-case case"
module: "CAAPLMSecUseCases"
tags: ["CAAENOPosApplicationBinderImplProxy", "CAAENOPosApplicationBinderImplUseCase", "CAAENOPosAppBinderDotNet1_1ClientBase", "CAAENOPosApplicationBinderImplWrapper", "CAAENOPosAppBinderDotNet1_1Client", "CAAPLMSecurity"]
source_file: "Doc/online/CAAPLMSecUseCases/CAAENOPosAppBinderDotNetClient.htmmd"
converted: "2026-05-11T17:33:45.579695"
```

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

This article discusses the **CAAENOPosAppBinderDotNet1_1Client** use case. It describes how to use the C# client binding that can be generated using the wsdl.exe utility in order to consume the **ENOPosApplicationBinderImpl** CAA Web service. It provides a sample usage scenario that demonstrates how to manage a session with an ENOVIA LCA V5 system.

  * **What You Will Learn With This Use Case**
  * **The CAAENOPosAppBinderDotNet1_1Client Use Case**
    * What Does CAAENOPosAppBinderDotNet1_1Client Do
    * Where To Find the CAAENOPosAppBinderDotNet1_1Client Code
    * How to Launch CAAENOPosAppBinderDotNet1_1Client
  * **Step-by-step**
  * **In Short**
  * **References**

---

* * *
###  What You Will Learn With This Use Case

This use case demonstrates how to write a client application that consumes the ENOPosApplicationBinderImpl CAA Web service. It helps you to:

  * Generate the C# client binding for the ENOPosApplicationBinderImpl CAA Web service,
  * Configure and use the generated proxy,
  * Understand a sample usage scenario of the ENOPosApplicationBinderImpl CAA Web service.

[Top]
###  The CAAENOPosAppBinderDotNet1_1Client Use Case

CAAENOPosAppBinderDotNet1_1Client is a use case of the CAAPLMSecurity.edu framework that illustrates the ENOPosApplicationBinderImpl CAA Web service capabilities.

[Top]
####  What Does CAAENOPosAppBinderDotNet1_1Client Do

The sample usage scenario delivered with this use case contains the following steps:

  * Retrieve the contexts (or roles) available for a user specified in parameter, and then display the results to the standard output,
  * Select the first context available from the result list and use it to log on to ENOVIA LCA V5,
  * Log out from ENOVIA LCA V5 and terminate the opened session.

[Top]
####  Where To Find the CAAENOPosAppBinderDotNet1_1Client Code

The CAAENOPosAppBinderDotNet1_1Client use case is made of several classes located in both **CAAENOPosAppBinderDotNet1_1Client.m** and **CAAENOPosAppBinderDotNet1_1ClientBase.m** modules of the **CAAPLMSecurity.edu** framework:

`_< Install>_/CAAPLMSecurity.edu/CAAENOPosAppBinderDotNet1_1Client.m/src`
`_< Install>_/CAAPLMSecurity.edu/CAAENOPosAppBinderDotNet1_1ClientBase.m/src`
---

  * `_< Install>_`: the root directory where the CAA CD-ROM is installed.

The CAAENOPosAppBinderDotNet1_1ClientBase.m module (library) contains the following resources:

`_< Source>_/CAAENOPosApplicationBinderImplProxy.cs
_< Source>_/CAAENOPosApplicationBinderImplWrapper.cs`
---

  * `_< Source>_`: `_< Install>_/CAAPLMSecurity.edu/CAAENOPosAppBinderDotNet1_1ClientBase.m/src`.

_< Source>_/CAAENOPosApplicationBinderImplWrapper.cs`
The **CAAENOPosApplicationBinderImplProxy.cs** file contains the C# client binding generated using the wsdl.exe utility. A C# client binding consists of a proxy and several types definitions. The **CAAENOPosApplicationBinderImplWrapper.cs** file contains a class that describes how to configure the generated proxy and how to invoke its methods.

The CAAENOPosAppBinderDotNet1_1Client.m module (executable) contains the following resources:

`_< Source>_/CAAENOPosAppBinderDotNet1_1Client.cs
The **CAAENOPosApplicationBinderImplProxy.cs** file contains the C# client binding generated using the wsdl.exe utility. A C# client binding consists of a proxy and several types definitions. The **CAAENOPosApplicationBinderImplWrapper.cs** file contains a class that describes how to configure the generated proxy and how to invoke its methods.
The CAAENOPosAppBinderDotNet1_1Client.m module (executable) contains the following resources:
_< Source>_/CAAENOPosApplicationBinderImplUseCase.cs`

---

  * `_< Source>_`: `_< Install>_/CAAPLMSecurity.edu/CAAENOPosAppBinderDotNet1_1Client.m/src`.

The **CAAENOPosAppBinderDotNet1_1Client.cs** file contains the main program. It parses the command line inputs and starts up the use case. The **CAAENOPosApplicationBinderImplUseCase.cs** file contains the sample use case scenario.

[Top]
####  How to Launch CAAENOPosAppBinderDotNet1_1Client

The **CAAENOPosAppBinderDotNet1_1Client.cs** file contains the main program. It parses the command line inputs and starts up the use case. The **CAAENOPosApplicationBinderImplUseCase.cs** file contains the sample use case scenario.
To run the CAAENOPosAppBinderDotNet1_1Client use case, you will need to build both CAAENOPosAppBinderDotNet1_1ClientBase.m and CAAENOPosAppBinderDotNet1_1Client.m modules. The use case code can be built using either the CAA V5 buildtime environment, or Visual Studio .NET 2003 as explained in [1].

You can then execute the command described below:

`CAAENOPosAppBinderDotNet1_1Client -w _< URI>_ -e _< ENOVIA username>_ -u _< Basic Authentication username>_ -p _< Basic Authentication password>_`
---

  * `_< URI>_`: is the root URI of the Web application where the ENOPosApplicationBinderImpl CAA Web service is deployed,
  * `_< ENOVIA username>_`: is a valid username declared in the ENOVIA P&O database,
  * `_< Basic Authentication Username>_ and _< Basic Authentication Password>_`: are a valid set of credentials for authentication on the remote Web server.

Here follows a sample command, to be updated with your own environment configuration:

`CAAENOPosAppBinderDotNet1_1Client -w http://stophe1dsy.dsy.ds:9080/B17 -e cjk -u wpsadmin -p wpsadmin`
---

When building the modules with the CAA V5 buildtime environment, the CAAENOPosAppBinderDotNet1_1Client executable can be launched from the following location:

`_< Install>_/CAAPLMSecurity.edu/intel_a/code/clr`
---

  * `_< Install>_`: the root directory where the CAA CD-ROM is installed.

[Top]
###  Step-by-step

The following section first explains how to generate the C# client binding for the ENOPosApplicationBinderImpl CAA Web service demonstrated. The remaining sections describe how to configure the generated proxy and how to consume the Web service:

The following section first explains how to generate the C# client binding for the ENOPosApplicationBinderImpl CAA Web service demonstrated. The remaining sections describe how to configure the generated proxy and how to consume the Web service:
  1. Creating the C# Client Binding
  2. Instantiating and Configuring the Generated Proxy
  3. Retrieving User Contexts
  4. Logging On To ENOVIA LCA V5
  5. Logging Out From ENOVIA LCA V5
  6. Sample Usage Scenario

[Top]
####  Creating the C# Client Binding

6. Sample Usage Scenario
Please refer to [2] for details on how to generate the C# client binding using the wsdl.exe utility.

Here follows a sample command in order to generate the C# client binding for the ENOPosApplicationBinderImpl CAA Web service:

`wsdl /namespace:com.dassault_systemes.caaplmsecurity.caaenoposappbinderdotnet1_1clientbase.enoposapplicationbinderimpl /username:wpsadmin /password:wpsadmin /out:CAAENOPosApplicationBinderImplProxy.cs http://stophe1dsy.dsy.ds:9080/B17/wsdl?service=urn:com:dassault_systemes:ENOPosWS:ENOPosAppliBinder:ENOPosApplicationBinderImpl`
---

The server name, port, and context root URI information must be updated to match the server where the ENOPosApplicationBinderImpl CAA Web service has been deployed. The `/username` and `/username` options are required to authenticate on the Web server hosting the Web service.

[Top]
####  Instantiating and Configuring the Generated Proxy

The server name, port, and context root URI information must be updated to match the server where the ENOPosApplicationBinderImpl CAA Web service has been deployed. The `/username` and `/username` options are required to authenticate on the Web server hosting the Web service.
In order to consume an implementation of the ENOPosApplicationBinderImpl CAA Web service deployed on a target Web server, you first need to instantiate the proxy generated using the wsdl.exe utility. This proxy must then be configured in order to manage authentication on the remote Web server, timeout, and session management. Maintaining the HTTP session state is mandatory when consuming ENOVIA LCA V5 CAA Web services.

The generated proxy class is used in order to marshall method calls and objects to SOAP requests, and to unmarshall SOAP responses to objects. The following code describes how to instantiate and configure it:

`public class CAAENOPosApplicationBinderImplWrapper {
In order to consume an implementation of the ENOPosApplicationBinderImpl CAA Web service deployed on a target Web server, you first need to instantiate the proxy generated using the wsdl.exe utility. This proxy must then be configured in order to manage authentication on the remote Web server, timeout, and session management. Maintaining the HTTP session state is mandatory when consuming ENOVIA LCA V5 CAA Web services.
The generated proxy class is used in order to marshall method calls and objects to SOAP requests, and to unmarshall SOAP responses to objects. The following code describes how to instantiate and configure it:
```vbscript
  private const string SERVICE_ID = "urn!com!dassault_systemes!ENOPosWS!ENOPosAppliBinder!ENOPosApplicationBinderImpl";
  private CAAENOPosApplicationBinderImplProxy proxy = null;

  public CAAENOPosApplicationBinderImplWrapper(
```

    CookieContainer container,
    string uri,
    string credUser,
    string credPwd,
    int timeOut) {
```vbscript
    proxy = new CAAENOPosApplicationBinderImplProxy(#);

```

    // Compute the SOAP endpoint URI value that bounds to the deployed
    // implementation of the ENOPosApplicationBinderImpl CAA Web service
int timeOut) {
proxy = new CAAENOPosApplicationBinderImplProxy(#);
```vbscript
```vbscript
    proxy.Url = uri + "servicerouter?service=" + SERVICE_ID;

```

```

    // Required for HTTP session state management
```vbscript
    proxy.CookieContainer = container; **(1)**

```

    // Required for the Basic Authentication mechanism
proxy.CookieContainer = container; **(1)**
    ICredentials credentials = new NetworkCredential(credUser, credPwd);
```vbscript
    proxy.Credentials = credentials; **(2)**

```

    // Increase the default client time-out
ICredentials credentials = new NetworkCredential(credUser, credPwd);
proxy.Credentials = credentials; **(2)**
```vbscript
```vbscript
    proxy.Timeout = timeOut; **(3)**

```

```

   }
}`
---

**(1)** : in order to maintain the HTTP session state between successive calls performed using either the same or multiple proxy instances, the `CookieContainer` property must be set on the proxy. This is mandatory in the context of ENOVIA LCA V5 CAA Web services,
**(2)** : when security is enabled on the remote Web server, it is mandatory to set the `Credentials` property on the proxy. The values specified must match a valid set of credentials for the Basic Authentication mechanism,
**(3)** : the default timeout value can be increased in order to avoid potential issues at runtime, such as losing the HTTP connection before receiving the SOAP responses. The sample value specified in the code is in milliseconds.

[Top]
####  Retrieving User Contexts

In order to log on to ENOVIA LCA V5, you must first retrieve the contexts associated with a given user declared in the P&O (People & Organization) database. This can be achieved using the following method, which is available through the generated proxy:

`public Status getUserContexts(string iUserName, ref string[] oUserContexts)`
---

This method accepts the following parameters:

`[in] iUserName` |    The name of a user declared in the P&O database
---|---
`[in/out] oUserContexts` |    The list of contexts allowed for the specified user (for example VPMDESIGNER.VPM.DEFAULT)

The following code demonstrates the use of the `getUserContexts` method:

`public class CAAENOPosApplicationBinderImplWrapper {
 ...
The following code demonstrates the use of the `getUserContexts` method:
```vbscript
  public string[] GetUserContexts(string username) {
    if (username == null) {
```

      throw new ApplicationException("Illegal argument: P&O username is null");

    }

```vbscript
public string[] GetUserContexts(string username) {
if (username == null) {
```

throw new ApplicationException("Illegal argument: P&O username is null");
    string[] userContexts = null;
    try {

      **Status status = proxy.****getUserContexts****(username, ref userContexts);**
string[] userContexts = null;
try {
      Console.Out.WriteLine("Status: {0}", status.Status1);

    } catch (Exception e) {
string[] userContexts = null;
try {
Console.Out.WriteLine("Status: {0}", status.Status1);
      throw new ApplicationException("Failed to get user contexts", e);

    }

Console.Out.WriteLine("Status: {0}", status.Status1);
throw new ApplicationException("Failed to get user contexts", e);
    if (userContexts == null) {
      throw new ApplicationException("Failed to get user contexts");

    }
```vbscript
if (userContexts == null) {
throw new ApplicationException("Failed to get user contexts");
    return userContexts;
```

  }
}`
---

[Top]
####  Logging On To ENOVIA LCA V5

You can then log on to ENOVIA LCA V5 with one of the contexts available for the user specified using the following method:

`public Status bindToApplication(string iSelectedUserContext, ref SessionToken oSessionId)`
---

This method accepts the following parameters:

`[in] iSelectedUserContext` |    The context to use in order to log on to ENOVIA LCA V5
---|---
`[in/out] oSessionId` |    The session identifier, if any (may be null)

The following code demonstrates the use of the `bindToApplication` method:

`public class CAAENOPosApplicationBinderImplWrapper {
  ...
The following code demonstrates the use of the `bindToApplication` method:
```vbscript
  public SessionToken Login(string context) {
    if (context == null) {
```

      throw new ApplicationException("Illegal argument: context is null");

    }

```vbscript
public SessionToken Login(string context) {
if (context == null) {
```

throw new ApplicationException("Illegal argument: context is null");
    SessionToken sessionToken = null;
    try {

      **Status status = proxy.bindToApplication(context, ref sessionToken);
**       Console.Out.WriteLine("Status: {0}", status.Status1);
    } catch (Exception e) {
SessionToken sessionToken = null;
try {
      throw new ApplicationException("Failed to login", e);

    }

    return sessionToken;
  }
}`
---

[Top]
####  Logging Out From ENOVIA LCA V5

You can finally log off from ENOVIA LCA V5 and terminate the opened session using the following method:

`public Status releaseFromApplication(SessionToken iSessionId)`
---

The method accepts the following parameters:

`[in] iSessionId` |   The session identifier retrieved through the call to `bindToApplication`, if any (may be null)
---|---

The following code demonstrates the use of the `releaseFromApplication` method:

`public class CAAENOPosApplicationBinderImplWrapper {
  ...
The following code demonstrates the use of the `releaseFromApplication` method:
  public void Logout(SessionToken sessionToken) {
    try {

      **Status status = proxy.releaseFromApplication(sessionToken);**
public void Logout(SessionToken sessionToken) {
try {
      Console.Out.WriteLine("Status: {0}", status.Status1);

    } catch (Exception e) {
public void Logout(SessionToken sessionToken) {
try {
Console.Out.WriteLine("Status: {0}", status.Status1);
      throw new ApplicationException("Failed to log out", e);

    }
  }
}`
---

[Top]
####  Sample Usage Scenario

The following code depends on the CAAENOPosApplicationBinderImplWrapper class described above. It demonstrates a sample usage scenario for the ENOPosApplicationBinderImpl CAA Web service:

`public class CAAENOPosApplicationBinderImplUseCase {
The following code depends on the CAAENOPosApplicationBinderImplWrapper class described above. It demonstrates a sample usage scenario for the ENOPosApplicationBinderImpl CAA Web service:
```vbscript
  private string uri = null;
  private string credUser = null;
  private string credPwd = null;

  public CAAENOPosApplicationBinderImplUseCase(
```

    string uri,
    string credUser,
    string credPwd) {
    this.uri = uri;
```vbscript
```vbscript
    this.credUser = credUser;
    this.credPwd = credPwd;

```

```

  }

this.uri = uri;
```vbscript
```vbscript
this.credUser = credUser;
this.credPwd = credPwd;
```

```

  public void RunSampleUsageScenario(string enoviaUser) {
    try {

      // ------------------------------------------------------------
      // Step 1 - Instantiate and configure the proxy
      // ------------------------------------------------------------

      // Create a CookieContainer object to maintain the HTTP session state
      CookieContainer container = new CookieContainer(#);

      **CAAENOPosApplicationBinderImplWrapper wrapper =
CookieContainer container = new CookieContainer(#);
            new CAAENOPosApplicationBinderImplWrapper(
          container, uri, credUser, credPwd, 360000);**

      // ------------------------------------------------------------
      // Step 2 - Get contexts for the user specified
      // ------------------------------------------------------------
      **string[] userContexts = wrapper.GetUserContexts(enoviaUser);**
      if (userContexts.Length == 0) {
        throw new ApplicationException("No context found for the user specified");
      }

      // ------------------------------------------------------------
      // Step 3 - Log on to ENOVIA LCA V5 with the first available context
      // ------------------------------------------------------------
      **SessionToken sessionToken = wrapper.Login(userContexts[0]);**

      // ------------------------------------------------------------
      // Step 4 - Log out from ENOVIA LCA V5
      // ------------------------------------------------------------
      **wrapper.Logout(sessionToken);**
    } catch (Exception e) {
      ...
    }
  }
}`
---

[Top]

* * *
###  In Short

This use case explains how to use the C# client binding generated using the wsdl.exe utility in order to consume the ENOPosApplicationBinderImpl CAA Web service. It also gives an overview of the available methods:

  * `getUserContexts`: retrieve the contexts associated with a given user declared in the P&O database,
  * `bindToApplication`: log on to ENOVIA LCA V5 using a specific context,
  * `releaseFromApplication`: log off from ENOVIA LCA V5 in order to terminate an opened session.

[Top]

* * *
###  References

[1]  |  Building and Launching a CAA Web Service Use Case
---|---
[2]  |  Generating a C# Client Binding
[Top]

* * *
###  History

Version: **1** [Jan 2006]  |  Document created
---|---
[Top]

* * *

_Copyright 2006, Dassault Systmes. All rights reserved._
