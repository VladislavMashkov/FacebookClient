#include <string>
#include <map>

namespace Facebook{
  class Client{
  public:
  	char* id;
  	char* pass;
    using dict_t = std::map<std::string, std::string>;
    dict_t info;
    Client(dict_t settings);
    auto check_connection() -> bool;

  };
}
