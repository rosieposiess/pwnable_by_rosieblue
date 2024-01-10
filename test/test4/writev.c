#include <unistd.h>
#include <sys/uio.h>

int main() {
    char buf[100] = "DH{000000000000000000000jjjjjj}";

    struct iovec iov = {
        .iov_base = buf,
        .iov_len = sizeof(buf)
    };

    ssize_t nwritten = writev(1,buf-0x10, 1);

    // nwritten에 쓴 바이트 수가 저장됩니다.

    return 0;
}
