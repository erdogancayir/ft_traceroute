FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    gcc \
    make \
    iputils-ping \
    traceroute \
    net-tools \
    build-essential \
    sudo \
    curl \
    vim \
    netcat \
    iproute2 \
    git

WORKDIR /usr/src/app

COPY . .

CMD ["tail", "-f", "/dev/null"]