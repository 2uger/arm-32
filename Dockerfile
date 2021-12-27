FROM stronglytyped/arm-none-eabi-gcc:latest
WORKDIR /vision
RUN apt-get update && apt-get install -y \
    qemu-system-arm \
    ranger \
    vim
