FROM ubuntu:22.04@sha256:b6b83d3c331794420340093eb706a6f152d9c1fa51b262d9bf34594887c2c7ac

ENV user pwn
RUN adduser pwn
RUN adduser pwned
RUN echo "ecsctf\necsctf\n" | passwd pwn

RUN apt update
RUN apt-get install -y xinetd ssh git gdb python2 python3-pip
RUN apt-get install -y openssh-server
WORKDIR /home/pwn
RUN git clone https://github.com/longld/peda.git /home/pwn/peda
RUN pwd
RUN git clone https://github.com/scwuaptx/Pwngdb.git 
RUN ls -la ./Pwngdb
RUN cp /home/pwn/Pwngdb/.gdbinit /home/pwn/.gdbinit

RUN python3 -m pip install --upgrade pip
RUN pip3 install unicorn
RUN pip3 install keystone-engine
RUN pip3 install pwntools
RUN apt-get install vim -y

RUN echo "ecsctf\necsctf\n" | passwd pwn
RUN echo "Port 31337" >> /etc/ssh/sshd_config
#RUN echo "Port 31337" >> /etc/ssh/ssh_config

COPY ./deploy/flag /home/pwn/flag
COPY ./deploy/chall /home/pwn/chall

RUN chown pwned:pwned /home/pwn/flag
RUN chown pwned:pwned /home/pwn/chall
RUN chmod 2640 /home/pwn/flag
RUN chmod 2755 /home/pwn/chall

RUN ssh-keygen -A
RUN mkdir -p /run/sshd
USER pwn

EXPOSE 31337
CMD ["/usr/sbin/sshd", "-D"]
