# R-TYPE NETWORK

The r-type must be a multi player game, where we can play level with 1-4 players and we can connect to multiple server game.

That's why we chose to make 2 server in the game for the different case.

When the player connect to the main server, where he can create his own game, join a game or create an account, the server will be TCP

For all the other steps (lobby and the game), the server will be UDP

## Server Choice

### TCP

TCP are slower than UDP server, but in term of data their better because we cannot lose data when sending it, their always a response from the server/client to know if everythnig went well

[If you wanna know more about it](https://en.wikipedia.org/wiki/Transmission_Control_Protocol)

### UDP

UDP are faster for sending data because they don't need to wait an answer, it just send data and don't know if the client receive it. These server are better when we need to be fast, like in video games (but the lose of data can create lags)

[If you wanna know more about it](https://fr.wikipedia.org/wiki/User_Datagram_Protocol)

## Tools Choice

For this project we use boost::asio a c++ library with lot's of tools for create good server

### installation on windows

in progress

### installation on linux

in progress

## Protocols

### TCP protocol:

[tcp](rfcTCP.txt)

### UDP protocol:

[udp](rfcUDP.txt)
