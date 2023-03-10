FROM debian

RUN apt update
RUN apt install gcc xorg imagemagick libasan5 git libx11-dev g++ make -y
WORKDIR /app

ENTRYPOINT ["tail", "-f", "/dev/null"]
