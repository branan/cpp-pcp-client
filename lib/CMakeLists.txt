include_directories(
    inc
    ${Boost_INCLUDE_DIRS}
    ${VALIJSON_INCLUDE_DIRS}
    ${WEBSOCKETPP_INCLUDE_DIRS}
    ${LEATHERMAN_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}
)

set(SOURCES
    src/connector/client_metadata.cc
    src/connector/connection.cc
    src/connector/connector.cc
    src/connector/session_association.cc
    src/connector/timings.cc
    src/protocol/chunks.cc
    src/protocol/message.cc
    src/protocol/schemas.cc
    src/protocol/serialization.cc
    src/util/logging.cc
    src/validator/schema.cc
    src/validator/validator.cc
)

# Static libraries should come before shared libraries, or you can end up
# with some really annoying link errors. However, we can configure whether
# Boost and Leatherman are linked statically or dynamically.
if (LEATHERMAN_SHARED)
    # If Leatherman is shared, Boost should come first because
    # it's static, or the order doesn't matter.
    list(APPEND LIBS ${Boost_LIBRARIES} ${LEATHERMAN_LIBRARIES})
else()
    # If Leatherman is static, it should come first as it depends
    # on Boost.
    list(APPEND LIBS ${LEATHERMAN_LIBRARIES} ${Boost_LIBRARIES})
endif()

list(APPEND LIBS
    ${OPENSSL_SSL_LIBRARY}
    ${OPENSSL_CRYPTO_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
)

if (WIN32)
    set(PLATFORM_LIBS Ws2_32)
elseif ("${CMAKE_SYSTEM_NAME}" MATCHES "SunOS")
    set(PLATFORM_LIBS socket nsl)
endif()

add_library(libcpp-pcp-client ${SOURCES})

# Explicit dependency on external projects to ensure they get
# extracted when building with multiple jobs
add_dependencies(libcpp-pcp-client websocketpp valijson)

target_link_libraries(libcpp-pcp-client PRIVATE ${LIBS} ${PLATFORM_LIBS})

# Generate the export header
include(GenerateExportHeader)
generate_export_header(libcpp-pcp-client EXPORT_FILE_NAME "${CMAKE_CURRENT_LIST_DIR}/inc/cpp-pcp-client/export.h")
target_compile_definitions(libcpp-pcp-client PRIVATE -Dlibcpp_pcp_client_EXPORTS)

if ((NOT APPLE) AND (NOT CMAKE_SYSTEM_NAME MATCHES "AIX") AND BUILD_SHARED_LIBS)
    set_target_properties(libcpp-pcp-client PROPERTIES VISIBILITY_INLINES_HIDDEN ON)
endif()

leatherman_install(libcpp-pcp-client)
install(DIRECTORY inc/cpp-pcp-client DESTINATION include)

add_subdirectory(tests)
