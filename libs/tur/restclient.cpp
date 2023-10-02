#include "restclient.h"

RestClient::RestClient() : curl(curl_easy_init())
{
    curl_global_init(CURL_GLOBAL_ALL);
}

RestClient::~RestClient()
{
    curl_global_cleanup();
}

std::string RestClient::get_stop_place(std::string stop_place, std::string date)
{
    pthread_t req;

    struct Request request;
    request.url = "https://api.entur.io/journey-planner/v3/graphql";

    struct StopInfoArgs stop_info = {
        stop_place,
        date,
        request};

    pthread_create(&req,
                   NULL,
                   RestClient::get_stop_place,
                   &stop_info);

    pthread_join(req, NULL);

    return stop_info.request.response;
}

size_t RestClient::writeFunction(void *ptr, size_t size, size_t nmemb, std::string *data)
{
    data->append((char *)ptr, size * nmemb);
    return size * nmemb;
}

void *RestClient::get_stop_place(void *_args)
{
    struct StopInfoArgs *args = (struct StopInfoArgs *)_args;

    std::string query =
        "{\"query\": \" { stopPlace(id: \\\"" + args->stop_place + "\\\") { id name estimatedCalls(startTime: \\\"" + args->date + "\\\", timeRange: 72100, numberOfDepartures: 50) { realtime aimedArrivalTime expectedArrivalTime date forBoarding destinationDisplay { frontText } quay { id name publicCode description } serviceJourney { id journeyPattern { line { id publicCode name transportMode } } } } } } \" }";

    RestClient::fetch(args->request.url, query, &args->request.response);

    return nullptr;
}

void *RestClient::get_journey(void *_args)
{
    struct JourneyArgs *args = (struct JourneyArgs *)_args;

    std::string query =
        "{\"query\": \" { serviceJourney(id: \\\"" + args->journey_id + "\\\") { estimatedCalls(date: \"\(date)\") { aimedDepartureTime expectedDepartureTime quay { id name } } } }  \" }";

    RestClient::fetch(args->request.url, query, &args->request.response);

    return nullptr;
}

void *RestClient::fetch(std::string url, std::string query, std::string *response)
{

    CURL *curl;

    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "ET-Client-Name: tmnio-sanntidsappen-dev-cpp");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

    CURLcode r;
    r = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return NULL;
}
