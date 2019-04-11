/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - inherits from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
private:
    int _count;
    vector<list<pair<K,V>>> * _table;
    //vector<list<V>> * _table;

public:
    ChainingHash(int n = 11) {
        _count = 0;
        //pair<K,V> p(0, 0);
        list<pair<K,V>> l;
        // p.first = 0;
        // p.second = 0;
        _table = new vector<list<pair<K,V>>>;
        _table->resize(n, l);
        //_table = new vector<list<V>>(n, list<V>(0));
    }

    ~ChainingHash() {
        //this->clear();
        delete _table;
        _count = 0;
    }

    bool empty() {
        bool empty = false;
        if (_count <= 0){
            empty = true;
        }
        return empty;
    }

    int size() {
        return _count;
    }

    V& at(const K& key) {
        for (auto it = _table->at(hash(key)).begin(); it != _table->at(hash(key)).end(); it++){
            if(it->first == key) {
                return it->second;
            }
        }
        throw std::out_of_range("Key not in hash");
        
    }

    V& operator[](const K& key) {
        return this->at(key);
    }

    int count(const K& key) {
        int count = 0;
        for (auto it = _table->at(hash(key)).begin(); it != _table->at(hash(key)).end(); it++){
            if(it->first == key) {
                ++count;
            }
        }
        return count;
    }

    void emplace(K key, V value) {
        pair<K,V> pair(key, value);
        insert(pair);
    }

    void insert(const std::pair<K, V>& pair) {
        int hashKey = hash(pair.first);
        if (load_factor() > 1.0){
            rehash();
        }
        // if (_table[hashKey].empty()){
        //     //_table[hashKey].insert(pair.second);
        //     list<V> value(pair.second);
        //     _table->insert(_table->begin() + hashKey, value);
        // } 
        // else {
        //     _table->at(hashKey).push_back(pair.second); 
        // }
        this->erase(pair.first);
        ++_count;
        _table->at(hashKey).push_front(pair); 

        //Concept: _table[hash(pair.first)] = pair.second;
        //check for rehash
    }

    void erase(const K& key) {
        for (auto it = _table->at(hash(key)).begin(); it != _table->at(hash(key)).end(); it++){
            if(it->first == key) {
                it = _table->at(hash(key)).erase(it);
                _count--;             
            }
        }
    }

    void clear() {
        int tableSize = _table->capacity();
        delete _table;
        //_table = new vector<list<pair<K,V>>>(tableSize);
        _table = new vector<list<pair<K,V>>>(tableSize);
        _count = 0;
    }

    int bucket_count() {
        return _table->capacity();
    }

    int bucket_size(int n) {
       return _table->at(n).size();
    }

    int bucket(const K& key) {
        int hashKey = hash(key);
        if (hashKey > _table->capacity()) {
            throw std::out_of_range("Key not in hash");
        } 
        else {
            return hashKey;
        }
    }

    float load_factor() {
        return (float)_count/(float)_table->capacity();
    }

    void rehash() {
        list<pair<K,V>> l;
        vector<list<pair<K,V>>> v = std::move(*_table);
        _table->resize(findNextPrime(_table->capacity()), l);
        for (int i = 0; i < v.capacity(); i++){
            while(v[i].empty() == false){
                _count--;
                insert(v[i].front());
                v[i].pop_front();
            }
        }
    }

    void rehash(int n) {
        //_table->resize(findNextPrime(n));
        list<pair<K,V>> l;
        vector<list<pair<K,V>>> v = std::move(*_table);
        _table->resize(findNextPrime(n), l);
        for (int i = 0; i < v.capacity(); i++){
            while(v[i].empty() == false){
                _count--;
                insert(v[i].front());
                v[i].pop_front();
            }
        }
    }


private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) {
        return (key % _table->capacity());
    }

};

#endif //__CHAINING_HASH_H
