#pragma once
#include <stdexcept>
#include <string>

namespace url::protocols {
    inline std::string ToLower(const std::string& input)
    {
        std::string result;
        std::transform(
                input.begin(),
                input.end(),
                std::back_inserter(result),
                [](unsigned char ch) -> char { return static_cast<char>(tolower(ch)); }
        );
        return result;
    }

    enum class Protocol {
        HTTP,
        HTTPS
    };

    inline Protocol GetProtocolFromString(const std::string &protocol) {
        const auto lowerProtocol = ToLower(protocol);
        if (lowerProtocol == "http") {
            return Protocol::HTTP;
        }
        if (lowerProtocol == "https") {
            return Protocol::HTTPS;
        }
        throw std::invalid_argument("invalid string protocol");
    }

    inline int GetDefaultPort(Protocol protocol) {
        switch (protocol) {
            case Protocol::HTTP:
                return 80;
            case Protocol::HTTPS:
                return 443;
            default:
                throw std::invalid_argument("invalid string protocol");
        }
    }

    inline std::string GetProtocolFromEnum(const Protocol protocol) {
        switch (protocol) {
            case Protocol::HTTP:
                return "http";

            case Protocol::HTTPS:
                return "https";

            default:
                throw std::invalid_argument("invalid protocol");
        }
    }
}