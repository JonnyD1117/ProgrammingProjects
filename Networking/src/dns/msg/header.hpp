#include <bitset>
#include <string>

/*
DNS Header Structure & Content

0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|                      ID                       |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|QR|   Opcode  |AA|TC|RD|RA|   Z    |   RCODE   |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|                    QDCOUNT                    |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|                    ANCOUNT                    |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|                    NSCOUNT                    |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|                    ARCOUNT                    |
+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+


*/

namespace DNS
{

namespace Header
{

}

    enum class Opcodes
    {
        QUERY=0,
        IQUERY,
        STATUS,
    };

    class Header
    {
        public:

        Header()
        {

        }

        ~Header()
        {

        }

        private:

        std::bitset<16> m_ID;               // Random? number used to correleate response with requests
        std::bitset<1> m_QR;                // Query(0) || Response(1)
        std::bitset<4> m_OPCODE;            // Opcode (0) std query, 1=inv query, 2=server status, 3= 3-15 future
        std::bitset<1> m_TC;                // Truncation (not required for short queries) (0) 
        std::bitset<1> m_RD;                // Recursion Desired (1)
        std::bitset<1> m_RA;                // Recursion Available (0) - set or cleared in the response
        std::bitset<3> m_Z{0};              // Reserved for future use: Must be zeros for all query/response (0)
        std::bitset<4> m_RCODE;             // (0) don't know
        std::bitset<16> m_QDCOUNT;          // unsigned 16 bit int that specifies the nbmber of entries in the question
        std::bitset<16> m_ANCOUNT;          // number of resource records in the answer section (response only)
        std::bitset<16> m_NSCOUNT;          // number of nameserver records in the authory records section 
        std::bitset<16> m_ARCOUNT;          // number of resource records in the additional records 


        void print(bool encoded=false)
        {

        }


    };

}