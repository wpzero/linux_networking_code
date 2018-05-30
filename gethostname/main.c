#include <unistd.h>
#include <stdio.h>

int main() {
  char hostname[100];
  gethostname(hostname, sizeof(hostname));
  printf("%s\n", hostname);
  return 0;
}
