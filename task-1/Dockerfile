FROM ubuntu:20.04

RUN apt-get update && \
 apt-get install -y python3-pip && \
 apt-get install -y unzip && \
 pip3 install kaggle
 
 WORKDIR /joki-ml-bang
COPY ayamgoreng.c .


RUN gcc ayamgoreng.c -o ayamgoreng

CMD ["./ayamgoreng"]
