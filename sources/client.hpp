#include <string>
#include <map>
#include <curl/curl.h>

namespace Facebook{
  class Client{
  public:
    using dict_t = std::map<std::string, std::string>;
    Client(dict_t settings);
    dict_t info;
    char* id;
  	char* pass;
    auto check_connection() -> bool;

  };
}