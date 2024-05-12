#pragma once

#include <Framework/Mdib/Private/Model/Alert/AlertConditionDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Alert/AlertConditionStateVisit.h>
#include <Framework/Mdib/Private/Model/Alert/AlertSignalDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Alert/AlertSignalStateVisit.h>
#include <Framework/Mdib/Private/Model/Alert/AlertSystemDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Alert/AlertSystemStateVisit.h>
#include <Framework/Mdib/Private/Model/Alert/CauseInfoVisit.h>
#include <Framework/Mdib/Private/Model/Alert/LimitAlertConditionDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Alert/LimitAlertConditionStateVisit.h>
#include <Framework/Mdib/Private/Model/CodedValueTranslationVisit.h>
#include <Framework/Mdib/Private/Model/CodedValueVisit.h>
#include <Framework/Mdib/Private/Model/CodingSystemVisit.h>
#include <Framework/Mdib/Private/Model/Component/BatteryDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Component/BatteryStateVisit.h>
#include <Framework/Mdib/Private/Model/Component/CalibrationDocumentationVisit.h>
#include <Framework/Mdib/Private/Model/Component/CalibrationInfoVisit.h>
#include <Framework/Mdib/Private/Model/Component/CalibrationResultVisit.h>
#include <Framework/Mdib/Private/Model/Component/ChannelDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Component/ChannelStateVisit.h>
#include <Framework/Mdib/Private/Model/Component/ClockDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Component/ClockStateVisit.h>
#include <Framework/Mdib/Private/Model/Component/MdsDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Component/MdsStateVisit.h>
#include <Framework/Mdib/Private/Model/Component/MetaDataVisit.h>
#include <Framework/Mdib/Private/Model/Component/PhysicalConnectorInfoVisit.h>
#include <Framework/Mdib/Private/Model/Component/ProductionSpecificationVisit.h>
#include <Framework/Mdib/Private/Model/Component/ScoDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Component/ScoStateVisit.h>
#include <Framework/Mdib/Private/Model/Component/SystemContextDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Component/SystemContextStateVisit.h>
#include <Framework/Mdib/Private/Model/Component/UdiVisit.h>
#include <Framework/Mdib/Private/Model/Component/VmdDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Component/VmdStateVisit.h>
#include <Framework/Mdib/Private/Model/Context/EnsembleContextDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Context/EnsembleContextStateVisit.h>
#include <Framework/Mdib/Private/Model/Context/LocationContextDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Context/LocationContextStateVisit.h>
#include <Framework/Mdib/Private/Model/Context/LocationDetailVisit.h>
#include <Framework/Mdib/Private/Model/Context/PatientContextDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Context/PatientContextStateVisit.h>
#include <Framework/Mdib/Private/Model/Context/PatientDemographicsCoreDataVisit.h>
#include <Framework/Mdib/Private/Model/Context/PersonReferenceVisit.h>
#include <Framework/Mdib/Private/Model/ExtensionDom/NodeVisit.h>
#include <Framework/Mdib/Private/Model/ExtensionTypeVisit.h>
#include <Framework/Mdib/Private/Model/InstanceIdentifierVisit.h>
#include <Framework/Mdib/Private/Model/LocalizedTextVisit.h>
#include <Framework/Mdib/Private/Model/MeasurementVisit.h>
#include <Framework/Mdib/Private/Model/Metric/AllowedEnumValueVisit.h>
#include <Framework/Mdib/Private/Model/Metric/DistributionSampleArrayMetricDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Metric/DistributionSampleArrayMetricStateVisit.h>
#include <Framework/Mdib/Private/Model/Metric/EnumStringMetricDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Metric/EnumStringMetricStateVisit.h>
#include <Framework/Mdib/Private/Model/Metric/MetricQualityVisit.h>
#include <Framework/Mdib/Private/Model/Metric/NumericMetricDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Metric/NumericMetricStateVisit.h>
#include <Framework/Mdib/Private/Model/Metric/NumericMetricValueVisit.h>
#include <Framework/Mdib/Private/Model/Metric/RealTimeSampleArrayMetricDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Metric/RealTimeSampleArrayMetricStateVisit.h>
#include <Framework/Mdib/Private/Model/Metric/RelationVisit.h>
#include <Framework/Mdib/Private/Model/Metric/SampleArrayValueVisit.h>
#include <Framework/Mdib/Private/Model/Metric/StringMetricDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Metric/StringMetricStateVisit.h>
#include <Framework/Mdib/Private/Model/Metric/StringMetricValueVisit.h>
#include <Framework/Mdib/Private/Model/Operation/ActivateArgumentVisit.h>
#include <Framework/Mdib/Private/Model/Operation/ActivateOperationDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Operation/ActivateOperationStateVisit.h>
#include <Framework/Mdib/Private/Model/Operation/OperationGroupVisit.h>
#include <Framework/Mdib/Private/Model/Operation/SetAlertStateOperationDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Operation/SetAlertStateOperationStateVisit.h>
#include <Framework/Mdib/Private/Model/Operation/SetComponentStateOperationDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Operation/SetComponentStateOperationStateVisit.h>
#include <Framework/Mdib/Private/Model/Operation/SetContextStateOperationDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Operation/SetContextStateOperationStateVisit.h>
#include <Framework/Mdib/Private/Model/Operation/SetMetricStateOperationDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Operation/SetMetricStateOperationStateVisit.h>
#include <Framework/Mdib/Private/Model/Operation/SetStringOperationDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Operation/SetStringOperationStateVisit.h>
#include <Framework/Mdib/Private/Model/Operation/SetValueOperationDescriptorVisit.h>
#include <Framework/Mdib/Private/Model/Operation/SetValueOperationStateVisit.h>
#include <Framework/Mdib/Private/Model/RangeVisit.h>
#include <Framework/Mdib/Private/Model/RootVisit.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>
#include <Framework/Utils/Public/LanguageTag.h>
#include <Framework/Utils/Public/Utf8.h>

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <set>

namespace DFL::Mdib::Impl
{

/**
 * @brief Dummy visitor (for non-existing members)
 * @ingroup Mdib
 */
template<class Visitor, class T,
        typename std::enable_if<std::is_fundamental<T>{} || std::is_enum<T>{}, bool>::type = true>
void visitMembers(Visitor&, T)
{
    // fundamental types and enums have no member
}

// Variadic template version does not work with VxWorks gcc 4.8.1,
// so instead we have to add multiple version with different
// amount of StrongTypedef skills
//
//template<class Visitor, class T, class ... Args>
//void visitMembers(Visitor& vis, StrongTypedef<T, Args ...> st)
//{
//    vis(st.get());
//}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template<class Visitor, class T, class Tag>
void visitMembers(Visitor& vis, StrongTypedef<T, Tag> st)
{
    vis(st.get());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template<class Visitor, class T, class Tag, template<class> class Skill1>
void visitMembers(Visitor& vis, StrongTypedef<T, Tag, Skill1> st)
{
    vis(st.get());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template<class Visitor, class T, class Tag, template<class> class Skill1, template<class> class Skill2>
void visitMembers(Visitor& vis, StrongTypedef<T, Tag, Skill1, Skill2> st)
{
    vis(st.get());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template<class Visitor, class T, class Tag, template<class> class Skill1, template<class> class Skill2, template<class> class Skill3>
void visitMembers(Visitor& vis, StrongTypedef<T, Tag, Skill1, Skill2, Skill3> st)
{
    vis(st.get());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template<class Visitor, class T, class Tag, template<class> class Skill1, template<class> class Skill2, template<class> class Skill3,
         template<class> class Skill4>
void visitMembers(Visitor& vis, StrongTypedef<T, Tag, Skill1, Skill2, Skill3, Skill4> st)
{
    vis(st.get());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template<class Visitor, class T, class Tag, template<class> class Skill1, template<class> class Skill2, template<class> class Skill3,
         template<class> class Skill4, template<class> class Skill5>
void visitMembers(Visitor& vis, StrongTypedef<T, Tag, Skill1, Skill2, Skill3, Skill4, Skill5> st)
{
    vis(st.get());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template<class Visitor, class T, class Tag, template<class> class Skill1, template<class> class Skill2, template<class> class Skill3,
         template<class> class Skill4, template<class> class Skill5, template<class> class Skill6>
void visitMembers(Visitor& vis, StrongTypedef<T, Tag, Skill1, Skill2, Skill3, Skill4, Skill5, Skill6> st)
{
    vis(st.get());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template<class Visitor, class T, class Tag, template<class> class Skill1, template<class> class Skill2, template<class> class Skill3,
         template<class> class Skill4, template<class> class Skill5, template<class> class Skill6, template<class> class Skill7>
void visitMembers(Visitor& vis, StrongTypedef<T, Tag, Skill1, Skill2, Skill3, Skill4, Skill5, Skill6, Skill7> st)
{
    vis(st.get());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor, class T, class A>
void visitMembers(Visitor& vis, const std::vector<T, A>& var)
{
    for (const auto& v : var)
    {
        vis(v);
    }
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor, class T, class A>
void visitMembers(Visitor& vis, const std::set<T, A>& var)
{
    for (const auto& v : var)
    {
        vis(v);
    }
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor, class T1, class T2>
void visitMembers(Visitor& vis, const std::pair<T1, T2>& var)
{
    vis(var.first);
    vis(var.second);
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor, class K, class V, class C, class A>
void visitMembers(Visitor& vis, const std::map<K, V, C, A>& map)
{
    for (const auto& v : map)
    {
        vis(v);
    }
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor, class K, class V, class C, class A>
void visitMembers(Visitor& vis, const std::multimap<K, V, C, A>& map)
{
    for (const auto& v : map)
    {
        vis(v);
    }
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const Handle& h)
{
    vis(h.string());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor, class T_Entity>
void visitMembers(Visitor& vis, const BasicHandle<T_Entity>& h)
{
    vis(h.string());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const Locale::Utf8& utf8)
{
    vis(utf8.value());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const VersionCounter& v)
{
    vis(v.get());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const Decimal& d)
{
    vis(d.intValue());
    vis(d.intExponent());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const RemedyInfo& r)
{
    vis(r.description());
    vis(r.extensions());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const Sample& s)
{
    vis(s.value());
    vis(s.annotations());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const DFL::Locale::LanguageTag& tag)
{
    vis(tag.tag());
}

/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor, class A>
void visitMembers(Visitor& vis, const boost::optional<A>& opt)
{
    if (opt)
    {
        vis(*opt);
    }
}

/**
 * @brief Dummy visitor (for non-existing members)
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor&, const DateOfBirth&)
{
    // no member
}

/**
 * @brief Dummy visitor (for non-existing members)
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor&, Timestamp)
{
    // no member
}

/**
 * @brief Dummy visitor (for non-existing members)
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor&, Duration)
{
    // no member
}

/**
 * @brief Dummy visitor (for non-existing members)
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor&, Chrono::Hours)
{
    // no member
}

/**
 * @brief Dummy visitor (for non-existing members)
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor&, const std::string&)
{
    // no member
}

/**
 * @brief Dummy visitor (for non-existing members)
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor&, const Chrono::TimeZone&)
{
    // no member
}

/**
 * @brief Generic visitor implementation to visit one specific type.
 * @ingroup Mdib
 */
template<class TypeToVisit>
class TypeVisitor
{
    public:
        /**
         * @brief Ctor taking the callback handle function.
         */
        explicit TypeVisitor(const std::function<void(const TypeToVisit&)>& function) :
                m_function(function) {}

        /**
         * @brief Operator for specific type.
         * This overload is required to "catch" calls with const lvalues like
         *  - TypeVisitor(constStdString) or
         *  - TypeVisitor(constInt).
         */
        void operator()(const TypeToVisit& type)
        {
            m_function(type);
        }

        /**
         * @brief Operator for specific type.
         * @details
         * This overload is required to "catch" calls with non-const lvalues like
         *  - TypeVisitor(nonConstStdString) or
         *  - TypeVisitor(nonConstInt).
         */
        void operator()(TypeToVisit& type)
        {
            m_function(type);
        }

        /**
         * @brief Operator for specific type.
         * @details
         * This overload is required to "catch" calls with rvalues like
         *  - TypeVisitor(std::string{"temp std::string"}) or
         *  - TypeVisitor(3).
         */
        void operator()(TypeToVisit&& type)
        {
            m_function(type);
        }

        /**
         * @brief Operator for other type.
         * @details
         * It calls the visitMembers function (recursively) to visit all
         * sub-members in this case. Thus, the whole member tree is visited.
         */
        template<class Other>
        void operator()(Other&& other)
        {
            // Not interested in this member, but maybe members are relevant.
            using DFL::Mdib::Impl::visitMembers;
            visitMembers(*this, std::forward<Other>(other));
        }

    private:
        const std::function<void(const TypeToVisit&)>& m_function;
};

}
