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
#include <json.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <thread>
#include "sformat.h"

#include "absl/flags/flag.h"
#include "absl/strings/str_format.h"

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

#include "google/protobuf/util/delimited_message_util.h"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "SdcProvider.h"
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
using json = nlohmann::json;

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

namespace MedibusServer
{
	struct MetricInfo
	{
		std::string MedibusCode;
		std::string MedibusCodePage;
		std::string CurAllowedValueCode;
		std::string CurAllowedValue;
		std::vector<std::string> AllowedValueCodes;
		std::vector<std::string> AllowedValues;
		std::string UnitCode;
		std::string CF10TypeCode;
		std::string Context;
		std::string CF10TypeCodeDes;
		std::string MedicalClass;
		std::string Category;
		std::string Availability;
		std::string Derivation;
		std::string Resolution;
		std::string DeterminationPeriod;
		std::string MaxDelayTime;
		std::string LifeTimePeriod;
		std::string LowRange;
		std::string UpperRange;
		std::string VmdHandle;
		std::string VmdCF10Code;
		std::string VmdCF10CodeDes;
		std::string ChannelHandle;
		std::string ChannelCF10Code;
		std::string ChannelCF10CodeDes;
	};

	struct DeviceInfo
	{
		std::string DeviceName;
		std::string DeviceId;
		std::string CF10TypeCode;
		std::string Context;
		std::string CF10TypeCodeDes;
	};

	class JsonHandlerSingleton
	{
	public:
		static JsonHandlerSingleton& instance() {
			static JsonHandlerSingleton instance;
			return instance;
		}
		JsonHandlerSingleton(const JsonHandlerSingleton&) = delete;
		JsonHandlerSingleton& operator = (const JsonHandlerSingleton&) = delete;

		static bool GetDeviceInfo(const std::string& strDeviceId, DeviceInfo& deviceInfo)
		{
			if (device_identification_map.find(strDeviceId) != device_identification_map.end())
			{
				deviceInfo = device_identification_map[strDeviceId];
				return true;
			}
			return false;
		}

		static bool GetDeviceSettings(const std::string& strMedibusCode, MetricInfo& metricInfo)
		{
			if (device_settings_map.find(strMedibusCode) != device_settings_map.end())
			{
				metricInfo = device_settings_map[strMedibusCode];
				return true;
			}
			return false;
		}

		static bool GetMeasuredDataAndAlarmLimits1(const std::string& strMedibusCode, MetricInfo& metricInfo)
		{
			if (measured_data_and_alarm_limits1_map.find(strMedibusCode) != measured_data_and_alarm_limits1_map.end())
			{
				metricInfo = measured_data_and_alarm_limits1_map[strMedibusCode];
				return true;
			}
			return false;
		}

		static bool GetMeasuredDataAndAlarmLimits2(const std::string& strMedibusCode, MetricInfo& metricInfo)
		{
			if (measured_data_and_alarm_limits2_map.find(strMedibusCode) != measured_data_and_alarm_limits2_map.end())
			{
				metricInfo = measured_data_and_alarm_limits2_map[strMedibusCode];
				return true;
			}
			return false;
		}

		static bool GetTextMessage(const std::string& strMedibusCode, MetricInfo& metricInfo)
		{
			if (text_message_map.find(strMedibusCode) != text_message_map.end())
			{
				metricInfo = text_message_map[strMedibusCode];
				return true;
			}
			return false;
		}
	private:
		json loadDataFromJson(const std::string& strFileName)
		{
			std::ifstream f(strFileName.c_str());

			json::parser_callback_t cb = [](int depth, json::parse_event_t event, json& parsed)
			{
				// skip object elements with key "Device identification numbers"
				if (event == json::parse_event_t::key && parsed == json("Device identification numbers"))
				{
					return false;
				}
				else if (event == json::parse_event_t::key && parsed == json("Issued commands"))
				{
					return false;
				}
				else if (event == json::parse_event_t::key && parsed == json("Responded commands"))
				{
					return false;
				}
				else if (event == json::parse_event_t::key && parsed == json("Measured data and alarm limits"))
				{
					return false;
				}
				else if (event == json::parse_event_t::key && parsed == json("Real-time data"))
				{
					return false;
				}
				else if (event == json::parse_event_t::key && parsed == json("Alarm status"))
				{
					return false;
				}
				else if (event == json::parse_event_t::key && parsed == json("Text messages"))
				{
					return false;
				}
				else
				{
					return true;
				}

			};
			data = json::parse(f);
			return data;
		}

		void getDeviceIdentificationFromJson(const json& data)
		{
			auto dev = data.find("Device identification numbers");
			if (dev != data.end()) {
				if (dev.value().is_array()) {
					for (const auto& element : dev.value()) {
						//std::cout << "Element: " << element << std::endl;
						DeviceInfo devInfo;
						for (const auto& x : element.items()) {
							{
								//std::cout << "key: " << x.key() << ", value: " << x.value() << '\n';
								if (x.key() == "Device") {
									devInfo.DeviceName = x.value();
								}
								else if (x.key() == "ID number") {
									devInfo.DeviceId = x.value();
								}
								else if (x.key() == "CF10 Code") {
									devInfo.CF10TypeCode = x.value();
								}
								else if (x.key() == "Full Device\/Context Alarm") {
									devInfo.Context = x.value();
								}
								else if (x.key() == "CF10Code Description") {
									devInfo.CF10TypeCodeDes = x.value();
								}
							}
						}
						device_identification_map.insert(std::make_pair(devInfo.DeviceId, devInfo));
					}
				}
			}
		}

		void getDeviceSettingsFromJson(const json& data)
		{
			auto dev = data.find("Device settings");
			if (dev != data.end()) {
				if (dev.value().is_array()) {
					for (const auto& element : dev.value()) {
						//std::cout << "Element: " << element << std::endl;
						MetricInfo metricInfo;
						for (const auto& x : element.items()) {
							{
								//std::cout << "key: " << x.key() << ", value: " << x.value() << '\n';
								if (x.key() == "Code") {
									std::string medibuscode = x.value();
									const char last = medibuscode.back();
									if (last == 'h' || last == 'H')
									{
										std::string str = medibuscode.substr(0, medibuscode.size() - 1);
										metricInfo.MedibusCode = str;
									}
									else
									{
										metricInfo.MedibusCode = x.value();
									}
								}
								else if (x.key() == "UnitCode") {
									metricInfo.UnitCode = x.value();
								}
								else if (x.key() == "CF10 Code") {
									metricInfo.CF10TypeCode = x.value();
								}
								else if (x.key() == "Full Device\/Context Alarm") {
									metricInfo.Context = x.value();
								}
								else if (x.key() == "CF10Code Description") {
									metricInfo.CF10TypeCodeDes = x.value();
								}
								else if (x.key() == "MedicalClass") {
									metricInfo.MedicalClass = x.value();
								}
								else if (x.key() == "Category") {
									metricInfo.Category = x.value();
								}
								else if (x.key() == "Availability") {
									metricInfo.Availability = x.value();
								}
								else if (x.key() == "Derivation") {
									metricInfo.Derivation = x.value();
								}
								else if (x.key() == "Resolution") {
									metricInfo.Resolution = x.value();
								}
								else if (x.key() == "Range") {
									std::smatch m;
									std::string val = std::string(x.value());
									std::regex_match(val, m, std::regex(R"(Upper=\"(\d+|\d*\.\d*)\"\sLower=\"(\d+|\d*\.\d*)\")"));
									std::string str1 = m[0].str();
									std::string str2 = m[1].str();
									std::string str3 = m[2].str();
									metricInfo.LowRange = m[2].str();
									metricInfo.UpperRange = m[1].str();
								}
								else if (x.key() == "VMD") {
									metricInfo.VmdHandle = x.value();
								}
								else if (x.key() == "VMD CF10Code") {
									metricInfo.VmdCF10Code = x.value();
								}
								else if (x.key() == "VMD Description") {
									metricInfo.VmdCF10CodeDes = x.value();
								}
								else if (x.key() == "Channel") {
									metricInfo.ChannelHandle = x.value();
								}
								else if (x.key() == "Channel CF10 Code") {
									metricInfo.ChannelCF10Code = x.value();
								}
								else if (x.key() == "Channel Description") {
									metricInfo.ChannelCF10CodeDes = x.value();
								}
							}
						}
						device_settings_map.insert(std::make_pair(metricInfo.MedibusCode, metricInfo));
					}
				}
			}
		}


		void getMeasuredDataAndAlarmLimits1FromJson(const json& data)
		{
			auto dev = data.find("Measured data and alarm limits1");
			if (dev != data.end()) {
				if (dev.value().is_array()) {
					for (const auto& element : dev.value()) {
						//std::cout << "Element: " << element << std::endl;
						MetricInfo metricInfo;
						for (const auto& x : element.items()) {
							{
								//std::cout << "key: " << x.key() << ", value: " << x.value() << '\n';
								if (x.key() == "Code") {
									std::string medibuscode = x.value();
									const char last = medibuscode.back();
									if (last == 'h' || last == 'H')
									{
										std::string str = medibuscode.substr(0, medibuscode.size() - 1);
										metricInfo.MedibusCode = str;
									}
									else
									{
										metricInfo.MedibusCode = x.value();
									}
								}
								else if (x.key() == "Code page") {
									metricInfo.MedibusCodePage = x.value();
								}
								else if (x.key() == "UnitCode") {
									metricInfo.UnitCode = x.value();
								}
								else if (x.key() == "CF10 Code") {
									metricInfo.CF10TypeCode = x.value();
								}
								else if (x.key() == "Full Device\/Context Alarm") {
									metricInfo.Context = x.value();
								}
								else if (x.key() == "CF10Code Description") {
									metricInfo.CF10TypeCodeDes = x.value();
								}
								else if (x.key() == "MedicalClass") {
									metricInfo.MedicalClass = x.value();
								}
								else if (x.key() == "Category") {
									metricInfo.Category = x.value();
								}
								else if (x.key() == "Availability") {
									metricInfo.Availability = x.value();
								}
								else if (x.key() == "Derivation") {
									metricInfo.Derivation = x.value();
								}
								else if (x.key() == "Resolution") {
									metricInfo.Resolution = x.value();
								}
								else if (x.key() == "DeterminationPeriod") {
									metricInfo.DeterminationPeriod = x.value();
								}
								else if (x.key() == "MaxDelayTime") {
									metricInfo.MaxDelayTime = x.value();
								}
								else if (x.key() == "LifeTimePeriod") {
									metricInfo.LifeTimePeriod = x.value();
								}
								else if (x.key() == "Range") {
									std::smatch m;
									std::string val = std::string(x.value());
									std::regex_match(val, m, std::regex(R"(Upper=\"(\d+|\d*\.\d*)\"\sLower=\"(\d+|\d*\.\d*)\")"));
									std::string str1 = m[0].str();
									std::string str2 = m[1].str();
									std::string str3 = m[2].str();
									metricInfo.LowRange = m[2].str();
									metricInfo.UpperRange = m[1].str();
								}
								else if (x.key() == "VMD") {
									metricInfo.VmdHandle = x.value();
								}
								else if (x.key() == "VMD CF10Code") {
									metricInfo.VmdCF10Code = x.value();
								}
								else if (x.key() == "VMD Description") {
									metricInfo.VmdCF10CodeDes = x.value();
								}
								else if (x.key() == "Channel") {
									metricInfo.ChannelHandle = x.value();
								}
								else if (x.key() == "Channel CF10 Code") {
									metricInfo.ChannelCF10Code = x.value();
								}
								else if (x.key() == "Channel Description") {
									metricInfo.ChannelCF10CodeDes = x.value();
								}
							}
						}
						measured_data_and_alarm_limits1_map.insert(std::make_pair(metricInfo.MedibusCode, metricInfo));
					}
				}
			}
		}

		void getMeasuredDataAndAlarmLimits2FromJson(const json& data)
		{
			auto dev = data.find("Measured data and alarm limits2");
			if (dev != data.end()) {
				if (dev.value().is_array()) {
					for (const auto& element : dev.value()) {
						//std::cout << "Element: " << element << std::endl;
						MetricInfo metricInfo;
						for (const auto& x : element.items()) {
							{
								//std::cout << "key: " << x.key() << ", value: " << x.value() << '\n';
								if (x.key() == "Code") {
									std::string medibuscode = x.value();
									const char last = medibuscode.back();
									if (last == 'h' || last == 'H')
									{
										std::string str = medibuscode.substr(0, medibuscode.size() - 1);
										metricInfo.MedibusCode = str;
									}
									else
									{
										metricInfo.MedibusCode = x.value();
									}
								}
								else if (x.key() == "Code page") {
									metricInfo.MedibusCodePage = x.value();
								}
								else if (x.key() == "UnitCode") {
									metricInfo.UnitCode = x.value();
								}
								else if (x.key() == "CF10 Code") {
									metricInfo.CF10TypeCode = x.value();
								}
								else if (x.key() == "Full Device\/Context Alarm") {
									metricInfo.Context = x.value();
								}
								else if (x.key() == "CF10Code Description") {
									metricInfo.CF10TypeCodeDes = x.value();
								}
								else if (x.key() == "MedicalClass") {
									metricInfo.MedicalClass = x.value();
								}
								else if (x.key() == "Category") {
									metricInfo.Category = x.value();
								}
								else if (x.key() == "Availability") {
									metricInfo.Availability = x.value();
								}
								else if (x.key() == "Derivation") {
									metricInfo.Derivation = x.value();
								}
								else if (x.key() == "Resolution") {
									metricInfo.Resolution = x.value();
								}
								else if (x.key() == "DeterminationPeriod") {
									metricInfo.DeterminationPeriod = x.value();
								}
								else if (x.key() == "MaxDelayTime") {
									metricInfo.MaxDelayTime = x.value();
								}
								else if (x.key() == "LifeTimePeriod") {
									metricInfo.LifeTimePeriod = x.value();
								}
								else if (x.key() == "Range") {
									std::smatch m;
									std::string val = std::string(x.value());
									std::regex_match(val, m, std::regex(R"(Upper=\"(\d+|\d*\.\d*)\"\sLower=\"(\d+|\d*\.\d*)\")"));
									std::string str1 = m[0].str();
									std::string str2 = m[1].str();
									std::string str3 = m[2].str();
									metricInfo.LowRange = m[2].str();
									metricInfo.UpperRange = m[1].str();
								}
								else if (x.key() == "VMD") {
									metricInfo.VmdHandle = x.value();
								}
								else if (x.key() == "VMD CF10Code") {
									metricInfo.VmdCF10Code = x.value();
								}
								else if (x.key() == "VMD Description") {
									metricInfo.VmdCF10CodeDes = x.value();
								}
								else if (x.key() == "Channel") {
									metricInfo.ChannelHandle = x.value();
								}
								else if (x.key() == "Channel CF10 Code") {
									metricInfo.ChannelCF10Code = x.value();
								}
								else if (x.key() == "Channel Description") {
									metricInfo.ChannelCF10CodeDes = x.value();
								}
							}
						}
						measured_data_and_alarm_limits2_map.insert(std::make_pair(metricInfo.MedibusCode, metricInfo));
					}
				}
			}
		}


		void getTextMessageFromJson(const json& data)
		{
			auto dev = data.find("Text messages");
			if (dev != data.end()) {
				if (dev.value().is_array()) {
					for (const auto& element : dev.value()) {
						//std::cout << "Element: " << element << std::endl;
						MetricInfo metricInfo;
						for (const auto& x : element.items()) {
							{
								//std::cout << "key: " << x.key() << ", value: " << x.value() << '\n';
								if (x.key() == "Code") {
									std::string medibuscode = x.value();
									const char last = medibuscode.back();
									if (last == 'h' || last == 'H')
									{
										std::string str = medibuscode.substr(0, medibuscode.size() - 1);
										metricInfo.MedibusCode = str;
									}
									else
									{
										metricInfo.MedibusCode = x.value();
									}
								}
								else if (x.key() == "Code page") {
									metricInfo.MedibusCodePage = x.value();
								}
								else if (x.key() == "AllowedValueCode") {
									metricInfo.CurAllowedValueCode = x.value();
								}
								else if (x.key() == "AllowedValue") {
									metricInfo.CurAllowedValue = x.value();
								}
								else if (x.key() == "AllowedValueCodes") {
									metricInfo.AllowedValueCodes = x.value();
								}
								else if (x.key() == "AllowedValues") {
									metricInfo.AllowedValues = x.value();
								}
								else if (x.key() == "UnitCode") {
									metricInfo.UnitCode = x.value();
								}
								else if (x.key() == "CF10 Code") {
									metricInfo.CF10TypeCode = x.value();
								}
								else if (x.key() == "Full Device\/Context Alarm") {
									metricInfo.Context = x.value();
								}
								else if (x.key() == "CF10Code Description") {
									metricInfo.CF10TypeCodeDes = x.value();
								}
								else if (x.key() == "MedicalClass") {
									metricInfo.MedicalClass = x.value();
								}
								else if (x.key() == "Category") {
									metricInfo.Category = x.value();
								}
								else if (x.key() == "Availability") {
									metricInfo.Availability = x.value();
								}
								else if (x.key() == "Derivation") {
									metricInfo.Derivation = x.value();
								}
								else if (x.key() == "Resolution") {
									metricInfo.Resolution = x.value();
								}
								else if (x.key() == "DeterminationPeriod") {
									metricInfo.DeterminationPeriod = x.value();
								}
								else if (x.key() == "MaxDelayTime") {
									metricInfo.MaxDelayTime = x.value();
								}
								else if (x.key() == "LifeTimePeriod") {
									metricInfo.LifeTimePeriod = x.value();
								}
								else if (x.key() == "Range") {
									std::smatch m;
									std::string val = std::string(x.value());
									std::regex_match(val, m, std::regex(R"(Upper=\"(\d+|\d*\.\d*)\"\sLower=\"(\d+|\d*\.\d*)\")"));
									std::string str1 = m[0].str();
									std::string str2 = m[1].str();
									std::string str3 = m[2].str();
									metricInfo.LowRange = m[2].str();
									metricInfo.UpperRange = m[1].str();
								}
								else if (x.key() == "VMD") {
									metricInfo.VmdHandle = x.value();
								}
								else if (x.key() == "VMD CF10Code") {
									metricInfo.VmdCF10Code = x.value();
								}
								else if (x.key() == "VMD Description") {
									metricInfo.VmdCF10CodeDes = x.value();
								}
								else if (x.key() == "Channel") {
									metricInfo.ChannelHandle = x.value();
								}
								else if (x.key() == "Channel CF10 Code") {
									metricInfo.ChannelCF10Code = x.value();
								}
								else if (x.key() == "Channel Description") {
									metricInfo.ChannelCF10CodeDes = x.value();
								}
							}
						}
						text_message_map.insert(std::make_pair(metricInfo.MedibusCode, metricInfo));
					}
				}
			}
		}
		JsonHandlerSingleton()
		{
			//data = loadDataFromJson("D:\\project\\MedibusServer\\medibus\\build\\src\\RelWithDebInfo\\example.json");
			std::string ModulePath;
			char buffer[MAX_PATH];
			GetModuleFileName(NULL, buffer, MAX_PATH);
			std::string::size_type pos = std::string(buffer).find_last_of("\\/");
			if (pos != std::string::npos)
			{
				ModulePath = std::string(buffer).substr(0, pos);
			}

			std::string filePath = ModulePath + "\\" + "example.json";
			data = loadDataFromJson(filePath);
			getDeviceIdentificationFromJson(data);
			getDeviceSettingsFromJson(data);
			getMeasuredDataAndAlarmLimits1FromJson(data);
			getMeasuredDataAndAlarmLimits2FromJson(data);
			getTextMessageFromJson(data);
		}
		~JsonHandlerSingleton() {}

		static std::map<std::string, DeviceInfo> device_identification_map;
		static std::map<std::string, MetricInfo> device_settings_map;
		static std::map<std::string, MetricInfo> measured_data_and_alarm_limits1_map;
		static std::map<std::string, MetricInfo> measured_data_and_alarm_limits2_map;
		static std::map<std::string, MetricInfo> text_message_map;
		static std::mutex m;
		json data;
		
	};
	std::map<std::string, DeviceInfo> JsonHandlerSingleton::device_identification_map;
	std::map<std::string, MetricInfo> JsonHandlerSingleton::device_settings_map;
	std::map<std::string, MetricInfo> JsonHandlerSingleton::measured_data_and_alarm_limits1_map;
	std::map<std::string, MetricInfo> JsonHandlerSingleton::measured_data_and_alarm_limits2_map;
	std::map<std::string, MetricInfo> JsonHandlerSingleton::text_message_map;
	std::mutex JsonHandlerSingleton::m;

	class DataQueueSingleton
	{
	public:
		static DataQueueSingleton& instance() {
			static DataQueueSingleton instance;
			return instance;
		}
		DataQueueSingleton(const DataQueueSingleton&) = delete;
		DataQueueSingleton& operator = (const DataQueueSingleton&) = delete;

		static std::tuple<bool, bool, int> try_push(std::string instanceId, int sequenceId) {
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
		static std::tuple<bool, bool, int> push(std::string instanceId, int sequenceId) {
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
			return std::tuple<bool, bool, int>(isSuccess, isFirstTime, sequenceId);
		};

		static void update(std::string instanceId, int sequenceId) {
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
}
namespace MedibusServer
{
	class ExtraInfo
	{
	public:
		std::string MedibusCode;
		std::string CF10Code;
		std::string CF10CodeDes;
		std::string value;
		std::string facility;
		std::string poc;
		std::string bed;
	};

	class CallData
	{
	public:
		CallData(Medibus::AsyncService* pService, ServerCompletionQueue* pCq, std::map<std::string, std::map<std::string, std::pair<ExtraInfo, int>>>* pDataModel)
			:m_pService(pService), m_pCq(pCq), m_eStatus(CREATE), m_pDataModel(pDataModel) {};
		virtual ~CallData() {}
		virtual void Proceed(bool ok) = 0;

		Medibus::AsyncService* m_pService;
		ServerCompletionQueue* m_pCq;
		enum CallStatus
		{
			CREATE,
			PROCESS,
			FINISH
		};


		CallStatus m_eStatus; // The current serving state.
		// first param is strKey
		// second param is strCode or device id number
		// third param is value object(including facility, poc, bed )
		// forth param is sequenceId
		// sequenceId begin from 1, 0 is reverse
		// if sequenceId equal -1, it means the value is not updated, skip to update SDC
		// if sequenceId equal -2, it means the value is not available for this time(there is scenario  in Text messages), update SDC with Validity = NA
		// if sequenceId equal -3, 
		std::map<std::string, std::map<std::string, std::pair<ExtraInfo, int>>>* m_pDataModel;
	};


	class DelimitedDataInEachLoopRequest final : public CallData
	{
	public:
		explicit DelimitedDataInEachLoopRequest(Medibus::AsyncService* pService, ServerCompletionQueue* pCq, SdcProvider* pProvider,
			std::map<std::string, std::map<std::string, std::pair<ExtraInfo, int>>>* pdatamodel)
			: CallData(pService, pCq, pdatamodel), m_Responder(&m_ctx), m_stream(&m_ctx), m_pProvider(pProvider)
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
					new DelimitedDataInEachLoopRequest(m_pService, m_pCq, m_pProvider, m_pDataModel);

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
					new DelimitedDataInEachLoopRequest(m_pService, m_pCq, m_pProvider, m_pDataModel);

					// 
					auto t1 = std::chrono::high_resolution_clock::now();
					while (1) {

						auto rtnv = DataQueueSingleton::instance().try_push(m_LoopRequest.instance_id(), m_LoopRequest.sequence_id());
						if (std::get<0>(rtnv)) {
							// the sequence id is equal , it's my turn to handle the msg
							if (m_LoopRequest.has_cur_measured_data_cp1())
							{
								// handle curmeasureddatacp1
								std::map<std::string, std::pair<ExtraInfo, int>>& data = m_pDataModel->at("Measured data and alarm limits1");
								for (int i = 0; i < m_LoopRequest.cur_measured_data_cp1().deviceresponds_size(); i++)
								{
									auto req = m_LoopRequest.cur_measured_data_cp1();

									std::stringstream ss;
									ss << std::this_thread::get_id();
									std::string str = ss.str();
									formatted_string = SFormat("Receiving current measured data and alarm limits with thread id=<{0}> and id=<{1}> and sequence id=<{2}>  code=<{3}>  value=<{4}>  unit=<{5}> ", str, m_LoopRequest.instance_id(),
										m_LoopRequest.sequence_id(), req.deviceresponds(i).code(), req.deviceresponds(i).value(), req.deviceresponds(i).unit());
									BOOST_LOG(lg) << formatted_string;

									ExtraInfo medibus_val;
									medibus_val.value = req.deviceresponds(i).value();
									if (data.find(req.deviceresponds(i).code()) == data.end())
									{
										// data is new
										data[req.deviceresponds(i).code()] = std::make_pair(medibus_val, m_LoopRequest.sequence_id());
									}
									else
									{
										if (data[req.deviceresponds(i).code()].first.value != req.deviceresponds(i).value())
										{
											// data need to be updated
											data[req.deviceresponds(i).code()] = std::make_pair(medibus_val, m_LoopRequest.sequence_id());
										}
										else
										{
											// set sequenceid -1 to indicate skip this value when we handle this value to SDC
											data[req.deviceresponds(i).code()] = std::make_pair(medibus_val, -1);
										}
										// if the code of next time is not available, the sequence id is the last time 

									}
								}
								m_data["Measured data and alarm limits1"] = data;
							}
							if (m_LoopRequest.has_cur_low_alarm_limits_cp1())
							{
								// handle CurLowAlarmLimitsCP1
							}
							if (m_LoopRequest.has_cur_high_alarm_limits_cp1())
							{
								// handle CurHighAlarmLimitsCP1
							}
							if (m_LoopRequest.has_cur_alarms_cp1())
							{
								// handle CurAlarmsCP1
							}
							if (m_LoopRequest.has_cur_device_settings())
							{
								std::map<std::string, std::pair<ExtraInfo, int>>& data = m_pDataModel->at("Device settings");
								for (int i = 0; i < m_LoopRequest.cur_device_settings().deviceresponds_size(); i++)
								{
									auto req = m_LoopRequest.cur_device_settings();
									/*std::cout << "server side:  "
										<< "DataInEachLoopRequest Proceed(), ThreadId: " << std::this_thread::get_id() << "\r\n"
										<< "DataInEachLoopRequest Proceed(), status: " << m_eStatus << "\r\n"
										<< "DataInEachLoopRequest Proceed(), id: " << m_LoopRequest.instance_id() << "\r\n"
										<< "DataInEachLoopRequest Proceed(), code: " << req.deviceresponds(i).code() << "\r\n"
										<< "DataInEachLoopRequest Proceed(), value: " << req.deviceresponds(i).value() << "\r\n"
										<< "DataInEachLoopRequest Proceed(), unit: " << req.deviceresponds(i).unit() << "\r\n"
										<< std::endl;*/

									std::stringstream ss;
									ss << std::this_thread::get_id();
									std::string str = ss.str();
									formatted_string = SFormat("Receiving device settings with thread id=<{0}> and id=<{1}> and sequence id=<{2}>  code=<{3}>  value=<{4}>  unit=<{5}> ", str, m_LoopRequest.instance_id(),
										m_LoopRequest.sequence_id(), req.deviceresponds(i).code(), req.deviceresponds(i).value(), req.deviceresponds(i).unit());
									BOOST_LOG(lg) << formatted_string;

									ExtraInfo medibus_val;
									medibus_val.value = req.deviceresponds(i).value();
									if (data.find(req.deviceresponds(i).code()) == data.end())
									{
										// data is new
										data[req.deviceresponds(i).code()] = std::make_pair(medibus_val, m_LoopRequest.sequence_id());
									}
									else
									{
										if (data[req.deviceresponds(i).code()].first.value != req.deviceresponds(i).value())
										{
											// data need to be updated
											data[req.deviceresponds(i).code()] = std::make_pair(medibus_val, m_LoopRequest.sequence_id());
										}
										else
										{
											// set sequenceid -1 to indicate skip this value when we handle this value to SDC
											data[req.deviceresponds(i).code()] = std::make_pair(medibus_val, -1);
										}
										// if the code of next time is not available, the sequence id is the last time 

									}
								}
								m_data["Device settings"] = data;
							}

							if (m_LoopRequest.has_text_messages())
							{
								// handle text message
								std::map<std::string, std::pair<ExtraInfo, int>>& data = m_pDataModel->at("Text messages");
								std::stringstream ss;
								ss << std::this_thread::get_id();
								std::string str = ss.str();

								// for cache the code in m_LoopRequest
								std::vector<std::string> vecCurrentCF10Codes;

								// search is there new value in request in m_LoopRequest loop first
								for (int i = 0; i < m_LoopRequest.text_messages().deviceresponds_size(); i++)
								{
									
									auto req = m_LoopRequest.text_messages();
									formatted_string = SFormat("Receiving text message with thread id=<{0}> and id={1} and sequence id=<{2}>  code=<{3}>  value=<{4}>  unit=<{5}> ", str, m_LoopRequest.instance_id(),
										m_LoopRequest.sequence_id(), req.deviceresponds(i).code(), req.deviceresponds(i).value(), req.deviceresponds(i).unit());
									BOOST_LOG(lg) << formatted_string;
									ExtraInfo medibus_val;
									// cache the code
									std::string temp = req.deviceresponds(i).code();
									medibus_val.MedibusCode = req.deviceresponds(i).code();

									MetricInfo metricInfo;
									if (JsonHandlerSingleton::instance().GetTextMessage(req.deviceresponds(i).code(), metricInfo))
									{
										medibus_val.CF10Code = metricInfo.CF10TypeCode;
									}

									vecCurrentCF10Codes.emplace_back(medibus_val.CF10Code);

									if (data.find(medibus_val.CF10Code) == data.end())
									{
										// data is new
										data[medibus_val.CF10Code] = std::make_pair(medibus_val, m_LoopRequest.sequence_id());
									}
									else
									{
										if (data[medibus_val.CF10Code].second == -2)
										{
											// re-activate
											data[medibus_val.CF10Code] = std::make_pair(medibus_val, m_LoopRequest.sequence_id());
										}
										else
										{
											if (data[medibus_val.CF10Code].first.MedibusCode != req.deviceresponds(i).code())
											{
												// data need to be updated
												data[medibus_val.CF10Code] = std::make_pair(medibus_val, m_LoopRequest.sequence_id());
											}
											else
											{
												// set sequenceid -1 to indicate skip this value when we handle this value to SDC
												data[medibus_val.CF10Code].second = -1;
											}
											// if the code of next time is not available, the sequence id is the last time 
										}
										
									}
								}

								// then check is all values in data model in data loop
								// set sequence -2 when the value is not in request this time
								for (auto& it : data) {
									
									// check it exists in request
									auto result = std::find(vecCurrentCF10Codes.begin(), vecCurrentCF10Codes.end(), it.first);
									if (result == vecCurrentCF10Codes.end())
									{
										// check the sequenceId is not the same with the current sequenceId
										if (it.second.second != m_LoopRequest.sequence_id())
										{
											it.second.second = -2;
										}
									}

									
								}
								m_data["Text messages"] = data;
							}
							if (m_LoopRequest.has_cur_measured_data_cp2())
							{
								// handle CurMeasuredDataCP2
								std::map<std::string, std::pair<ExtraInfo, int>>& data = m_pDataModel->at("Measured data and alarm limits2");
								for (int i = 0; i < m_LoopRequest.cur_measured_data_cp2().deviceresponds_size(); i++)
								{
									auto req = m_LoopRequest.cur_measured_data_cp2();

									std::stringstream ss;
									ss << std::this_thread::get_id();
									std::string str = ss.str();
									formatted_string = SFormat("Receiving current measured data and alarm limits with thread id=<{0}> and id=<{1}> and sequence id=<{2}>  code=<{3}>  value=<{4}>  unit=<{5}> ", str, m_LoopRequest.instance_id(),
										m_LoopRequest.sequence_id(), req.deviceresponds(i).code(), req.deviceresponds(i).value(), req.deviceresponds(i).unit());
									BOOST_LOG(lg) << formatted_string;

									ExtraInfo medibus_val;
									medibus_val.value = req.deviceresponds(i).value();
									if (data.find(req.deviceresponds(i).code()) == data.end())
									{
										// data is new
										data[req.deviceresponds(i).code()] = std::make_pair(medibus_val, m_LoopRequest.sequence_id());
									}
									else
									{
										if (data[req.deviceresponds(i).code()].first.value != req.deviceresponds(i).value())
										{
											// data need to be updated
											data[req.deviceresponds(i).code()] = std::make_pair(medibus_val, m_LoopRequest.sequence_id());
										}
										else
										{
											// set sequenceid -1 to indicate skip this value when we handle this value to SDC
											data[req.deviceresponds(i).code()] = std::make_pair(medibus_val, -1);
										}
										// if the code of next time is not available, the sequence id is the last time 

									}
								}
								m_data["Measured data and alarm limits2"] = data;
							}
							if (m_LoopRequest.has_cur_low_alarm_limits_cp2())
							{
								// handle CurLowAlarmLimitsCP2
							}
							if (m_LoopRequest.has_cur_high_alarm_limits_cp2())
							{
								// handle CurHighAlarmLimitsCP2
							}
							if (m_LoopRequest.has_cur_alarms_cp2())
							{
								// handle CurAlarmsCP2
							}
							if (m_LoopRequest.has_device_identification())
							{
								// handle DeviceIdentification
								std::map<std::string, std::pair<ExtraInfo, int>>& data = m_pDataModel->at("Device identification numbers");
								{
									auto req = m_LoopRequest.device_identification();
									ExtraInfo extra_val;
									extra_val.value = req.deviceresponds().deviceid();
									extra_val.facility = req.deviceresponds().facility();
									extra_val.poc = req.deviceresponds().poc();
									extra_val.bed = req.deviceresponds().bed();

									std::stringstream ss;
									ss << std::this_thread::get_id();
									std::string str = ss.str();
									formatted_string = SFormat("Receiving device settings with thread id=<{0}> and id=<{1}> and sequence id=<{2}>  deviceid=<{3}>  devicename=<{4}>  facility=<{5}>  poc=<{6}> bed=<{7}>", str, m_LoopRequest.instance_id(),
										m_LoopRequest.sequence_id(), req.deviceresponds().deviceid(), req.deviceresponds().devicename(), req.deviceresponds().facility(), req.deviceresponds().poc(), req.deviceresponds().bed());
									BOOST_LOG(lg) << formatted_string;
									if (data.find(req.deviceresponds().deviceid()) == data.end())
									{
										// data is new
										data[req.deviceresponds().deviceid()] = std::make_pair(extra_val, m_LoopRequest.sequence_id());
									}
									else
									{
										if (data[req.deviceresponds().deviceid()].first.facility != req.deviceresponds().facility()
											|| data[req.deviceresponds().deviceid()].first.poc != req.deviceresponds().poc()
											|| data[req.deviceresponds().deviceid()].first.bed != req.deviceresponds().bed())
										{
											// data need to be updated
											data[req.deviceresponds().deviceid()] = std::make_pair(extra_val, m_LoopRequest.sequence_id());
										}
										else
										{
											// set sequenceid -1 to indicate skip this value when we handle this value to SDC
											data[req.deviceresponds().deviceid()] = std::make_pair(extra_val, -1);
										}
										// if the code of next time is not available, the sequence id is the last time 

									}
								}
								m_data["Device identification numbers"] = data;
							}
							if (m_LoopRequest.has_cur_alarms_cp3())
							{
								// handle CurAlarmsCP3
							}
							if (m_LoopRequest.real_time_size())
							{
								// handle RealTime
							}
							if (std::get<1>(rtnv)) {
								// this is the first time, we get the instance_id, so sdc provider must be created.
								// otherwise, sdc provider must skip the creation
								// 
								// create sdc provider with the instance_id
								// all function is called with prefix INSERT in sdc library.
								DFL::Mdib::MdibChangeSet changeSet;

								std::map<std::string, std::pair<ExtraInfo, int>> data;
								data = m_data["Device identification numbers"];
								
								ExtraInfo extra_value;
								int sequenceId;

								DeviceInfo deviceInfo;

								for (auto it = data.begin(); it != data.end(); ++it)
								{
									// take the first element
									extra_value = it->second.first;
									sequenceId = it->second.second;

									// get the information from json
									if (JsonHandlerSingleton::instance().GetDeviceInfo(extra_value.value, deviceInfo))
									{
										if (sequenceId != -1)
										{
											m_pProvider->start(deviceInfo.DeviceName, deviceInfo.CF10TypeCode, "mds0" + deviceInfo.CF10TypeCode);
											m_pProvider->initLocation(extra_value.facility, extra_value.poc, extra_value.bed);
										}
									}
								}

								// Device settings 
								data = m_data["Device settings"];
								for (auto it = data.begin(); it != data.end(); ++it)
								{
									extra_value = it->second.first;
									sequenceId = it->second.second;
									// get the information from json
									MetricInfo metricInfo;
									if (JsonHandlerSingleton::instance().GetDeviceSettings(it->first, metricInfo))
									{
										if (sequenceId != -1)
										{
											// first time to init metric
											m_pProvider->initNumericMetric(
												changeSet, "mds0" + deviceInfo.CF10TypeCode, metricInfo.VmdHandle,
												metricInfo.VmdCF10Code, metricInfo.ChannelHandle,
												metricInfo.ChannelCF10Code,
												metricInfo.MedibusCode + metricInfo.CF10TypeCode, metricInfo.MedicalClass,
												metricInfo.CF10TypeCode, metricInfo.UnitCode, metricInfo.Category,
												metricInfo.LowRange, metricInfo.UpperRange, "", "", "", metricInfo.Resolution, metricInfo.Derivation, metricInfo.Availability);

											// second time to call update metric
											m_pProvider->updateNumericMetricValue(metricInfo.MedibusCode + metricInfo.CF10TypeCode, 
												extra_value.value.empty()? 0 : std::stoi(extra_value.value));
										}
									}
								}

								// Measured data and alarm limits1 
								data = m_data["Measured data and alarm limits1"];
								for (auto it = data.begin(); it != data.end(); ++it)
								{
									extra_value = it->second.first;
									sequenceId = it->second.second;
									// get the information from json
									MetricInfo metricInfo;
									if (JsonHandlerSingleton::instance().GetMeasuredDataAndAlarmLimits1(it->first, metricInfo))
									{
										if (sequenceId != -1)
										{
											// first time to init metric
											m_pProvider->initNumericMetric(
												changeSet, "mds0" +  deviceInfo.CF10TypeCode, metricInfo.VmdHandle,
												metricInfo.VmdCF10Code, metricInfo.ChannelHandle,
												metricInfo.ChannelCF10Code,
												metricInfo.MedibusCode + metricInfo.MedibusCodePage + metricInfo.CF10TypeCode, metricInfo.MedicalClass,
												metricInfo.CF10TypeCode, metricInfo.UnitCode, metricInfo.Category,
												metricInfo.LowRange, metricInfo.UpperRange, metricInfo.DeterminationPeriod, metricInfo.LifeTimePeriod, metricInfo.MaxDelayTime, metricInfo.Resolution, metricInfo.Derivation, metricInfo.Availability);

											// second time to call update metric
											m_pProvider->updateNumericMetricValue(metricInfo.MedibusCode + metricInfo.MedibusCodePage + metricInfo.CF10TypeCode,
												extra_value.value.empty() ? 0 : std::stoi(extra_value.value));
										}
									}
								}

								// Measured data and alarm limits2 
								data = m_data["Measured data and alarm limits2"];
								for (auto it = data.begin(); it != data.end(); ++it)
								{
									extra_value = it->second.first;
									sequenceId = it->second.second;
									// get the information from json
									MetricInfo metricInfo;
									if (JsonHandlerSingleton::instance().GetMeasuredDataAndAlarmLimits2(it->first, metricInfo))
									{
										if (sequenceId != -1)
										{
											// first time to init metric
											m_pProvider->initNumericMetric(
												changeSet, "mds0" + deviceInfo.CF10TypeCode, metricInfo.VmdHandle,
												metricInfo.VmdCF10Code, metricInfo.ChannelHandle,
												metricInfo.ChannelCF10Code,
												metricInfo.MedibusCode + metricInfo.MedibusCodePage + metricInfo.CF10TypeCode, metricInfo.MedicalClass,
												metricInfo.CF10TypeCode, metricInfo.UnitCode, metricInfo.Category,
												metricInfo.LowRange, metricInfo.UpperRange, metricInfo.DeterminationPeriod, metricInfo.LifeTimePeriod, metricInfo.MaxDelayTime, metricInfo.Resolution, metricInfo.Derivation, metricInfo.Availability);

											// second time to call update metric
											m_pProvider->updateNumericMetricValue(metricInfo.MedibusCode + metricInfo.MedibusCodePage + metricInfo.CF10TypeCode,
												extra_value.value.empty() ? 0 : std::stoi(extra_value.value));
										}
									}
								}

								// Text message 
								data = m_data["Text messages"];
								for (auto it = data.begin(); it != data.end(); ++it)
								{
									extra_value = it->second.first;
									sequenceId = it->second.second;
									// get the information from json
									MetricInfo metricInfo;
									if (JsonHandlerSingleton::instance().GetTextMessage(extra_value.MedibusCode, metricInfo))
									{
										if (sequenceId > 0)
										{
											// first time to init metric
											m_pProvider->initEnumStringMetric(
												changeSet, "mds0" + deviceInfo.CF10TypeCode, metricInfo.VmdHandle,
												metricInfo.VmdCF10Code, metricInfo.ChannelHandle,
												metricInfo.ChannelCF10Code,
												metricInfo.CF10TypeCode, metricInfo.MedicalClass,
												metricInfo.CF10TypeCode, metricInfo.UnitCode, metricInfo.AllowedValueCodes, metricInfo.AllowedValues, metricInfo.Category, metricInfo.Derivation, metricInfo.Availability);

											// second time to call update metric
											// comment logic which use the value from medibus
											/*m_pProvider->updateEnumStringMetricValue(metricInfo.MedibusCode + metricInfo.MedibusCodePage + metricInfo.CF10TypeCode,
												extra_value.value.empty() ? "" : extra_value.value);*/
											m_pProvider->updateEnumStringMetricValue(metricInfo.CF10TypeCode,
											    metricInfo.CurAllowedValue);
										}
									}
								}
								
							}
							else
							{
								// all function is called with prefix UPDATE in sdc library.

								{
									// Device settings 
									std::map<std::string, std::pair<ExtraInfo, int>> data;
									data = m_data["Device settings"];
									ExtraInfo extra_value;
									int sequenceId;

									for (auto it = data.begin(); it != data.end(); ++it)
									{
										extra_value = it->second.first;
										sequenceId = it->second.second;
										// get the information from json
										MetricInfo metricInfo;
										if (JsonHandlerSingleton::instance().GetDeviceSettings(it->first, metricInfo))
										{
											if (sequenceId != -1)
											{
												m_pProvider->updateNumericMetricValue(metricInfo.MedibusCode + metricInfo.CF10TypeCode,
													extra_value.value.empty() ? 0 : std::stoi(extra_value.value));

											}
										}
									}
								}

								{
									// Measured data and alarm limits1 
									std::map<std::string, std::pair<ExtraInfo, int>> data;
									data = m_data["Measured data and alarm limits1"];
									ExtraInfo extra_value;
									int sequenceId;

									for (auto it = data.begin(); it != data.end(); ++it)
									{
										extra_value = it->second.first;
										sequenceId = it->second.second;
										// get the information from json
										MetricInfo metricInfo;
										if (JsonHandlerSingleton::instance().GetMeasuredDataAndAlarmLimits1(it->first, metricInfo))
										{
											if (sequenceId != -1)
											{
												m_pProvider->updateNumericMetricValue(metricInfo.MedibusCode + metricInfo.MedibusCodePage + metricInfo.CF10TypeCode,
													extra_value.value.empty() ? 0 : std::stoi(extra_value.value));

											}
										}
									}
								}

								{
									// Measured data and alarm limits2 
									std::map<std::string, std::pair<ExtraInfo, int>> data;
									data = m_data["Measured data and alarm limits2"];
									ExtraInfo extra_value;
									int sequenceId;

									for (auto it = data.begin(); it != data.end(); ++it)
									{
										extra_value = it->second.first;
										sequenceId = it->second.second;
										// get the information from json
										MetricInfo metricInfo;
										if (JsonHandlerSingleton::instance().GetMeasuredDataAndAlarmLimits2(it->first, metricInfo))
										{
											if (sequenceId != -1)
											{
												m_pProvider->updateNumericMetricValue(metricInfo.MedibusCode + metricInfo.MedibusCodePage + metricInfo.CF10TypeCode,
													extra_value.value.empty() ? 0 : std::stoi(extra_value.value));

											}
										}
									}
								}

								{
									// Text message 
									std::map<std::string, std::pair<ExtraInfo, int>> data;
									data = m_data["Text messages"];
									ExtraInfo extra_value;
									int sequenceId;

									for (auto it = data.begin(); it != data.end(); ++it)
									{
										extra_value = it->second.first;
										sequenceId = it->second.second;
										// get the information from json
										MetricInfo metricInfo;
										if (JsonHandlerSingleton::instance().GetTextMessage(extra_value.MedibusCode, metricInfo))
										{
											if (sequenceId > 0)
											{
												// comment logic which use the value from medibus
												/*m_pProvider->updateEnumStringMetricValue(metricInfo.MedibusCode + metricInfo.MedibusCodePage + metricInfo.CF10TypeCode,
													extra_value.value.empty() ? "" : extra_value.value);*/
												m_pProvider->updateEnumStringMetricValue(metricInfo.CF10TypeCode,
													metricInfo.CurAllowedValue);

											}
											else if (sequenceId == -2)
											{
												m_pProvider->updateEnumStringMetricValue(metricInfo.CF10TypeCode,
													"");
											}
										}
									}
								}
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
				new DelimitedDataInEachLoopRequest(m_pService, m_pCq, m_pProvider, m_pDataModel);


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
		SdcProvider* m_pProvider;
		std::map<std::string, std::map<std::string, std::pair<ExtraInfo, int>>> m_data;
	};


	class ServerImpl final
	{
	public:
		explicit ServerImpl(SdcProvider* pProvider);

		~ServerImpl()
		{
			m_Server->Shutdown();
			// Always shutdown the completion queue after the server.
			for (auto cq = m_vecpCqs.begin(); cq != m_vecpCqs.end(); ++cq)
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
			builder.RegisterService(&m_Service);
			// Get hold of the completion queue used for the asynchronous communication
			// with the gRPC runtime.
			for (int i = 0; i < m_nNumThreads; i++)
				m_vecpCqs.emplace_back(builder.AddCompletionQueue());

			for (int i = 0; i < m_nNumThreads; i++)
			{
				m_vecproviders.emplace_back(std::make_unique<SdcProvider>());
			}
				
			for (int i = 0; i < m_nNumThreads; i++)
			{
				ExtraInfo extraInfo;
				std::map<std::string, std::map<std::string, std::pair<ExtraInfo, int>>> exInfo;
				std::map<std::string, std::pair<ExtraInfo, int>> innerMap; 
				//innerMap.emplace("", std::make_pair(extraInfo, -1)) ;
				exInfo.emplace("Device identification numbers", innerMap);
				exInfo.emplace("Device settings", innerMap);
				exInfo.emplace("Measured data and alarm limits1", innerMap);
				exInfo.emplace("Measured data and alarm limits2", innerMap);
				exInfo.emplace("Real-time data", innerMap);
				exInfo.emplace("Alarm status", innerMap);
				exInfo.emplace("Text messages", innerMap);
				m_vecdataModel.emplace_back(std::make_unique<std::map<std::string, std::map<std::string, std::pair<ExtraInfo, int>>>>(exInfo));
			}
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
				std::cout << "Server listening on pipe index " << i << std::endl;
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
				new DelimitedDataInEachLoopRequest(&m_Service, m_vecpCqs[i].get(), m_vecproviders[i].get(), m_vecdataModel[i].get());
				threads.emplace_back(std::thread(&ServerImpl::ServeThread, this, i));
			}
			for (auto thr = threads.begin(); thr != threads.end(); ++thr)
				thr->join();
		}
		std::vector<std::unique_ptr<std::map<std::string, std::map<std::string, std::pair<ExtraInfo, int>>>>> m_vecdataModel;
		std::vector<std::unique_ptr<SdcProvider>> m_vecproviders;
		std::vector<std::unique_ptr<ServerCompletionQueue>> m_vecpCqs;
		Medibus::AsyncService m_Service;
		std::unique_ptr<Server> m_Server;
		SdcProvider* m_pProvider;
		int m_nNumThreads{ 64 };
	};

	ServerImpl::ServerImpl(SdcProvider* pProvider) :m_pProvider(pProvider)
	{

	}
}

int main(int argc, char** argv)
{
	MedibusServer::init_logging();
	SdcProvider provider;
	MedibusServer::ServerImpl server(&provider);
	server.Run(absl::GetFlag(FLAGS_port));

	return 0;
}
