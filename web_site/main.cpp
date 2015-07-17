#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

void return_error(int error_code)
{
	std::cout << "Error: " << error_code;
}

int main(int argc, char* argv[])
{
	std::ifstream template_start("html/template.html");
	std::ifstream template_end("html/template-end.html");


	if(!(template_start && template_end))
	{
		std::terminate(); // FATAL ERROR
	}
	
	std::cout << "Content-type: text/html\r\n\r\n";
	std::cout << template_start.rdbuf();

	std::string get{getenv("QUERY_STRING")};
	std::map<std::string, std::string> query_values;

	auto key_start = get.begin();
	auto key_end = find(get.begin(), get.end(), '=');
	std::string key{key_start, key_end};
	
	auto value_start = key_end + 1;
	auto value_end   = get.end();
	std::string value{value_start, get.end()};
	query_values.insert({move(key), move(value)});
	
	std::ifstream content("html/" + query_values["page"]);

	if(content.is_open())
	{
		std::cout << content.rdbuf();
		std::cout << template_end.rdbuf();
	}
	else
	{
		std::cout << "404: Not found\nDiese Seite gibt es nicht (mehr)";
	}
	std::cout << template_end.rdbuf();

	return 0;
}
