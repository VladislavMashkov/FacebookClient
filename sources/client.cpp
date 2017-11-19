#include <string>
#include <map>
#include <ios>
#include <curl/curl.h>
#include "client.hpp"
#include <iostream>
using namespace std;

Facebook::Client::Client (dict_t settings) {
	info = settings;
	dict_t::iterator it=info.find("app_id");
	if(it != info.end()) id = const_cast<char*>((it->second).c_str());
	cout << id << endl;
	dict_t::iterator it1=info.find("app_secret");
	if(it1 != info.end()) pass = const_cast<char*>((it1->second).c_str());
	cout << pass << endl;
};

auto Facebook::Client::check_connection()->bool {
	CURL *curl = curl_easy_init(); // инициализация сессии
	CURLcode res;
    if(curl) {
    	curl_easy_setopt(curl, CURLOPT_URL, "https://login.facebook.com/login.php"); // URL, с которым будет производиться операция.
    	curl_easy_setopt(curl, CURLOPT_NOBODY, true); // При установке этого параметра в ненулевое значение результат не будет включать документ 
    	curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_6) AppleWebKit/603.3.8 (KHTML, like Gecko) Version/10.1.2 Safari/603.3.8"); // Задает значение HTTP заголовка "User-Agent: "
    	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt"); // Имя файла, содержащего данные cookie. 
    	curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");
    	curl_easy_setopt(curl, CURLOPT_REFERER, "http://facebook.com/login.php"); // Задает значение HTTP заголовка "Referer:
    	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    	curl_easy_setopt(curl, CURLOPT_HEADER, 1);
    	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); // Устанавливаем этот параметр в ноль, чтобы запретить проверку сертификата удаленного сервера
    	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0); // Запрещаем проверку имени, указанного в сертификате удаленного сервера
    	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "email=Vladislav_mashkow@mail.ru&pass=adamwarner1488");
        curl_easy_perform(curl);
        
        
        curl_easy_cleanup(curl); //Завершение сессии
        return true;
    }
    return false;
};

int main () {
  using dict_t = map<string, string>;
  auto options = dict_t {
    { "app_id", "1234567890" },
    { "app_secret", "xxxxxxxxxxxxxx" }
  };
  using Facebook::Client;
  auto client = Client{ options };
  auto is_connected = client.check_connection();
  cout << boolalpha << (is_connected ? "connected" : "not connected") << endl;
}