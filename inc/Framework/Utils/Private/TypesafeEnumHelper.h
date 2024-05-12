#pragma once

#include <boost/preprocessor.hpp>

#define DFL_IMPL_VAL_TO_STR(r, Unused, Val)     \
  case Val: return BOOST_PP_STRINGIZE(Val);

#define DFL_IMPL_CHECK_VAL(r, Unused, Val)      \
  case Val: return;

#define DFL_IMPL_TYPESAFE_ENUM_VALUE(r, Unused, Val)           \
  class BOOST_PP_CAT(Val, Type) : public Type                   \
  {                                                             \
  public:                                                       \
    BOOST_PP_CAT(Val, Type)();                                  \
    static const Type::Native Value = Type::Val;                \
  };                                                            \
  inline BOOST_PP_CAT(Val, Type)::BOOST_PP_CAT(Val, Type)()     \
                               : Type(Type::Val)                \
  {}                                                            \
  BOOST_PP_CAT(Val, Type) const Val;
