#include "item.h"

template <class T>
Item<T>::Item() : id(0), occur_time(0), work_time(0), idle_time(0) {}

template <class T>
Item<T>::Item(int id_s, int occur_time_s, int work_time_s, int idle_time_s) {
    id = id_s;
    occur_time = occur_time_s;
    work_time = work_time_s;
    idle_time = idle_time_s;
}

template <class T>
bool Item<T>::operator<(const Item& other) const {
    return id < other.id;
}

template <class T>
bool Item<T>::compareByOccurTime(const Item& other) const {
    return occur_time < other.occur_time;
}

template <class T>
bool Item<T>::compareByIdleTime(const Item& other) const {
    return idle_time < other.idle_time;
}
