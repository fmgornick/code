/**
 * @file search_strategy.h
 */
#ifndef SEARCH_STRATEGY_H
#define SEARCH_STRATEGY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "i_movement_strategy.h"
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <list>
#include <iterator>
#include "picojson.h"
#include "vector3.h"
#include <typeinfo>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @ingroup simulation
 * @brief partent class for the search strategys
 */
class SearchStrategy {
public:
    /**
    * @brief deconstructor
    */
    ~SearchStrategy() {}
    /**
    * @brief Virtual Search function for all the search strategies.
    */
    virtual Vector3* Search(Vector3 currentPos) = 0;
    /**
    * @brief Parses the edges and nodes json files into unordered maps for the use in the search functions
    */
    void ParseJson();
    /**
    * @brief Returns Node Map
    */
    std::unordered_map<std::string, Vector3*> GetNodeMap(){
        return nodemap;
    }
        /**
    * @brief Returns Edges Map
    */
    std::unordered_map<std::string, std::vector<std::string> > GetEdgesMap(){
        return edgesmap;
    }
    /** @brief Returns Visited Map
    */
    std::unordered_map<std::string, bool> GetVisitedMap(){
        return vistedmap;
    }



    protected:
        /**
        * @brief Unordered map of the nodes and their positions stored as vector3
        */
        std::unordered_map<std::string, Vector3*> nodemap;
        /**
        * @brief Unordered map of the edges. has a vector of all adjacent nodes to one node
        */
        std::unordered_map<std::string, std::vector<std::string> > edgesmap; 
        /**
        * @brief Unordered map of the nodes if they have been visited or not
        */
        std::unordered_map<std::string, bool> vistedmap;

};

#endif
