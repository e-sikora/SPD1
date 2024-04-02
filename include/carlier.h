#pragma once

#include <utility>
#include <limits>
#include "problem.h"

/**
 * @brief Template class for managing branches in a Carlier algorithm fork.
 *
 * This class is designed to hold and manage two branches of problems (A and B branches)
 * in the context of a Carlier scheduling algorithm fork. It supports operations like
 * setting flags to indicate the state of each branch, saving problem branches,
 * and managing linkage to previous forks in the chain.
 *
 * @tparam T The data type of the items in the problem.
 */
template <typename T>
class CarlierFork {
private:
    Problem<Item<T>> A_branch; ///< Holds the A branch of the problem.
    Problem<Item<T>> B_branch; ///< Holds the B branch of the problem.
    bool A_flag; ///< Flag indicating the state of the A branch.
    bool B_flag; ///< Flag indicating the state of the B branch.
    CarlierFork *prev_fork; ///< Pointer to the previous fork in the chain.

public:
    /**
     * @brief Constructs a new Carlier Fork instance.
     *
     * Initializes the A and B flags to false, and sets the prev_fork pointer to nullptr,
     * indicating that this fork initially has no previous fork in the chain.
     */
    CarlierFork() : A_flag(false), B_flag(false), prev_fork(nullptr) {}

    /**
     * @brief Destroys the Carlier Fork instance.
     *
     * Cleans up by deleting the prev_fork, ensuring no memory leaks for dynamically
     * allocated previous forks.
     */
    ~CarlierFork() {
        delete prev_fork;
    }

    /**
     * @brief Sets the A_flag to the specified value.
     *
     * @param flag The new value for the A_flag.
     */
    void set_A_flag(bool flag) {
        A_flag = flag;
    }

    /**
     * @brief Sets the B_flag to the specified value.
     *
     * @param flag The new value for the B_flag.
     */
    void set_B_flag(bool flag) {
        B_flag = flag;
    }

    /**
     * @brief Saves the given branch into the A_branch of the fork.
     *
     * @param branch The problem order to be saved into A_branch.
     */
    void save_branch_in_A(Problem<Item<int>> branch) {
        A_branch = std::move(branch);
    }

    /**
     * @brief Saves the given branch into the B_branch of the fork.
     *
     * @param branch The problem order to be saved into B_branch.
     */
    void save_branch_in_B(Problem<Item<int>> branch) {
        B_branch = std::move(branch);
    }

    /**
     * @brief Assigns the provided CarlierFork as the previous fork in the chain.
     *
     * @param prev A pointer to the CarlierFork that should be set as the previous fork.
     */
    void assign_prev_fork(CarlierFork* prev) {
        prev_fork = prev;
    }
};
//
//template<typename T>
//class CarlierAlgorithm {
//private:
//    int a = 0;
//    int b = 0;
//    int c = -1;
//    Problem<Item<int>> problem;
//    int U = 0;
//    int LB = 0;
//    int UB = std::numeric_limits<int>::max();
//public:
//    int Carlier(){
//
//        if(U<UB) UB=U;
//        // przypisanie zadań poszeregowanych przez Schrage
//
//        // znalezeinei a,b i c
//        // sprawdzenie czy C istnieje
//        // slice z problem, wyodrębnienie zbioru K
//        // wyliczenie r, q ,p od K
//        // pierwszy branch -- podmiana r
//        // schrage*
//        // aktualizacja LB
//
//        // drugi branch
//        retrun 0;
//    }
//
//
//
//};
