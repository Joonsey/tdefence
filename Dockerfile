# Use the official Ubuntu base image
FROM ubuntu:latest

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive
ENV PATH="/usr/local/sdl2/bin:${PATH}"

# Install required packages and dependencies
RUN apt-get update && \
    apt-get install -y \
	mingw-w64 \
    wget \
    tar \
	libsdl2-image-dev \
	libsdl2-dev \
	libsdl2-gfx-dev \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Download and extract SDL2 for Windows
RUN wget https://www.libsdl.org/release/SDL2-devel-2.30.3-mingw.tar.gz && \
    tar -xzf SDL2-devel-2.30.3-mingw.tar.gz && \
	mkdir /usr/local/sdl2 && \
    mv SDL2-2.30.3/x86_64-w64-mingw32/* /usr/local/sdl2/

RUN wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.8.0-mingw.tar.gz && \
    tar -xzf SDL2_image-devel-2.8.0-mingw.tar.gz && \
    cp -r SDL2_image-2.8.0/x86_64-w64-mingw32/* /usr/local/sdl2

# Define the working directory
WORKDIR /workspace

# Copy the example C source code into the container
COPY src /workspace/

ENV PATH=/usr/i686-w64-mingw32/sys-root/usr/bin:$PATH
ENV CFLAGS=-m64

# Build command using mingw-w64 g++ (assuming C++)
run mkdir /build
RUN x86_64-w64-mingw32-gcc -o /build/main.exe *.c -lm \
    -I/usr/local/sdl2/include \
    -L/usr/local/sdl2/lib \
	-lwinmm -lpthread -lws2_32\
	-lmingw32 \
    -lSDL2 \
    -lSDL2_image \
    -lSDL2_gfx

run ls /build

# Specify the entrypoint to keep the container running
ENTRYPOINT ["tail", "-f", "/dev/null"]
