#pragma once

#include <Framework/Mdib/Public/Model/Component/MetaData.h>

namespace S31::Test
{

/*!
 * \brief Makes example system meta datas for tests.
 */
class SystemMetaDataFactory
{
    public:
        static DFL::Mdib::MetaData getSystemMetaData()
        {
            DFL::Mdib::Udis udis;
            udis.push_back(DFL::Mdib::Udi(
                DFL::Mdib::DeviceIdentifier(DFL::Locale::Utf8("device identifier")),
                DFL::Mdib::HumanReadableForm(DFL::Locale::Utf8("human readable form")),
                DFL::Mdib::InstanceIdentifier(DFL::Mdib::Root(DFL::Mdib::Uri("https://issuerroot")), DFL::Mdib::Extension(DFL::Locale::Utf8("issuerextension")))));

            DFL::Mdib::LocalizedTexts manufacturers;
            manufacturers.push_back(DFL::Mdib::LocalizedText(DFL::Locale::Utf8("Manufacturer 1")));
            manufacturers.push_back(DFL::Mdib::LocalizedText(DFL::Locale::Utf8("Manufacturer 2")));

            DFL::Mdib::LocalizedTexts modelNames;
            modelNames.push_back(DFL::Mdib::LocalizedText(DFL::Locale::Utf8("model name 1")));
            modelNames.push_back(DFL::Mdib::LocalizedText(DFL::Locale::Utf8("model name 2")));

            DFL::Mdib::SerialNumbers serialNumbers;
            serialNumbers.push_back(DFL::Mdib::SerialNumber(DFL::Locale::Utf8("serial 8547823654786325788")));
            serialNumbers.push_back(DFL::Mdib::SerialNumber(DFL::Locale::Utf8("serial o8345893457934857893457")));

            DFL::Mdib::MetaData systemMetaData(udis,
                                               DFL::Locale::Utf8("lot number"),
                                               manufacturers,
                                               boost::none,
                                               boost::none,
                                               modelNames,
                                               DFL::Locale::Utf8("model number 123"),
                                               serialNumbers);

            return systemMetaData;
        }
};

}
