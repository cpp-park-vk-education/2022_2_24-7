FROM gcc:latest
LABEL org.opencontainers.image.authors="gevorkgabrielan@gmail.com"
RUN apt update -y && \
    apt install -y cppcheck clang-tidy clang-format python3-pip libc6-dbg cmake libgtest-dev man tree vim
RUN pip install cpplint
RUN wget https://sourceware.org/pub/valgrind/valgrind-3.18.1.tar.bz2 && \
    tar xfv valgrind-3.18.1.tar.bz2 && \
    cd valgrind-3.18.1 && \
    ./autogen.sh && \
    ./configure && \
    make && \
    make install 
