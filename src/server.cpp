/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <sstream>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include "sformat.h"
#include <S31/Log/Public/Logger.h>
#include <S31/TestLog/S31Only/LogFile.h>

#include <Framework/Crypto/Public/Environment.h>

#include <Framework/Utils/Public/Scope.h>

#include "absl/flags/flag.h"
// #include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>

#include "proto/medibus.grpc.pb.h"

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>



#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Public/Common/CoreConfiguration.h>
#include <S31/Sdc/Public/Common/InstanceIdentifierFactory.h>
#include <S31/Sdc/Public/Common/S31CoreFactory.h>
#include <S31/Sdc/Public/Common/ThreadPoolDispatcher.h>
#include <S31/Sdc/Public/Device/LocalDevice.h>
#include <S31/Sdc/Test/Public/Common/CoreConfigurationHelper.h> // for test certificates
#include <S31/Utils/Public/MdibAccessUtil.h>

#include <Framework/Crypto/Public/RandomUuidGenerator.h>
#include <Framework/Mdib/Public/MdibFactory.h>
#include <Framework/Mdib/Public/Model/CodedValueConstants.h>
#include <Framework/Mdib/Public/Model/Component/MetaDataBuilder.h>
#include <Framework/Mdib/Public/Model/Context/PatientDemographicsCoreDataBuilder.h>
#include <Framework/Mdib/Public/Model/ExtensionKnown/CodedAttributes.h>
#include <Framework/Mdib/Public/Model/ExtensionKnown/SdpiExtensions.h>
#include <Framework/Mdib/Public/WriteResultIo.h>
#include <Framework/Utils/Public/ScopeExit.h>
#include "google/protobuf/util/delimited_message_util.h"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"
ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerAsyncReader;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;
using medibus::Medibus;
using medibus::MedibusReply;
using medibus::MedibusRequest;
using medibus::LoopRequest;
using medibus::DelimitedLoopRequest;
using namespace google::protobuf::util;
using namespace google::protobuf::io;

using DFL::Locale::Utf8;

S31_LOGGER("TestDevice");

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

namespace S31
{
    class DataQueueSingleton
    {
    public:
        static DataQueueSingleton& instance() {
            static DataQueueSingleton instance;
            return instance;
        }
        DataQueueSingleton(const DataQueueSingleton&) = delete;
        DataQueueSingleton& operator = (const DataQueueSingleton&) = delete;

        std::tuple<bool, bool, int> try_push(std::string instanceId, int sequenceId) {
            bool isFirstTime = false;
            bool isSuccess = false;
            std::lock_guard<std::mutex> lock(m);
            auto iter = instance_sequence_que.find(instanceId);
            if (iter == instance_sequence_que.end()) {
                // first time, then set initial value of sequenceId is 0
                // the sequenceId from message must begin from 1.
                isFirstTime = true;
                //instance_sequence_que.emplace(instanceId, 0);
            }

            // get the current value of sequenceId and plus one equal to self
            // instance_sequence_que[instanceId] must have value, because above code will add initial value if the key is first time found.
            if (sequenceId == instance_sequence_que[instanceId] + 1) {
                //instance_sequence_que[instanceId] = sequenceId;
                isSuccess = true;
            }
            return std::tuple<bool, bool, int>(isSuccess, isFirstTime, sequenceId);
        };
    // first parameter is for checking whether my turn(thread) to handle msg
    // secodn parameter is for checking whether is the first time for this instance
    std::tuple<bool,bool,int> push(std::string instanceId, int sequenceId) {
            bool isFirstTime = false;
            bool isSuccess = false;
            std::lock_guard<std::mutex> lock(m);
            auto iter = instance_sequence_que.find(instanceId);
            if (iter == instance_sequence_que.end()) {
                // first time, then set initial value of sequenceId is 0
                // the sequenceId from message must begin from 1.
                isFirstTime = true;
                instance_sequence_que.emplace(instanceId, 0);
            }
            
            // get the current value of sequenceId and plus one equal to self
            // instance_sequence_que[instanceId] must have value, because above code will add initial value if the key is first time found.
            if (sequenceId == instance_sequence_que[instanceId] + 1) {
                instance_sequence_que[instanceId] = sequenceId;
                isSuccess = true;
            }
            return std::tuple<bool,bool,int>(isSuccess, isFirstTime, sequenceId);
        };
        void update(std::string instanceId, int sequenceId) {
            if (instance_sequence_que.empty()) {
                return;
            }
            std::lock_guard<std::mutex> lock(m);
            //instance_sequence_que.erase(remove_if(begin(instance_sequence_que), end(instance_sequence_que), [instanceId](auto iter) { return *iter == instanceId; }));
            auto iter = instance_sequence_que.find(instanceId);
            if (iter != instance_sequence_que.end()) {
                instance_sequence_que.erase(iter);
                instance_sequence_que.emplace(instanceId, sequenceId);
            }
        }
    private:
        DataQueueSingleton() {}
        ~DataQueueSingleton() {}
    private:
        static std::map<std::string, int> instance_sequence_que;
        static std::mutex m;
    };
    std::map<std::string, int> DataQueueSingleton::instance_sequence_que;
    std::mutex DataQueueSingleton::m;

    template<typename ... Args>
    static std::string str_format(const std::string& format, Args ... args)
    {
        auto size_buf = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
        std::unique_ptr<char[]> buf(new(std::nothrow) char[size_buf]);

        if (!buf)
            return std::string("");

        std::snprintf(buf.get(), size_buf, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size_buf - 1);
    }

    // boost log file
    src::logger lg;
    // Create a text file sink
    typedef sinks::synchronous_sink< sinks::text_file_backend > file_sink;
    boost::shared_ptr< file_sink > sink(new file_sink(
        keywords::file_name = "medibus.log",                       // file name pattern
        keywords::target_file_name = "%Y%m%d_%H%M%S_%5N.log",   // file name pattern
        keywords::rotation_size = 1638400                         // rotation size, in characters
    ));
    void init_logging()
    { 
        
        // Set up where the rotated files will be stored
        sink->locked_backend()->set_file_collector(sinks::file::make_collector(
            keywords::target = "logs",                              // where to store rotated files
            keywords::max_size = 100 * 1024 * 1024,                  // maximum total size of the stored files, in bytes
            keywords::min_free_space = 100 * 1024 * 1024,           // minimum free space on the drive, in bytes
            keywords::max_files = 512                               // maximum number of stored files
        ));

        // Upon restart, scan the target directory for files matching the file_name pattern
        sink->locked_backend()->scan_for_files();

        sink->set_formatter
        (
            expr::format("%1%: [%2%] - %3%")
            % expr::attr< unsigned int >("RecordID")
            % expr::attr< boost::posix_time::ptime >("TimeStamp")
            //% expr::attr< attrs::current_thread_id::value_type >("ThreadID")
            % expr::smessage
        );

        // Add it to the core
        logging::core::get()->add_sink(sink);

        // Add some attributes too
        logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
        logging::core::get()->add_global_attribute("RecordID", attrs::counter< unsigned int >());
        //logging::core::get()->add_global_attribute("ThreadID", attrs::current_thread_id());

    }


    namespace Sdc
    {
        class IDispatcher;
        class LocalDevice;
    }
    namespace medibus
    {
        class CallData
        {
        public:
            CallData(Medibus::AsyncService* pService, ServerCompletionQueue* pCq)
                :m_pService(pService), m_pCq(pCq), m_eStatus(CREATE) {};
            virtual ~CallData() {}
            virtual void Proceed(bool ok) = 0;
        public:
            Medibus::AsyncService* m_pService;
            ServerCompletionQueue* m_pCq;
            enum CallStatus
            {
                CREATE,
                PROCESS,
                FINISH
            };
            CallStatus m_eStatus; // The current serving state.
        };


        class CurMeasuredDataCP1Request final : public CallData
        {
        public:
            explicit CurMeasuredDataCP1Request(Medibus::AsyncService* pService, ServerCompletionQueue* pCq)
                : CallData(pService, pCq), m_Responder(&m_ctx)
            {
                Proceed(true);
            }

            ~CurMeasuredDataCP1Request() {}

            void Proceed(bool ok) override
            {
                std::cout << "this:  " << this
                    << "CurMeasuredDataCP1Request Proceed(), status: " << m_eStatus
                    << std::endl;
                if (m_eStatus == CREATE)
                {
                    std::cout << "this:  " << this
                        << "CurMeasuredDataCP1Request Proceed(), status: " << m_eStatus
                        << std::endl;
                    // Make this instance progress to the PROCESS state.
                    m_eStatus = PROCESS;
                    // As part of the initial CREATE state, we *request* that the system
                    // start processing SayHello requests. In this request, "this" acts are
                    // the tag uniquely identifying the request (so that different CallData
                    // instances can serve different requests concurrently), in this case
                    // the memory address of this CallData instance.
                    m_pService->RequestCurMeasuredDataCP1(&m_ctx, &m_Request, &m_Responder, m_pCq, m_pCq,
                        this);

                }
                else if (m_eStatus == PROCESS)
                {
                    if (!ok)
                    {
                        // Not ok in PROCESS means the server has been Shutdown
                        // before the call got matched to an incoming RPC.
                        delete this;
                    }
                    // Spawn a new CallData instance to serve new clients while we process
                    // the one for this CallData. The instance will deallocate itself as
                    // part of its FINISH state.
                    new CurMeasuredDataCP1Request(m_pService, m_pCq);

                    // The actual processing.
                    /*std::string prefix("Hello ");
                    std::string tmp;
                    for (int i = 0; i < request_.deviceresponds_size(); i++)
                    {
                      tmp += request_.deviceresponds(i).code() + request_.deviceresponds(i).value() + request_.deviceresponds(i).unit();
                    }
                    reply_.set_message(prefix + tmp);
                    std::cout << "Binding " << this << "Receive message  "  << prefix + tmp << std::endl;*/
                    // And we are done! Let the gRPC runtime know we've finished, using the
                    // memory address of this instance as the uniquely identifying tag for
                    // the event.
                    m_eStatus = FINISH;
                    m_Responder.Finish(m_Reply, grpc::Status::OK, this);
                }
                else
                {
                    GPR_ASSERT(m_eStatus == FINISH);
                    // Once in the FINISH state, deallocate ourselves (CallData).
                    delete this;
                }
            }

        private:
            ServerAsyncResponseWriter<MedibusReply> m_Responder;
            MedibusRequest m_Request;
            MedibusReply m_Reply;
            ServerContext m_ctx;
        };

        class CurDeviceSettingsRequest final : public CallData
        {
        public:
            explicit CurDeviceSettingsRequest(Medibus::AsyncService* pService, ServerCompletionQueue* pCq)
                : CallData(pService, pCq), m_Responder(&m_ctx)
            {
                Proceed(true);
            }

            void Proceed(bool ok) override
            {
                std::cout << "this:  " << this
                    << "CurDeviceSettingsRequest Proceed(), status: " << m_eStatus
                    << std::endl;
                if (m_eStatus == CREATE)
                {
                    std::cout << "this:  " << this
                        << "CurDeviceSettingsRequest Proceed(), status: " << m_eStatus
                        << std::endl;
                    // Make this instance progress to the PROCESS state.
                    m_eStatus = PROCESS;

                    // As part of the initial CREATE state, we *request* that the system
                    // start processing SayHello requests. In this request, "this" acts are
                    // the tag uniquely identifying the request (so that different CallData
                    // instances can serve different requests concurrently), in this case
                    // the memory address of this CallData instance.
                    m_pService->RequestCurDeviceSettings(&m_ctx, &m_Request, &m_Responder, m_pCq, m_pCq,
                        this);
                }
                else if (m_eStatus == PROCESS)
                {
                    if (!ok)
                    {
                        // Not ok in PROCESS means the server has been Shutdown
                        // before the call got matched to an incoming RPC.
                        delete this;
                    }
                    // Spawn a new CallData instance to serve new clients while we process
                    // the one for this CallData. The instance will deallocate itself as
                    // part of its FINISH state.
                    new CurDeviceSettingsRequest(m_pService, m_pCq);

                    // The actual processing.
                   /* std::string prefix("Hello ");
                    std::string tmp;
                    for (int i = 0; i < request_.deviceresponds_size(); i++)
                    {
                        tmp += request_.deviceresponds(i).code() + request_.deviceresponds(i).value() + request_.deviceresponds(i).unit();
                    }
                    reply_.set_message(prefix + tmp);*/

                    // And we are done! Let the gRPC runtime know we've finished, using the
                    // memory address of this instance as the uniquely identifying tag for
                    // the event.
                    m_eStatus = FINISH;
                    m_Responder.Finish(m_Reply, grpc::Status::OK, this);
                }
                else
                {
                    GPR_ASSERT(m_eStatus == FINISH);
                    // Once in the FINISH state, deallocate ourselves (CallData).
                    delete this;
                }
            }

        private:
            ServerAsyncResponseWriter<MedibusReply> m_Responder;
            MedibusRequest m_Request;
            MedibusReply m_Reply;
            ServerContext m_ctx;
        };

        class CurLowAlarmLimitsCP1Request final : public CallData
        {
        public:
            explicit CurLowAlarmLimitsCP1Request(Medibus::AsyncService* pService, ServerCompletionQueue* pCq)
                : CallData(pService, pCq), m_Responder(&m_ctx)
            {
                Proceed(true);
            }

            void Proceed(bool ok) override
            {
                std::cout << "this:  " << this
                    << "CurLowAlarmLimitsCP1Request Proceed(), status: " << m_eStatus
                    << std::endl;
                if (m_eStatus == CREATE)
                {
                    std::cout << "this:  " << this
                        << "CurLowAlarmLimitsCP1Request Proceed(), status: " << m_eStatus
                        << std::endl;

                    // Make this instance progress to the PROCESS state.
                    m_eStatus = PROCESS;

                    // As part of the initial CREATE state, we *request* that the system
                    // start processing SayHello requests. In this request, "this" acts are
                    // the tag uniquely identifying the request (so that different CallData
                    // instances can serve different requests concurrently), in this case
                    // the memory address of this CallData instance.
                    m_pService->RequestCurLowAlarmLimitsCP1(&m_ctx, &m_Request, &m_Responder, m_pCq, m_pCq,
                        this);
                }
                else if (m_eStatus == PROCESS)
                {
                    if (!ok)
                    {
                        // Not ok in PROCESS means the server has been Shutdown
                        // before the call got matched to an incoming RPC.
                        delete this;
                    }
                    // Spawn a new CallData instance to serve new clients while we process
                    // the one for this CallData. The instance will deallocate itself as
                    // part of its FINISH state.
                    new CurLowAlarmLimitsCP1Request(m_pService, m_pCq);

                    // The actual processing.
                    /*std::string prefix("Hello ");
                    std::string tmp;
                    for (int i = 0; i < request_.deviceresponds_size(); i++)
                    {
                        tmp += request_.deviceresponds(i).code() + request_.deviceresponds(i).value() + request_.deviceresponds(i).unit();
                    }
                    reply_.set_message(prefix + tmp);*/

                    // And we are done! Let the gRPC runtime know we've finished, using the
                    // memory address of this instance as the uniquely identifying tag for
                    // the event.
                    m_eStatus = FINISH;
                    m_Responder.Finish(m_Reply, grpc::Status::OK, this);
                }
                else
                {
                    GPR_ASSERT(m_eStatus == FINISH);
                    // Once in the FINISH state, deallocate ourselves (CallData).
                    delete this;
                }
            }

        private:
            ServerAsyncResponseWriter<MedibusReply> m_Responder;
            MedibusRequest m_Request;
            MedibusReply m_Reply;
            ServerContext m_ctx;
        };

        class DataInEachLoopRequest final : public CallData
        {
        public:
            explicit DataInEachLoopRequest(Medibus::AsyncService* pService, ServerCompletionQueue* pCq)
                : CallData(pService, pCq), m_Responder(&m_ctx), m_stream(&m_ctx)
            {
                Proceed(true);
            }

            void Proceed(bool ok) override
            {
                if (m_eStatus == CREATE)
                {
                    std::cout << "this:  " << this
                        << "DataInEachLoopRequest Proceed(), status: " << m_eStatus
                        << std::endl;

                    std::string formatted_string = str_format("Waiting for data <{0}> with status <{1}> ", this, m_eStatus);
                    BOOST_LOG(lg) << formatted_string;
                    // Make this instance progress to the PROCESS state.
                    m_eStatus = PROCESS;
                    
                    // As part of the initial CREATE state, we *request* that the system
                    // start processing SayHello requests. In this request, "this" acts are
                    // the tag uniquely identifying the request (so that different CallData
                    // instances can serve different requests concurrently), in this case
                    // the memory address of this CallData instance.
                    m_pService->RequestDataInEachLoop(&m_ctx, &m_stream,m_pCq, m_pCq,
                        this);
                }
                else if (m_eStatus == PROCESS)
                {
                    std::cout << "this:  " << this
                        << "DataInEachLoopRequest Proceed(), status: " << m_eStatus
                        << std::endl;

                    std::string formatted_string = str_format("Processing data <{0}> with status <{1}> ", this, m_eStatus);
                    BOOST_LOG(lg) << formatted_string;
                    if (!ok)
                    {
                        // Not ok in PROCESS means the server has been Shutdown
                        // before the call got matched to an incoming RPC.
                        m_eStatus = FINISH;
                        delete this;
                        return;
                    }
                   
                    // The actual processing.
                    // sometimes read will get nothing, so we must check the id if request 
                    m_stream.Read(&m_LoopRequest, this);
                    if (m_LoopRequest.has_instance_id())
                    {
                        // Spawn a new CallData instance to serve new clients while we process
                        // the one for this CallData. The instance will deallocate itself as
                        // part of its FINISH state.
                        new DataInEachLoopRequest(m_pService, m_pCq);

                        std::string prefix("Hello ");
                        std::string tmp;
                        if (m_LoopRequest.has_cur_measured_data_cp1())
                        {
                            // handle curmeasureddatacp1
                        }
                        if (m_LoopRequest.has_cur_device_settings())
                        {

                            for (int i = 0; i < m_LoopRequest.cur_device_settings().deviceresponds_size(); i++)
                            {
                                auto req = m_LoopRequest.cur_device_settings();
                                /*std::cout << "server side:  "
                                    << "DataInEachLoopRequest Proceed(), status: " << m_eStatus << "\r\n"
                                    << "DataInEachLoopRequest Proceed(), id: " << m_LoopRequest.id() << "\r\n"
                                    << "DataInEachLoopRequest Proceed(), code: " << req.deviceresponds(i).code() << "\r\n"
                                    << "DataInEachLoopRequest Proceed(), value: " << req.deviceresponds(i).value() << "\r\n"
                                    << "DataInEachLoopRequest Proceed(), unit: " << req.deviceresponds(i).unit() << "\r\n"
                                    << std::endl;*/

                                std::string formatted_string = str_format("Receiving data with id=<{0}> and code=<{1}> and value=<{2}> and unit=<{3}> ", m_LoopRequest.instance_id(),
                                    req.deviceresponds(i).code(), req.deviceresponds(i).value(), req.deviceresponds(i).unit());
                                BOOST_LOG(lg) << formatted_string;
                                //tmp += req.deviceresponds(i).code() + req.deviceresponds(i).value() + req.deviceresponds(i).unit();
                            }
                            //m_Reply.set_message(prefix + tmp);
                            
                        }

                        if (m_LoopRequest.has_text_messages())
                        {

                            for (int i = 0; i < m_LoopRequest.text_messages().deviceresponds_size(); i++)
                            {
                                auto req = m_LoopRequest.text_messages();
                                std::string formatted_string = str_format("Receiving data with id=<{0}> and code=<{1}> and value=<{2}> and unit=<{3}> ", m_LoopRequest.instance_id(),
                                    req.deviceresponds(i).code(), req.deviceresponds(i).value(), req.deviceresponds(i).unit());
                                BOOST_LOG(lg) << formatted_string;

                                //tmp += req.deviceresponds(i).code() + req.deviceresponds(i).value() + req.deviceresponds(i).unit();
                            }
                            //m_Reply.set_message(prefix + tmp);
                          
                        }

                        // And we are done! Let the gRPC runtime know we've finished, using the
                        // memory address of this instance as the uniquely identifying tag for
                        // the event.

                        // for client-side stream, we not to send finish status
                        // m_eStatus = FINISH;
                        // m_Responder.Finish(m_Reply, Status::OK, this);
                    }
                    

                }
                else
                {
                    GPR_ASSERT(m_eStatus == FINISH);
                    // Once in the FINISH state, deallocate ourselves (CallData).
                    delete this;
                }
            }

        private:
            ServerAsyncResponseWriter<MedibusReply> m_Responder;
            LoopRequest m_LoopRequest;
            MedibusReply m_Reply;
            ServerContext m_ctx;
            ServerAsyncReader<MedibusReply, LoopRequest> m_stream;
        };


        class DelimitedDataInEachLoopRequest final : public CallData
        {
        public:
            explicit DelimitedDataInEachLoopRequest(Medibus::AsyncService* pService, ServerCompletionQueue* pCq)
                : CallData(pService, pCq), m_Responder(&m_ctx), m_stream(&m_ctx)
            {
                Proceed(true);
            }

            void Proceed(bool ok) override
            {
                if (m_eStatus == CREATE)
                {
                    std::cout << "this:  " << this
                        << "DelimitedDataInEachLoopRequest Proceed(), status: " << m_eStatus
                        << std::endl;

                    /*std::string formatted_string = str_format("Waiting for data <{0}> with status <{1}> ", this, m_eStatus);
                    BOOST_LOG(lg) << formatted_string;*/
                    // Make this instance progress to the PROCESS state.
                    m_eStatus = PROCESS;

                    // As part of the initial CREATE state, we *request* that the system
                    // start processing SayHello requests. In this request, "this" acts are
                    // the tag uniquely identifying the request (so that different CallData
                    // instances can serve different requests concurrently), in this case
                    // the memory address of this CallData instance.
                    m_pService->RequestDelimitedDataInEachLoop(&m_ctx, &m_stream, m_pCq, m_pCq,
                        this);
                }
                else if (m_eStatus == PROCESS)
                {
                    std::string formatted_string;
                   /* std::cout << "this:  " << this
                        << "DelimitedDataInEachLoopRequest Proceed(), status: " << m_eStatus
                        << std::endl;

                    std::string formatted_string = str_format("Processing data <{0}> with status <{1}> ", this, m_eStatus);
                    BOOST_LOG(lg) << formatted_string;*/
                    if (!ok)
                    {
                        // Not ok in PROCESS means the server has been Shutdown
                        // before the call got matched to an incoming RPC.
                        // reset sequence id of current instance
                        // for next new connection from the same instance
                        DataQueueSingleton::instance().update(m_LoopRequest.instance_id(), 0);
                        std::cout << "detect disconnection:  " 
                            << "Instance ID: " << m_LoopRequest.instance_id()
                            << "ThreadID: " << std::this_thread::get_id()
                            << std::endl;

                        std::stringstream ss;
                        ss << std::this_thread::get_id();
                        std::string str = ss.str();
                        formatted_string = SFormat("Detect disconnection with threadid={0} and id={1}  > ", str, m_LoopRequest.instance_id());
                        BOOST_LOG(lg) << formatted_string;

                        // Spawn a new CallData instance to serve new clients while we process
                        // the one for this CallData. The instance will deallocate itself as
                        // part of its FINISH state.
                        // Waiting for new instance ot the same instance with new connection.
                        new DelimitedDataInEachLoopRequest(m_pService, m_pCq);

                        // set current status is FINISH and delete ourselves
                        m_eStatus = FINISH;
                        delete this;

                        return;
                    }

                    // The actual processing.
                    // sometimes read will get nothing, so we must check the id if request 
                    m_stream.Read(&m_DelimitedLoopRequest, this);
                    bool clean_eof = true;
                    std::stringstream stream(m_DelimitedLoopRequest.msg());
                    m_DelimitedLoopRequest.clear_msg();
                    IstreamInputStream istream_input_stream(&stream);
                    m_LoopRequest.Clear();
                    ParseDelimitedFromZeroCopyStream(&m_LoopRequest, &istream_input_stream, &clean_eof);
                    if (!clean_eof)
                    {
                        // Spawn a new CallData instance to serve new clients while we process
                        // the one for this CallData. The instance will deallocate itself as
                        // part of its FINISH state.
                        new DelimitedDataInEachLoopRequest(m_pService, m_pCq);

                        // 
                        auto t1 = std::chrono::high_resolution_clock::now();
                        while (1) {
                            
                            auto rtnv = DataQueueSingleton::instance().try_push(m_LoopRequest.instance_id(), m_LoopRequest.sequence_id());
                            if (std::get<0>(rtnv)) {
                                // the sequence id is equal , it's my turn to handle the msg
                                if (m_LoopRequest.has_cur_measured_data_cp1())
                                {
                                    // handle curmeasureddatacp1
                                }
                                if (m_LoopRequest.has_cur_device_settings())
                                {

                                    for (int i = 0; i < m_LoopRequest.cur_device_settings().deviceresponds_size(); i++)
                                    {
                                        auto req = m_LoopRequest.cur_device_settings();
                                        std::cout << "server side:  "
                                            << "DataInEachLoopRequest Proceed(), ThreadId: " << std::this_thread::get_id() << "\r\n"
                                            << "DataInEachLoopRequest Proceed(), status: " << m_eStatus << "\r\n"
                                            << "DataInEachLoopRequest Proceed(), id: " << m_LoopRequest.instance_id() << "\r\n"
                                            << "DataInEachLoopRequest Proceed(), code: " << req.deviceresponds(i).code() << "\r\n"
                                            << "DataInEachLoopRequest Proceed(), value: " << req.deviceresponds(i).value() << "\r\n"
                                            << "DataInEachLoopRequest Proceed(), unit: " << req.deviceresponds(i).unit() << "\r\n"
                                            << std::endl;

                                        std::stringstream ss;
                                        ss << std::this_thread::get_id();
                                        std::string str = ss.str();
                                        formatted_string = SFormat("Receiving device settings with thread id=<{0}> and id=<{1}> and sequence id=<{2}>  code=<{3}>  value=<{4}>  unit=<{5}> ", str, m_LoopRequest.instance_id(),
                                            m_LoopRequest.sequence_id(),  req.deviceresponds(i).code(), req.deviceresponds(i).value(), req.deviceresponds(i).unit());
                                        BOOST_LOG(lg) << formatted_string;
                                    }
                                }

                                if (m_LoopRequest.has_text_messages())
                                {
                                    std::stringstream ss;
                                    ss << std::this_thread::get_id();
                                    std::string str = ss.str();
                                    for (int i = 0; i < m_LoopRequest.text_messages().deviceresponds_size(); i++)
                                    {
                                        auto req = m_LoopRequest.text_messages();
                                        formatted_string = SFormat("Receiving text message with thread id=<{0}> and id={1} and sequence id=<{2}>  code=<{3}>  value=<{4}>  unit=<{5}> ", str, m_LoopRequest.instance_id(),
                                            m_LoopRequest.sequence_id(), req.deviceresponds(i).code(), req.deviceresponds(i).value(), req.deviceresponds(i).unit());
                                        BOOST_LOG(lg) << formatted_string;

                                    }

                                }
                                if (std::get<1>(rtnv)) {
                                    // this is the first time, we get the instance_id, so sdc provider must be created.
                                    // otherwise, sdc provider must skip the creation
                                    // 
                                    // create sdc provider with the instance_id
                                    // all function is called with prefix INSERT in sdc library.
                                }
                                else {
                                    // all function is called with prefix UPDATE in sdc library.
                                }

                                // push data actually
                                // There is conflict if  we call push at the position of try_push(), 
                                // it is possible that another thread get the ownership to handle its owner data. This thread maybe run fast than us.
                                // we must keep the sequence of data.
                                DataQueueSingleton::instance().push(m_LoopRequest.instance_id(), m_LoopRequest.sequence_id());
                                break;
                            }
                            else {
                                // the sequence id is not equal, wait for my turn 
                                // count for 30 seconds, still not my turn, then abandon this msg
                                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                                auto t2 = std::chrono::high_resolution_clock::now();
                                if (std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() > 10) {
                                    if (std::get<2>(rtnv) + 1 > m_LoopRequest.sequence_id()) {
                                        // if the sequence id is greater than self, then do nothing just abandon this msg                                    
                                        std::cout << "wait time(seconds) out:  " << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count()
                                            << "ThreadID: " << std::this_thread::get_id()
                                            << std::endl;
                                        formatted_string = SFormat("Abandoning data with id={0} and sequence_id={1} and wait seconds = {2}> ", m_LoopRequest.instance_id(),
                                            m_LoopRequest.sequence_id(), std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count());
                                        BOOST_LOG(lg) << formatted_string;
                                        break;
                                    }
                                    else {
                                        // if the sequence id is less than self and time is out, then skip the current sequenceid and insert into table and update the sequenceid with the new one(current - 1 = latester one)
                                        // Then handle this data from the beginning of the while loop
                                        DataQueueSingleton::instance().update(m_LoopRequest.instance_id(), m_LoopRequest.sequence_id() - 1);
                                        std::cout << "wait time(seconds) out:  " << std::chrono::duration_cast<std::chrono::minutes>(t2 - t1).count()
                                            << "ThreadID: " << std::this_thread::get_id()
                                            << std::endl;
                                        formatted_string = SFormat("Updating data with id={0} and sequence_id={1} and wait seconds = {2}> ", m_LoopRequest.instance_id(),
                                            m_LoopRequest.sequence_id(), std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count());
                                        BOOST_LOG(lg) << formatted_string;
                                    }
                                }
                            }
                        }
                     
                        

                        // And we are done! Let the gRPC runtime know we've finished, using the
                        // memory address of this instance as the uniquely identifying tag for
                        // the event.

                        // for client-side stream, we not to send finish status
                        // m_eStatus = FINISH;
                        // m_Responder.Finish(m_Reply, Status::OK, this);
                    }


                }
                else
                {
                    GPR_ASSERT(m_eStatus == FINISH);

                    // reset sequence id of current instance
                    // for next new connection from the same instance
                    DataQueueSingleton::instance().update(m_LoopRequest.instance_id(), 0);
                    std::cout << "detect disconnection:  "
                        << "Instance ID: " << m_LoopRequest.instance_id()
                        << "ThreadID: " << std::this_thread::get_id()
                        << std::endl;

                    std::stringstream ss;
                    ss << std::this_thread::get_id();
                    std::string str = ss.str();
                    std::string formatted_string = SFormat("Detect disconnection with thread id={0} and id={1}  > ", str, m_LoopRequest.instance_id());
                    BOOST_LOG(lg) << formatted_string;


                    // Spawn a new CallData instance to serve new clients while we process
                	// the one for this CallData. The instance will deallocate itself as
                	// part of its FINISH state.
                    // Waiting for new instance ot the same instance with new connection.
                    new DelimitedDataInEachLoopRequest(m_pService, m_pCq);


                    // Once in the FINISH state, deallocate ourselves (CallData).
                    delete this;
                }
            }

        private:
            ServerAsyncResponseWriter<MedibusReply> m_Responder;
            DelimitedLoopRequest m_DelimitedLoopRequest;
            LoopRequest m_LoopRequest;
            MedibusReply m_Reply;
            ServerContext m_ctx;
            ServerAsyncReader<MedibusReply, DelimitedLoopRequest> m_stream;
        };
        class ServerImpl final
        {
        public:
            ~ServerImpl()
            {
                m_Server->Shutdown();
                // Always shutdown the completion queue after the server.
                for (auto cq = m_vecpCqs.begin(); cq != m_vecpCqs.end(); ++cq)
                    (*cq)->Shutdown();
            }

            void addSslConfiguration(S31::CoreConfiguration& configuration)
            {
                // It is fine to create test certificates in the sample code ...
                S31::Utils::Test::useTestCertificateWithAllRolesAndWildcardWhitelist(configuration, "medibus");
                // ... and allow test root CAs.
                S31::Utils::Test::addTestRootCas(configuration);
            }

            void initSDC()
            {
                // init SDC
                DFL::Crypto::Environment::init();
                std::shared_ptr<S31::Sdc::LocalDevice>   dpwsDevice;
                S31_STREAM_INFO("starting S31.Core TestProvider");
                DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> localMdibAccess(DFL::Mdib::MdibFactory::createLocalMdibAccess(DFL::Mdib::MdibConstraints::allConstraints()));

                CoreConfiguration configuration;
                configuration.customAppMaxDelay = DFL::Chrono::Milliseconds(100);
                addSslConfiguration(configuration);

                std::string urn = urn = "urn:uuid:" + DFL::Crypto::generateRandomUuidString();
                std::shared_ptr<S31::Sdc::IDispatcher>  dispatcher = std::make_shared<S31::Sdc::ThreadPoolDispatcher>();
                configuration.httpIPv4Port = S31::CoreConfiguration::PORTNUMBER_ANY;
                configuration.udpIPv4Port = S31::CoreConfiguration::PORTNUMBER_ANY;

                configuration.compressionLevel = 9;

                S31::S31CoreFactory s31Factory(DFL::asNotNull(dispatcher), configuration);

                // For device side only it has to be started explicitly,
                // while the client is starting the dispatcher on client start automatically.
                dispatcher->start();

                Sdc::MedicalDpwsData dpwsData{
                        S31::Sdc::EndpointReference{DFL::Net::Uri{urn}},
                        S31::Sdc::MetadataVersion{0U},
                        Sdc::DpwsDeviceMetadata{},
                        Sdc::CompressionConfiguration::Compression };
                Sdc::MedicalDeviceData medicalDevice{ localMdibAccess };

                dpwsDevice = s31Factory.createBicepsDevice(dpwsData, medicalDevice);
                //  Start the S31 device
                dpwsDevice->start();
            }
            // There is no shutdown handling in this code.
            void Run(uint16_t port)
            {
                std::string server_address = absl::StrFormat("0.0.0.0:%d", port);

                ServerBuilder builder;
                // Listen on the given address without any authentication mechanism.
                int selected_port;
                builder.AddListeningPort(server_address, grpc::InsecureServerCredentials(), &selected_port);
                if (selected_port == 0)
                {
                    std::cerr << "Could not bind to a port" << std::endl;
                    exit(EXIT_FAILURE);
                }
                // Register "service_" as the instance through which we'll communicate with
                // clients. In this case it corresponds to an *asynchronous* service.
                builder.RegisterService(&m_Service);
                // Get hold of the completion queue used for the asynchronous communication
                // with the gRPC runtime.
                for (int i = 0; i < m_nNumThreads; i++)
                    m_vecpCqs.emplace_back(builder.AddCompletionQueue());
                // Finally assemble the server.
                m_Server = builder.BuildAndStart();
                std::cout << "Server listening on " << server_address << std::endl;

                // Proceed to the server's main loop.
                HandleRpcs();
            }

        private:
            void ServeThread(int i)
            {
                void* tag;
                bool ok;
                while (m_vecpCqs[i]->Next(&tag, &ok))
                {
                    /*auto proceed = static_cast<std::function<void(bool)> *>(tag);
                    (*proceed)(ok);*/
                    static_cast<CallData*>(tag)->Proceed(ok);
                }
            }
            // This can be run in multiple threads if needed.
            void HandleRpcs()
            {
                std::vector<std::thread> threads;
                for (int i = 0; i < m_nNumThreads; i++)
                {
                    // Spawn a new CallData instance to serve new clients.
                   /* new CurMeasuredDataCP1Request(&m_Service, m_vecpCqs[i].get());
                    new CurDeviceSettingsRequest(&m_Service, m_vecpCqs[i].get());
                    new CurLowAlarmLimitsCP1Request(&m_Service, m_vecpCqs[i].get());*/
                    new DelimitedDataInEachLoopRequest(&m_Service, m_vecpCqs[i].get());
                    threads.emplace_back(std::thread(&ServerImpl::ServeThread, this, i));
                }
                for (auto thr = threads.begin(); thr != threads.end(); ++thr)
                    thr->join();
            }

            std::vector<std::unique_ptr<ServerCompletionQueue>> m_vecpCqs;
            Medibus::AsyncService m_Service;
            std::unique_ptr<Server> m_Server;
            int m_nNumThreads{ 64 };
        };

    }
}
int main(int argc, char **argv)
{
  S31::init_logging();
  // absl::ParseCommandLine(argc, argv);
  S31::medibus::ServerImpl server;
  server.Run(absl::GetFlag(FLAGS_port));

  return 0;
}
