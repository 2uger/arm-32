FROM stronglytyped/arm-none-eabi-gcc:latest
RUN apt-get update && apt-get install -y \
    qemu-system-arm \
    ranger \
    vim
ENTRYPOINT ["tail", "-f", "/dev/null"]
