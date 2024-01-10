FROM ubuntu:20.04@sha256:703218c0465075f4425e58fac086e09e1de5c340b12976ab9eb8ad26615c3715

ENV user ez_sandrop
ENV chall_port 5555

RUN apt-get update
RUN apt-get -y install socat

RUN adduser --disabled-password $user

ADD ./chall /home/$user/chall


RUN chown -R root:root /home/$user/
RUN chown root:$user /home/$user/chall
RUN chmod 755 /home/$user/chall

WORKDIR /home/$user/
USER $user
EXPOSE $chall_port
CMD while :; do socat -T 30 TCP-LISTEN:$chall_port,reuseaddr,fork EXEC:/home/$user/chall ; done
