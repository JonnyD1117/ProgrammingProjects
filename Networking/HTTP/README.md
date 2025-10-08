
# HTTP Server 
HTTP is the the application layer that sits on top of TCP/IP and is used to make HTTP requests to a web server which in turn makes a HTTP reply to the client. HTTP has a handful of commands `POST`, `PUT`, `GET`, and `DELETE`. My current understanding of what HTTP is and how it works is that HTTP is specification for the type and format of the data that is being carried over the network via TCP/IP. This means that any HTTP client/server pair will be able to encode & decode (serialize & deserialize?) the messages contained in the HTTP message which is (to the best of my understanding) just a string of characters that TCP has delivered between two computers on a network. 

## HTTP Message Serialization & Deserialization
My understanding of HTTP messages is that they are usually in the form of a string which is transmitted over the network as a stream of bytes. Once the bytes from one host have been transmitted to the other host. The next step is to reconstruct the byte stream into a single entity (e.g. file || string? ). I'm assuming this string and be used directly or that this string can deserialized into an programmatic object that the receiving host can use directly with code that is in the application layer. 

If I'm thinking about this correctly, this would allow would work like the following example. 

1. A program on the client side wants to use HTTP to make a request over the network to a server.
2. This program would serialize any data it wanted to transmit
3. Transmit this serialized HTTP message as a byte stream over TCP/IP
4. The server would reconstruct this byte stream via TCP
5. The reconstructed serialized message could then be deserialized.
6. A program on the server side can then take that deserialized object and perform normal operations on it. 
7. A result would be computed or obtained
8. The server would send a response message back to the client containing the HTTP status and any request information.  


