#include "CUrlParsingError.h"

CUrlParsingError CUrlParsingError::InvalidUrl() {
    return CUrlParsingError("invalid url");
}

CUrlParsingError CUrlParsingError::InvalidProtocol(const std::string &message) {
    return CUrlParsingError("invalid protocol. " + message);
}

CUrlParsingError CUrlParsingError::InvalidPort(const std::string &message) {
    return CUrlParsingError("invalid port. " + message);
}

CUrlParsingError CUrlParsingError::PortOutOfRange() {
    return CUrlParsingError("port out of range");
}

CUrlParsingError::CUrlParsingError(const std::string &message)
        : std::invalid_argument(message) {
}
