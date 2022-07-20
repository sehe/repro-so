FROM ubuntu

ENV DEBIAN_FRONTEND=noninteractive
RUN apt -qyyy update
RUN apt -qyyy install build-essential cmake
RUN apt -qyyy install python3-pip
RUN apt -qyyy install libboost-all-dev libsnappy-dev git
COPY work work
WORKDIR work
RUN git clone https://github.com/apache/avro
RUN mkdir build
WORKDIR build
RUN cmake .. -DCMAKE_BUILD_TYPE=Debug
RUN cmake --build . -j

CMD ./sotest
