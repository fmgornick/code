#include "deapth_first_search.h"



bool DeapthFirstSearch::IsDroneAtNode(Vector3 currentPos, std::string v) {
    int current_x = (int)currentPos.GetX();
    int current_z = (int)currentPos.GetZ();

    int expected_x = (int)nodemap[v]->GetX();
    int expected_z = (int)nodemap[v]->GetZ();
    if(current_x == expected_x && current_z == expected_z){
        return true;
    }
    return false;
}

Vector3* DeapthFirstSearch::Search(Vector3 currentPos) {
    std::string v = stack.top();
    if(IsDroneAtNode(currentPos, v)) {
        //v is not labeled as discovered
        if(vistedmap[v] == false){
            vistedmap[v] == true;
            stack.pop();
        }
        for(int i = 0; i < edgesmap[v].size(); i++){
            if(vistedmap[edgesmap[v].at(i)] == false){
                stack.push(edgesmap[v].at(i));
            }
            
        }
    }
    return nodemap[stack.top()];
}