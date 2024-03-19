#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>
#include <functional>

#include "item.h"

/**
 * @brief A class representing a problem with a list of items.
 *
 * This class provides methods to manipulate a list of items,
 * including loading items from a file, performing various sorting
 * algorithms, calculating work time, and saving results to a file.
 *
 * @tparam Item The type of items in the problem.
 */
template<class Item>
class Problem {
private:
    std::vector<Item> main_list; /**< The main list of items. */
    int list_size; /**< The size of the list. */

public:
    /**
     * @brief Default constructor for Problem class.
     */
    Problem();

    /**
     * @brief Get the size of the list.
     * @return The size of the list.
     */
    size_t getSize();

    /**
     * @brief Get an item from the list by index.
     * @param index The index of the item to retrieve.
     * @return A reference to the item at the specified index.
     */
    Item &getItem(size_t index);

    /**
     * @brief Load items from a file into the list.
     * @param file_name The name of the file to load from.
     */
    void loadFromFile(const std::string &file_name);

    /**
     * @brief Calculate the total work time for the list of items.
     * @return The total work time.
     */
    int workTime(const bool count_idle_time);

    /**
     * @brief Create a new file or clear an existing one.
     * @param file_name The name of the file to create or clear.
     */
    void createOrClearFile(const std::string file_name);

    /**
     * @brief Save the best permutation result to a file.
     * @param best_order The best permutation order of items.
     * @param best_time The total time for the best permutation.
     * @param result_file The name of the file to save results to.
     */
    void savePermResult(const std::vector<Item> best_order, const int best_time, std::string result_file);

    /**
     * @brief Displays the result of the problem.
     *
     * This method prints out the final order of items and the total time taken to process these items.
     *
     * @param order The final order of items after sorting.
     * @param time The total time taken to process the items.
     */
    void displayResult(const std::vector<Item> order, const int time);

    /**
     * @brief Perform a permutation sort on the list of items.
     */
    void permutationSort();

    /**
     * @brief Perform a sort based on item occurrence time.
     */
    void occurTimeSort();

    /**
     * @brief Sorts the list of items based on their idle time.
     *
     * This method organizes items in the list in ascending order of their idle times.
     * The sort is performed in-place.
     */
    void idleTimeSort();

    /**
     * @brief Removes a specific item from a list based on its serial number.
     *
     * This method erases an item from the provided list that matches the given serial number.
     *
     * @param list The list from which the item should be erased.
     * @param serial The serial number of the item to be removed.
     */
    void eraseChosenElement(std::vector<Item> &list, const int serial);

    /**
     * @brief Executes the first version of the Schrage algorithm.
     *
     * This method sorts the items in the list according to the Schrage algorithm without expropriation.
     */
    void schrageAlgorithmV1();

    /**
     * @brief Executes the second version of the Schrage algorithm.
     *
     * This method sorts the items in the list according to the Schrage algorithm and includes improvements over version 1.
     */
    void schrageAlgorithmV2();

    /**
     * @brief Executes the Schrage algorithm with expropriation.
     *
     * This method sorts the items in the list using the Schrage algorithm with expropriation to potentially reduce total work time.
     */
    void schrageAlgorithmWithExpropriation();
};

#ifdef ENABLE_DOCTEST_IN_LIBRARY

#include "doctest/doctest.h"
#include "item.h"


TEST_CASE("Problem class tests") {
    int workTime_forTestSet = 32;
    // Test loading from file
    SUBCASE("Load from file") {
        Problem<Item<int>> problem;

//        WARN_THROWS(problem.loadFromFile("../data/dummy_test.txt"));
        CHECK_NOTHROW(problem.loadFromFile("../data/test_data.txt"));  // Replace with your test file name
    }
    SUBCASE("Checking data loaded from (test) file") {
        Problem<Item<int>> problem;
        Item<int> first_item = Item<int>(1, 1, 5, 9);
        CHECK_NOTHROW(problem.loadFromFile("../data/test_data.txt"));
        // Check if the size is as expected
        CHECK(problem.getSize() == 6);
        CHECK(problem.getItem(0).getId() == first_item.getId());
        CHECK(problem.getItem(0).getWorkTime() == first_item.getWorkTime());
        CHECK(problem.getItem(0).getIdleTime() == first_item.getIdleTime());
        CHECK(problem.getItem(0).getOccurTime() == first_item.getOccurTime());
    }

    SUBCASE("File creation or clearing") {
        std::string file_name = "test_file.txt";
        Problem<Item<int>> problem_instance;

        problem_instance.createOrClearFile(file_name);

        // Check if the file exists and is empty
        std::ifstream file(file_name);
        REQUIRE(file.is_open());
        REQUIRE(file.peek() == std::ifstream::traits_type::eof());
    }

    SUBCASE("Checking if the result is saved correctly") {
#include <cstdio>
        // Create a sample vector and file name
        Item<int> problem1 = Item<int>(1, 1, 1, 1);
        Item<int> problem2 = Item<int>(2, 2, 2, 2);
        Item<int> problem3 = Item<int>(3, 3, 3, 3);
        std::vector<Item<int>> best_order = {problem1, problem2, problem3};
        int best_time = 10;
        const char *result_file = "../data/test_result.txt";

        // Call the function
        Problem<Item<int>> problem;
        problem.savePermResult(best_order, best_time, result_file);

        std::ifstream input_file(result_file);
        std::string line;

        REQUIRE(input_file.is_open());

        // Read the last line in the file
        std::string last_line;
        while (std::getline(input_file, line)) {
            last_line = line;
        }

        // Check if the last line contains expected content
//        std::cout << last_line << std::endl;
        std::string expected_value = "1 2 3   Czas: 10";
        CHECK(last_line == expected_value);

        input_file.close();
        REQUIRE(std::remove(result_file) == 0);
    }

    SUBCASE("Checking calculations") {
        Problem<Item<int>> problem;
        CHECK_NOTHROW(problem.loadFromFile("../data/test_data.txt"));
        CHECK(problem.workTime(true) == workTime_forTestSet);
    };
}


TEST_CASE("permutationSort") {
    Problem<Item<int>> problem;

    CHECK_NOTHROW(problem.loadFromFile("../data/test_data.txt"));

    SUBCASE("Optimal order should be {?}") {
        problem.permutationSort();
        CHECK(problem.workTime(true) == 32);

        std::vector<int> result_order;
        std::vector<int> expected_order = {1, 2, 3, 4, 5, 6};
        for (int i = 0; i < int(problem.getSize()); i++) {
            result_order.push_back(problem.getItem(i).getId());
        }
        CHECK(result_order == expected_order);
    }
}

//TEST_CASE("occurTimeSort") {
//    Problem<Item<int>> problem;
//    CHECK_NOTHROW(problem.loadFromFile("../data/test_data.txt"));
//
//    SUBCASE("Optimal order should be {?}") {
//        problem.occurTimeSort();
//        CHECK(problem.workTime(true) == 62);
//
//        std::vector<int> result_order;
//        std::vector<int> expected_order = {1, 2, 3, 4, 5, 6};
//        for (int i = 0; i < int(problem.getSize()); i++) {
//            result_order.push_back(problem.getItem(i).getId());
//        }
//        CHECK(result_order == expected_order);
//    }
//}
////
//TEST_CASE("idleTimeSort") {
//    Problem<Item<int>> problem;
//    CHECK_NOTHROW(problem.loadFromFile("../data/test_data.txt"));
//
//    SUBCASE("Optimal order should be {?}") {
//        problem.idleTimeSort();
//        CHECK(problem.workTime(true) == 62);
//
//        std::vector<int> result_order;
//        std::vector<int> expected_order = {1, 2, 3, 4, 5, 6};
//        for (int i = 0; i < int(problem.getSize()); i++) {
//            result_order.push_back(problem.getItem(i).getId());
//        }
//        CHECK(result_order == expected_order);
//    }
//}

TEST_CASE("Testing eraseChosenElement with Item<int>") {
    Problem<Item<int>> problem; // Using Problem with Item<int>
    Item<int> item1 = Item<int>(1, 1, 1, 1);
    Item<int> item2 = Item<int>(2, 2, 2, 2);
    Item<int> item3 = Item<int>(3, 3, 3, 3);
    SUBCASE("Erase an existing element") {
        std::vector<Item<int>> list = {item1, item2, item3};
        problem.eraseChosenElement(list, 2);
        CHECK(list.size() == 2);
        CHECK(list[0].getId() == 1);
        CHECK(list[1].getId() == 3);
    }

    SUBCASE("Attempt to erase a non-existing element") {
        std::vector<Item<int>> list = {item1, item2, item3};
        problem.eraseChosenElement(list, 4);
        CHECK(list.size() == 3); // Size should remain unchanged
    }

    SUBCASE("Erase from an empty list") {
        std::vector<Item<int>> list;
        problem.eraseChosenElement(list, 1);
        CHECK(list.empty());
    }
}


TEST_CASE("Testing schrageAlgorithmV1") {
    // Initialize Problem object with a predefined list of items
    Problem<Item<int>> problem;
    problem.loadFromFile("../data/test_data.txt");
    // Manually populate main_list with Item<int> instances
    // Adjust the numbers as needed to match your test case

    // Run schrageAlgorithmV1
    problem.schrageAlgorithmV1();

    // Example checks
    // Verify that main_list is sorted correctly
    // This needs to be adjusted based on expected behavior of the algorithm
    // Perhaps check the first and last elements as a simple verification
    std::vector<int> expected_array = {1, 5, 3, 2, 4, 6};
    std::vector<int> result_array;
    for (int i = 0; i < int(problem.getSize()); i++) {
        result_array.push_back(problem.getItem(i).getId());
    }

    CHECK(result_array == expected_array);

    // Optionally, verify the total work time against an expected value
    int total_work_time = problem.workTime(true);  // Assuming true includes idle time
    CHECK(total_work_time == 32);
}

TEST_CASE("Testing schrageAlgorithmV2") {
    // Initialize Problem object with a predefined list of items
    Problem<Item<int>> problem;
    problem.loadFromFile("../data/test_data.txt");
    // Manually populate main_list with Item<int> instances
    // Adjust the numbers as needed to match your test case

    // Run schrageAlgorithmV1
    problem.schrageAlgorithmV2();

    // Example checks
    // Verify that main_list is sorted correctly
    // This needs to be adjusted based on expected behavior of the algorithm
    // Perhaps check the first and last elements as a simple verification
    std::vector<int> expected_array = {1, 5, 3, 2, 4, 6};
    std::vector<int> result_array;
    for (int i = 0; i < int(problem.getSize()); i++) {
        result_array.push_back(problem.getItem(i).getId());
    }

    CHECK(result_array == expected_array);

    // Optionally, verify the total work time against an expected value
    int total_work_time = problem.workTime(true);  // Assuming true includes idle time
    CHECK(total_work_time == 32);
}

TEST_CASE("Testing schrageAlgorithmWithExpropriation") {
    // Initialize Problem object with a predefined list of items
    Problem<Item<int>> problem;
    problem.loadFromFile("../data/test_data.txt");
    // Manually populate main_list with Item<int> instances
    // Adjust the numbers as needed to match your test case

    // Run schrageAlgorithmV1
    problem.schrageAlgorithmWithExpropriation();

    // Example checks
    // Verify that main_list is sorted correctly
    // This needs to be adjusted based on expected behavior of the algorithm
    // Perhaps check the first and last elements as a simple verification
    std::vector<int> expected_array = {1, 5, 3, 2, 4, 6};
    std::vector<int> result_array;
    for (int i = 0; i < int(problem.getSize()); i++) {
        result_array.push_back(problem.getItem(i).getId());
    }

    CHECK(result_array == expected_array);

    // Optionally, verify the total work time against an expected value
    int total_work_time = problem.workTime(true);  // Assuming true includes idle time
    CHECK(total_work_time == 32);
}

#endif