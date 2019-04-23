/***************************************************************************
 *
 *  Sorting algorithms and counting work - Merge sort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented mergesort
 *
 */

#ifndef __INSTRUMENTED_MS_H
#define __INSTRUMENTED_MS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;

void merge(vector<int> & a, SortStats & stats, int left, int right, int rightEnd){
	int leftEnd = right -1;
	int tempI = left;
	int elements = rightEnd - left + 1;
	// int i = 0, j = 0, k = 1;
	// int l = right - left + 1;
	// int r = rightEnd - right;
	// vector<int> leftV;
	// vector<int> rightV;

	// for (i = 0; i < l; i++){
	// 	leftV[i] = a[l+i];
	// }
	// for (j = 0; j < r; j++){
	// 	rightV[j] = a[right + 1 + j];
	// }
	// i = 0;
	// j = 0;

	// while (i < l && j < r){
	// 	if (++stats.compares && leftV[i] <= rightV[j]){
	// 		a[k] = leftV[i];
	// 		i++;
	// 		++stats.moves;
	// 	}
	// 	else {
	// 		a[k] = rightV[j];
	// 		j++;
	// 		++stats.moves;
	// 	}
	// 	k++;
	// }

	// while (i < l){
	// 	a[k] = leftV[i];
	// 	i++;
	// 	k++;
	// 	++stats.moves;
	// }
	
	// while (j < r){
	// 	a[k] = rightV[j];
	// 	j++;
	// 	k++;
	// 	++stats.moves;
	// }
	vector<int> temp(a.size());
	while (left <= leftEnd && right <= rightEnd){
		if (++stats.compares && a[left] <= a[right]){
			temp[tempI++] = std::move(a[left++]);
		}
		else {
			temp[tempI++] = std::move(a[right++]);

		}
		
	}
	while (left <= leftEnd){
		temp[tempI++] = std::move(a[left++]);

	}
	while (right <= rightEnd){
		temp[tempI++] = std::move(a[right++]);

	}
	for(int it = 0; it < elements; ++it, --rightEnd){
		a[rightEnd] = std::move(temp[rightEnd]);
		stats.moves++;

	}
	
}

void mergeSort(vector<int> & a, SortStats & stats, int left, int right){
	if (left < right){
		int center = (left + right)/2;
		//int center = left + (right-1)/2;
		mergeSort(a, stats, left, center);
		mergeSort(a, stats, center+1, right);
		merge(a, stats, left, center+1, right);
	}
}

void instrumentedMergeSort( vector<int> & a, SortStats & stats )
{
    clock_t time_begin = clock();		// Please leave in place for stats

	// Begin sorting algorithm

	// Begin your merge sort code here
	// You're free to add more functions if you like, but vector<int> a must be sorted when done
	// NOTE: you must update stats with comparisons and moves as your algorithm runs
	//  The best example of updating the stats is available in the file:
	//  instrumentedBubbleSort.h

	//Using your stuff to help get started. 
	mergeSort(a, stats, 0, a.size()-1);

	// End sorting algorithm

    clock_t time_end = clock();			// Please leave in place for stats
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}


#endif
