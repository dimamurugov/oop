#pragma once
#include <stdexcept>

class CUrlParsingError : public std::invalid_argument {
    public:
        static CUrlParsingError InvalidUrl();

        static CUrlParsingError InvalidProtocol(const std::string &message);

        static CUrlParsingError InvalidPort(const std::string &message);

        static CUrlParsingError PortOutOfRange();

    private:
        explicit CUrlParsingError(const std::string &message);
    };