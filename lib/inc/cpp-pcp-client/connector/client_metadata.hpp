#ifndef CPP_PCP_CLIENT_SRC_CONNECTOR_CLIENT_METADATA_H_
#define CPP_PCP_CLIENT_SRC_CONNECTOR_CLIENT_METADATA_H_

#include <cpp-pcp-client/export.h>
#include <string>

namespace PCPClient {

LIBCPP_PCP_CLIENT_EXPORT void validatePrivateKeyCertPair(const std::string& key, const std::string& crt);

LIBCPP_PCP_CLIENT_EXPORT std::string getCommonNameFromCert(const std::string& crt);

class LIBCPP_PCP_CLIENT_EXPORT ClientMetadata {
  public:
    std::string ca;
    std::string crt;
    std::string key;
    std::string client_type;
    std::string common_name;
    std::string uri;
    long connection_timeout;

    /// Throws a connection_config_error in case: the client
    /// certificate file does not exist or is invalid; it fails to
    /// retrieve the client identity from the file; the client
    /// certificate and private key are not paired
    ClientMetadata(std::string _client_type,
                   std::string _ca,
                   std::string _crt,
                   std::string _key,
                   long _connection_timeout);
};

}  // namespace PCPClient

#endif  // CPP_PCP_CLIENT_SRC_CONNECTOR_CLIENT_METADATA_H_
