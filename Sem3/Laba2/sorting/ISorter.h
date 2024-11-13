#pragma once

#include <functional>
#include "../../../Sem2/Laba2/LABA2_Mephi/DynamicArray.h"

template<class T>
class ISorter {
public:
    virtual ~ISorter() = default;

    virtual void sort(typename DynamicArray<T>::Iterator begin, typename DynamicArray<T>::Iterator end,
                      std::function<bool(const T &, const T &)> comp) = 0;
};
