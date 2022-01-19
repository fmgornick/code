/**
 * @file search_algo_test.cc
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "breadth_first_search.h"
#include "deapth_first_search.h"
#include "picojson.h"
#include "search_strategy.h"
#include "gtest/gtest.h"

/*******************************************************************************
 * Class Definition
 ******************************************************************************/

class SearchAlgoTest : public ::testing::Test {
public:
  void SetUp() { return; }
};

/**
 * @brief Test for Search Algorithms, These are 5 Component tests. Tests the
 * data structures of the breadth first search algorithms checks to make sure
 * that the data structures are initialized correctly.
 */
TEST_F(SearchAlgoTest, BFSDataStructures) {
  BreadthFirstSearch *BFS = new BreadthFirstSearch();
  BFS->ParseJson();
  EXPECT_EQ(BFS->GetVisitedMap()[BFS->GetQueue().front()], false)
      << "Visited Map Not Correct";
  EXPECT_EQ(BFS->GetQueue().front(), "1721335785")
      << "Front of queue is incorrect";
  EXPECT_EQ(BFS->GetEdgesMap().size(), 8571)
      << "EdgesMap does not have all nodes";
  EXPECT_EQ(BFS->GetNodeMap().size(), 8571)
      << "NodeMap does not have all nodes";
}

/**
 * @brief Test for Search Algorithms, Component tests. Tests the data structures
 * of the deapth first search algorithms checks to make sure that the data
 * structures are initialized correctly
 */
TEST_F(SearchAlgoTest, DFSDataStructures) {
  DeapthFirstSearch *DFS = new DeapthFirstSearch();
  DFS->ParseJson();
  EXPECT_EQ(DFS->GetVisitedMap()[DFS->GetStack().top()], false)
      << "Visited Map Not Correct";
  EXPECT_EQ(DFS->GetStack().top(), "1721335785")
      << "Front of Stack is incorrect";
  EXPECT_EQ(DFS->GetEdgesMap().size(), 8571)
      << "EdgesMap does not have all nodes";
  EXPECT_EQ(DFS->GetNodeMap().size(), 8571)
      << "NodeMap does not have all nodes";
}

/**
 * @brief Test for Search Algorithms, Component tests. Tests the data structures
 * of the deapth first search algorithms checks to make sure that the data
 * structures are initialized correctly
 */
TEST_F(SearchAlgoTest, BFSSearching) {
  BreadthFirstSearch *BFS = new BreadthFirstSearch();
  BFS->ParseJson();
  // returns the correct vector cords
  EXPECT_EQ((int)BFS->Search(Vector3(0, 0, 0))->GetX(), -41)
      << "X is incorrect";
  EXPECT_EQ((int)BFS->Search(Vector3(0, 0, 0))->GetZ(), -11)
      << "Z is incorrect";

  // makes sure it changes
  EXPECT_EQ((int)BFS->Search(Vector3(-41, 0, -11))->GetX(), -40)
      << "X is incorrect";
  EXPECT_EQ((int)BFS->Search(Vector3(-41, 0, -11))->GetZ(), -9)
      << "Z is incorrect";
}

/**
 * @brief Test for Search Algorithms, Component tests. Tests the data structures
 * of the deapth first search algorithms checks to make sure that the data
 * structures are initialized correctly
 */
TEST_F(SearchAlgoTest, DFSSearching) {
  DeapthFirstSearch *DFS = new DeapthFirstSearch();
  DFS->ParseJson();
  // returns the correct vector cords
  EXPECT_EQ((int)DFS->Search(Vector3(0, 0, 0))->GetX(), -41)
      << "X is incorrect";
  EXPECT_EQ((int)DFS->Search(Vector3(0, 0, 0))->GetZ(), -11)
      << "Z is incorrect";

  // makes sure it changes
  EXPECT_EQ((int)DFS->Search(Vector3(-41, 0, -11))->GetX(), -41)
      << "X is incorrect";
  EXPECT_EQ((int)DFS->Search(Vector3(-41, 0, -11))->GetZ(), -12)
      << "Z is incorrect";
}

/**
 * @brief Can DFS and BFS access ParseJson and get the same results
 */
TEST_F(SearchAlgoTest, AccessParseJsonData) {
  DeapthFirstSearch *DFS = new DeapthFirstSearch();
  BreadthFirstSearch *BFS = new BreadthFirstSearch();
  DFS->ParseJson();
  BFS->ParseJson();
  // returns the correct vector cords
  EXPECT_EQ(DFS->GetEdgesMap()["320613987"].size(), 3)
      << "Edges map is incorrect";
  EXPECT_EQ(DFS->GetVisitedMap()["320613987"], false)
      << "Visited map is incorrect";
  EXPECT_EQ((int)DFS->GetNodeMap()["320613987"]->GetX(), -10)
      << "X is incorrect";
  EXPECT_EQ((int)DFS->GetNodeMap()["320613987"]->GetZ(), -24)
      << "Z is incorrect";

  // makes sure it changes
  EXPECT_EQ(BFS->GetEdgesMap()["320613987"].size(), 3)
      << "Edges map is incorrect";
  EXPECT_EQ(BFS->GetVisitedMap()["320613987"], false)
      << "Visited map is incorrect";
  EXPECT_EQ((int)BFS->GetNodeMap()["320613987"]->GetX(), -10)
      << "X is incorrect";
  EXPECT_EQ((int)DFS->GetNodeMap()["320613987"]->GetZ(), -24)
      << "Z is incorrect";
}
