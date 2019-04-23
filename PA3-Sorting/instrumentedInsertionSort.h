/***************************************************************************
 *
 *  Sorting algorithms and counting work - Insertion sort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented insertionsort
 *
 */

#ifndef __INSTRUMENTED_IS_H
#define __INSTRUMENTED_IS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;

void instrumentedInsertionSort( vector<int> & a, SortStats & stats )
{
	clock_t time_begin = clock();			// Please leave this in for timing stats

	// Begin sorting algorithm

	// Begin your insertion sort code here
	// You're free to add more functions if you like, but vector<int> a must be sorted when done
	// NOTE: you must update stats with comparisons and moves as your algorithm runs
	//  The best example of updating the stats is available in the file:
	//  instrumentedBubbleSort.h

	//Using your stuff to help get started. 
	bool swap = true;
	while(swap){
		swap = false;
		int j = 0;
		for (int i = 1; i < a.size(); i++){
			auto temp = std::move(a[i]);
			for (j = i; j > 0 && temp < a[j - 1]; j--){
				if ( ++stats.compares ){
					stats.moves++;
					a[j] = std::move(a[j-1]);
					swap = true;
				}
			}
			a[j] = std::move(temp);
		}
	}


	// End sorting algorithm


	clock_t time_end = clock();				// Please leave this in for timing stats
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}

#endif
