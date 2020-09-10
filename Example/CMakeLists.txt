cmake_minimum_required(VERSION 3.15)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(ProgramTrade)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ctp_library_path "OTCApi/CTP/v6.3.15_20190220_api_tradeapi_se")
set(boost_library_root ../DevLibs/OpenSource/BoostInstall)
set(boost_library_include "${boost_library_root}/include")
set(boost_library_binary "${boost_library_root}/lib")

set(ka_include_dirs ${CMAKE_CURRENT_SOURCE_DIR} 
    ${boost_library_include} 
    "../DevLibs/OpenSource/spdlog/include"
    ${ctp_library_path} 
#    StrategyEngine
)


set(ka_cpp_file_list
    Logger.cpp
    TradingProgram.cpp
    MarketData/MarketDataProvider.cpp
    #OrderService
    StrategyEngine/StrategyEngine.cpp
)

add_executable(ProgramTrade main.cpp ${ka_cpp_file_list})
target_include_directories(ProgramTrade PUBLIC ${ka_include_dirs})
target_link_directories(ProgramTrade PUBLIC ${ctp_library_path})
#target_link_directories(ProgramTrade PUBLIC "../DevLibs/OpenSource/BoostInstall/lib")
#find_library(lib_ctp_md thostmduserapi_se.so "OTCApi/CTP/v6.3.15_20190220_api_tradeapi_se")
#message(STATUS "echo lib_ctp_md " ${lib_ctp_md})

target_link_libraries(ProgramTrade pthread thostmduserapi_se)

set(ka_unit_test_file_list
    UnitTest/TestMarketDataProvider.cpp
    )

#unit test
#set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
find_library(lib_boost_unit_test libboost_unit_test_framework.a ${boost_library_binary})
message(STATUS "echo lib_boost_unit_test " ${lib_boost_unit_test})
message(STATUS "echo CMAKE_FIND_LIBRARY_SUFFIXES " ${CMAKE_FIND_LIBRARY_SUFFIXES})
add_executable(UnitTest ${ka_unit_test_file_list} ${ka_cpp_file_list})
target_include_directories(UnitTest PUBLIC ${ka_include_dirs})
target_link_directories(UnitTest PUBLIC ${ctp_library_path})
target_link_libraries(UnitTest pthread thostmduserapi_se ${lib_boost_unit_test})

