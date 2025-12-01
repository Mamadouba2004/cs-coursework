#ifndef HASHED_ENTRY_
#define HASHED_ENTRY_

#include <memory>
#include "MapEntry.h"

template<class KeyType, class ValueType>
class HashedEntry : public MapEntry<KeyType, ValueType>
{
private:
    std::shared_ptr<HashedEntry<KeyType, ValueType>> nextPtr;

public:
    HashedEntry();
    HashedEntry(KeyType someKey, ValueType someValue);
    HashedEntry(KeyType someKey, ValueType someValue,
                std::shared_ptr<HashedEntry<KeyType, ValueType>> nextEntryPtr);

    void setNext(std::shared_ptr<HashedEntry<KeyType, ValueType>> nextEntryPtr);
    std::shared_ptr<HashedEntry<KeyType, ValueType>> getNext() const;
};

// ========== IMPLEMENTATIONS ==========

template<class KeyType, class ValueType>
HashedEntry<KeyType, ValueType>::HashedEntry() 
    : MapEntry<KeyType, ValueType>(), nextPtr(nullptr) 
{
}

template<class KeyType, class ValueType>
HashedEntry<KeyType, ValueType>::HashedEntry(KeyType someKey, 
                                               ValueType someValue)
    : MapEntry<KeyType, ValueType>(someKey, someValue), 
      nextPtr(nullptr) 
{
}

template<class KeyType, class ValueType>
HashedEntry<KeyType, ValueType>::HashedEntry(
    KeyType someKey, 
    ValueType someValue,
    std::shared_ptr<HashedEntry<KeyType, ValueType>> nextEntryPtr)
    : MapEntry<KeyType, ValueType>(someKey, someValue), 
      nextPtr(nextEntryPtr) 
{
}

template<class KeyType, class ValueType>
void HashedEntry<KeyType, ValueType>::setNext(
    std::shared_ptr<HashedEntry<KeyType, ValueType>> nextEntryPtr) 
{
    nextPtr = nextEntryPtr;
}

template<class KeyType, class ValueType>
std::shared_ptr<HashedEntry<KeyType, ValueType>> 
HashedEntry<KeyType, ValueType>::getNext() const 
{
    return nextPtr;
}

#endif