# B-CPP-500-PAR-5-1-rtype-pierre-alexandre.delgado-arevalo

## The project

The objective of the project is to create a [game engine](https://en.wikipedia.org/wiki/Game_engine) for 2d games with network. And we need to recreate the famous game [R-TYPE](https://fr.wikipedia.org/wiki/R-Type) with multiplayer.

## Build

You need to install [cmake](https://cmake.org/download/).

To build the project you can use the binaries in the last release. (use in bash shell for linux and command prompt for windows)

Or you can do it manually by doing at the root of the project:
```
create folder build

go to build

run cmake ..

run cmake --build .

go back to the root of the project

if you are on windows:

go to Debug and copy the .exe at the root of the directory
```
### Build with RTYPE--Linux.sh on linux
Along with all the files of the game, you will have a file named RTYPE--Linux.sh.
On your terminal launch the RTYPE--Linux.sh, it will ask you to download files, and then you need to move the files generated into the root
```
./RTYPE--Linux.sh
```  
Input to accept download :  q, y enter, y enter.  
It will generate a RTYPE--Linux folder, you now need to move some files  
```
mv RTYPE--Linux/bin/* .
```

## run

To run the project you simply need to start the binaries ```rtype_server``` and ```rtype_client``` with no arguments. You just need to have the Assets/ directory at the same directory as the binaries.

## Graphical library

For this project, we use the [Raylib](https://www.raylib.com/) for our engine. But you can change it and use your own library

See [documentation about encapsulation to know more about it](Libs/Encapsulation/Documentation/README.md)

# Use Docker

[install docker](https://docs.docker.com/get-docker/)

[install docker compose](https://docs.docker.com/compose/install/)

The project can be build with a container, base on [ubuntu:latest](https://hub.docker.com/_/ubuntu)

## Dockerfile
Build:
```sh
docker build -t <image name> .
```
Test
```sh
docker run -t <image name>
```
## docker-compose.yml

Launch all service:

```bash
docker-compose up
```

Launch specific service:

```bash
docker-compose up <service name>
```

All service:
  - gcc-debug-build-make
  - gcc-debug-build
  - gcc-release-build
  - clang-debug-build
  - clang-release-build

## Engine

For our engine, we chose to use an ECS architecture.

See more [here](Engine/README.md)

## Network

In this project, we use the asio libary for managing our server and client.

We made a TCP ```and``` UDP server/client communication

See more [here](Server/README.md)
