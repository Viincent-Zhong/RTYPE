FROM ubuntu:latest as build

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends apt-utils
RUN apt-get -y install g++ cmake git
RUN apt-get -y install libglfw3-dev
RUN apt-get -y install libx11-dev
RUN apt-get -y install libxrandr-dev
RUN apt-get -y install libxinerama-dev
RUN apt-get -y install libxcursor-dev
RUN apt-get -y install libxi-dev
RUN apt-get -y install libicu-dev
RUN apt-get -y install freeglut3-dev
RUN apt-get -y install x11-apps

COPY . /usr/src/dockertest1

WORKDIR /usr/src/dockertest1

RUN mkdir -p ./build
RUN cmake -B/build -S . -D CMAKE_BUILD_TYPE=Release
RUN cmake --build /build
RUN make -C /build

FROM build as test

WORKDIR /usr/src/dockertest1

CMD ["./rtype"]
