cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(ProgramTrade)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ka_include_dirs ${CMAKE_CURRENT_SOURCE_DIR} 
    "../DevLibs/OpenSource/BoostInstall/include"
#    StrategyEngine
)


set(ka_cpp_file_list
    TradingProgram.cpp
    MarketData/MarketDataProvider.cpp
    #OrderService
    StrategyEngine/StrategyEngine.cpp
)

add_executable(ProgramTrade main.cpp ${ka_cpp_file_list})
target_include_directories(ProgramTrade PUBLIC ${ka_include_dirs})
target_link_libraries(ProgramTrade pthread)

