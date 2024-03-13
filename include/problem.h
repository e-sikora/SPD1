#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

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
    size_t get_size();

    /**
     * @brief Get an item from the list by index.
     * @param index The index of the item to retrieve.
     * @return A reference to the item at the specified index.
     */
    Item &get_item(size_t index);

    /**
     * @brief Load items from a file into the list.
     * @param file_name The name of the file to load from.
     */
    void loadFromFile(const std::string &file_name);

    /**
     * @brief Calculate the total work time for the list of items.
     * @return The total work time.
     */
    int workTime();

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
     * @brief Perform a permutation sort on the list of items.
     */
    void permutationSort();

    /**
     * @brief Perform a sort based on item occurrence time.
     */
    void occurTimeSort();

    /**
     * @brief Perform a sort based on item idle time.
     */
    void idleTimeSort();
};


#ifdef ENABLE_DOCTEST_IN_LIBRARY

#include "doctest/doctest.h"
#include "item.h"


TEST_CASE("Problem class tests") {
    int workTime_forTestSet = 62;
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
        CHECK(problem.get_size() == 6);
        CHECK(problem.get_item(0).get_id() == first_item.get_id());
        CHECK(problem.get_item(0).get_work_time() == first_item.get_work_time());
        CHECK(problem.get_item(0).get_idle_time() == first_item.get_idle_time());
        CHECK(problem.get_item(0).get_occur_time() == first_item.get_occur_time());
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
        const char* result_file = "../data/test_result.txt";

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
        CHECK(problem.workTime() == workTime_forTestSet);
    };
}


TEST_CASE("permutationSort") {
    Problem<Item<int>> problem;

    CHECK_NOTHROW(problem.loadFromFile("../data/test_data.txt"));

    SUBCASE("Optimal order should be {?}") {
        problem.permutationSort();
        CHECK(problem.workTime() == 62);

        std::vector<int> result_order;
        std::vector<int> expected_order = {1, 2, 3, 4, 5, 6};
        for (int i = 0; i < int(problem.get_size()); i++) {
            result_order.push_back(problem.get_item(i).get_id());
        }
        CHECK(result_order == expected_order);
    }
}

TEST_CASE("occurTimeSort") {
    Problem<Item<int>> problem;
    CHECK_NOTHROW(problem.loadFromFile("../data/test_data.txt"));

    SUBCASE("Optimal order should be {?}") {
        problem.occurTimeSort();
        CHECK(problem.workTime() == 62);

        std::vector<int> result_order;
        std::vector<int> expected_order = {1, 2, 3, 4, 5, 6};
        for (int i = 0; i < int(problem.get_size()); i++) {
            result_order.push_back(problem.get_item(i).get_id());
        }
        CHECK(result_order == expected_order);
    }
}

TEST_CASE("idleTimeSort") {
    Problem<Item<int>> problem;
    CHECK_NOTHROW(problem.loadFromFile("../data/test_data.txt"));

    SUBCASE("Optimal order should be {?}") {
        problem.idleTimeSort();
        CHECK(problem.workTime() == 62);

        std::vector<int> result_order;
        std::vector<int> expected_order = {1, 2, 3, 4, 5, 6};
        for (int i = 0; i < int(problem.get_size()); i++) {
            result_order.push_back(problem.get_item(i).get_id());
        }
        CHECK(result_order == expected_order);
    }
}


#endif