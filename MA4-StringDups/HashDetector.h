/*
 *  Brute force detector implementation
 * 
 *  Aaron S. Crandall <acrandal@wsu.edu> - 2019
 * 
 */

#ifndef __HASH_DETECTOR_H
#define __HASH_DETECTOR_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>        // a C++11 STL std::unordered_map is a hash table
using std::vector;
using std::string;
using std::unordered_map;

/*
 *  Function to return a list of the strings appearing more than one time in an input vector
 */
std::vector<std::string> find_duplicates_with_hashtable(std::vector<std::string> & strings) {
    std::vector<std::string> dups;

    // MA TODO: Implement the duplicate finder using a hash table (unordered_map)
    unordered_map<string, int> map;
    int count = 1;
    for (int i = 0; i < strings.size(); i++){
        std::unordered_map<std::string,int>::const_iterator found = map.find(strings[i]);
        if (found == map.end()){
            count = 1;
            map.insert({strings[i], count});
        }
        else {
            map[strings[i]] = count++;
        }
    }
    std::unordered_map<std::string,int>::iterator it;
    for (it = map.begin(); it != map.end(); it++){
        if (it->second > 1){
            dups.insert(dups.begin(), it->first);
        }
    }

    return dups;
    // Note on return here: it's returning to the caller via a move constructor
    // The vector (dups) lives on the stack, but the stored array contents live on the heap
    // When dups is returned, a new vector shall be instantiated using a move constructor
    // The new vector's move constructor is called with dups as the && other object
}




#endif
