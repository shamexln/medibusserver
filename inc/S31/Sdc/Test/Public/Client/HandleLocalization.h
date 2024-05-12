#pragma once

/** @note This file is included into the documentation as sample. So don't use doxygen comments in it
 *  because these will be striped when included in the documentation.
 */

/// [SdcClientLocalizationSample]
#include <S31/Sdc/Public/Client/RemoteDevice.h>
#include <S31/Sdc/Public/Client/RemoteDevicesObserver.h>
#include <S31/Sdc/Public/Common/MdibAccess.h>
#include <S31/Sdc/Public/Common/MdibAccessSmartPtrTypes.h>
#include <S31/Localization/Public/Client/References.h>
#include <S31/Test/S31Only/Exception.h>
#include <S31/Log/Public/Logger.h>

#include <Framework/Mdib/Public/MdibObserver.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/LanguageTagIo.h>

#include <thread>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <queue>

namespace S31::Sdc::Test
{

// Holds Notifiers of text or languages fetches.
// Notifiers have to life to get notifications and this class allows easy mangement of them.
class Notifiers
{
    public:
        // Returns a unique id to re-identify the notifier later.
        int add(const S31::Sdc::LocalizationClientRequestCompletePtr& notifier);

        // Mark the notifier for removal (later automatic removal is handled also by this class)
        void remove(int id);

    private:
        void cleanup();

        enum class ValueStatus
        {
            Active,
            MarkedForDeletion
        };

        struct Value
        {
            S31::Sdc::LocalizationClientRequestCompletePtrNullable notifier;
            ValueStatus status{ValueStatus::Active};
        };

        std::map<int, Value> m_notifiers;
        mutable std::mutex m_mutex;
        int m_counter{0};
};

class TextFetchHandler;

// A Mdib observer that triggers fetches of texts in Mdib Changes sets.
class ObserveMdibAndFetch: public DFL::Mdib::MdibObserver
{
    public:
        ObserveMdibAndFetch(S31::Sdc::EndpointReference epr, std::weak_ptr<TextFetchHandler> handler):
            m_epr(std::move(epr)),
            m_handler(std::move(handler))
        {}

        void onChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType) override;

    private:
        S31::Sdc::EndpointReference m_epr;
        std::weak_ptr<TextFetchHandler> m_handler;
};

// Just a container for collecting error messages.
class TextFetchErrors
{
    public:
        void add(std::string msg);

        // Get all errors which were collected so far.
        std::string errors() const;

    private:
        std::vector<std::string> m_messages;
};

#define ADD_FETCH_ERROR(msg) m_errors.add(msg + "~" + __FILE__ + ":" + std::to_string(__LINE__))

// Queue of (basically) changes sets to whose texts are needed to be fetched.
class FetchQueue
{
    public:
        struct Data
        {
                DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr> changes;
                DFL::Mdib::MdibChangeType changeType;
        };

        void push(Data data);

        Data pop();

        bool empty() const;

    private:
        std::queue<Data> m_queue;
        mutable std::mutex m_mutex;

};


// Core class for fetching texts from remote device.
class TextFetchHandler: public std::enable_shared_from_this<TextFetchHandler>
{
    public:
        ~TextFetchHandler();


        // To be called first.
        // Triggers fetching of available languages.
        // After that is called, queueing of text fetch request for Mdib change sets is possible
        void init(const DFL::NotNull<std::shared_ptr<S31::Sdc::RemoteDevice>>& remoteDevice);

        // Remove the device from the monitored devices container.
        // Especially the fetch queue is dropped and the Mdib observer too.
        void drop(const S31::Sdc::EndpointReference& epr);

        // Gets called by a Mdib observer.
        // The changes are queued and are processed separately by the this handler.
        // The Mdib observer is also automatically managed (created, stored, handled) by this class.
        void wantTextForNewMdibChanges(const S31::Sdc::EndpointReference& epr, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType);

        // Gets called when fetching availbale languages is complete.
        // Selects a active language and triggers fetching texts used in the initial Mdib.
        void onLanguageFetchComplete(int oldNotifierId, const S31::Sdc::EndpointReference& epr);

        // Gets called when fetching texts from the initial Mdib is complete.
        // After this the texts from the queued change sets can be processed.
        void onInitialMdibFetchComplete(int notifierId, const S31::Sdc::EndpointReference& epr);

        // Gets called when a single fetching texts operation for a change set is complete.
        void onFetchTextsComplete(int notifierId);

        // Collection of errors so far.
        const TextFetchErrors& errors() const;

    private:
        struct DeviceAndFetchQueue
        {
                std::weak_ptr<S31::Sdc::RemoteDevice> device;
                std::unique_ptr<FetchQueue> fetchQueue{std::make_unique<FetchQueue>()};
                std::shared_ptr<ObserveMdibAndFetch> mdibObserver;
        };

        std::weak_ptr<TextFetchHandler> weakThis() noexcept;

        void wakeUp();

        void handleQueuedDevicesToInit();

        void handleQueuedFetchTextRequests(DeviceAndFetchQueue& deviceAndFetchQueue);

        void handleQueuedFetchTextRequests();

        void threadFunction();

        template <typename Value>
        void erase(std::map<std::string, Value>& map, const std::string& key)
        {
            auto it = map.find(key);
            if (it != map.end())
            {
                map.erase(it);
            }
        }

        DFL::Locale::LanguageTag setActiveLanguage(S31::Sdc::LocalizationClient& localization);

        mutable std::recursive_mutex m_mutex;
        std::map<std::string, std::weak_ptr<S31::Sdc::RemoteDevice>> m_devicesToInit; // devices waiting to be initialized
        std::map<std::string, std::weak_ptr<S31::Sdc::RemoteDevice>> m_devicesOnInit; // devices are here while initialized
        std::map<std::string, DeviceAndFetchQueue> m_devicesOnFetch; // tracked devices

        Notifiers m_notifiers;
        TextFetchErrors m_errors;

        std::thread m_triggerFetchThread; // a thread that triggers localization fetch operations
        bool m_stop{false};
        std::condition_variable_any m_condVar;
        size_t m_activeLanguageCounter = 0;
};

// This is the only thing that a user of this example handler need to instantiate.
// Instantiate (in a shared_ptr) and register as observer in the remoteDeviceProvider.
class TextFetchConfigurator: public S31::Sdc::RemoteDevicesObserver
{
    public:
        TextFetchConfigurator():
            m_textFetchHandler(DFL::asNotNull(std::make_shared<TextFetchHandler>()))
        {
        }

        void online(const DFL::NotNull<std::shared_ptr<S31::Sdc::RemoteDevice>>& remoteDevice) override
        {
            m_textFetchHandler->init(remoteDevice);
        }

        void offline(const S31::Sdc::EndpointReference& epr, const S31::Utils::Error& /*error*/) override
        {
            m_textFetchHandler->drop(epr);
        }

        // The handler, especially for accessing potential errors.
        const TextFetchHandler& textFetchHandler() const
        {
            return *m_textFetchHandler;
        }

    private:
        DFL::NotNull<std::shared_ptr<TextFetchHandler>> m_textFetchHandler;

};

inline void ObserveMdibAndFetch::onChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& /*mdib*/, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType)
{
    if (auto handler = m_handler.lock())
    {
        handler->wantTextForNewMdibChanges(m_epr, changes, changeType);
    }
}

inline TextFetchHandler::~TextFetchHandler()
{
    {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
        m_stop = true;
    }
    wakeUp();
    if (m_triggerFetchThread.joinable())
    {
        m_triggerFetchThread.join();
    }
}

inline void TextFetchHandler::init(const DFL::NotNull<std::shared_ptr<S31::Sdc::RemoteDevice>>& remoteDevice)
{
    // here it all starts for a new device
    // the initialization task is queued, also because it has be executed in another context
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    m_devicesToInit[remoteDevice->endpointReference().address().str()] = remoteDevice.get();

    auto mdibObserver = std::make_shared<ObserveMdibAndFetch>(remoteDevice->endpointReference(), weakThis());
    remoteDevice->mdibAccess()->registerObserver(mdibObserver);

    DeviceAndFetchQueue data;
    data.device = remoteDevice.get();
    data.mdibObserver = mdibObserver;
    DeviceAndFetchQueue value{remoteDevice.get(), std::make_unique<FetchQueue>(), mdibObserver};
    m_devicesOnFetch.emplace(remoteDevice->endpointReference().address().str(), std::move(value));
    wakeUp();
}

inline void TextFetchHandler::drop(const EndpointReference& epr)
{
    const auto eprs = epr.address().str();
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    erase(m_devicesOnInit, eprs);
    erase(m_devicesToInit, eprs);
    erase(m_devicesOnFetch, eprs);
}

inline void TextFetchHandler::wantTextForNewMdibChanges(const S31::Sdc::EndpointReference& epr, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType)
{
    FetchQueue::Data data{changes, changeType};
    const auto& eprs = epr.address().str();

    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    auto it = m_devicesOnFetch.find(eprs);
    if (it == m_devicesOnFetch.end())
    {
        ADD_FETCH_ERROR(eprs + " is not in m_devicesOnFetch");
    }

    auto& queue = it->second.fetchQueue;
    queue->push(std::move(data));
    wakeUp();
}

inline void TextFetchHandler::onLanguageFetchComplete(int oldNotifierId, const S31::Sdc::EndpointReference& epr)
{
    m_notifiers.remove(oldNotifierId);
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    const auto& eprs = epr.address().str();
    auto it = m_devicesOnInit.find(eprs);
    if (it == m_devicesOnInit.end())
    {
        ADD_FETCH_ERROR(eprs + " is not in m_devicesOnInit");
        return;
    }
    const auto device = it->second.lock();
    if (!device)
    {
        return;
    }

    const auto localization = device->localization();
    if (!localization)
    {
        ADD_FETCH_ERROR(epr.address().str() + " has no localization service.");
        erase(m_devicesOnInit, eprs);
        return;
    }

    const auto& langs = localization->supportedLanguages();
    if (langs.empty())
    {
        ADD_FETCH_ERROR(epr.address().str() + " has no languages. ");
        erase(m_devicesOnInit, eprs);
        return;
    }

    {
        auto l = setActiveLanguage(*localization);
        S31_STREAM_INFO_LOGGER("Test", "Tracking localized texts on ", epr, ". Active language is ", l);
    }

    // fetch all the texts used in the current Mdib to have almost all texts ready to use.
    // (some texts may be used only in states (from time to time))
    const auto mdib = device->mdibAccess()->latestMdib();
    auto refs = S31::Localization::Client::References::textReferenceAll(*mdib);

    if (refs.empty())
    {
        erase(m_devicesOnInit, eprs);
        return;
    }

    auto notifier = localization->fetch(std::move(refs));
    const auto notifierId = m_notifiers.add(notifier);

    auto onCompleted = [notifierId, epr, wt = weakThis()]()
    {
        if (auto t = wt.lock())
        {
            t->onInitialMdibFetchComplete(notifierId, epr);
        }
    };

    notifier->registerCallback(onCompleted);
}

inline void TextFetchHandler::onInitialMdibFetchComplete(int notifierId, const S31::Sdc::EndpointReference& epr)
{
    m_notifiers.remove(notifierId);
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    const auto& eprs = epr.address().str();
    auto it = m_devicesOnInit.find(eprs);
    if (it == m_devicesOnInit.end())
    {
        ADD_FETCH_ERROR(eprs + " is not in m_devicesOnInit");
    }

    erase(m_devicesOnInit, eprs); // initalization complete
    wakeUp(); // trigger processing of entries from queue
}

inline void TextFetchHandler::onFetchTextsComplete(int notifierId)
{
    m_notifiers.remove(notifierId);
}

inline const TextFetchErrors& TextFetchHandler::errors() const
{
    return m_errors;
}

inline std::weak_ptr<TextFetchHandler> TextFetchHandler::weakThis() noexcept
{
    // thanks Windriver for not having weak_from_this()
    // Note: weak_from_this() is specified as noexcept
    try
    {
        std::weak_ptr<TextFetchHandler> result = shared_from_this();
        return result;
    }
    catch(const std::bad_weak_ptr&)
    {
        // Object is destructed (or destructing), no longer shareable.
    }
    catch(...)
    {
        S31_STREAM_ERROR_LOGGER("Test", "Unknown exception thrown during TextFetchHandler::weakThis()");
    }
    // Empty weak_ptr
    return std::weak_ptr<TextFetchHandler>{};
}

inline void TextFetchHandler::wakeUp()
{
    if (!m_triggerFetchThread.joinable())
    {
        m_triggerFetchThread = std::thread(
                [this]()
                {
                    try
                    {
                        this->threadFunction();
                    }
                    catch (const std::exception& ex)
                    {
                        S31_STREAM_ERROR_LOGGER("Test", "Exception from TextFetchHandler::threadFunction ", ex.what());
                    }
                });
    }
    else
    {
        m_condVar.notify_one();
    }
}

inline void TextFetchHandler::handleQueuedDevicesToInit()
{
    while (!m_devicesToInit.empty())
    {
        const auto it = m_devicesToInit.begin();
        const auto device = it->second.lock();
        m_devicesToInit.erase(it);

        if (!device)
        {
            continue;
        }

        const auto& epr = device->endpointReference();
        m_devicesOnInit[epr.address().str()] = device;
        const auto localization = device->localization();

        if (!localization)
        {
            ADD_FETCH_ERROR(epr.address().str() + " has no localization service.");
            continue;
        }

        auto notifier = localization->fetchSupportedLanguages();
        const auto notifierId = m_notifiers.add(notifier);

        auto onCompleted = [notifierId, epr, wt = weakThis()]()
        {
            if (auto t = wt.lock())
            {
                t->onLanguageFetchComplete(notifierId, epr);
            }
        };

        notifier->registerCallback(onCompleted);
    }
}

inline void TextFetchHandler::handleQueuedFetchTextRequests(DeviceAndFetchQueue& deviceAndFetchQueue)
{
    while (!deviceAndFetchQueue.fetchQueue->empty())
    {
        auto entry = deviceAndFetchQueue.fetchQueue->pop();

        const auto device = deviceAndFetchQueue.device.lock();
        if (!device)
        {
            return;
        }

        const auto localization = device->localization();
        if (!localization)
        {
            ADD_FETCH_ERROR(device->endpointReference().address().str() + " has no localization service.");
            return;
        }

        S31::Localization::LocalizedTextReferences refs;
        if (entry.changeType == DFL::Mdib::MdibChangeType::Description)
        {
            refs = S31::Localization::Client::References::textReferenceAll(*entry.changes);
        }
        else
        {
            refs = S31::Localization::Client::References::textReferenceStates(*entry.changes);
        }

        if (refs.empty())
        {
            return;
        }

        auto notifier = localization->fetch(std::move(refs));
        const auto notifierId = m_notifiers.add(notifier);

        auto onCompleted = [notifierId, wt = weakThis()]()
        {
            if (auto t = wt.lock())
            {
                t->onFetchTextsComplete(notifierId);
            }
        };

        notifier->registerCallback(onCompleted);
    }
}

inline void TextFetchHandler::handleQueuedFetchTextRequests()
{
    for (auto& [epr, deviceOnFetch] : m_devicesOnFetch)
    {
        if (m_devicesToInit.find(epr) != m_devicesToInit.end()
                || m_devicesOnInit.find(epr) != m_devicesOnInit.end())
        {
            // still not completly initialized, leave the stuff in the queue
            continue;
        }

        handleQueuedFetchTextRequests(deviceOnFetch);
    }
}

inline void TextFetchHandler::threadFunction()
{
    while (true)
    {
        std::unique_lock<std::recursive_mutex> lock(m_mutex);

        if (m_stop)
        {
            return;
        }

        handleQueuedDevicesToInit();

        handleQueuedFetchTextRequests();

        m_condVar.wait(lock);
    }
}

inline DFL::Locale::LanguageTag TextFetchHandler::setActiveLanguage(LocalizationClient& localization)
{
    const auto& langs = localization.supportedLanguages();
    if (langs.empty())
    {
        return DFL::Locale::LanguageTag{};
    }

    // when connecting to multiple devices have some variation in the active language
    m_activeLanguageCounter++;
    if (m_activeLanguageCounter >= langs.size())
    {
        m_activeLanguageCounter = 0;
    }
    auto choosenLang = langs[m_activeLanguageCounter];
    localization.setActiveLanguage(choosenLang);
    return choosenLang;
}

inline void FetchQueue::push(Data data)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.push(std::move(data));
}

inline FetchQueue::Data FetchQueue::pop()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_queue.empty())
    {
        THROW_EXCEPTION("Queue is empty");
    }
    auto result = std::move(m_queue.front());
    m_queue.pop();
    return result;
}

inline bool FetchQueue::empty() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.empty();
}

inline void TextFetchErrors::add(std::string msg)
{
    m_messages.push_back(std::move(msg));
}

inline std::string TextFetchErrors::errors() const
{
    std::string result;
    for (const auto& s : m_messages)
    {
        if (!result.empty())
        {
            result.append("\n");
        }
        result.append(s);
    }
    return result;
}

inline int Notifiers::add(const LocalizationClientRequestCompletePtr& notifier)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    cleanup();
    auto id = ++m_counter;
    m_notifiers[id] = Value{notifier.get(), ValueStatus::Active};
    return id;
}

inline void Notifiers::remove(int id)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_notifiers.find(id);
    if (it == m_notifiers.end())
    {
        return;
    }
    it->second.status = ValueStatus::MarkedForDeletion;
}

inline void Notifiers::cleanup()
{
    for (auto it = m_notifiers.begin(); it != m_notifiers.end();)
    {
        if (it->second.status == ValueStatus::MarkedForDeletion)
        {
            it = m_notifiers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

}
/// [SdcClientLocalizationSample]
