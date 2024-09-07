add_subdirectory(${3RD_PARTY_DIR}/libwebsockets)

set(3RD_PARTY_INCLUDE_DIRS
    ${3RD_PARTY_DIR}/libwebsockets/include
    CACHE INTERNAL "3rdparty include directories"
)

set(3RD_PARTY_LIBRARIES
    websockets
    CACHE INTERNAL "3rdparty libraries"
)
