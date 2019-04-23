/***************************************************************************
 *
 *  Sorting algorithms and counting work - Quicksort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented quicksort
 *
 */

#ifndef __INSTRUMENTED_QS_H
#define __INSTRUMENTED_QS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;
int part(vector<int> &a, SortStats &stats, int low, int high){
	//Lets Try Lomuto!
	int pivot = a[high];
	int i = low -1;
	int j;
	for (j = low; j <= high -1; j++){
		if (++stats.compares && a[j] <= pivot){
			i++;
			swap(a[i], a[j]);
			++stats.moves;
		}
	}
	swap(a[i+1], a[high]);
	++stats.moves;
	return (i+1);
	// algorithm partition(A, lo, hi) is
    // pivot := A[hi]
    // i := lo
    // for j := lo to hi - 1 do
    //     if A[j] < pivot then
    //         swap A[i] with A[j]
    //         i := i + 1
    // swap A[i] with A[hi]
    // return i
}

void quickSort(vector<int> &a, SortStats &stats, int low, int high){
	//Lets try Lomuto!
	if (low < high){
		int p = part(a, stats, low, high);
		quickSort(a, stats, low, p-1);
		quickSort(a, stats, p+1, high);
	}
	// algorithm quicksort(A, lo, hi) is
    // if lo < hi then
    //     p := partition(A, lo, hi)
    //     quicksort(A, lo, p - 1)
    //     quicksort(A, p + 1, hi)
}

void instrumentedQuickSort( vector<int> & a, SortStats & stats )
{
	clock_t time_begin = clock();		// Please leave in place for stats


	// Begin sorting algorithm

	// Begin your quicksort code here
	// You're free to add more functions if you like, but vector<int> a must be sorted when done
	// NOTE: you must update stats with comparisons and moves as your algorithm runs
	//  The best example of updating the stats is available in the file:
	//  instrumentedBubbleSort.h

	quickSort(a, stats, 0, a.size()-1);

	

	// End sorting algorithm


	clock_t time_end = clock();			// Please leave in place for stats
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}

#endif
