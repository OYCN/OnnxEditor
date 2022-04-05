FROM ubuntu

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y wget git gcc g++ qtdeclarative5-dev
RUN wget https://github.com/bazelbuild/bazelisk/releases/download/v1.11.0/bazelisk-linux-amd64 \
    && chmod +x bazelisk-linux-amd64 \
    && mv bazelisk-linux-amd64 /usr/bin/bazelisk
