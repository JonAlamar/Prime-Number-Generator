#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

int currentPrime;

int main() {

  struct termios info;
  tcgetattr(0, &info);
  info.c_lflag &= ~ICANON;
  tcsetattr(0, TCSANOW, &info);

  int i, isPrime = 0;
  int num;
  void f(int);

  signal(SIGINT, f);
  for (num = 1; num < 1000000; num++) {
    for (i = 2; i <= (num / 2); ++i) {
      if (num % i == 0) {
        isPrime = 1;
        break;
      }
    }
    if (isPrime == 0) {
      currentPrime = num;
    } else
      isPrime = 0;
      usleep(100000);
  }
}

void f(int signum) {
  bool choice = true;
  int ch;
  printf("\nCurrent prime is %d\n", currentPrime);
  while (choice) {
    printf("Quiz [y/n]? ");
    ch = getchar();
    if (ch == 78 || ch == 110) {
      break;
    } else if (ch == 89 || ch == 121) {
      exit(1);
    } else {
      printf("\nPlease enter a valid letter option\n");
    }
  }
}