#include "CHttpUrl.h"

namespace
{
    const std::regex PARSE_URL_REGEX(R"((.*)://([0-9A-Za-z\-.]+)(?::(\d+))?(?:/(.*))?)", std::regex::icase);
    std::optional<std::smatch> ParseURL(const std::string &url) {
        std::smatch match;
        if (std::regex_match(url, match, PARSE_URL_REGEX)) {
            return match;
        }
        return std::nullopt;
    }
}

namespace url {
    using namespace protocols;

    CHttpUrl::CHttpUrl(const std::string &url) {
        const auto parsedUrl = ParseURL(url);

        if (parsedUrl == std::nullopt) {
            throw CUrlParsingError::InvalidUrl();
        }
        auto portValue = parsedUrl.value()[3];
        auto protocolValue = parsedUrl.value()[1];
        auto domainValue = parsedUrl.value()[2];
        auto documentValue = parsedUrl.value()[4];

        m_protocol = ParseProtocol(protocolValue);
        m_domain = ParseDomain(domainValue);
        m_port = !portValue.str().empty() ? ParsePort(portValue) : GetDefaultPort(m_protocol);
        m_document = UpdateDocumentWithBackslashIfNeeds(documentValue);
        BuildURLToString();
    }

    CHttpUrl::CHttpUrl(const std::string &domain, const std::string &document, protocols::Protocol protocol, int port) {
        m_protocol = protocol;
        m_domain = ParseDomain(domain);
        m_port = CheckPort(port) ? port : GetDefaultPort(m_protocol);
        m_document = UpdateDocumentWithBackslashIfNeeds(document);
        BuildURLToString();
    }

    CHttpUrl::CHttpUrl(const std::string &domain, const std::string &document, protocols::Protocol protocol)
            : CHttpUrl(domain, document, protocol, 1) {
        m_protocol = protocol;
        m_port = GetDefaultPort(m_protocol);
        m_domain = ParseDomain(domain);
        m_document = UpdateDocumentWithBackslashIfNeeds(document);
        BuildURLToString();
    }

    std::string CHttpUrl::UpdateDocumentWithBackslashIfNeeds(const std::string &document) {
        if (document.empty()) {
            return "/";
        }
        if (document[0] == '/') {
            return document;
        }
        return "/" + document;
    }

    void CHttpUrl::BuildURLToString() {
        m_url = GetProtocolFromEnum(m_protocol) + "://" + m_domain;
        if (GetDefaultPort(m_protocol) != m_port) {
            m_url += ':' + std::to_string(m_port);
        }
        m_url += m_document;
    }

    const std::string& CHttpUrl::GetURL() const {
        return m_url;
    }

    const std::string& CHttpUrl::GetDomain() const {
        return m_domain;
    }

    const std::string& CHttpUrl::GetDocument() const {
        return m_document;
    }

    Protocol CHttpUrl::GetProtocol() const {
        return m_protocol;
    }

    int CHttpUrl::GetPort() const {
        return m_port;
    }

    Protocol CHttpUrl::ParseProtocol(std::string const &protocol) {
        try {
            return GetProtocolFromString(protocol);
        }
        catch (const std::exception &ex) {
            throw CUrlParsingError::InvalidProtocol(protocol);
        }
    }

    const std::string& CHttpUrl::ParseDomain(std::string const &domain) const {
        CheckDomain(domain);
        return domain;
    }

    void CHttpUrl::CheckDomain(const std::string &domain) const {
        if (domain.empty()) {
            throw CUrlParsingError::InvalidUrl();
        }
    }

    bool CHttpUrl::CheckPort(int port) const {
        return (port > 0) && (port <= USHRT_MAX); // todo 0 port +++
    }

    unsigned short CHttpUrl::ParsePort(std::string const &port) const {
        int result;
        try {
            result = std::stoi(port);
        }
        catch (const std::exception &ex) {
            throw CUrlParsingError::InvalidPort(port);
        }
        if (!CheckPort(result)) {
            throw CUrlParsingError::PortOutOfRange();
        }

        return static_cast<unsigned short>(result);
    }
}