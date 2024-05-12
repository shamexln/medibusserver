#pragma once

#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>
#include <S31/Localization/S31Only/Device/LocalizedTextStoreImpl.h>

#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Test/Public/TestFactory.h>

#include <functional>
#include <queue>

namespace S31::Sdc::Test
{

/**
 * @brief Store handles to be used later for referencing purposes.
 */
class HandleQueue
{
    public:
        void push(const DFL::Mdib::Handle& h);
        DFL::Mdib::Handle pop();

    private:
        std::queue<DFL::Mdib::Handle> m_queue;
};

enum class LocaLizedTextStoreGeneration
{
    DontGenerate,
    Generate
};

/**
 * @brief Create Mdib test data.
 *
 * @details
 * == Localized Text Store ==
 * With the according configuration a text is created also that contains texts for all coded Values in the Mdib.
 *
 * The reference for those texts are in the format `ref:<number>`
 *
 * Additionally there are texts that are not used in the initial Mdib, the references have the format `ext:<number>` with
 * 1000 <= numer < 1100. These can be used in e.g. annotations in states.
 */
class S31_CORE_IT_UTIL_EXPIMP MdibDataFactory
{
    public:
        struct Configuration
        {
            Configuration() {}
            int numberOfMds = 1;
            int vmdPerMds = 2;
            int channelsPerVmd = 2;
            int numericMetricsPerChannel = 10;
            int rtsasPerChannel = 2;
            int scoPerMds = 1;
            int scoPerVmd = 1;
            int activateOperationsPerSco = 3;
            int setStringOperationsPerSco = 3;
            int alertSystemPerMds = 1; //0..1
            int alertSystemPerVmd = 0; //0..1
            int alertConditionsPerAlertSystem = 10;
            int limitAlertConditionsPerAlertSystem = 10;
            int alertSignalsPerCondition = 2; // 0..3
            LocaLizedTextStoreGeneration textStore = LocaLizedTextStoreGeneration::DontGenerate;
            S31::Localization::Device::Languages languages
            {
                DFL::Locale::LanguageTag("de-DE"),
                DFL::Locale::LanguageTag("en-US"),
                DFL::Locale::LanguageTag("es-ES"),
                DFL::Locale::LanguageTag("bg-BG"),
                DFL::Locale::LanguageTag("el-GR")
            };
        };

        explicit MdibDataFactory(const Configuration& config = Configuration{});

        DFL::Mdib::MdibChangeSet generateMdib();

        struct MdibAndStore
        {
                DFL::Mdib::MdibChangeSet mdibChanges;
                std::shared_ptr<S31::Localization::Device::LocalizedTextStoreImpl> store;
        };

        MdibAndStore generateMdibAndStore();

    private:

        Configuration m_config;
        DFL::Mdib::MdibChangeSet m_resultChangeSet;
        std::shared_ptr<S31::Localization::Device::LocalizedTextStoreImpl> m_resultStore;
        int m_resultStoreSize{0};

        int m_handleId = 0; // for unique handle names
        int m_textRefId = 0; // for unique text references
        int m_type = 0;
        int m_textWithSetCounter = 0;

        void addMds();
        void addVmd(const DFL::Mdib::MdsHandle& mds);
        void addChannel(const DFL::Mdib::VmdHandle& vmd);
        void addRtsa(const DFL::Mdib::ChannelHandle& ch);
        void addNumericMetric(const DFL::Mdib::ChannelHandle& ch);
        void addAlertSystem(const DFL::Mdib::MdsHandle& mds);
        void addAlertSystem(const DFL::Mdib::VmdHandle& vmd);
        void addSco(const DFL::Mdib::MdsHandle& mds);
        void addSco(const DFL::Mdib::VmdHandle& vmd);

        template <typename DescBuilder>
        void setType(DescBuilder& desc)
        {
            using namespace DFL::Mdib;
            desc.type(codedValues11073());
        }

        template <typename Condition, typename Parent>
        void addAlertCondition(const DFL::Mdib::BasicHandle<Parent>& parent);

        template <typename Operation, typename Parent>
        void addOperation(const DFL::Mdib::BasicHandle<Parent>& parent);

        DFL::Mdib::LocalizedTexts makeStoreText(const DFL::Mdib::LocalizedTextRef& ref, const DFL::Locale::LanguageTag& language, const std::set<DFL::Mdib::LocalizedTextWidth>& tws);
        void makeAdditionalStoreTexts();

        DFL::Mdib::LocalizedTexts texts();

        /// provides different combinations of text widths, to have some variations.
        std::set<DFL::Mdib::LocalizedTextWidth> textWidthSet();

        DFL::Mdib::CodedValue codedValues11073();

        void nTimes(int times, const std::function<void()>& f);

        // get a unique handle
        template <typename Entity>
        DFL::Mdib::BasicHandle<Entity> handle(const std::string& prefix);

        DFL::Mdib::LocalizedTextRef textRef();

        HandleQueue m_numericMetricHandles;
};

template<typename Operation, typename Parent>
void MdibDataFactory::addOperation(const DFL::Mdib::BasicHandle<Parent>& parent)
{
    using namespace DFL::Mdib;
    auto h = handle<Operation>("▶");
    typename Operation::DescriptorBuilderType desc;
    auto metric = m_numericMetricHandles.pop();
    m_numericMetricHandles.push(metric);
    desc.operationTarget(metric);
    desc.type(DFL::Mdib::Test::TestFactory::hashCodedValue(h.string()));
    m_resultChangeSet.addOneToInsert(EntityFactory::create(h, desc, parent));
}

template<typename Condition, typename Parent>
void MdibDataFactory::addAlertCondition(const DFL::Mdib::BasicHandle<Parent>& parent)
{
    using namespace DFL::Mdib;
    auto condHandle = handle<Condition>("alertCond");
    {
        typename Condition::DescriptorBuilderType desc;
        const auto s = m_numericMetricHandles.pop();
        if (s.isValid())
        {
            desc.sources(Handles{s});
            m_numericMetricHandles.push(s);
        }
        setType(desc);
        desc.kind(DFL::Mdib::AlertConditionKind::Physiological);
        desc.priority(DFL::Mdib::AlertConditionPriority::Medium);
        m_resultChangeSet.addOneToInsert(EntityFactory::create(condHandle, desc, parent));
    }

    auto makeSignal = [&](AlertSignalManifestation manifestation)
    {
        auto h = handle<typename Parent::AlertSignalType>("signal");
        typename Parent::AlertSignalType::DescriptorBuilderType desc;
        desc.manifestation(manifestation);
        desc.conditionSignaledHandle(toHandle(condHandle));
        m_resultChangeSet.addOneToInsert(EntityFactory::create(h, desc, parent));
    };

    if (m_config.alertSignalsPerCondition > 0)
    {
        makeSignal(AlertSignalManifestation::Audible);
    }
    if (m_config.alertSignalsPerCondition > 1)
    {
        makeSignal(AlertSignalManifestation::Visible);
    }
    if (m_config.alertSignalsPerCondition > 2)
    {
        makeSignal(AlertSignalManifestation::Tangible);
    }
}

template<typename Entity>
DFL::Mdib::BasicHandle<Entity> MdibDataFactory::handle(const std::string& prefix)
{
    auto s = prefix;
    s.append(std::to_string(m_handleId++));
    return DFL::Mdib::BasicHandle<Entity>(s);
}

}
