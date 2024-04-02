#pragma once

#include <iostream>

/**
 * @brief A class representing an item with attributes like ID, occurrence time,
 * work time, and idle time.
 *
 * @tparam T The type of the item (currently unused).
 */
template<class T>
class Item {
private:
    int id; ///< The unique identifier of the item.
    int occur_time; ///< The time at which the item occurs.
    int work_time; ///< The time required to process the item.
    int idle_time; ///< The idle time associated with the item.

public:
    /**
   * @brief Default constructor initializing all attributes to zero.
   */
    Item();

    /**
     * @brief Parameterized constructor to initialize the item with provided values.
     *
     * @param id_s The ID of the item.
     * @param occur_time_s The occurrence time of the item.
     * @param work_time_s The work time required for the item.
     * @param idle_time_s The idle time associated with the item.
     */
    Item(int id_s, int occur_time_s, int work_time_s, int idle_time_s);

    /**
     * @brief Getter method for the ID of the item.
     *
     * @return int The ID of the item.
     */
    int getId() const { return id; }

    /**
     * @brief Getter method for the occurrence time of the item.
     *
     * @return int The occurrence time of the item.
     */
    int getOccurTime() const { return occur_time; }

    /**
    * @brief Getter method for the work time required for the item.
    *
    * @return int The work time required for the item.
    */
    int getWorkTime() const { return work_time; }

    /**
     * @brief Sets the work time required for the item.
     *
     * This method assigns the specified work time to the item.
     *
     * @param work_time_s The new work time to set for the item.
     */
    void setWorkTime(int work_time_s) { work_time = work_time_s; }

    /**

     * @brief Decrements the work time of the item by one.
     *
     * This method is used to decrement the current work time of the item, typically indicating a unit of work has been completed.
     */
    void workTimeDecrement() { work_time--; }


    /**
   * @brief Getter method for the idle time associated with the item.
   *
   * @return int The idle time associated with the item.
   */
    int getIdleTime() const { return idle_time; }

    /**
     * @brief Sets the idle time associated with the item.
     *
     * This method assigns the specified idle time to the item.
     *
     * @param idle_time_s The new idle time to set for the item.
     */
    void setIdleTime(int idle_time_s) { idle_time = idle_time_s; }

    /**
    * @brief Overloaded less than operator for comparing items based on their IDs.
    *
    * @param other The other item to compare with.
    * @return true If this item's ID is less than the other item's ID.
    * @return false Otherwise.
    */
    bool operator<(const Item &other) const;

    /**
   * @brief Compares two items based on their occurrence times.
   *
   * @param other The other item to compare with.
   * @return true If this item's occurrence time is less than the other item's.
   * @return false Otherwise.
   */
    bool compareByOccurTime(const Item &other) const;

    /**
     * @brief Compares two items based on their idle times.
     *
     * @param other The other item to compare with.
     * @return true If this item's idle time is less than the other item's.
     * @return false Otherwise.
     */
    bool compareByIdleTime(const Item &other) const;

    bool compareByWorkAndOccurTime(const Item &other) const;
};


template <class T>
bool Item<T>::compareByWorkAndOccurTime(const Item& other) const {
    return (work_time + occur_time) < (other.work_time + other.occur_time);
}



#ifdef ENABLE_DOCTEST_IN_LIBRARY

#include "doctest/doctest.h"

TEST_CASE("Item class") {
    // Default constructor
    Item<int> defaultItem;
    CHECK(defaultItem.getId() == 0);
    CHECK(defaultItem.getOccurTime() == 0);
    CHECK(defaultItem.getWorkTime() == 0);
    CHECK(defaultItem.getIdleTime() == 0);

    // Parameterized constructor
    Item<int> item1(1, 10, 5, 2);
    CHECK(item1.getId() == 1);
    CHECK(item1.getOccurTime() == 10);
    CHECK(item1.getWorkTime() == 5);
    CHECK(item1.getIdleTime() == 2);

    // Comparison operators
    Item<int> item2(2, 15, 3, 7);
    CHECK(item1 < item2);
    CHECK(item1.compareByOccurTime(item2));
    CHECK(item1.compareByIdleTime(item2));

    SUBCASE("setWorkTime") {
        Item<int> item;
        item.setWorkTime(10);
        CHECK(item.getWorkTime() == 10);  // Verifying that work time is set correctly
    }

    // Testing workTimeDecrement
    SUBCASE("workTimeDecrement") {
        Item<int> item(1, 10, 5, 2); // Initializing item with work time of 5
        item.workTimeDecrement();
        CHECK(item.getWorkTime() == 4);  // Verifying that work time is decremented by 1
    }

    // Testing setIdleTime
    SUBCASE("setIdleTime") {
        Item<int> item;
        item.setIdleTime(20);
        CHECK(item.getIdleTime() == 20);  // Verifying that idle time is set correctly
    }
}

#endif