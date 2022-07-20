FROM ubuntu

ENV DEBIAN_FRONTEND=noninteractive
RUN apt -qyyy update
RUN apt -qyyy install build-essential cmake
RUN apt -qyyy install python3-pip
RUN pip3 install conan
COPY work work
WORKDIR work
RUN mkdir build
WORKDIR build
RUN conan install ..
RUN cmake .. -DCMAKE_BUILD_TYPE=Debug
RUN cmake --build . -j

CMD ./bin/sotest
