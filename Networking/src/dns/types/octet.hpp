//std
#include <iostream>
#include <string> 
#include <cstdint>
#include <cstddef>
#include <array>
#include <vector>


namespace DNS
{
    const uint8_t NUM_OCTETS = 4; 

    class Octet
    {
        const size_t m_num_octets = 4; 

        public:

        Octet(std::string octet_str) : m_octet_str(octet_str)
        {

        }

        Octet(std::byte octet_1, std::byte octet_2, std::byte octet_3, std::byte octet_4) 
        : m_octet_arr{{octet_1, octet_2, octet_3, octet_4}}
        {
            std::vector<char> char_vec;

            for(auto c : m_octet_arr)
            {
                char_vec.push_back(std::to_integer<char>(c));
            }
        }


        ~Octet()=default;




        private:

        std::array<std::byte, NUM_OCTETS> m_octet_arr;

        std::string m_octet_str; 



    }
}