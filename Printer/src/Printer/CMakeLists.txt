project(printer LANGUAGES CXX)

find_package(Qt5 COMPONENTS Core Quick Qml REQUIRED)   
find_package(Threads REQUIRED)

set(CMAKE_AUTOMOC ON)

add_library(printer_lib)

set_target_properties(printer_lib PROPERTIES PREFIX "" OUTPUT_NAME "printer"
                                                       CXX_STANDARD 20
                                                       CXX_STANDARD_REQUIRED ON
                                                       CXX_EXTENSIONS OFF)

target_compile_options(printer_lib PUBLIC -DDEBUG)

target_sources(printer_lib PUBLIC 
                                    Core/Application.cpp
                                    Core/Log.cpp 
                                    Core/SignalHandler.cpp  
                                    GPIO/Controller.cpp
                                    Motion/Stepper.cpp
                                    Motoion/Controller.cpp
                                                          ) 

target_include_directories(printer_lib PUBLIC ${SRC_DIR}
                                              ${CMAKE_CURRENT_BINARY_DIR}
                                              ${3RD_PARTY_DIR}/spdlog/include
                                                                              )

target_link_libraries(printer_lib PUBLIC  -lrt
                                          -pthread
                                          Qt5::Core
                                          Qt5::Quick
                                          Qt5::Qml
                                          Threads::Threads
                                          spdlog)    
