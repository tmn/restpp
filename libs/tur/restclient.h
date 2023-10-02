#pragma once

#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <pthread.h>

struct Request
{
    std::string url;
    std::string response;
};

struct JourneyArgs
{
    std::string journey_id;

    struct Request request;
};

struct StopInfoArgs
{
    std::string stop_place;
    std::string date;

    struct Request request;
};

struct AutoCompleteArgs
{
    std::string query;

    struct Request request;
};

struct NearbyArgs
{
    std::string latitude;
    std::string longitude;

    struct Request request;
};

class RestClient
{
public:
    RestClient();
    ~RestClient();

    std::string get_stop_place(std::string stop_place, std::string date);

private:
    CURL *curl;

    static void *fetch(std::string url, std::string query, std::string *response);
    static size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string *data);

    static void *get_nearby_stops(void *req_args);
    static void *get_autocomplete_bus_stop(void *req_args);
    static void *get_stop_place(void *req_args);
    static void *get_journey(void *req_args);
    static void *get_quay_info(void *req_args);
};
