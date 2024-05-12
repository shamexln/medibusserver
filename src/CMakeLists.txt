set(target medibus)

include(filelist.cmake)

add_executable( ${target}
    ${MEDIBUS_FILES}
    sformat.h
    SdcProvider.h
)

include_directories("./")

target_compile_options(${target}
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/std:c++17>
        # warning C4251: needs to have dll-interface to be used by clients
        $<$<CXX_COMPILER_ID:MSVC>:/wd4251>
        # warning C4275: An exported class was derived from a class that wasn't exported.
        # C4275 can be ignored if you are deriving from a type in the C++ Standard Library
        $<$<CXX_COMPILER_ID:MSVC>:/wd4275>
)

include(${CMAKE_CURRENT_LIST_DIR}/../cmake/CompileOptions.cmake)

target_include_directories(${target}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)

target_link_directories(${target}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

target_link_libraries(${target} PRIVATE gRPC::grpc++ protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite
        S31_Core
        S31_Log
    S31_SdcTestUtils
    S31_TestUtils
    S31_History
    S31_Lts
    S31_Utils
    DFL_Crypto
    DFL_Mdib
    DFL_Utils
    DFL_Log
    DFL_Chrono
    DFL_Encoding
    DFL_Filesystem
    DFL_Format
    DFL_Thread
    DFL_Mdib
    Boost_chrono
    Boost_filesystem
    Boost_date_time
    Boost_system
    Boost_thread
    Boost_serialization
    ${OPENSSL_LIBRARIES}
)

install(TARGETS ${target}
    DESTINATION ${CMAKE_INSTALL_PREFIX})

