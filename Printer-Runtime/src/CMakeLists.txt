cmake_minimum_required(VERSION 3.5)

project(printer-app LANGUAGES CXX)

# if(NOT ENABLE_QT6)
    find_package(Qt5 COMPONENTS Core Quick Qml QuickControls2 REQUIRED)
# else()
 #   find_package(Qt6 COMPONENTS Core Quick REQUIRED)
# endif()

# Add the executable
add_executable(${PROJECT_NAME} "main.cpp" "resources.qrc")

target_include_directories(${PROJECT_NAME} PUBLIC ${SRC_DIR}
                    ${CMAKE_SOURCE_DIR}/Printer/src/Printer)

# # Add the Qt modules to the target
# if(NOT ENABLE_QT6)
    target_link_libraries(${PROJECT_NAME} PRIVATE printer_lib Qt5::Core Qt5::Quick Qt5::Qml Qt5::QuickControls2)
# else()
  #  target_link_libraries(${PROJECT_NAME} PRIVATE printer_lib Qt6::Core Qt6::Quick)
# endif()

# Set the executable properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

# Set up resource file
if(NOT ENABLE_QT6)
    qt5_add_resources(QT_RESOURCES resources.qrc)
else()
  #  qt6_add_resources(QT_RESOURCES resources.qrc)
endif()

target_sources(${PROJECT_NAME} PRIVATE ${QT_RESOURCES})