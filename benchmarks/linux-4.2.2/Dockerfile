FROM alexyu0/ubuntu_base

LABEL maintainer="ayu1@andrew.cmu.edu"

COPY linux-4.2.2.zip run_kernel_compile.sh /

RUN apt-get -y update
RUN apt-get -y upgrade
RUN apt-get -y install build-essential \
    unzip \
    bc \
    openssl \
    libssl-dev

CMD ./run_kernel_compile.sh container_cmd

