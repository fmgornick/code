/**
 * @file breadth_first_search.h
 */
#ifndef BREADTH_FIRST_SEARCH_H
#define BREADTH_FIRST_SEARCH_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "search_strategy.h"
#include "vector3.h"
#include <queue>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief Beeline movement- will move directly towards a robot given a vector3
 * position. extends iMovementStrategy so each function overwrites the parent
 */
class BreadthFirstSearch : public SearchStrategy {
    public:
        /**
        * @brief default constructor
        */
        BreadthFirstSearch() {
            queue.push("1721335785");
        };
        /**
        * @brief Searching function for Breadth First Search
        */
        Vector3* Search(Vector3 currentPos);
        /**
        * @brief Returns Queue
        */
        std::queue<std::string> GetQueue(){
            return queue;
        }
    private:
        /**
        * @brief Private bool to see the the drone is currently at the expected node or not
        */
        bool IsDroneAtNode(Vector3 currentPos);
        /**
        * @brief Queue for BreadthFirstSearch searching.
        */
        std::queue<std::string> queue;
    };

#endif
