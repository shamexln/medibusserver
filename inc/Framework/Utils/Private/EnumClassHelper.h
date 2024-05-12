#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Public/StaticAssert.h>

#include <boost/preprocessor.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

/// This macro is used in \ref DFL_ENUM_CLASS_STREAM_OPERATOR to add case blocks to switch statement
#define DFL_STREAM_VALUE_TO_CSTR(r, data, elem) case data::elem: return BOOST_PP_STRINGIZE(elem);

/// This macro is used in \ref DFL_ENUM_CLASS_SERIALIZATION_MAPPING_ASSERT
#define DFL_ENUM_CLASS_SERIALIZATION_ASSERT_ENUM_INT(r,name,elem) \
DFL_STATIC_ASSERT_INCOMPATIBLE_ENUMS_EQ(name::BOOST_PP_TUPLE_ELEM(2,0,elem), BOOST_PP_TUPLE_ELEM(2,1,elem));\

/// This macro adds static asserts for enum integer mapping.
#define DFL_ENUM_CLASS_SERIALIZATION_MAPPING_ASSERT(name, enumerators) \
BOOST_PP_SEQ_FOR_EACH(DFL_ENUM_CLASS_SERIALIZATION_ASSERT_ENUM_INT,name,enumerators)

/// This macro is used in \ref DFL_ENUM_CLASS_SERIALIZATION_LOAD_SAVE_METHODS
#define DFL_ENUM_CLASS_SERIALIZATION_CASE_ASSIGN(r,name,elem) \
  case BOOST_PP_TUPLE_ELEM(2,1,elem): enumValue = name::BOOST_PP_TUPLE_ELEM(2,0,elem); break;\

/// This macro has to be used outside other namespaces to provide load and save method for boost serialization.
#define DFL_ENUM_CLASS_SERIALIZATION_LOAD_SAVE_METHODS(name, enumerators) \
BOOST_SERIALIZATION_SPLIT_FREE(name) \
BOOST_CLASS_VERSION(name, 0) \
namespace boost {\
namespace serialization {\
template<class Archive> \
void save(Archive & ar, const name& enumValue, const unsigned int /*version*/) \
{\
    /* convert enum to integers on save (as done in boost)*/\
    const int i = boost::underlying_cast<int>(enumValue); \
    ar << make_nvp(NULL, i); \
}\
template<class Archive> \
void load(Archive & ar, name& enumValue, const unsigned int /*version*/) \
{\
    /* convert integers to correct enum to load (as done in boost) */\
    int i = 0;\
    ar >> make_nvp(NULL, i);\
    switch (i) {\
      BOOST_PP_SEQ_FOR_EACH(DFL_ENUM_CLASS_SERIALIZATION_CASE_ASSIGN,name,enumerators) \
      default:\
      ::DFL::Format::Stream errMsg; \
      errMsg << "Invalid integer value " << i << " for enum " BOOST_PP_STRINGIZE(name);\
      throw std::runtime_error(errMsg.cStr());\
    }\
}\
}\
}
