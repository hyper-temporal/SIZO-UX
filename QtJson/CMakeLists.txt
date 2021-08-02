cmake_minimum_required(VERSION 3.14)

project(QTJSON LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)


set(PROJECT_SOURCES
    json.hpp
    qtjson.cpp
    qtjson.h

)



add_library(QTJSON SHARED
    ${PROJECT_SOURCES}
)


target_compile_definitions(QTJSON
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(QTJSON
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core

  )


