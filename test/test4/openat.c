#include <fcntl.h>


int main(){
  openat(AT_FDCWD,"./flag",O_RDONLY);
}
