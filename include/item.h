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
   * @brief Getter method for the idle time associated with the item.
   *
   * @return int The idle time associated with the item.
   */
    void setWorkTime(int work_time_s) { work_time = work_time_s; }

    /**
   * @brief Getter method for the idle time associated with the item.
   *
   * @return int The idle time associated with the item.
   */
    void workTimeDecrement() { work_time -= 1; }

    /**
   * @brief Getter method for the idle time associated with the item.
   *
   * @return int The idle time associated with the item.
   */
    int getIdleTime() const { return idle_time; }

    /**
   * @brief Getter method for the idle time associated with the item.
   *
   * @return int The idle time associated with the item.
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

    /**
    * @brief Compares two items based on their work times and occurrence times.
     *
     * @param other The other item to compare with.
     * @return true If this item's work time is less than the other item's, or if their work times are equal and this item's occurrence time is less.
     * @return false Otherwise.
     */
    bool compareByWorkAndOccurTime(const Item &other) const;
};

/**
 * @brief Compares two items based on their work times and occurrence times.
 *
 * @tparam T The type of the item (currently unused).
 * @param other The other item to compare with.
 * @return true If this item's work time is less than the other item's, or if their work times are equal and this item's occurrence time is less.
 * @return false Otherwise.
 */
template<class T>
bool Item<T>::compareByWorkAndOccurTime(const Item &other) const {
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
}

#endif