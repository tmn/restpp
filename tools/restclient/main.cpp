#include "simdjson.h"
#include "simdjson/padded_string.h"

#include "restclient.h"

int main()
{
    simdjson::ondemand::parser parser;

    RestClient rc = RestClient();

    std::string response = rc.get_stop_place("NSR:StopPlace:610", "2023-10-07T19:18:53Z");

    simdjson::padded_string data(response);
    simdjson::ondemand::document doc = parser.iterate(data);

    std::cout << "Data: " << doc.find_field("data") << '\n';

    return 0;
}
