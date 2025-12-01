#ifndef MAP_ENTRY_
#define MAP_ENTRY_

template<class KeyType, class ValueType>
class MapEntry
{
private:
    KeyType searchKey;
    ValueType value;

protected: 
    void setKey(const KeyType& someKey);

public:
    MapEntry();
    MapEntry(const KeyType& someKey, const ValueType& someValue);
    KeyType getKey() const noexcept;
    ValueType getValue() const noexcept;
    void setValue(const ValueType& someValue);
    bool operator==(const MapEntry<KeyType, ValueType>& rightHandItem) const;
    bool operator>(const MapEntry<KeyType, ValueType>& rightHandItem) const;
};

// ========== IMPLEMENTATIONS ==========

template<class KeyType, class ValueType>
MapEntry<KeyType, ValueType>::MapEntry() 
    : searchKey(KeyType()), value(ValueType()) 
{
}

template<class KeyType, class ValueType>
MapEntry<KeyType, ValueType>::MapEntry(const KeyType& someKey, 
                                        const ValueType& someValue)
    : searchKey(someKey), value(someValue) 
{
}

template<class KeyType, class ValueType>
void MapEntry<KeyType, ValueType>::setKey(const KeyType& someKey) 
{
    searchKey = someKey;
}

template<class KeyType, class ValueType>
KeyType MapEntry<KeyType, ValueType>::getKey() const noexcept 
{
    return searchKey;
}

template<class KeyType, class ValueType>
ValueType MapEntry<KeyType, ValueType>::getValue() const noexcept 
{
    return value;
}

template<class KeyType, class ValueType>
void MapEntry<KeyType, ValueType>::setValue(const ValueType& someValue) 
{
    value = someValue;
}

template<class KeyType, class ValueType>
bool MapEntry<KeyType, ValueType>::operator==(
    const MapEntry<KeyType, ValueType>& rightHandItem) const 
{
    return searchKey == rightHandItem.searchKey;
}

template<class KeyType, class ValueType>
bool MapEntry<KeyType, ValueType>::operator>(
    const MapEntry<KeyType, ValueType>& rightHandItem) const 
{
    return searchKey > rightHandItem.searchKey;
}

#endif