FROM alexyu0/filebench_image

LABEL maintainer="ayu1@andrew.cmu.edu"

COPY . /

RUN libtoolize
RUN aclocal
RUN autoheader
RUN automake --add-missing
RUN autoconf
RUN ./configure
RUN make
RUN make install

CMD ./run_filebench.sh container_cmd

