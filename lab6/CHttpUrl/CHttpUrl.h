#include <string>
#include <optional>
#include <regex>
#include "CUrlParsingError.h"
#include "Protocol.h"

namespace url {
    class CHttpUrl {
    public:
        explicit CHttpUrl(const std::string &url);

        CHttpUrl(const std::string &domain, const std::string &document, protocols::Protocol protocol, int port);

        CHttpUrl(const std::string &domain, const std::string &document, protocols::Protocol protocol);

        const std::string& GetURL() const;

        const std::string& GetDomain() const;

        const std::string& GetDocument() const;

        url::protocols::Protocol GetProtocol() const;

        int GetPort() const;

    private:
        static std::string UpdateDocumentWithBackslashIfNeeds(const std::string &document);

        static protocols::Protocol ParseProtocol(std::string const &protocol);

        const std::string& ParseDomain(std::string const &domain) const;

        void CheckDomain(const std::string &domain) const;

        unsigned short ParsePort(std::string const &port) const;

        bool CheckPort(int port) const;

        void BuildURLToString();

        std::string m_url;
        protocols::Protocol m_protocol;
        std::string m_domain;
        std::string m_document;
        int m_port;
    };
}