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

#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "absl/flags/flag.h"
// #include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>

#include "../proto/medibus.grpc.pb.h"

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;
using medibus::Medibus;
using medibus::MedibusReply;
using medibus::MedibusRequest;
namespace medibus
{
  class RequestData
  {
  public:
   RequestData(Medibus::AsyncService* _service, ServerCompletionQueue* _cq)
          :service(_service), cq(_cq) {};
  public:
    Medibus::AsyncService *service;
    ServerCompletionQueue *cq;
  };
  // Base class used to cast the void* tags we get from
  // the completion queue and call Proceed() on them.
  class Request
  {
  public:
    virtual void Proceed(bool ok) = 0;
  };

  class CurMeasuredDataCP1Request final : public Request
  {
  public:
    explicit CurMeasuredDataCP1Request(std::shared_ptr<RequestData> data)
        : data_(data), responder_(&ctx_), status_(CREATE)
    {

      /*proceed = [&](bool ok)
      { Proceed(ok); };*/
      Proceed(true);
    }

    void Proceed(bool ok)
    {
      if (status_ == CREATE)
      {

        // Make this instance progress to the PROCESS state.
        status_ = PROCESS;
        std::cout << "Prepare for binding  " << this << std::endl;
        // As part of the initial CREATE state, we *request* that the system
        // start processing SayHello requests. In this request, "this" acts are
        // the tag uniquely identifying the request (so that different CallData
        // instances can serve different requests concurrently), in this case
        // the memory address of this CallData instance.
        data_->service->RequestCurMeasuredDataCP1(&ctx_, &request_, &responder_, data_->cq, data_->cq,
                                                  this);
      }
      else if (status_ == PROCESS)
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
        new CurMeasuredDataCP1Request(data_);

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
        status_ = FINISH;
        responder_.Finish(reply_, Status::OK, this);
      }
      else
      {
        GPR_ASSERT(status_ == FINISH);
        // Once in the FINISH state, deallocate ourselves (CallData).
        delete this;
      }
    }

    //std::function<void(bool)> proceed;

  private:
    std::shared_ptr<RequestData> data_;
    ServerContext ctx_;
    ServerAsyncResponseWriter<MedibusReply> responder_;
    MedibusRequest request_;
    MedibusReply reply_;
    enum CallStatus
    {
      CREATE,
      PROCESS,
      FINISH
    };
    CallStatus status_; // The current serving state.
  };

  class CurDeviceSettingsRequest final : public Request
  {
  public:
      explicit CurDeviceSettingsRequest(std::shared_ptr<RequestData> data)
          : data_(data), responder_(&ctx_), status_(CREATE)
      {
          /*proceed = [&](bool ok)
          { Proceed(ok); };*/
          Proceed(true);
      }

      void Proceed(bool ok)
      {
          if (status_ == CREATE)
          {

              // Make this instance progress to the PROCESS state.
              status_ = PROCESS;

              // As part of the initial CREATE state, we *request* that the system
              // start processing SayHello requests. In this request, "this" acts are
              // the tag uniquely identifying the request (so that different CallData
              // instances can serve different requests concurrently), in this case
              // the memory address of this CallData instance.
              data_->service->RequestCurDeviceSettings(&ctx_, &request_, &responder_, data_->cq, data_->cq,
                  this);
          }
          else if (status_ == PROCESS)
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
              new CurDeviceSettingsRequest(data_);

              // The actual processing.
              std::string prefix("Hello ");
              std::string tmp;
              for (int i = 0; i < request_.deviceresponds_size(); i++)
              {
                  tmp += request_.deviceresponds(i).code() + request_.deviceresponds(i).value() + request_.deviceresponds(i).unit();
              }
              reply_.set_message(prefix + tmp);

              // And we are done! Let the gRPC runtime know we've finished, using the
              // memory address of this instance as the uniquely identifying tag for
              // the event.
              status_ = FINISH;
              responder_.Finish(reply_, Status::OK, this);
          }
          else
          {
              GPR_ASSERT(status_ == FINISH);
              // Once in the FINISH state, deallocate ourselves (CallData).
              delete this;
          }
      }

      //std::function<void(bool)> proceed;

  private:
      std::shared_ptr<RequestData> data_;
      ServerContext ctx_;
      ServerAsyncResponseWriter<MedibusReply> responder_;
      MedibusRequest request_;
      MedibusReply reply_;
      enum CallStatus
      {
          CREATE,
          PROCESS,
          FINISH
      };
      CallStatus status_; // The current serving state.
  };

  class CurLowAlarmLimitsCP1Request final : public Request
  {
  public:
      explicit CurLowAlarmLimitsCP1Request(std::shared_ptr<RequestData> data)
          : data_(data), responder_(&ctx_), status_(CREATE)
      {
          /*proceed = [&](bool ok)
          { Proceed(ok); };*/
          Proceed(true);
      }

      void Proceed(bool ok)
      {
          if (status_ == CREATE)
          {

              // Make this instance progress to the PROCESS state.
              status_ = PROCESS;

              // As part of the initial CREATE state, we *request* that the system
              // start processing SayHello requests. In this request, "this" acts are
              // the tag uniquely identifying the request (so that different CallData
              // instances can serve different requests concurrently), in this case
              // the memory address of this CallData instance.
              data_->service->RequestCurLowAlarmLimitsCP1(&ctx_, &request_, &responder_, data_->cq, data_->cq,
                  this);
          }
          else if (status_ == PROCESS)
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
              new CurLowAlarmLimitsCP1Request(data_);

              // The actual processing.
              std::string prefix("Hello ");
              std::string tmp;
              for (int i = 0; i < request_.deviceresponds_size(); i++)
              {
                  tmp += request_.deviceresponds(i).code() + request_.deviceresponds(i).value() + request_.deviceresponds(i).unit();
              }
              reply_.set_message(prefix + tmp);

              // And we are done! Let the gRPC runtime know we've finished, using the
              // memory address of this instance as the uniquely identifying tag for
              // the event.
              status_ = FINISH;
              responder_.Finish(reply_, Status::OK, this);
          }
          else
          {
              GPR_ASSERT(status_ == FINISH);
              // Once in the FINISH state, deallocate ourselves (CallData).
              delete this;
          }
      }

      //std::function<void(bool)> proceed;

  private:
      std::shared_ptr<RequestData> data_;
      ServerContext ctx_;
      ServerAsyncResponseWriter<MedibusReply> responder_;
      MedibusRequest request_;
      MedibusReply reply_;
      enum CallStatus
      {
          CREATE,
          PROCESS,
          FINISH
      };
      CallStatus status_; // The current serving state.
  };

  class ServerImpl final
  {
  public:
    ~ServerImpl()
    {
      server_->Shutdown();
      // Always shutdown the completion queue after the server.
      for (auto cq = cqs_.begin(); cq != cqs_.end(); ++cq)
        (*cq)->Shutdown();
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
      builder.RegisterService(&service_);
      // Get hold of the completion queue used for the asynchronous communication
      // with the gRPC runtime.
      for (int i = 0; i < num_threads_; i++)
        cqs_.emplace_back(builder.AddCompletionQueue());
      // Finally assemble the server.
      server_ = builder.BuildAndStart();
      std::cout << "Server listening on " << server_address << std::endl;

      // Proceed to the server's main loop.
      HandleRpcs();
    }

  private:
    void ServeThread(int i)
    {
      void *tag;
      bool ok;
      while (cqs_[i]->Next(&tag, &ok))
      {
        /*auto proceed = static_cast<std::function<void(bool)> *>(tag);
        (*proceed)(ok);*/
        static_cast<Request*>(tag)->Proceed(ok);
      }
    }
    // This can be run in multiple threads if needed.
    void HandleRpcs()
    {
      std::vector<std::thread> threads;
      for (int i = 0; i < num_threads_; i++)
      {
          std::shared_ptr<RequestData> data = std::make_shared<RequestData>( &service_, cqs_[i].get());
        // Spawn a new CallData instance to serve new clients.
        new CurMeasuredDataCP1Request(data);
        new CurDeviceSettingsRequest(data);
        new CurLowAlarmLimitsCP1Request(data);
         threads.emplace_back(std::thread(&ServerImpl::ServeThread, this, i));
      }
      //server_->Shutdown(std::chrono::system_clock::now());
      for (auto thr = threads.begin(); thr != threads.end(); thr++)
        thr->join();
    }

    std::vector<std::unique_ptr<ServerCompletionQueue>> cqs_;
    Medibus::AsyncService service_;
    std::unique_ptr<Server> server_;
    int num_threads_{5};
  };

}
int main(int argc, char **argv)
{
  // absl::ParseCommandLine(argc, argv);
  medibus::ServerImpl server;
  server.Run(absl::GetFlag(FLAGS_port));

  return 0;
}
