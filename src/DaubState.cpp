/**
* @author L. Nicole  Wilson [n.wilson@uleth.ca]
* @date 2023-09
*/
#include "DaubState.h"

DaubState::DaubState() {}

DaubState::~DaubState() {}

NoDaub::NoDaub() {}

NoDaub::~NoDaub() {}

bool NoDaub::isDaubed() {
  return false;
}

bool NoDaub::isCorrect() {
  return true;
}

GoodDaub::GoodDaub() {}

GoodDaub::~GoodDaub() {}

bool GoodDaub::isDaubed() {
  return true;
}

bool GoodDaub::isCorrect() {
  return true;
}

BadDaub::BadDaub() {}

BadDaub::~BadDaub() {}

bool BadDaub::isDaubed() {
  return true;
}

bool BadDaub::isCorrect() {
  return false;
}

NeedsDaub::NeedsDaub() {}

NeedsDaub::~NeedsDaub() {}

bool NeedsDaub::isDaubed() {
  return false;
}

bool NeedsDaub::isCorrect() {
  return false;
}
