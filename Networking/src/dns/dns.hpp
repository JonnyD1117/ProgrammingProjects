//std 
#include <string> 
#include <iostream>

// dns
// #include "udp.hpp"


namespace DNS
{

    enum class QueryType
    {
        A=0,
        AAAA,
        MX,
        NS,
        CNAME
    };

    class Resolver
    {
        public: 

        Resolver(std::string domain, QueryType query_t, size_t port=53, std::string nameserver="8.8.8.8", size_t timeout=10)
        : m_domain_name(domain)
        , m_query_t(query_t)
        , m_port(port)
        , m_nameserver(nameserver)
        , m_timeout(timeout) 
        {

        }

        ~Resolver()=default;

        

        private:

        QueryType m_query_t;


        std::string m_nameserver;               // String octet of default nameserver
        std::string m_domain_name;              // the Domain
        size_t m_port; 
        size_t m_timeout; 

    };
}