FROM ubuntu:22.04@sha256:b6b83d3c331794420340093eb706a6f152d9c1fa51b262d9bf34594887c2c7ac

RUN apt update
RUN apt-get install -y xinetd ssh
RUN apt-get install -y openssh-server
RUN apt-get install vim gdb python3 python3-pip -y

RUN python3 -m pip install --upgrade pip
RUN pip3 install unicorn
RUN pip3 install keystone-engine
RUN pip3 install pwntools

RUN adduser pwn --disabled-password --gecos ''
RUN adduser pwned
RUN echo "Port 22" >> /etc/ssh/sshd_config
RUN echo "	StrictHostKeyChecking no" >> /etc/ssh/ssh_config
RUN echo  "	UserKnownHostsFile=/dev/null" >> /etc/ssh/ssh_config
RUN mkdir -p /home/pwn/.ssh/
RUN touch /home/pwn/.ssh/config
RUN echo "Host * \
   StrictHostKeyChecking no \
   UserKnownHostsFile=/dev/null" > /home/pwn/.ssh/config

RUN chmod 777 /etc/ssh/
COPY ./deploy/flag /home/pwn/flag
COPY ./deploy/chall /home/pwn/chall

RUN chown root:pwned /home/pwn/flag
RUN chown root:pwned /home/pwn/chall
RUN chmod 2640 /home/pwn/flag
RUN chmod 2755 /home/pwn/chall


# SSH 서비스 설정
RUN echo "Port 22" >> /etc/ssh/sshd_config
RUN echo "PasswordAuthentication yes" >> /etc/ssh/sshd_config
RUN echo "PermitRootLogin yes" >> /etc/ssh/sshd_config

RUN echo 'pwn:pwn' | chpasswd
#RUN ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key -N "" -y
#RUN echo "HostKey /etc/ssh/ssh_host_rsa_key" >> /etc/ssh/sshd_config
#RUN ssh-keygen -A
RUN mkdir -p /run/sshd
#RUN sed -i 's|session    required     pam_loginuid.so|session    optional     pam_loginuid.so|g' /etc/pam.d/sshd

RUN service ssh --full-restart
WORKDIR /home/pwn

EXPOSE 22
#USER pwn
CMD ["/usr/sbin/sshd","-D"]
