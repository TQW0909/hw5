

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

// Helper function
bool schedule(
	int n,
	int d,
	vector<unsigned int>& remaining,
	const AvailabilityMatrix& avail,
	const size_t dailyNeed,
	DailySchedule& sched
);

// Checking if woker can be place in given location
bool isValid(
	int n,
	int d,
	vector<unsigned int>& remaining,
	const AvailabilityMatrix& avail);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
	if(avail.size() == 0U){
			return false;
	}
	sched.clear();
	// Add your code below

	// Creating a vector that contains the number of remaining shifts for each k workers
	vector<unsigned int> remaining;
	for (Worker_T i = 0; i < avail[0].size(); i++)
	{
		remaining.push_back(maxShifts);
	}

	// Initializing sched
	for (Worker_T i = 0; i < avail.size(); i++)
	{
		vector<Worker_T> temp;
		for (Worker_T j = 0; j < dailyNeed; j++)
		{
			temp.push_back(INVALID_ID);
		}
		sched.push_back(temp);
	}

	return schedule(0, 0, remaining, avail, dailyNeed, sched);

}

// Helper
bool schedule(
	int n,
	int d,
	vector<unsigned int>& remaining,
	const AvailabilityMatrix& avail,
	const size_t dailyNeed,
	DailySchedule& sched
)
{
	// Base case
	if (n == int(avail.size()))
	{
		return true;
	}

	for (Worker_T i = 0; i < avail[0].size(); i++) // Tying every worker
	{
		sched[n][d] = i;

		if (isValid(n, i, remaining, avail))
		{
			// Recurse
			if (d == int(dailyNeed) - 1) // Reached the end of the row
			{
				if (schedule(n + 1, 0, remaining, avail, dailyNeed, sched) == true)
				{
					return true;
				}
			}
			else
			{
				if (schedule(n, d + 1, remaining, avail, dailyNeed, sched) == true)
				{
					return true;
				}
			}
			remaining[d]++; // Undoing changes (done in isValid)
		}
	}

	return false;
}


bool isValid(
	int n,
	int d,
	vector<unsigned int>& remaining,
	const AvailabilityMatrix& avail)
{
	// Check 1: worker is avaible on the given day
	if (avail[n][d])
	{
		// Check 2: worker has not exceeded maxShifts
		if (remaining[d] > 0)
		{
			remaining[d]--;
			return true;
		}
	}
	return false;

}
