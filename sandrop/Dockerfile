FROM ubuntu:20.04@sha256:703218c0465075f4425e58fac086e09e1de5c340b12976ab9eb8ad26615c3715

ENV user sandrop
ENV chall_port 4444

RUN apt-get update
RUN apt-get -y install socat

RUN adduser $user

ADD ./flag /home/$user/flag
ADD ./chall /home/$user/chall

RUN chown root:$user /home/$user/flag
RUN chown root:$user /home/$user/chall

RUN chmod 755 /home/$user/chall
RUN chmod 440 /home/$user/flag

WORKDIR /home/$user
USER $user
EXPOSE $chall_port
CMD socat -T 30 TCP-LISTEN:$chall_port,reuseaddr,fork EXEC:/home/$user/chall
