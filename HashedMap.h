#ifndef HASHED_MAP_
#define HASHED_MAP_

#include <vector>
#include <memory>
#include <string>
#include "HashedEntry.h"

template<class KeyType, class ValueType>
class HashedMap
{
private:
    static const int DEFAULT_CAPACITY = 101;
    std::vector<std::shared_ptr<HashedEntry<KeyType, ValueType>>> hashTable;
    int itemCount;
    int hashTableSize;

    int getHashIndex(const KeyType& key) const;

public:
    HashedMap();
    HashedMap(int tableSize);
    virtual ~HashedMap();

    bool add(const KeyType& key, const ValueType& value);
    bool remove(const KeyType& key);
    bool getValue(const KeyType& key, ValueType& out) const;
    bool contains(const KeyType& key) const;
    bool isEmpty() const;
    int getNumberOfEntries() const;
    void clear();
};

// ========== IMPLEMENTATIONS ==========

// Hash function
template<class KeyType, class ValueType>
int HashedMap<KeyType, ValueType>::getHashIndex(const KeyType& key) const 
{
    int hash = 0;
    for (char ch : key) {
        hash = (hash * 31 + ch) % hashTableSize;
    }
    return hash;
}

// Default constructor
template<class KeyType, class ValueType>
HashedMap<KeyType, ValueType>::HashedMap() 
    : itemCount(0), hashTableSize(DEFAULT_CAPACITY) 
{
    hashTable.resize(DEFAULT_CAPACITY, nullptr);
}

// Constructor with custom size
template<class KeyType, class ValueType>
HashedMap<KeyType, ValueType>::HashedMap(int tableSize) 
    : itemCount(0), hashTableSize(tableSize) 
{
    hashTable.resize(tableSize, nullptr);
}

// Destructor
template<class KeyType, class ValueType>
HashedMap<KeyType, ValueType>::~HashedMap() 
{
    clear();
}

// isEmpty
template<class KeyType, class ValueType>
bool HashedMap<KeyType, ValueType>::isEmpty() const 
{
    return itemCount == 0;
}

// getNumberOfEntries
template<class KeyType, class ValueType>
int HashedMap<KeyType, ValueType>::getNumberOfEntries() const 
{
    return itemCount;
}

// contains
template<class KeyType, class ValueType>
bool HashedMap<KeyType, ValueType>::contains(const KeyType& key) const 
{
    int index = getHashIndex(key);
    auto currentEntry = hashTable[index];

    while (currentEntry != nullptr) {
        if (currentEntry->getKey() == key) {
            return true;
        }
        currentEntry = currentEntry->getNext();
    }

    return false;
}

// getValue
template<class KeyType, class ValueType>
bool HashedMap<KeyType, ValueType>::getValue(const KeyType& key, 
                                               ValueType& out) const 
{
    int index = getHashIndex(key);
    auto currentEntry = hashTable[index];

    while (currentEntry != nullptr) {
        if (currentEntry->getKey() == key) {
            out = currentEntry->getValue();
            return true;
        }
        currentEntry = currentEntry->getNext();
    }

    return false;
}

// add
template<class KeyType, class ValueType>
bool HashedMap<KeyType, ValueType>::add(const KeyType& key, 
                                         const ValueType& value) 
{
    int index = getHashIndex(key);

    // Check if key already exists
    auto currentEntry = hashTable[index];
    while (currentEntry != nullptr) {
        if (currentEntry->getKey() == key) {
            currentEntry->setValue(value);
            return true;
        }
        currentEntry = currentEntry->getNext();
    }

    // Create new entry and insert at front
    auto newEntry = std::make_shared<HashedEntry<KeyType, ValueType>>(key, value);
    newEntry->setNext(hashTable[index]);
    hashTable[index] = newEntry;
    itemCount++;

    return true;
}

// remove
template<class KeyType, class ValueType>
bool HashedMap<KeyType, ValueType>::remove(const KeyType& key) 
{
    int index = getHashIndex(key);
    auto currentEntry = hashTable[index];
    std::shared_ptr<HashedEntry<KeyType, ValueType>> previousEntry = nullptr;

    while (currentEntry != nullptr) {
        if (currentEntry->getKey() == key) {
            if (previousEntry == nullptr) {
                hashTable[index] = currentEntry->getNext();
            } else {
                previousEntry->setNext(currentEntry->getNext());
            }
            itemCount--;
            return true;
        }
        previousEntry = currentEntry;
        currentEntry = currentEntry->getNext();
    }

    return false;
}

// clear
template<class KeyType, class ValueType>
void HashedMap<KeyType, ValueType>::clear() 
{
    for (int i = 0; i < hashTableSize; i++) {
        hashTable[i] = nullptr;
    }
    itemCount = 0;
}

#endif