#include "breadth_first_search.h"
/* --------- GOALS ----------- */

bool BreadthFirstSearch::IsDroneAtNode(Vector3 currentPos){
    int current_x = (int)currentPos.GetX();
    int current_z = (int)currentPos.GetZ();

    int expected_x = (int)nodemap[queue.front()]->GetX();
    int expected_z = (int)nodemap[queue.front()]->GetZ();
    //std::cout << "CurX : " << current_x << " ExpX: " << expected_x << "            "<< " CurZ : " << current_z << " ExpZ: " << expected_z << std::endl;

    if(current_x == expected_x && current_z == expected_z){
        return true;
    }
    return false;
}

Vector3* BreadthFirstSearch::Search(Vector3 currentPos) {  

    if(IsDroneAtNode(currentPos)){
        vistedmap[queue.front()] = true;
        for(int i = 0; i < edgesmap[queue.front()].size(); i++){
            if(vistedmap[edgesmap[queue.front()].at(i)] == false){
                queue.push(edgesmap[queue.front()].at(i));
            }
        }
        queue.pop();
        return nodemap[queue.front()];
    }
    return nodemap[queue.front()];
}

