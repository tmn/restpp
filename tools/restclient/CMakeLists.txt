include(FetchContent)

FetchContent_Declare(
    simdjson
    GIT_REPOSITORY https://github.com/simdjson/simdjson.git
    GIT_TAG  tags/v3.3.0
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(simdjson)

add_executable(restclient main.cpp)
target_link_libraries(restclient PUBLIC simdjson tur)
