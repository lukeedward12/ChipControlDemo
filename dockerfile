FROM ubuntu:20.04

# Update and install necessary packages
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make

# Set the working directory in the Docker container
WORKDIR /ChipControlDemo

# Build the project using CMake
CMD rm -rf build && mkdir build && cd build && cmake .. && make clean && make && ctest
