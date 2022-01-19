/**
 * @file deapth_first_search.h
 */
#ifndef DEAPTH_FIRST_SEARCH_H
#define DEAPTH_FIRST_SEARCH_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "search_strategy.h"
#include "vector3.h"
#include <stack>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief 
 *
 */
class DeapthFirstSearch : public SearchStrategy {
public:
  /**
   * @brief default constructor
   */
  DeapthFirstSearch() { stack.push("1721335785"); };
  /**
   * @brief Searching function for Depth First Search
   */
  Vector3 *Search(Vector3 currentPos);

  std::stack<std::string> GetStack() { return stack; }

private:
  /**
   * @brief Private bool to see the the drone is currently at the expected node
   * or not
   */
  bool IsDroneAtNode(Vector3 currentPos, std::string v);
  /**
   * @brief stack for Deapth First Search searching.
   */
  std::stack<std::string> stack;
};

#endif
