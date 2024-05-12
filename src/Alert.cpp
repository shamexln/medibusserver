#include <Alert.h>

#include <S31/Log/Public/Logger.h>

#include <Framework/Mdib/Public/LocalMdibAccess.h>
#include <Framework/Mdib/Public/WriteResultIo.h>

#include <Framework/Mdib/Public/Model/CodedValueBuilder.h>
#include <Framework/Mdib/Public/Model/Component/Vmd.h>
#include <Framework/Mdib/Public/Model/EntityFactory.h>

// Alert System, Condition and Signal entities and builders
#include <Framework/Mdib/Public/Model/Alert/AlertSystem.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystemDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystemStateBuilder.h>

#include <Framework/Mdib/Public/Model/Alert/AlertCondition.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionStateBuilder.h>

#include <Framework/Mdib/Public/Model/Alert/AlertSignal.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalStateBuilder.h>

#include <iomanip>
#include <iostream>

using namespace DFL::Mdib;
using namespace S31::Samples;

S31_LOGGER("TestDevice");

const DFL::Mdib::VmdAlertSystemHandle vmdAlertSystemHandle("VmdAlertSystem");

const char HandleAlertCondition[]    = "SampleAlertCondition";
const char HandleAlertSignalAudio[]  = "AlertSignal_SampleAlertCondition_Aud";
const char HandleAlertSignalVisual[] = "AlertSignal_SampleAlertCondition_Vis";

template<typename Signal_T>
void addAlertSignal(
        MdibChangeSet&                                    changeSet,
        const BasicHandle<Signal_T>&                      alertSignalHandle,
        const Handle&                                     conditionSignaledHandle,
        AlertSignalManifestation                          manifestation,
        Latching                                          latching,
        const BasicHandle<typename Signal_T::ParentType>& system,
        const boost::optional<CodedValue>&                type = boost::none)
{
    AlertSignalDescriptorBuilder builder;
    builder.conditionSignaledHandle(conditionSignaledHandle).manifestation(manifestation).latching(latching).type(type);
    changeSet.addOneToInsert(EntityFactory::create(alertSignalHandle, builder, system));
}
  // namespace

void Alert::initMdib(
        DFL::Mdib::MdibChangeSet&                     changeSet,
        DFL::NotNull<std::shared_ptr<DFL::Mdib::Vmd>>     vmd,
        DFL::NotNull<std::shared_ptr<DFL::Mdib::Channel>> /*channel*/) const
{
    using namespace DFL::Mdib;
    
    auto alert = EntityFactory::create(vmdAlertSystemHandle, vmd->handle());
    changeSet.addOneToInsert(alert);

    AlertConditionDescriptorBuilder builder;

    // a condition with non latching signals
    CodedValueBuilder type(CodedValueFactory::create11073cfCode("111777"));
    builder.type(type.build());
    builder.priority(AlertConditionPriority::Medium);

    builder.kind(AlertConditionKind::Physiological);
    changeSet.addOneToInsert(
            EntityFactory::create(BasicHandle<VmdAlertCondition>(HandleAlertCondition), builder, vmdAlertSystemHandle));

    addAlertSignal(
            changeSet,
            BasicHandle<VmdAlertSignal>(HandleAlertSignalAudio),
            Handle(HandleAlertCondition),
            AlertSignalManifestation::Audible,
            Latching::NonLatchingSignal,
            vmdAlertSystemHandle);
    addAlertSignal(
            changeSet,
            BasicHandle<VmdAlertSignal>(HandleAlertSignalVisual),
            Handle(HandleAlertCondition),
            AlertSignalManifestation::Visible,
            Latching::NonLatchingSignal,
            vmdAlertSystemHandle);
}

void Alert::metricUpdateThread()
{
    int interval = 1000;  // Loop interval in milliseconds.
    CursorHelper cur(6);

    S31_STREAM_INFO("starting AlertHandler::updateThread");
    bool alertPresent{false};
    while (m_running)
    {
        auto currentMillis = DFL::Chrono::duration_cast<DFL::Chrono::Milliseconds>(
                                     DFL::Chrono::SystemClock::now().time_since_epoch())
                                     .count();
        auto previousTick = currentMillis - (currentMillis % interval);
        auto nextTick     = previousTick + interval;

        alertPresent = !alertPresent;
       writeAlertConditionsAndSignals(vmdAlertSystemHandle, alertPresent);

        std::stringstream msg;
        msg << cur.down() << "Alert: "
            << "set " << HandleAlertCondition << " and Signals to " << (alertPresent ? " ON" : "OFF") << cur.up();
        std::cout << msg.str();

        auto waitTime = DFL::Chrono::Milliseconds(DFL::Chrono::Milliseconds(
                nextTick
                - DFL::Chrono::duration_cast<DFL::Chrono::Milliseconds>(
                          DFL::Chrono::SystemClock::now().time_since_epoch())
                          .count()));
        if (waitTime > DFL::Chrono::Milliseconds(0))
        {
            DFL::Thread::ThisThread::sleepFor(waitTime);
        }
    }
}

void Alert::writeAlertConditionsAndSignals(const DFL::Mdib::VmdAlertSystemHandle& handle, bool alertPresent)
{
    auto                     mdib = m_localMdibAccess->latestMdib();
    DFL::Mdib::MdibChangeSet changeSet;

    auto alertSystem = m_localMdibAccess->latestMdib()->entity(DFL::Mdib::VmdAlertSystemHandle(handle));

    auto setAlertSystemState = [&](DFL::Mdib::AlertActivation activationState)
    {
        if (alertSystem)
        {
            DFL::Mdib::AlertSystemStateBuilder alertSystemStateBuilder(alertSystem->state());
            alertSystemStateBuilder.activationState(activationState);
            alertSystemStateBuilder.presentPhysiologicalAlarmConditions(
                DFL::Mdib::HandleSet{ DFL::Mdib::Handle(HandleAlertCondition) });
            changeSet.addOneToUpdate(
                DFL::Mdib::EntityFactory::create(DFL::asNotNull(alertSystem), alertSystemStateBuilder));
        }
    };

    // retrieve all alert conditions from vmd
    const auto alertConditions = mdib->range<DFL::Mdib::VmdAlertCondition>();
    for (const auto& alertCondition : alertConditions)
    {
        DFL::Mdib::AlertConditionStateBuilder alertConditionStateBuilder(alertCondition->state());

        // Toggle activation state
        alertConditionStateBuilder.activationState(DFL::Mdib::AlertActivation::On);
        alertConditionStateBuilder.presence(DFL::Mdib::AlertConditionPresence::Present);
        alertConditionStateBuilder.determinationTime(DFL::Chrono::SystemClock::now());
        setAlertSystemState(DFL::Mdib::AlertActivation::On);

        if (alertConditionStateBuilder.isChanged(*alertCondition->state()))
        {
            changeSet.addOneToUpdate(DFL::Mdib::EntityFactory::create(alertCondition, alertConditionStateBuilder));
        }
    }

    // retrieve all alert signals from vmd
    const auto alertSignals = mdib->range<DFL::Mdib::VmdAlertSignal>();
    for (const auto& alertSignal : alertSignals)
    {
        DFL::Mdib::AlertSignalStateBuilder alertSignalStateBuilder(alertSignal->state());

        // toggle alle audible alerts between paused and on
        if (alertSignal->descriptor()->manifestation() == DFL::Mdib::AlertSignalManifestation::Audible)
        {
            alertSignalStateBuilder.activationState(
                alertPresent ? DFL::Mdib::AlertActivation::On : DFL::Mdib::AlertActivation::Paused);
            alertSignalStateBuilder.presence(DFL::Mdib::AlertSignalPresence::On);
        }
        // toggle all other alerts (tangible, visible, other) between on and off
        else
        {
            alertSignalStateBuilder.activationState(
                alertPresent ? DFL::Mdib::AlertActivation::On : DFL::Mdib::AlertActivation::Off);
        }

        if (alertSignalStateBuilder.isChanged(*alertSignal->state()))
        {
            changeSet.addOneToUpdate(DFL::Mdib::EntityFactory::create(alertSignal, alertSignalStateBuilder));
        }
    }
    if (!changeSet.empty())
    {
        THROW_ON_MDIB_WRITE_FAILED(m_localMdibAccess->writeDescription(changeSet));
    }
}
