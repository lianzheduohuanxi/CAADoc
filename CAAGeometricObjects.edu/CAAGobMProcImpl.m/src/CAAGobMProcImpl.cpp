//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
// Sample code for : The MProc System
// Mission         : Show how to implement a simple parallel operation
// Overview        : This example demonstrates all the pieces needed to 
//                   implement a parallel operation, in this case
//                   to calculate the number of primes found within a user
//                   specified range using a specified number of processes.
//
// Type            : Batch program
// Inputs          : an end range of values to check for primality
//                 : the number of processes to use
// Outputs         : Return Codes 
//                   0 = OK
//                   1 = FAIL
//
// Illustrates:
//					1- A custom task manager called PrimesManager
//					2- A custom task container called PrimesTask
//					3- Even work distribution
//					4- Specifying the number of processes to use
//					5- Enable multiprocessing with CATMProcEnable
//					6- Run the parallel transaction
//					7- Aggregating results
//					8- Clean up and exit
//
// How to run it   : CAAGobMProcMain [range] [number of processes to use]
//=============================================================================

#include <stdio.h>
#include <time.h>
#include <math.h>

#include "CAAGobMProcImpl.h"

#include "CATIACGMLevel.h"
#ifdef CATIACGMV5R23

#include "CATBoolean.h"
#include "CATMProcSystem.h"
#include "CATMProcTaskManagerCGM.h"
#include "CATMProcTaskContainerCGM.h"

//
// Basic function to test for primality.
//
static CATBoolean IsPrime( unsigned int n) 
{
	if( n == 2)
		return TRUE;
	if( (n == 1) || (n % 2) == 0 )
		return FALSE;
    unsigned int iters = (unsigned int)sqrt( (double)n);    
    for( unsigned int i = 3; i <= iters; i+=2 )
		if( n % i == 0 )
			return FALSE;
    return TRUE;
}

//
// The task container derived from the base class.
// 
class PrimesTask : public CATMProcTaskContainerCGM
{
	CATULONG32 Start;	// The first number of the range.
	CATULONG32 Stop;	// The last number of the range.
	CATULONG32 Primes;	// The number of primes found.

public:
 
	// Default constructor to initialize all member data.
	PrimesTask() : Start(0), Stop(0), Primes(0) {}
	
	// Overloaded constructor.
	PrimesTask( unsigned int iStart, unsigned int iStop) : Start(iStart), Stop(iStop), Primes(0) {}

	// Method to retrieve the results.
	unsigned int GetPrimes() const { return Primes; }

	// Required method to run the task.
	virtual HRESULT Run()
    {
		// Iterate through the range.
		for (unsigned int i = Start; i <= Stop; ++i)
		{
			if ( IsPrime(i) )
			{
				++Primes; // Record the results.
			}
		}
        return S_OK;
    }

	// Required method to write the inputs to a buffer.
	virtual HRESULT StreamInput(CATCGMStream& iStream)
    {
		iStream.WriteULong(Start);
		iStream.WriteULong(Stop);
		return S_OK;
    }
 
	// Required method to read the inputs from a buffer.
	virtual HRESULT UnstreamInput(CATCGMStream& iStream)
    {
		// Read the inputs from the buffer.
		iStream.ReadULong(Start);
		iStream.ReadULong(Stop);
		return S_OK;
	}
 
	// Required method to write the results to a buffer.
	virtual HRESULT StreamOutput( CATCGMStream& iStream, HRESULT iResult)
    {
        HRESULT Result = iResult;
		// If the result of the operation was okay, write the result.
        if (Result == S_OK)
        {
			iStream.WriteULong( Primes);
        }
        return Result;
	}
 
	// Required method to read the results from a buffer.
	virtual HRESULT UnstreamOutput( CATCGMStream& iStream, HRESULT iResult)
    {
		// Read the result.
        HRESULT Result = iResult;
		// If the result of the operation was okay, write the result.
        if (Result == S_OK)
        {
			iStream.ReadULong( Primes);
        }
        return Result;
	}
};

//
// The task manager derived from the base class.
// 
class PrimesManager : public CATMProcTaskManagerCGM
{
	unsigned int Range;		// The specified range of numbers to test.
	unsigned int Processes;	// The number of processes to use.
	unsigned int Chunk;		// The size of the range for each process.
	unsigned int Remainder;	// To distribute the range correctly.
	unsigned int Scheduled;	// Keep track of what's been scheduled.
	unsigned int Primes;	// The number of primes found.

public:

	// The main constructor, with arguments to properly construct the base class.
	PrimesManager( const char* iRelation, const char* iLibrary, unsigned int iRange, unsigned int iProcesses)
		: Range(iRange), Chunk(iRange), Scheduled(0), Primes(0), Processes(iProcesses), Remainder(0),
			CATMProcTaskManagerCGM( iRelation, iLibrary, NULL)
	{
		// Divide the work amongst available processes.
		if (Processes > 1)
		{
			Chunk = Range / Processes;
			Remainder = Range % Processes;
		}
	}

	// Method to retrieve the results.
	unsigned int GetResult() const { return Primes; }

	// Required method to create the next task.
    virtual CATMProcTaskContainerCGM* NextTask( CATMProcProcessDataCGM*& ioProcessData)
    {
		PrimesTask* Task = NULL;
        if (Scheduled < Range)  // if work remains ...
		{
			unsigned int Start = Scheduled + 1;		// Start at next number.
			unsigned int Stop = Scheduled + Chunk;	// Add the chunk size.
			if (Remainder)
			{
				--Remainder;	// Distribute the remainder evenly.
				++Stop;	
			}
			Task = new PrimesTask( Start, Stop);
			Scheduled = Stop;	// Remember what's been handed out.
		}
        return Task;
    }
 
	// Required method to process the results of a completed operation.
	// This method should delete the task object after processing.
    virtual HRESULT EndTask(CATMProcTaskContainerCGM* iTask, CATMProcProcessDataCGM* iProcessData)
    {
		PrimesTask* Task = (PrimesTask*)iTask;
        Primes += Task->GetPrimes(); // Aggregate the results.
        delete Task;
		return S_OK;
    }
};

//
// State the relationship between the task manager and task container
//  with the CATMProcRealtionCGM macro. This provides the information
//  needed by the MProc system to instantiate the appropriate class objects.
//
CATMProcRelationCGM( CATMProcRelationCGMPrimes, PrimesManager, PrimesTask);
#endif
 
//
// The entry point for this example.
// The optional input arguments are: 
//  1) a positive value specifying the range of numbers to test for primes
//  2) a positive value specifying the number of processes to use
//
int CustomGobMProcExample( int argc, char** argv)
{
#ifdef CATIACGMV5R23
	HRESULT Result = E_FAIL;
	unsigned int Range = 0x0000FFFF;	// Select a modest default range.
	unsigned int Processes = 0;			// Use all available processors.
	
	if (argc > 1) 
	{
		Range = atoi(argv[1]);		// Get the user specified range.
	}

	if (argc > 2)
	{
		Processes = atoi(argv[2]);	// Get the user specified process count.
	}

	if (Processes != 1)  // One means disable multiprocessing.
	{
		unsigned int Processors = CATMProcSystem::NumberPhysicalProcessors();
		if (Processes == 0 || Processes > Processors)
		{
			Processes = Processors;	// Make sure the number is within range.
		}
	}

	if (Range && Processes)
	{
		// Enable multiprocessing.
		CATMProcSystem::EnableMProc(Processes);

		// Construct the example task manager.
		PrimesManager MyPrimesManager("CATMProcRelationCGMPrimes","CAAGobMProcImpl", Range, Processes);

		clock_t Start = clock();

		// Run the parallel transaction.
		Result = MyPrimesManager.Run();

		clock_t Stop = clock();

		// Process the results.
		if (Result == S_OK)
		{
			printf( "Found %d primes between 1 and %d in %d milliseconds using %d processes.\n", 
				MyPrimesManager.GetResult(), Range, Stop - Start, Processes);
		}
	}
	else
	{
		printf( "Error: Invalid arguments.\n");
	}

	return Result == S_OK ? 0 : 1;
#else
        return 0;
#endif
}
