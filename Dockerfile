# Use the official Ubuntu base image
FROM ubuntu:latest

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive
ENV PATH="/usr/local/sdl2/bin:${PATH}"

# Install required packages and dependencies
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    gcc-mingw-w64 \
    binutils-mingw-w64 \
	curl \
	unzip \
    && rm -rf /var/lib/apt/lists/*


# Clone raylib
RUN curl -L -k -o raylib.zip https://github.com/raysan5/raylib/releases/download/5.0/raylib-5.0_win32_mingw-w64.zip
RUN unzip raylib.zip
RUN mv raylib-5.0_win32_mingw-w64 /raylib

# Define the working directory
WORKDIR /src

# Copy the example C source code into the container
COPY . .

ENV PATH=/usr/i686-w64-mingw32/sys-root/usr/bin:$PATH
ENV CFLAGS=-m64

run mkdir /build
RUN i686-w64-mingw32-gcc -o /build/main.exe $(find src -type f -name "*.c") -I/raylib/include -L/raylib/lib -lraylib -lm -lgdi32 -lwinmm -lpthread -lws2_32 -static

run ls /build

# Specify the entrypoint to keep the container running
ENTRYPOINT ["tail", "-f", "/dev/null"]
