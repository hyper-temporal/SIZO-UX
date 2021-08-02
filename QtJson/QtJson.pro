QT          +=  core
TARGET      =   QtJson
TEMPLATE    =   lib
CONFIG      +=  c++20 qt warn_off exceptions

HEADERS  =  \
    json.hpp \
    qtjson.h

SOURCES =  \
    qtjson.cpp
