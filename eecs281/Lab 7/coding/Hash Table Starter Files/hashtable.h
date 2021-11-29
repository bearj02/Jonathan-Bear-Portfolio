#ifndef HASHTABLE_H
#define HASHTABLE_H

// Project Identifier: 2C4A3C53CD5AD45A7BEA3AE5356A3B1622C9D04B

// INSTRUCTIONS:
// fill out the methods in the class below.

// You may assume that the key and value types can be copied and have default
// constructors.

// You can also assume that the key type has (==) and (!=) methods.

// You may assume that Hasher is a functor type with a
// size_t operator()(const Key&) overload.

// The key/value types aren't guaranteed to support any other operations.

// Do not add, remove, or change any of the class's member variables.
// The num_deleted counter is *optional*. You might find it helpful, but it
// is not required to pass the lab assignment.

// Do not change the Bucket type.

// SUBMISSION INSTRUCTIONS:
// Submit this file, by itself, in a .tar.gz.
// Other files will be ignored.

#include <cstdint>
#include <functional> // where std::hash lives
#include <vector>
#include <cassert> // useful for debugging!
#include <iostream>

// A bucket's status tells you whether it's empty, occupied, 
// or contains a deleted element.
enum class Status : uint8_t {
    Empty,
    Occupied,
    Deleted
};

template<typename K, typename V, typename Hasher = std::hash<K>>
class HashTable {
    // used by the autograder; do not change/remove.
    friend class Verifier;
public:
    // A bucket has a status, a key, and a value.
    struct Bucket {
        // Do not modify Bucket.
        Status status = Status::Empty;
        K key;
        V val;
    };

    HashTable() {
        // TODO: a default constructor (possibly empty).

        // You can use the following to avoid implementing rehash_and_grow().
        // However, you will only pass the AG test cases ending in _C.
        // To pass the rest, start with at most 20 buckets and implement rehash_and_grow().
        //    buckets.resize(10000);
        for(int i = 0; i < 10; ++i){
            buckets.push_back(Bucket{});
        }
    }

    size_t size() const {
        return num_elements;
    }

    // returns a reference to the value in the bucket with the key, if it
    // already exists. Otherwise, insert it with a default value, and return
    // a reference to the resulting bucket.
    V& operator[](const K& key) {
        // TODO
        Hasher h;
        int m = (int)buckets.size();
        size_t hash = h(key);
        size_t i = hash % m;
        //std::cout << "hash index: " << i << "\t";
        while(buckets[i].status != Status::Empty){
            if(buckets[i].status != Status::Deleted){
                if(buckets[i].key == key) return buckets[i].val;
            }
            ++i;
            i = i % m;
            if(i == hash % m) break;
        }
        insert(key, V());
        int n = (int)buckets.size();
        i = hash % n;
        while(buckets[i].status == Status::Occupied){
            if(buckets[i].key == key) break;
            ++i;
            i = i % n;
        }
        return buckets[i].val;
    }

    // insert returns whether inserted successfully
    // (if the key already exists in the table, do nothing and return false).
    bool insert(const K& key, const V& val) {
        // TODO
        Hasher h;
        int m = (int)buckets.size();
        size_t hash = h(key);
        size_t i = hash % m;
        //std::cout << "hash index: " << i << "\t";
        int firstghost = -1;
        while(buckets[i].status != Status::Empty){
            if(buckets[i].status == Status::Occupied){
                if(buckets[i].key == key) return false;
            }
            else if(firstghost < 0) firstghost = (int) i;
            ++i;
            i = i % m;
            if(i == hash % m) break;
        }
        Bucket b = Bucket{Status::Occupied,key,val};
        buckets[(firstghost >= 0) ? firstghost : i] = b;
        ++num_elements;
        double load_factor = (double)(num_elements) / m;
        if(load_factor > 0.5) rehash_and_grow();
        return true;
    }
    // erase returns the number of items remove (0 or 1)
    size_t erase(const K& key) {
        // TODO
        Hasher h;
        int m = (int)buckets.size();
        size_t hash = h(key);
        size_t i = hash % m;
        //std::cout << "hash index: " << i << "\t";
        while(buckets[i].status != Status::Empty){
            if(buckets[i].status != Status::Deleted){
                //std::cout << "compared the key for index: " << i << "\n";
                if(buckets[i].key == key){
                    buckets[i].status = Status::Deleted;
                    num_deleted++;
                    num_elements--;
                    return 1;
                }
            }
            ++i;
            i = i % m;
            if(i == hash % m) break;
        }
        return 0;

    }

    void printVector(){
        std::cout << "|";
        for(Bucket b : buckets){
            if(b.status == Status::Empty){
                std::cout << " ___ |";
            }
            if(b.status == Status::Deleted){
                std::cout << " ghost |";
            }
            if(b.status == Status::Occupied){
                std::cout << " " << b.key << ": " << b.val << " |";
            }
        }
        std::cout << "\nVector size: " << buckets.size() << "\n";
    }

private:
    size_t num_elements = 0;
    size_t num_deleted = 0; // OPTIONAL: you don't need to use num_deleted to pass
    std::vector<Bucket> buckets;

    void rehash_and_grow() {
        // You can avoid implementing rehash_and_grow() by calling
        //    buckets.resize(10000);
        // in the constructor. However, you will only pass the AG test cases ending in _C.
        // To pass the rest, start with at most 20 buckets and implement rehash_and_grow().
        
        std::vector<Bucket> newbuckets(2*buckets.size(), Bucket{});
        int m = (int)newbuckets.size();
        Hasher h;
        for(Bucket b : buckets){
            if(b.status == Status::Occupied){
                size_t hash = h(b.key);
                size_t i = hash % m;
                while(newbuckets[i].status == Status::Occupied){
                    ++i;
                    i = i % m;
                }
                newbuckets[i] = b;
            }
        }
        buckets = newbuckets;
    }

    // You can add methods here if you like.
    // TODO
};

#endif // HASHTABLE_H