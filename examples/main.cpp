#include <facebook/сlient.hpp>
#include <string>
#include <map>
#include <ios>

int main () {
  using dict_t = std::map<std::string, std::string>;
  auto options = dict_t {
    { "app_id": "1234567890" },
    { "app_secret": "xxxxxxxxxxxxxx" }
  };
  using Facebook::Client;
  auto client = Client{ options };
  auto is_connected = client.check_connection();
  std::cout << std::boolalpha << (is_connected ? "connected" : "not connected") << std::endl;
}
