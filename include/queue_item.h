#pragma once

#include "item.h"

template<class Item>
class QueueItem {
    Item QItem;
    int priority;

    public:

    QueueItem();
    QueueItem(Item, int);

    Item getQItem() const { return QItem; }
    int getPriority() const { return priority; }
};