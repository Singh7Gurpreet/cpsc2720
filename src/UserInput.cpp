/**
* @author L. Nicole  Wilson [n.wilson@uleth.ca]
* @date 2023-09
*/
#include <iostream>

#include "UserInput.h"
#include "BingoTypes.h"
#include "Exceptions.h"

UserInput::UserInput() {}

UserInput::~UserInput() {}

bool UserInput::getDoYouResponse(std::istream& in) {
  char userSays = '\0';
  in >> userSays;

  if (tolower(userSays) == 'y' || tolower(userSays) == 't')
    return true;
  return false;
}

unsigned UserInput::getNumberResponse(std::istream& in, unsigned max,
                                      unsigned min) {
  if (min > max) {
    throw bad_input("Cannot have min > max.");
  }
  unsigned userSays = 0;
  in >> userSays;

  if (userSays < min || userSays > max) {
    std::string msg = "Number entered must in the range [";
    msg += std::to_string(min);
    msg += ", ";
    msg += std::to_string(max);
    msg += "].";
    throw bad_input(msg.c_str());
  }

  return userSays;
}

BingoTypes::gameType UserInput::getGameType(std::istream& in) {
  unsigned userSays = 0;
  in >> userSays;
  if (in.fail() || (userSays != 50 && userSays != 75)) {
    throw bad_input("Did not read expected numeric value of 50 or 75.");
  }

  return static_cast<BingoTypes::gameType>(userSays);
}

BingoTypes::victoryType UserInput::getVictoryType(std::istream& in) {
  unsigned userSays = 0;
  in >> userSays;
  if (in.fail()
      || userSays < 1 || userSays > BingoTypes::NUM_VICTORY_TYPES) {
    std::string msg = "Did not read expected numeric value ";
    msg += "in the range [1, ";
    msg += std::to_string(BingoTypes::NUM_VICTORY_TYPES);
    msg += "].";
    throw bad_input(msg.c_str());
  }
  return static_cast<BingoTypes::victoryType>(userSays);
}

BingoTypes::moveType UserInput::getMoveType(std::istream& in) {
  unsigned userSays = 0;
  in >> userSays;
  if (in.fail()
      || userSays < 1 || userSays > BingoTypes::NUM_MOVE_TYPES) {
    std::string msg = "Did not read expected numeric value ";
    msg += "in the range [1, ";
    msg += std::to_string(BingoTypes::NUM_MOVE_TYPES);
    msg += "].";
    throw bad_input(msg.c_str());
  }
  return static_cast<BingoTypes::moveType>(userSays);
}

BingoTypes::squarePos UserInput::getSquarePosition(std::istream& in) {
  BingoTypes::squarePos pos;

  in >> pos.row;
  if (in.fail() || pos.row < 1 || pos.row > 5) {
    throw bad_input
    ("Did not read expected numeric value for row in the range [1, 5].");
  }

  in >> pos.col;
  if (in.fail() || pos.col < 1 || pos.col > 5) {
    throw bad_input
    ("Did not read expected numeric value for col in the range [1, 5].");
  }

  return pos;
}

std::string UserInput::getPlayerId(std::istream& in) {
  std::string id = "";
  in >> id;

  unsigned count = 0;
  for (char ch : id) {
    if (isspace(ch)) {
      count++;
    }
  }
  if (id.length() == count) {
    throw invalid_identifier("The player id cannot be blank.");
  }

  return id;
}

