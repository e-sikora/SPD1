#include "queue_item.h"


template <class Item>
QueueItem<Item>::QueueItem() : QItem(), priority(0) {}

template <class Item>
QueueItem<Item>::QueueItem(Item qitem, int prio) {
    QItem = qitem;
    priority = prio;
}

