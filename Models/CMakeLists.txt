set(_libName OXI_CLIENT_MODELS)
add_library(${_libName})



include_directories(
    .
    )


target_sources(${_libName}
    PRIVATE

    boio.cpp 
    logger.cpp

    boio.h 
    logger.h

    )


