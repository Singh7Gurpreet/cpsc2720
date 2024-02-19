/**
* @author L. Nicole  Wilson [n.wilson@uleth.ca]
* @date 2023-09
*/
#include <iostream>

#include "Square.h"
#include "DaubState.h"

Square::Square(unsigned value) : _value{value} {}

Square::~Square() {
  delete _daubed;
}

unsigned Square::getValue() {
  return _value;
}

DaubState* Square::getDaubState() {
  return _daubed;
}

FreeSquare::FreeSquare(unsigned value) : Square(0) {
  _daubed = new GoodDaub();
}

FreeSquare::~FreeSquare() {}

bool FreeSquare::daubSquare(unsigned numberCalled) {
  return false;
}

void FreeSquare::shouldDaubSquare(unsigned numberCalled) {}

void FreeSquare::resetSquare() {}

std::string FreeSquare::toString() {
  return "free";
}

IntSquare::IntSquare(unsigned value) : Square{value} {
  _daubed = new NoDaub();
}

IntSquare::~IntSquare() {}

bool IntSquare::daubSquare(unsigned numberCalled) {
  bool toReturn = true;
  if ( _daubed->isDaubed() && _daubed->isCorrect()) return false;
  if ( _daubed->isDaubed()) toReturn = false;
  delete _daubed;
  _daubed = nullptr;
  if (numberCalled == _value) {
    _daubed = new GoodDaub();
  } else {
    _daubed = new BadDaub();
  }
  return toReturn;
}

void IntSquare::shouldDaubSquare(unsigned numberCalled) {
  if ((numberCalled == _value) && (_daubed->isDaubed() == false)) {
    delete _daubed;
    _daubed = nullptr;
    _daubed = new NeedsDaub();
  }
}

void IntSquare::resetSquare() {
  delete _daubed;
  _daubed = new NoDaub();
}

std::string IntSquare::toString() {
  std::string display = "";
  if (_daubed->isDaubed())
    display = "(";
  else
    display = " ";

  if (_value < 10)
    display += "0" + std::to_string(_value);
  else
    display += std::to_string(_value);

  if (_daubed->isDaubed())
    display += ")";
  else
    display += " ";

  return display;
}
