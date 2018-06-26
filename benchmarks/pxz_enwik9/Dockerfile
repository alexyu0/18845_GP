FROM alexyu0/ubuntu_base

LABEL maintainer="ayu1@andrew.cmu.edu"

COPY enwik9.zip run_pxz.sh /

RUN apt-get -y update
RUN apt-get -y upgrade
RUN apt-get -y install unzip pxz

CMD ./run_pxz.sh container_cmd
