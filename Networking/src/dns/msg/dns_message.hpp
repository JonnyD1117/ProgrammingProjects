#include <bitset>
#include <string>

namespace DNS
{
    

    class Message
    {
        private:
        std::string m_path;

        

        public:
        Message(std::string path) : m_path(path)
        {

        }

        ~Message()=default;

    };

    class Question
    {

    };

    class Answer
    {

    };

    class Additional
    {

    };
}