#pragma once
#include <iostream>

template <typename T>
class TArray
{
public:
    TArray();
    ~TArray();

    void AddElement(T NewElement);
    T& GetElement(int Index);
    void RemoveElement(int Index);
    bool IsValidIndex(int Index) const;
    bool Contains(T Element) const;
    int Num() const;

private:
    void Resize();
    T* Data;
    int Capacity;
    int Count;
    static constexpr int InitialCapacity = 5;
};

template <typename T> TArray<T>::TArray()
{
    Capacity = InitialCapacity;
    Count = 0;
    Data = new T[Capacity];
}

template <typename T> TArray<T>::~TArray()
{
    delete[] Data;
}

template <typename T> void TArray<T>::AddElement(T NewElement)
{
    if (Count == Capacity)
    {
        Resize();
    }
    Data[Count] = NewElement;
    Count++;
}

template <typename T> T& TArray<T>::GetElement(int Index)
{
    if (IsValidIndex(Index))
    {
        return Data[Index];
    }
    else
    {
        throw std::out_of_range("Invalid Index");
    }
}

template <typename T> void TArray<T>::RemoveElement(int Index)
{
    if (!IsValidIndex(Index))
    {
        throw std::out_of_range("Invalid Index");
    }

    for (int i = Index; i < Count - 1; ++i)
    {
        Data[i] = Data[i + 1];
    }
    Count--;
}

template <typename T> bool TArray<T>::IsValidIndex(int Index) const
{
    return Index >= 0 && Index < Count;
}

template <typename T> bool TArray<T>::Contains(T Element) const
{
    for (int i = 0; i < Count; ++i)
    {
        if (Data[i] == Element)
        {
            return true;
        }
    }
    return false;
}

template <typename T> int TArray<T>::Num() const
{
    return Count;
}

template <typename T> void TArray<T>::Resize()
{
    int NewCapacity = Capacity * 2;
    T* NewData = new T[NewCapacity];

    for (int i = 0; i < Count; ++i)
    {
        NewData[i] = Data[i];
    }

    delete[] Data;
    Data = NewData;
    Capacity = NewCapacity;
}
