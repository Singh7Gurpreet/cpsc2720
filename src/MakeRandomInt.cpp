/**
 * @author L. Nicole  Wilson [n.wilson@uleth.ca]
 * @date 2022-12
 */
#include <iostream>
#include <ctime>
#include <random>

#include "MakeRandomInt.h"

MakeRandomInt::MakeRandomInt() {
  _seed = time(NULL);
  _generator = std::default_random_engine(_seed);
}

MakeRandomInt& MakeRandomInt::getInstance() {
  static MakeRandomInt instance;
  return instance;
}

MakeRandomInt::~MakeRandomInt() {}

int MakeRandomInt::getValue(int max) {
  std::uniform_int_distribution<int> _distribution(0, max - 1);
  return _distribution(_generator);
}
