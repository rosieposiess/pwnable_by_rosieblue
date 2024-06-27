FROM ubuntu:20.04@sha256:703218c0465075f4425e58fac086e09e1de5c340b12976ab9eb8ad26615c3715 

#환경변수설정
ENV user ezbof
ENV chall_port 5555

#RUN 어쩌구는 저거 실행하세요! 라는 뜻
RUN apt-get update
RUN apt-get -y install socat

#나는 ez_sandrop라는 유저를 추가해줬고 비번 설정 x
RUN adduser --disabled-password $user

#로컬에 있는 ./oob_1(내 문제 바이너리)를 도커의 /home/$user/chall로 복사
ADD ./ezbof /home/$user/chall
ADD ./flag /home/$user/flag

#권한 설정
RUN chown -R root:root /home/$user/
RUN chown root:$user /home/$user/chall
RUN chmod 755 /home/$user/chall
RUN chown $user:$user /home/$user/flag

WORKDIR /home/$user/
USER $user
EXPOSE $chall_port
#socat으로 계속 바이너리에 listen할 거고 chall_port(우리가 위해서 정한 숫자)로 listen할거다~
CMD while :; do socat -T 30 TCP-LISTEN:$chall_port,reuseaddr,fork EXEC:/home/$user/chall ; done 
