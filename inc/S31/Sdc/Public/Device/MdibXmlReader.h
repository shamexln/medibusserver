#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Mdib/Public/WriteResult.h>

#include <iosfwd>
#include <string>

namespace S31
{
/**
 * \brief Parser for SDC XML schema compliant %MDIB structure parts (e.g., descriptors).
 * \ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP MdibXmlReader
{
    public:
        /**
         * \brief Write a XML string from the given %Mdib in the format of a GetMdibResponse
         * \param mdib The pointer to the DFL::Mdib::Mdib
         *
         * \return The xml string representing the MDIB as a GetMdibResponse
         */
        static std::string writeXmlString(const DFL::Mdib::MdibSharedPtr& mdib);

        /**
         * \brief Read a XML file with a GetMdibResponse message into the given %Mdib.
         * \param localMdibAccess The pointer to empty DFL::Mdib::LocalMdibAccess
         * \param filePath file name (including path) to read GetMdibResponse message.
         *
         * \return The write result (with error message).
         */
        static DFL::Mdib::WriteResult readMdib(DFL::Mdib::LocalMdibAccess& localMdibAccess, const std::string& filePath);

        /**
         * \brief Read an input C++ stream with a GetMdibResponse message into the given %Mdib.
         * \param localMdibAccess The pointer to empty DFL::Mdib::LocalMdibAccess
         * \param xmlStream input stream to read GetMdibResponse message.
         *
         * \return The write result (with error message).
         */
        static DFL::Mdib::WriteResult readMdib(DFL::Mdib::LocalMdibAccess& localMdibAccess, std::istream& xmlStream);

};

} /* namespace S31 */
