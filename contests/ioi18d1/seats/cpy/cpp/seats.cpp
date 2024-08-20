#include "seats.h"

std::vector<int> r;

void give_initial_chart(int H, int W, std::vector<int> R, std::vector<int> C) {
  r = R;
}

int swap_seats(int a, int b) {
  return r[a];
}
