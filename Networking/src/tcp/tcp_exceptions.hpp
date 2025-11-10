
#pragma once

#include <exception>
#include <string>


namespace TCP
{
    // Base Exception
    class TcpBaseException : public std::exception { 

        public: 
            explicit TcpBaseException(const char* message) : msg (message) {}

            virtual const char* what() const noexcept override 
            {
                return msg.c_str();
            }

        private:
        std::string msg; 
    };

    class TcpMethodNotImplemented : public TcpBaseException
    {
        public: 
            explicit TcpMethodNotImplemented(const char* message) : TcpBaseException("Method has NOT been implemented") { }
    };

    // Utility Exceptions
    class TcpHeartBeatTimedOut : public TcpBaseException
    {
        public:
            explicit TcpHeartBeatTimedOut(const char* message) : TcpBaseException(message) {}
    };

    // Client Exceptions 
    class TcpClientException : public TcpBaseException
    {
        public: 
            explicit TcpClientException(const char* message) : TcpBaseException(message) {}
    };

    class TcpClientSocketCreationFailed : public TcpClientException
    {
        public:
            explicit TcpClientSocketCreationFailed(const char* message) : TcpClientException(message){}
    };
    class TcpClientSocketCreationReAttemptFailed : public TcpClientException
    {
        public:
            explicit TcpClientSocketCreationReAttemptFailed(const char* message) : TcpClientException(message){}
    };


    class TcpClientBindFailed : public TcpClientException
    {
        public: 
            explicit TcpClientBindFailed(const char* message) : TcpClientException(message){}
    };

    class TcpClientSocketCloseFailed : public TcpClientException
    {
        public: 
            explicit TcpClientSocketCloseFailed(const char* message) : TcpClientException(message){}
    };

    class TcpClientConnectFailed : public TcpClientException
    {
        public: 
            explicit TcpClientConnectFailed(const char* message) : TcpClientException(message){}
    };

    //Server Exceptions
    class TcpServerException : public TcpBaseException
    {
        public: 
            explicit TcpServerException(const char* message) : TcpBaseException(message) {}
    };

    class TcpServerSocketCreationFailed : public TcpServerException
    {
        public:
            explicit TcpServerSocketCreationFailed(const char* message) : TcpServerException(message){}
    };

    class TcpServerBindFailed : public TcpServerException
    {
        public: 
            explicit TcpServerBindFailed(const char* message) : TcpServerException(message){}
    };

    class TcpServerListenFailed : public TcpServerException
    {
        public: 
            explicit TcpServerListenFailed(const char* message) : TcpServerException(message){}
    };

    class TcpServerAcceptFailed : public TcpServerException
    {
        public: 
            explicit TcpServerAcceptFailed(const char* message) : TcpServerException(message){}
    };

    // class TcpServerAcceptFailed : public TcpServerException
    // {
    //     public: 
    //         explicit TcpServerAcceptFailed(const char* message) : TcpServerException(message){}
    // };

    class TcpServerSocketCloseFailed : public TcpServerException
    {
        public: 
            explicit TcpServerSocketCloseFailed(const char* message) : TcpServerException(message){}
    };


}

