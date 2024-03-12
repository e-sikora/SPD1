#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#include "item.h"

template<class Item>
class Problem {
private:
    std::vector<Item> main_list;
    int list_size;

public:
    Problem() : list_size(0) {}

    size_t get_size() { return list_size; }

    Item &get_item(size_t index) { return main_list[index]; }

    void loadFromFile(const std::string &file_name);

    int workTime();

    void createOrClearFile(const std::string file_name);

    void savePermResult(const std::vector<Item> best_order, const int best_time, std::string result_file);

    void permutationSort();

    void occurTimeSort();

    void idleTimeSort();
};

template<class Item>
void Problem<Item>::loadFromFile(const std::string &file_name) {
    std::ifstream input_file(file_name);

    if (!input_file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku: " << file_name << "!\n";
        exit(EXIT_FAILURE);
    }

    std::string temp;

    if (!std::getline(input_file, temp)) {
        std::cerr << "Plik " << file_name << " jest pusty!\n";
        exit(EXIT_FAILURE);
    } else {
        list_size = std::stoi(temp);
    }

    Item new_item;
    int counter = 0, o_time, w_time, i_time;
    while (std::getline(input_file, temp)) {
        counter++;
        std::istringstream divide(temp);
        if (divide >> o_time >> w_time >> i_time) {
            new_item = Item(counter, o_time, w_time, i_time);
        } else {
            std::cerr << "Dane zostały źle podzielone!\n";
            exit(EXIT_FAILURE);
        }
        main_list.push_back(new_item);
    }
    if (counter != list_size) {
        std::cerr << "Liczba wczytanych zadań nie zgadza się z zadeklarowaną ilośćią!\n";
        exit(EXIT_FAILURE);
    }
    input_file.close();
}

template<class Item>
int Problem<Item>::workTime() {
    int total_work_time = 0;

    for (int i = 0; i < this->list_size; i++) {
        if (total_work_time < this->get_item(i).get_occur_time()) {
            total_work_time += (this->get_item(i).get_occur_time() - total_work_time);
        }
        total_work_time += this->get_item(i).get_work_time();
        total_work_time += this->get_item(i).get_idle_time();
    }

    return total_work_time;
}

template<class Item>
void Problem<Item>::createOrClearFile(const std::string file_name) {
    std::ofstream output_file(file_name);

    if (output_file.is_open()) {
        output_file.close();
        output_file.open(file_name, std::ios::out | std::ios::trunc);
    } else {
        std::ofstream file(file_name);
        if (!file.is_open()) {
            std::cout << "Plik nie został poprawnie utworzony!\n";
            exit(EXIT_FAILURE);
        }
    }
    output_file.close();
}

template<class Item>
void Problem<Item>::savePermResult(const std::vector<Item> best_order, int best_time, std::string result_file) {
    std::ofstream output_file(result_file, std::ios::app);

    if (!output_file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku do zapisu!" << std::endl;
        exit(EXIT_FAILURE);
    }

    for (const Item &item: best_order) {
        output_file << item.get_id() << " ";
    }

    output_file << "  Czas: " << best_time << std::endl;
    output_file.close();
}

template<class Item>
void Problem<Item>::permutationSort() {
//    std::string file_destination = ("data/perm_result.txt"); // commented due to unittesting
    std::vector<Item> original = main_list;
    int perm_work_time = 0;
    int best_time;
    std::vector<Item> best_order;
    bool first_iteration = true;

    do {
        perm_work_time = this->workTime();
        if (first_iteration == true) {
            best_time = perm_work_time;
            best_order.assign(main_list.begin(), main_list.end());
//            this->createOrClearFile(file_destination); // commented due to unittesting
            first_iteration = false;
        }
        if (perm_work_time < best_time) {
            best_time = perm_work_time;
            best_order.assign(main_list.begin(), main_list.end());
        }

//        this->savePermResult(main_list, perm_work_time, file_destination); // commented due to unittesting

    } while (std::next_permutation(main_list.begin(), main_list.end()));

    std::cout << "-------------------------Przegląd zupełny-------------------------" << std::endl;
    std::cout << "Optymalna kolejność wykonywania powyższych zadań jest dla ułożenia: ";
    for (Item &item: best_order) {
        std::cout << item.get_id();
    }
    std::cout << std::endl << "Czas potrzebny na wykonanie zadania w powyższej kolejności to: " << best_time
              << std::endl << std::endl;

    main_list = original;
}

template<class Item>
void Problem<Item>::occurTimeSort() {
    std::vector<Item> original = main_list;
    std::sort(main_list.begin(), main_list.end(), [](const Item &a, const Item &b) { return a.compareByOccurTime(b); });

    int best_time = this->workTime();
    std::cout << "------------Algorytm heurystyczny - r (termin dostępności)--------" << std::endl;
    std::cout << "Optymalna kolejność wykonywania powyższych zadań jest dla ułożenia: ";
    for (Item &item: main_list) {
        std::cout << item.get_id();
    }
    std::cout << std::endl << "Czas potrzebny na wykonanie zadania w powyższej kolejności to: " << best_time
              << std::endl << std::endl;

    main_list = original;
}

template<class Item>
void Problem<Item>::idleTimeSort() {
    std::vector<Item> original = main_list;
    std::sort(main_list.begin(), main_list.end(), [](const Item &a, const Item &b) { return a.compareByIdleTime(b); });

    int best_time = this->workTime();
    std::cout << "------------Algorytm heurystyczny - q (czas stygnięcia)-----------" << std::endl;
    std::cout << "Optymalna kolejność wykonywania powyższych zadań jest dla ułożenia: ";
    for (Item &item: main_list) {
        std::cout << item.get_id();
    }
    std::cout << std::endl << "Czas potrzebny na wykonanie zadania w powyższej kolejności to: " << best_time
              << std::endl << std::endl;

    main_list = original;
}


#ifdef ENABLE_DOCTEST_IN_LIBRARY

#include "doctest/doctest.h"
#include "item.h"

//TEST_CASE("Testing Problem class constructors")
//{
//    Problem<Item<int>> problem;
//}
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
        // Create a sample vector and file name
        Item<int> problem1 = Item<int>(1,1,1,1);
        Item<int> problem2 = Item<int>(2,2,2,2);
        Item<int> problem3 = Item<int>(3,3,3,3);
        std::vector<Item<int>> best_order = {problem1, problem2, problem3};
        int best_time = 10;
        std::string result_file = "../data/test_result.txt";

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
        std::vector<int> expected_order = {1,2,3,4,5,6};
        for(int i = 0; i < int(problem.get_size()); i++)
        {
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
        std::vector<int> expected_order = {1,2,3,4,5,6};
        for(int i = 0; i < int(problem.get_size()); i++)
        {
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
        std::vector<int> expected_order = {1,2,3,4,5,6};
        for(int i = 0; i < int(problem.get_size()); i++)
        {
            result_order.push_back(problem.get_item(i).get_id());
        }
        CHECK(result_order == expected_order);
    }
}





#endif