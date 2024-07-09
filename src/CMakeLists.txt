set(target medibus)

include(filelist.cmake)

include_directories(include)
include_directories(include/nlohmann)
include_directories(include/nlohmann/detail)
include_directories(include/nlohmann/detail/conversions)
include_directories(include/nlohmann/detail/input)
include_directories(include/nlohmann/detail/iterators)
include_directories(include/nlohmann/detail/meta)
include_directories(include/nlohmann/detail/meta/call_std)
include_directories(include/nlohmann/detail/output)
include_directories(include/nlohmann/thirdparty)
include_directories(include/nlohmann/thirdparty/hedley)

add_executable( ${target}
    ${MEDIBUS_FILES}
    sformat.h
    SdcProvider.h
	include/nlohmann/detail/conversions/from_json.hpp
        include/nlohmann/detail/conversions/to_chars.hpp
        include/nlohmann/detail/conversions/to_json.hpp
        include/nlohmann/detail/input/binary_reader.hpp
        include/nlohmann/detail/input/input_adapters.hpp
        include/nlohmann/detail/input/json_sax.hpp
        include/nlohmann/detail/input/lexer.hpp
        include/nlohmann/detail/input/parser.hpp
        include/nlohmann/detail/input/position_t.hpp
        include/nlohmann/detail/iterators/internal_iterator.hpp
        include/nlohmann/detail/iterators/iter_impl.hpp
        include/nlohmann/detail/iterators/iteration_proxy.hpp
        include/nlohmann/detail/iterators/iterator_traits.hpp
        include/nlohmann/detail/iterators/json_reverse_iterator.hpp
        include/nlohmann/detail/iterators/primitive_iterator.hpp
        include/nlohmann/detail/meta/call_std/begin.hpp
        include/nlohmann/detail/meta/call_std/end.hpp
        include/nlohmann/detail/meta/cpp_future.hpp
        include/nlohmann/detail/meta/detected.hpp
        include/nlohmann/detail/meta/identity_tag.hpp
        include/nlohmann/detail/meta/is_sax.hpp
        include/nlohmann/detail/meta/std_fs.hpp
        include/nlohmann/detail/meta/type_traits.hpp
        include/nlohmann/detail/meta/void_t.hpp
        include/nlohmann/detail/output/binary_writer.hpp
        include/nlohmann/detail/output/output_adapters.hpp
        include/nlohmann/detail/output/serializer.hpp
        include/nlohmann/detail/abi_macros.hpp
        include/nlohmann/detail/exceptions.hpp
        include/nlohmann/detail/hash.hpp
        include/nlohmann/detail/json_custom_base_class.hpp
        include/nlohmann/detail/json_pointer.hpp
        include/nlohmann/detail/json_ref.hpp
        include/nlohmann/detail/macro_scope.hpp
        include/nlohmann/detail/macro_unscope.hpp
        include/nlohmann/detail/string_concat.hpp
        include/nlohmann/detail/string_escape.hpp
        include/nlohmann/detail/value_t.hpp
        include/nlohmann/thirdparty/hedley/hedley.hpp
        include/nlohmann/thirdparty/hedley/hedley_undef.hpp
        include/nlohmann/adl_serializer.hpp
        include/nlohmann/byte_container_with_subtype.hpp
        include/nlohmann/json.hpp
        include/nlohmann/json_fwd.hpp
        include/nlohmann/ordered_map.hpp
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
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../inc)

target_link_directories(${target}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../lib)

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
)

install(TARGETS ${target}
    DESTINATION ${CMAKE_INSTALL_PREFIX})

