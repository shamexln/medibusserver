#pragma once

#include <S31/Base/S31Only/Exception.h>

#include <Framework/Format/Public/Stream.h>
#include <Framework/Mdib/Public/Model/ComponentActivation.h>
#include <Framework/Mdib/Public/Model/Metric/GenerationMode.h>
#include <Framework/Mdib/Public/Model/Metric/MeasurementValidity.h>

#include <boost/optional/optional.hpp>
#include <boost/preprocessor/library.hpp>

#include <cstring>
#include <stdexcept>

namespace S31::Sdc::Impl
{

#define S31_MDIB_ENUM_MAPPING_IF_BLOCK(R, DflMdibType, value) \
        if (strcmp(in, BOOST_PP_TUPLE_ELEM(2,0,value)) == 0) \
        { \
            return DFL::Mdib::DflMdibType::BOOST_PP_TUPLE_ELEM(2,1,value); \
        } \


#define S31_MDIB_ENUM_MAPPING(DflMdibType,values) \
static boost::optional<DFL::Mdib::DflMdibType> toOptional ## DflMdibType(const char* in); \
static DFL::Mdib::DflMdibType to ## DflMdibType(const char* in); \
inline boost::optional<DFL::Mdib::DflMdibType> toOptional ## DflMdibType(const char* in) \
{\
    if (in) \
    { \
        BOOST_PP_SEQ_FOR_EACH(S31_MDIB_ENUM_MAPPING_IF_BLOCK,DflMdibType,values) \
    } \
    return boost::none; \
} \
inline DFL::Mdib::DflMdibType to ## DflMdibType(const char* in) \
{\
    if (in) \
    { \
        BOOST_PP_SEQ_FOR_EACH(S31_MDIB_ENUM_MAPPING_IF_BLOCK,DflMdibType,values) \
    } \
    S31_THROW_EXCEPTION(S31::ExternalDataMappingFailed, "invalid " #DflMdibType "'" << in << "'"); \
} \


S31_MDIB_ENUM_MAPPING(MeasurementValidity,
    (("Vld",Valid))
    (("Vldated",ValidatedData))
    (("Ong",MeasurementOngoing))
    (("Qst",Questionable))
    (("Calib",CalibrationOngoing))
    (("Inv",Invalid))
    (("Oflw",Overflow))
    (("Uflw",Underflow))
    (("NA",NotAvailable))
)

S31_MDIB_ENUM_MAPPING(GenerationMode,
    (("Real",Real))
    (("Test",Test))
    (("Demo",Demo))
)

S31_MDIB_ENUM_MAPPING(ComponentActivation,
    (("On",On))
    (("NotRdy",NotReady))
    (("StndBy",StandBy))
    (("Off",Off))
    (("Shtdn",Shutdown))
    (("Fail",Failure))
)

S31_MDIB_ENUM_MAPPING(LocalizedTextWidth,
    (("xs",ExtraSmall))
    (("s",Small))
    (("m",Medium))
    (("l",Large))
    (("xl",ExtraLarge))
    (("xxl",ExtraExtraLarge))
)

}
