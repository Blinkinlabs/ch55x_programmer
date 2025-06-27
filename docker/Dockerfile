FROM docker.io/library/debian:12 AS base

RUN apt-get -qq update -y

RUN DEBIAN_FRONTEND=noninteractive \
       apt-get install -y --no-install-recommends \
            build-essential \
            libusb-1.0.0-dev \
            git \
            sdcc \
            ca-certificates

RUN git clone https://github.com/ole00/chprog.git /src
WORKDIR /src
RUN ./build_linux.sh
RUN cp ./chprog /usr/local/bin

# Needed for git --describe to work
RUN git config --global --add safe.directory /build
