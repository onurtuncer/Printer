project(printer LANGUAGES CXX)

# if("${ARCH}" STREQUAL "arm")
      find_package(Qt5 COMPONENTS Core Quick Qml REQUIRED)   
# else()
#       find_package(Qt6 COMPONENTS Core Quick Qml REQUIRED)
# endif()

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
                                    GPIO/PinController.cpp
                                    ) 

target_include_directories(printer_lib PUBLIC ${SRC_DIR}
                                              ${CMAKE_CURRENT_BINARY_DIR}
                                              ${3RD_PARTY_DIR}/spdlog/include
                                                                              )

# if("${ARCH}" STREQUAL "arm")
      target_link_libraries(printer_lib PUBLIC -lrt
            -pthread
            Qt5::Core
            Qt5::Quick
            Qt5::Qml
            Threads::Threads
            spdlog)
     
# else()
#       target_link_libraries(printer_lib PUBLIC -lrt
#             -pthread
#             Qt6::Core
#             Qt6::Quick
#             Qt6::Qml
#             Threads::Threads
#             spdlog)
# endif()