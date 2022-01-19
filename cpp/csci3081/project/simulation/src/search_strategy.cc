#include "search_strategy.h"

void SearchStrategy::ParseJson() {
  /* --------- nodes ------- */
  std::ifstream nodes;
  nodes.open("/home/user/repo/project/data/json/nodes.json");
  std::stringstream buf;
  buf << nodes.rdbuf();
  std::string nodes_json = buf.str();
  picojson::value nodes_v;
  std::string nodes_err = picojson::parse(nodes_v, nodes_json);
  float x, y, z;
  std::string x_str, y_str, z_str;
  std::string pos_str;

  if (!nodes_err.empty()) {
    std::cerr << nodes_err << std::endl;
  }

  /* ---------- Edges -------------- */
  std::ifstream edges;
  edges.open("/home/user/repo/project/data/json/edges.json");
  std::stringstream edges_buf;
  edges_buf << edges.rdbuf();
  std::string edges_json = edges_buf.str();
  picojson::value edges_v;
  std::string edges_err = picojson::parse(edges_v, edges_json);
  std::string edges_str;

  int node_pos;
  if (!edges_err.empty()) {
    std::cerr << edges_err << std::endl;
  } // else {
    // printf("Edges picojson parsed parsed\n");
  //}

  if (nodes_v.is<picojson::array>() && edges_v.is<picojson::array>()) {
    picojson::array nodes = nodes_v.get<picojson::array>();
    picojson::array edges = edges_v.get<picojson::array>();
    /* -------------- Nodes into nodesUMAP ------------ */
    for (int i = 0; i < nodes.size(); i++) {

      if (nodes[i].is<picojson::object>()) {
        picojson::object o = nodes[i].get<picojson::object>();
        for (picojson::value::object::const_iterator it = o.begin();
             it != o.end(); it++) {
          pos_str = it->second.serialize();
          vistedmap[it->first] = false;
          for (int i = 10; i < pos_str.length(); i++) {
            if (pos_str[i] == 'x') {
              std::stringstream x_str(pos_str.substr(i + 3, i + 15));
              x_str >> x;
              x = 1.4 * x / 20;
            }
            if (pos_str[i] == 'z') {
              std::stringstream z_str(pos_str.substr(i + 3, i + 15));
              z_str >> z;
              z = 1.4 * z / 20;
            }

            Vector3 *vec = new Vector3(x, 0, z);

            nodemap[it->first] = vec;
          }
        }
      } else {
        printf("array value is not a picojson::object\n");
      }
    }

    /* -------------------- EDGES into UMAP -------------- */
    std::string temp_string;
    std::stringstream num;
    int temp_num;
    int temp_itr = 0;
    std::vector<std::string> vector;
    for (int i = 0; i < edges.size(); i++) {
      if (edges[i].is<picojson::object>()) {
        picojson::object o = edges[i].get<picojson::object>();
        for (picojson::value::object::const_iterator it = o.begin();
             it != o.end(); it++) {
          edges_str = it->second.serialize();
          temp_itr++;
          for (int i = 0; i < edges_str.length(); i++) {
            int temp_iterator = i;
            if (edges_str[i] == '"') {
              temp_iterator = temp_iterator + 1;
              while (edges_str[temp_iterator] != '"') {
                temp_string = temp_string + edges_str[temp_iterator];
                temp_iterator = temp_iterator + 1;
              }
              i = temp_iterator;
              vector.push_back(temp_string);
              temp_string.clear();
            }
          }
          edgesmap[it->first] = vector;
          vector.clear();
        }

      } else {
        printf("array value is not a picojson::object\n");
      }
    }
  } else {
    printf("value is not an array\n");
  }

  /*
  for(auto x : edgesmap){
      std::cout << x.first << " Second: ";

         for(int i=0; i < x.second.size(); i++) {
          std::cout << x.second.at(i) << ' ';
         }
         std::cout << "\n";
  }

  for(auto x : nodemap) {
      std::cout << x.first << " " << x.second->GetX() << " " << x.second->GetY()
  << " " << x.second->GetZ()<< std::endl;
  }
  for(auto x : vistedmap) {
      std::cout << x.first << " " << x.second << std::endl;
  }
  */
}
