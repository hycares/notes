#include <bits/stdc++.h>
using namespace std;

class LRUCache {
    using lp = list<pair<int, int>>;
    lp linklist;
    unordered_map<int, lp::iterator> hashtable;
    int caps;
public:
    LRUCache(int capacity) : caps(capacity){

    }
    
    int get(int key) {
        auto it = hashtable.find(key);
        if (it == hashtable.end()) return -1;
        else {
            // move to the front
            linklist.splice(linklist.begin(), linklist, it->second);
            return it->second->second;
        }
    }
    
    void put(int key, int value) {
        // refresh
        auto it = hashtable.find(key);
        if (it != hashtable.end()) {
            linklist.splice(linklist.begin(), linklist, it->second);
            it->second->second = value;
            return;
        }
        // out of capacity
        linklist.emplace_front(key, value);
        hashtable[key] = linklist.begin();
        if (hashtable.size() > caps) {
            hashtable.erase(linklist.back().first);
            linklist.pop_back();
        }
    }
};