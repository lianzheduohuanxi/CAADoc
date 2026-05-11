---
```vbscript
title: "Introduction to Multiprocessing"
category: "concept"
module: "CAACgmModel"
tags: ["CAAGMModelInterfaces", "CAAGMModelTesMProcImpl", "CAAGMModelTesMProcMain"]
source_file: "Doc/online/CAACgmModel/CAACgmTaMultiProcIntro.htm"
converted: "2026-05-11T17:33:48.005017"
```

---
# Introduction to Multiprocessing

---
Technical Article
## Abstract

CGM contains a multiprocessing infrastructure called MProc. With it one can utilize available processors of a system to improve performance of compute intensive operations, or to compute tasks in the background leaving the foreground process responsive. Because the technology is based on multiple processes with inter-process communication, it does not require code to be thread-safe or reentrant. The MProc system handles the complexities of process management, communication, and scheduling, leaving a simple client implementation based on a minimal and structured interface. While the MProc system can be used for most any multi-process purpose, it has functionality to optimize the transfer of CGM objects between processes. This specialization provides an advantage that cannot be equaled with other multiprocessing tools.
    * Overview
    * Synchronous Multiprocessing
    * Asynchronous Multiprocessing
    * Sequential Tasks
    * Object Relationships
    * Task Manager Construction
    * Stream Optimizations
    * Process Specific Data
    * Enabling Multiprocessing
    * Resource Utilization
    * Debugging Techniques
    * In Short
---
## Overview

Adding multiprocessing to an algorithm requires several fundamental steps: operations must be divided into independent tasks, tasks must be distributed to available processes, and then computed, and finally the results accumulated. This requires process management, task management, and task containment.

Adding multiprocessing to an algorithm requires several fundamental steps: operations must be divided into independent tasks, tasks must be distributed to available processes, and then computed, and finally the results accumulated. This requires process management, task management, and task containment.
Process management is handled internally by the MProc Infrastructure. It interacts with the task manager, manages the lifetimes of processes, controls inter-process communications, and much more.

Task management is handled by the CATMProcTaskManagerCGM class. This class provides functionality for creating new tasks and for processing completed tasks. Custom implementations derive from this class to add task division and accumulation logic.

Task containment, which defines a container to hold operational data, is handled by the CATMProcTaskContainerCGM class. It provides functionality to format computational data into buffers that are used for inter-process communication, and to compute tasks. Custom implementations derive from this class to add data in the form of inputs and outputs, and operators to compute the results.

Additionally, an algorithm must be modified or newly developed to contain multiprocessing code, i.e. a parallel region. The code must handle situations where multiprocessing is not possible, on a single core machine for instance, by computing operations sequentially without introducing unnecessary complexities such as multiple code paths.

The ‘parallel region’ is handled effectively by the MProc infrastructure. It takes care of processor utilization and the CATMProcTaskManagerCGM has provisions to run the tasks sequentially when necessary. The client implementation does not need to provide special code for either scenario since it is handled transparently.

An example of MProc implementation is located in the CAAGMModelTesMProcImpl.m and CAAGMModelTesMProcMain.m modules of CAAGMModelInterfaces.edu. This article refers to this use case.

## Synchronous Multiprocessing

The ‘parallel region’ is handled effectively by the MProc infrastructure. It takes care of processor utilization and the CATMProcTaskManagerCGM has provisions to run the tasks sequentially when necessary. The client implementation does not need to provide special code for either scenario since it is handled transparently.
An example of MProc implementation is located in the CAAGMModelTesMProcImpl.m and CAAGMModelTesMProcMain.m modules of CAAGMModelInterfaces.edu. This article refers to this use case.
In the typical case, multiprocessing is used to compute particular operations as quickly as possible. Consider for instance the classic example of tessellating a multi-body model (aka assembly). In the sequential workflow, the bodies are tessellated one after the other. One can easily envision a loop, iterating over a list of bodies, tessellating and rendering each one in turn.

```vbscript
    for (int i = 1; i <= BodyList.Size(); ++i)

```

    {
In the typical case, multiprocessing is used to compute particular operations as quickly as possible. Consider for instance the classic example of tessellating a multi-body model (aka assembly). In the sequential workflow, the bodies are tessellated one after the other. One can easily envision a loop, iterating over a list of bodies, tessellating and rendering each one in turn.
for (int i = 1; i <= BodyList.Size(); ++i)
        CATBody* Body = BodyList[i];
        TessData* Data = Tessellate(Body);
        Render(Data);

    }

---

```vbscript
Render(Data);
In the parallel case, the loop will be replaced with a custom CATMProcTaskManagerCGM implementation, containing the list of bodies. This task manager is responsible for distributing the bodies, and for rendering them as each operation completes.

    CustomTessellator MyTessellator(BodyList);
    MyTessellator.Run();

```

---

CustomTessellator MyTessellator(BodyList);
MyTessellator.Run();
The base class Run method initiates the parallel transaction and hands control over to the process manager. When additional processes are not available, the Run method retains control and runs the tasks sequentially on the master process. In either case, the custom task manager is queried for tasks in the Virtual NextTask method and is presented with completed task in the virtual EndTask method until none remain.

The NextTask method receives a pointer to a CATMProcProcessDataCGM class object. This class is used to attach process specific data to slave processes. Once attached, the objects remain associated with the particular slave processes until the end of the parallel region. Custom implementations can use this to attach custom data to specific processes.

It is up to the custom implementation to track progress in order to know when all the tasks have been created. In this case the next body to tessellate is tracked with the variable Scheduled, as a class data member along with the body list. Appropriate constructors and destructors are omitted to simplify the example. However, these are discussed in the Object Relationships section.

    class CustomTessellator : public CATMProcTaskManagerCGM

    {
It is up to the custom implementation to track progress in order to know when all the tasks have been created. In this case the next body to tessellate is tracked with the variable Scheduled, as a class data member along with the body list. Appropriate constructors and destructors are omitted to simplify the example. However, these are discussed in the Object Relationships section.
class CustomTessellator : public CATMProcTaskManagerCGM
        ListPOfCATBody BodyList;
        int Scheduled;
        int Completed;

    public:

        virtual CATMProcTaskContainerCGM* NextTask(CATMProcProcessDataCGM*& ioProcessData)

        {
public:
virtual CATMProcTaskContainerCGM* NextTask(CATMProcProcessDataCGM*& ioProcessData)
            if (Scheduled < BodyList.Size())
              return new CustomTask(BodyList[++Scheduled]);
            else
              return NULL;

        }

return new CustomTask(BodyList[++Scheduled]);
else
return NULL;
        virtual HRESULT EndTask(CATMProcTaskContainerCGM* iTask, CATMProcProcessDataCGM* iProcessData)

        {
return NULL;
virtual HRESULT EndTask(CATMProcTaskContainerCGM* iTask, CATMProcProcessDataCGM* iProcessData)
            CustomTask* Task = (CustomTask*)iTask;
            Render( Task->GetTessData());
            delete Task;

            ++Completed; // Increment our counter of completed tasks.
CustomTask* Task = (CustomTask*)iTask;
Render( Task->GetTessData());
delete Task;
            return S_OK;

        }
    };

---

The individual tasks are defined in a custom class derived from CATMProcTaskContainerCGM. This class contains all the operational data, the inputs and outputs, and the operational task to be performed in the virtual Run method. In this example, the input is the body to tessellate and the output is the tessellation data.

The individual tasks are defined in a custom class derived from CATMProcTaskContainerCGM. This class contains all the operational data, the inputs and outputs, and the operational task to be performed in the virtual Run method. In this example, the input is the body to tessellate and the output is the tessellation data.
The derived class must also implement four methods needed to stream the operational data for inter-process communication. The inputs are streamed on the master side with StreamInput and un-streamed on the slave side with UnstreamInput. The outputs (results) are streamed on the slave side with StreamOutput and un-streamed on the master with UnstreamOutput. The streaming is necessary to place the data into a contiguous buffer. The buffer is then transferred between processes.

In our example we use the CGM functions WriteGeometry to stream the body and ReadGeometry to un-stream the body. We also use the CATCGMStream methods WriteBoolean and ReadBoolean to indicate whether or not we have streamed tessellation data. The CATCGMStream class has a rich set of methods to stream all types of data. The Functions used in the example to stream and un-stream tessellation data do not exist as such in CGM. They are simplifications, left to be implemented in client code using the CATCGMStream methods.

    class CustomTask : public CATMProcTaskContainerCGM

    {
In our example we use the CGM functions WriteGeometry to stream the body and ReadGeometry to un-stream the body. We also use the CATCGMStream methods WriteBoolean and ReadBoolean to indicate whether or not we have streamed tessellation data. The CATCGMStream class has a rich set of methods to stream all types of data. The Functions used in the example to stream and un-stream tessellation data do not exist as such in CGM. They are simplifications, left to be implemented in client code using the CATCGMStream methods.
class CustomTask : public CATMProcTaskContainerCGM
        CATBody* Body;
        TessData* Data;

    public:

        virtual HRESULT Run()

        {
public:
virtual HRESULT Run()
            Data = Tessellate(Body);
            return S_OK;

        }

Data = Tessellate(Body);
return S_OK;
        virtual HRESULT StreamInput(CATCGMStream& iStream)

        {
return S_OK;
virtual HRESULT StreamInput(CATCGMStream& iStream)
            return WriteGeometry(iStream, Body);

        }

virtual HRESULT StreamInput(CATCGMStream& iStream)
return WriteGeometry(iStream, Body);
        virtual HRESULT UnstreamInput(CATCGMStream& iStream)

        {
return WriteGeometry(iStream, Body);
virtual HRESULT UnstreamInput(CATCGMStream& iStream)
            return ReadGeometry(iStream, Body);

        }

virtual HRESULT UnstreamInput(CATCGMStream& iStream)
return ReadGeometry(iStream, Body);
        virtual HRESULT StreamOutput(CATCGMStream& iStream, HRESULT iResult)

        {
return ReadGeometry(iStream, Body);
virtual HRESULT StreamOutput(CATCGMStream& iStream, HRESULT iResult)
            HRESULT Result = iResult;
```vbscript
            if (Data && Result == S_OK)

```

            {
virtual HRESULT StreamOutput(CATCGMStream& iStream, HRESULT iResult)
HRESULT Result = iResult;
if (Data && Result == S_OK)
                iStream.WriteBoolean(TRUE);
```vbscript
                Result = MyStreamTessellationData(iStream, Data);

```

            }
```vbscript
if (Data && Result == S_OK)
iStream.WriteBoolean(TRUE);
Result = MyStreamTessellationData(iStream, Data);
            else // No tessellation data.
```

            {
iStream.WriteBoolean(TRUE);
Result = MyStreamTessellationData(iStream, Data);
else // No tessellation data.
                iStream.WriteBoolean(FALSE);

            }
else // No tessellation data.
iStream.WriteBoolean(FALSE);
            return Result;

        }

iStream.WriteBoolean(FALSE);
return Result;
        virtual HRESULT UnstreamOutput(CATCGMStream& iStream, HRESULT iResult)

        {
return Result;
virtual HRESULT UnstreamOutput(CATCGMStream& iStream, HRESULT iResult)
            HRESULT Result = iResult;
```vbscript
            if (Result == S_OK)

```

            {
virtual HRESULT UnstreamOutput(CATCGMStream& iStream, HRESULT iResult)
HRESULT Result = iResult;
if (Result == S_OK)
                CATBoolean HaveData = FALSE;
                iStream.ReadBoolean(HaveData);
```vbscript
                if (HaveData)

```

                {
CATBoolean HaveData = FALSE;
iStream.ReadBoolean(HaveData);
if (HaveData)
```vbscript
```vbscript
                    Result = MyUnstreamTessellationData(iStream, Data);			}

```

```

                }
            }
```vbscript
if (HaveData)
```vbscript
Result = MyUnstreamTessellationData(iStream, Data);			}
```

            return Result;
```

        }
    };

---

The four streaming methods are not utilized in the single process case, only when multiple processes are used. This allows a single implementation to be used in both cases, which greatly simplifies the code. A final important method to mention is Release. This purpose of this method is to clean up unnecessary data after the computational task is complete. For example, it is imperative to delete all newly created CGMObjects on slave processes because of potential conflicts with persistent identifiers. CGMObjects streamed to slave processes must retain their identifiers, which would not be possible if the identifiers are already used by other objects. Ideally, only the streamed CGMObjects are retained after the operations are complete, as these are used for stream optimizations.

In summary, adding a simple parallel region with the MProc system requires custom implementations of two classes: CATMProcTaskMangerCGM and CATMProcTaskContainerCGM. The NextTask and EndTask methods are required in the former - and the Run, Release, and four streaming methods are required in the later. The rest is handled by the MProc system.
### Asynchronous Multiprocessing

The four streaming methods are not utilized in the single process case, only when multiple processes are used. This allows a single implementation to be used in both cases, which greatly simplifies the code. A final important method to mention is Release. This purpose of this method is to clean up unnecessary data after the computational task is complete. For example, it is imperative to delete all newly created CGMObjects on slave processes because of potential conflicts with persistent identifiers. CGMObjects streamed to slave processes must retain their identifiers, which would not be possible if the identifiers are already used by other objects. Ideally, only the streamed CGMObjects are retained after the operations are complete, as these are used for stream optimizations.
In summary, adding a simple parallel region with the MProc system requires custom implementations of two classes: CATMProcTaskMangerCGM and CATMProcTaskContainerCGM. The NextTask and EndTask methods are required in the former - and the Run, Release, and four streaming methods are required in the later. The rest is handled by the MProc system.
In some cases it may be beneficial to compute operations in the background, giving priority to the task running in the foreground. Here tasks are scheduled asynchronously, and results collected when needed. With very few changes, we can modify our tessellation example to run asynchronously. This for example, will allow the end-user to interact fluidly with the application while the tessellation is computed in the background. Instead of calling the Run method we call the base class StartAsyncTasks and EndAsyncTasks methods respectively. Nothing else needs to be changed.

The behavior of these methods is not as straightforward as the Run method. The StartAsyncTasks method will continue to call NextTask until no more tasks exist (until it returns NULL). During this scheduling phase, EndTask may be called to complete tasks. It will also block when all processors are busy and more tasks remain. In blocking, it waits for processes to complete tasks so that more can be scheduled. The EndAsyncTasks method will block until all tasks are complete. This default use is best suited for scenarios with few tasks, to avoid excessive blocking.

    CustomTessellator MyTessellator(BodyList);
    MyTessellator.StartAsyncTasks();

    // Do something else ...
The behavior of these methods is not as straightforward as the Run method. The StartAsyncTasks method will continue to call NextTask until no more tasks exist (until it returns NULL). During this scheduling phase, EndTask may be called to complete tasks. It will also block when all processors are busy and more tasks remain. In blocking, it waits for processes to complete tasks so that more can be scheduled. The EndAsyncTasks method will block until all tasks are complete. This default use is best suited for scenarios with few tasks, to avoid excessive blocking.
CustomTessellator MyTessellator(BodyList);
MyTessellator.StartAsyncTasks();
    MyTessellator.EndAsyncTasks();

---

MyTessellator.EndAsyncTasks();
With a slightly more complex implementation it is possible to avoid blocking. Both StartAsyncTasks and EndAsyncTasks take an optional “no block” argument. When set, StartAsyncTasks returns when no slave processes are available to accept tasks. In this mode, StartAsyncTasks may have to be called more than once to get all tasks scheduled. Similarly, EndAsyncTasks returns when no completed tasks are available to be received, also leaving it to be called more than once in some cases. Note, calling StartAsyncTasks after calling EndAsyncTasks is not supported, since the parallel transaction is automatically terminated once EndAsyncTasks has been called and all scheduled tasks complete.

    CustomTessellator MyTessellator(BodyList);
```vbscript
    while (MyTessellator.HasTasks()) /* Scheduled < BodyList.Size() */

```

    {
With a slightly more complex implementation it is possible to avoid blocking. Both StartAsyncTasks and EndAsyncTasks take an optional “no block” argument. When set, StartAsyncTasks returns when no slave processes are available to accept tasks. In this mode, StartAsyncTasks may have to be called more than once to get all tasks scheduled. Similarly, EndAsyncTasks returns when no completed tasks are available to be received, also leaving it to be called more than once in some cases. Note, calling StartAsyncTasks after calling EndAsyncTasks is not supported, since the parallel transaction is automatically terminated once EndAsyncTasks has been called and all scheduled tasks complete.
CustomTessellator MyTessellator(BodyList);
while (MyTessellator.HasTasks()) /* Scheduled < BodyList.Size() */
        MyTessellator.StartAsyncTasks();

        // Do something else ...
    }
    ...
MyTessellator.StartAsyncTasks();
```vbscript
    while (MyTessellator.NotComplete()) /* Completed < BodyList.Size() */

```

    {
        MyTessellator.EndAsyncTasks();
        // Do something else ...
    }

---
### Sequential Tasks

In some scenarios it makes sense to schedule certain tasks on the master process instead of on a slave process. These tasks may be simple and quick to compute, and not warrant the overhead of streaming the computational data to and from slave processes. As an example, tessellating analytic bodies is very fast. The streaming overhead might be less efficient. These can be computed on the master, while more complex shapes are scheduled on slave processes.

In some scenarios it makes sense to schedule certain tasks on the master process instead of on a slave process. These tasks may be simple and quick to compute, and not warrant the overhead of streaming the computational data to and from slave processes. As an example, tessellating analytic bodies is very fast. The streaming overhead might be less efficient. These can be computed on the master, while more complex shapes are scheduled on slave processes.
Sequential operations in the master process can be scheduled by setting the appropriate values in the optional task manager method IsNextTaskSequential. Specifically, setting the output argument oIsSequential to true will result in the operator being run on the master process. When implementing this method, it is essential to set the output argument oNextTaskExists correctly, whether or not the operator is sequential, as this may release slave processes for the remainder of the parallel transaction. The remaining arguments are described in the reference material.

The ability to schedule tasks sequentially in our tessellator example is added by implementing the IsNextTaskSequential and by setting oIsSequential when the next body to tessellate is “simple”. In the example code we call IsSimple, which is not CGM functionality. This must be implemented by the client.

    class CustomTessellator : public CATMProcTaskManagerCGM

    {
The ability to schedule tasks sequentially in our tessellator example is added by implementing the IsNextTaskSequential and by setting oIsSequential when the next body to tessellate is “simple”. In the example code we call IsSimple, which is not CGM functionality. This must be implemented by the client.
class CustomTessellator : public CATMProcTaskManagerCGM
        ListPOfCATBody BodyList;
        int Scheduled;
        int Completed;

    public:

        virtual HRESULT IsNextTaskSequential(
            CATMProcProcessDataCGM* iParallelProcessData,
            CATMProcProcessDataCGM* iSequentialProcessData,
            CATBoolean&             oIsSequential,
            CATBoolean&             oNextTaskExists)

        {
CATMProcProcessDataCGM* iParallelProcessData,
CATMProcProcessDataCGM* iSequentialProcessData,
CATBoolean&             oIsSequential,
CATBoolean&             oNextTaskExists)
```vbscript
            if (Scheduled < BodyList.Size())

```

            {
CATBoolean&             oIsSequential,
CATBoolean&             oNextTaskExists)
if (Scheduled < BodyList.Size())
                oNextTaskExists = TRUE;
                CATBody* Body = BodyList[Scheduled];
                if ( IsSimple(Body) )
                    oIsSequential = TRUE;

             }
        }

```vbscript
if ( IsSimple(Body) )
oIsSequential = TRUE;
        virtual CATMProcTaskContainerCGM* NextTask(CATMProcProcessDataCGM*& ioProcessData)
```

        {
virtual CATMProcTaskContainerCGM* NextTask(CATMProcProcessDataCGM*& ioProcessData)
            if (Scheduled < BodyList.Size())
                return new CustomTask(BodyList[Scheduled++]);
            else
                return NULL;

        }

return new CustomTask(BodyList[Scheduled++]);
else
return NULL;
        virtual HRESULT EndTask(CATMProcTaskContainerCGM* iTask, CATMProcProcessDataCGM* iProcessData)

        {
return NULL;
virtual HRESULT EndTask(CATMProcTaskContainerCGM* iTask, CATMProcProcessDataCGM* iProcessData)
            CustomTask* Task = (CustomTask*)iTask;
            Render( Task->GetTessData());
            delete Task;

            ++Completed; // Increment our counter of completed tasks.
CustomTask* Task = (CustomTask*)iTask;
Render( Task->GetTessData());
delete Task;
            return S_OK;

        }
    };

---
### Object Relationships

The MProc system requires the relationships between the task managers and task containers be stated explicitly. This information is used by slave processes to instantiate the appropriate derived class objects. Use the CATMProcRelationCGM macro to associate the custom CATMProcTaskManagerCGM class with the custom CATMProcTaskContainerCGM class. The named relationship is needed by the CATMProcTaskManagerCGM constructor and is passed on to slave processes.

The MProc system requires the relationships between the task managers and task containers be stated explicitly. This information is used by slave processes to instantiate the appropriate derived class objects. Use the CATMProcRelationCGM macro to associate the custom CATMProcTaskManagerCGM class with the custom CATMProcTaskContainerCGM class. The named relationship is needed by the CATMProcTaskManagerCGM constructor and is passed on to slave processes.
The macro, among other things, defines exported functions that instantiate the custom classes. The first argument is simply a name used as an identifier. It must begin with "CATMProcRelationCGM" in order to distinguish it from legacy implementations. Also, it should be unique in order to avoid duplicates. The second argument is the name of the custom task manager, the third the name of the custom task container.

    CATMProcRelationCGM( CATMProcRelationCGMTessellator, CustomTessellator, CustomTask);

---
### Task Manager Construction

```vbscript
CATMProcRelationCGM( CATMProcRelationCGMTessellator, CustomTessellator, CustomTask);
Custom task managers derive from CATMProcTaskManagerCGM. The base class has mandatory construction arguments. The first is the name of the custom CATMProcRelationCGM, the second is the name of the library that contains the custom implementation. The third argument is the current factory. The library name is needed by the slave processes in order to load the exported functions that instantiate the custom classes.

To correct our example, we add the appropriate use of the CATMProcRelationCGM macro and additional arguments to the task manager constructor.

    CATMProcRelationCGM( CATMProcRelationCGMTessellator, CustomTessellator, CustomTask);

    CustomTessellator MyTessellator(“CATMProcRelationCGMTessellator”,”MyDll”, Factory, BodyList);

```

---
### Stream Optimizations

The MProc system has a built-in optimization that avoids duplicate inter-process transmissions of fundamental CGM objects. A model and its supporting structures, having been sent once to a process, will not be sent again in subsequent communications. This can significantly reduce the overhead of sending data to slave processes. All objects streamed with the WriteGeometry functions participate in this optimization.
### Process Specific Data

Process specific data is optionally attached to slaves in the NextTask method using custom derived CATMProcProcessDataCGM implementations. For each slave process utilized, the pointer to the argument passed to the NextTask method will originally be NULL. Here the custom implementation can attach a derived object by setting the pointer appropriately. The specific processes can then be identified by querying the passed in pointer. This provides the ability to customize tasks for specific processes. Custom implementations must use standard new to create these objects, since they are automatically deleted by the MProc system at the end of the parallel transactions.
### Enabling Multiprocessing

Process specific data is optionally attached to slaves in the NextTask method using custom derived CATMProcProcessDataCGM implementations. For each slave process utilized, the pointer to the argument passed to the NextTask method will originally be NULL. Here the custom implementation can attach a derived object by setting the pointer appropriately. The specific processes can then be identified by querying the passed in pointer. This provides the ability to customize tasks for specific processes. Custom implementations must use standard new to create these objects, since they are automatically deleted by the MProc system at the end of the parallel transactions.
Ideally, one would either enable or disable multiprocessing only once during the lifetime of an application, based upon end-user input. Applications that support multiprocessing typically expose some means of selecting the number of processors to use on a given system. The selection can then be set in the MProc system with the static function **CATMProcSystem::EnableMProc**.

Calling this function will by default enable the use of all available processes. Specifying a 1 through the optional number-of-processes-to-use argument, disables multiprocessing altogether. Specifying a positive value greater than one will result in the use of that many processes, maxing out at the number of physically available processors. Since this is a global setting, it affects all parallel regions. Turning it on, in other words, enables all parallel regions to utilize multiple processes when possible.

The state of the MProc system can be changed at any time, except during parallel operations. For example, the end-user might chose to use fewer processors at some point in the lifecycle of the application. This can easily be accommodated by calling **CATMProcSystem::EnableMProc** appropriately. The change will affect all subsequent parallel transactions.

It should be noted that the MProc system does **not** support nested parallelism. Parallel regions encountered within an already active parallel region, will not have access to additional proceses and will run sequentially.

### Resource Utilization

The state of the MProc system can be changed at any time, except during parallel operations. For example, the end-user might chose to use fewer processors at some point in the lifecycle of the application. This can easily be accommodated by calling **CATMProcSystem::EnableMProc** appropriately. The change will affect all subsequent parallel transactions.
It should be noted that the MProc system does **not** support nested parallelism. Parallel regions encountered within an already active parallel region, will not have access to additional proceses and will run sequentially.
Client implementations can customize the number of processes to use in the parallel transaction by setting a minimum and/or maximum value in their derived task manager class. This should be used at the client code level, where it's possible to define an optimal number of processes to be used for a given computation, regardless of the number of physically available processors.

Setting a minimum value makes sense when multiprocessing is viable only when a certain number of processors are available. Setting a maximum value makes sense when an algorithm scales poorly past a certain number of processors. Note, the parallel transaction will fail and the Run method will return the failure, when the minimum number of requested processors cannot be acquired.

Asynchronous multiprocessing implies a minimum number of processes to use of 1. As a consequence, **StartAsyncTasks** will fail when an additional processor is not available. Otherwise, the effects of setting minimum and maximum values is the same as synchronous multiprocessing.

To show this in an example, we can update our tessellator case to use a minimum of two and a maximum of four slave processes.

    CustomTessellator MyTessellator(“CATMProcRelationCGMTessellator”,”MyDll”, Factory, BodyList);
    MyTessellator.SetMinNbProcessesToUse(2); // Use at least two
    MyTessellator.SetMaxNbProcessesToUse(4); //  at most four.
    MyTessellator.Run();

---
### Debugging Techniques

Debugging operations that run on different processes can be challenging. To help make this easier and to help assure a correct implementation, the MProc systems provides an operational mode called MonoProcMode. Running parallel transactions with this mode enabled causes all operations that normally execute on slave processes to be exercised on the master process. This provides a straightforward debugging technique to help verify proper implementations. Enable MonoProcMode with the static method **CATMProcSystem::EnableMonoProcMode**. Once enabled, this mode cannot be disabled in the current session.
### In Short

    * Use the MProc system to speed up compute intensive operations with concurrent operations on multiple processes.
    * Compute tasks in the background with asynchronous multiprocessing.
    * Take advantage of stream optimizations to avoid the overhead of inter-process communication.
    * Schedule tasks additionally on the master process to optimize efficiency.
### History

Version: **1** [Oct 2011] | Document created
---|---
