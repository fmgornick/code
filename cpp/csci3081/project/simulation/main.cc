#include "logger_manager.h"
#include "web_app.h"
#include "search_strategy.h"
#include <iostream>
#include <map>

int main(int argc, char **argv) {


  if (argc > 1) {
    int port = std::atoi(argv[1]);
    std::string webDir = std::string(argv[2]);
    WebServer<WebApp> server(port, webDir);
    while (true) {
      server.service();
    }
  } else {
    std::cout << "Usage: ./build/WebApp 8081 web" << std::endl;
  }

  return 0;
}
