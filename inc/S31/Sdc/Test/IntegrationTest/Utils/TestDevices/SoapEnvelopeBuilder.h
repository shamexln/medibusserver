#pragma once

#include <sstream>
#include <string>
#include <string_view>

namespace S31::Sdc::Impl::Test
{

class SoapEnvelopeBuilder
{
    public:

        SoapEnvelopeBuilder()
        {
            m_msg << m_soapEnvelopeBegin;
        }
        SoapEnvelopeBuilder& action(std::string_view action)
        {
            m_msg << "<wsa5:Action>" << action << "</wsa5:Action>";
            return *this;
        }
        SoapEnvelopeBuilder& to(std::string_view to)
        {
            m_msg << "<wsa5:To>" << to << "</wsa5:To>";
            return *this;
        }
        SoapEnvelopeBuilder& body(std::string_view body)
        {
            m_msg << m_soapHeadBodyJoin;
            m_msg << body;
            m_msg << m_soapEnvelopeEnd;
            return *this;
        }
        std::string str() const
        {
            return m_msg.str();
        }

    private:
        std::ostringstream m_msg;

        static constexpr std::string_view m_soapEnvelopeBegin{
                R"(<?xml version="1.0" encoding="UTF-8"?>)"
                R"(<s:Envelope xmlns:s="http://www.w3.org/2003/05/soap-envelope")"
                R"( xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance")"
                R"( xmlns:wsa5="http://www.w3.org/2005/08/addressing")"
                R"( xmlns:wsd11="http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01")"
                R"( xmlns:wse4="http://schemas.xmlsoap.org/ws/2004/08/eventing")"
                R"( xmlns:dpws="http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01")"
                R"( xmlns:srv="http://standards.ieee.org/downloads/11073/11073-20701-2018")"
                R"( xmlns:pm="http://standards.ieee.org/downloads/11073/11073-10207-2017/participant")"
                R"( xmlns:msg="http://standards.ieee.org/downloads/11073/11073-10207-2017/message")"
                R"( xmlns:wsx4="http://schemas.xmlsoap.org/ws/2004/09/mex"><s:Header>)"};
        static constexpr std::string_view m_soapHeadBodyJoin{R"(</s:Header><s:Body>)"};
        static constexpr std::string_view m_soapEnvelopeEnd{R"(</s:Body></s:Envelope>)"};
};

}  // namespace S31::Sdc::Impl::Test
