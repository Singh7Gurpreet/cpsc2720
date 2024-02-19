/**
 * @author L. Nicole Wilson [n.wilson@uleth.ca]
 * @date 2023-09, 2023-10
 */
#include <algorithm>
#include <iterator>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "BingoCaller.h"
#include "BingoTypes.h"
#include "MakeRandomInt.h"
#include "Exceptions.h"

BingoCaller::BingoCaller(BingoTypes::victoryType victory)
  : _victory{victory} {
  _currentBall = _ballsChosen.end();
}

BingoCaller::~BingoCaller() {}

BingoTypes::victoryType BingoCaller::getVictoryType() {
  return _victory;
}

BingoTypes::gameType BingoCaller::getGameType() {
  return _game;
}

unsigned BingoCaller::getNumBalls() {
  return static_cast<unsigned>(_game);
}

unsigned BingoCaller::getNumBallsPulled() {
  return _ballsChosen.size();
}

unsigned BingoCaller::getNumBallsInCage() {
  return _ballCage.size();
}

std::string BingoCaller::listPulledBalls() {
  std::string result;
  try {
    result = makeList(_ballsChosen);
  } catch (invalid_size) {
    result = "No balls have been pulled.";
  }
  return result;
}

std::string BingoCaller::listUnpulledBalls() {
  std::string result;
  try {
    result = makeList(_ballCage);
  } catch (invalid_size) {
    result = "No balls are left in the cage.";
  }
  return result;
}

void BingoCaller::setVictoryType(BingoTypes::victoryType victory) {
  if (!_ballsChosen.empty()) {
    throw function_unavailable("Game has begun cannot set victory type");
  }
  _victory = victory;
}

bool BingoCaller::pullBall() {
  if ( _ballCage.size() == 0 ) return false;
  int curr = *_ballCage.begin();
  _ballCage.erase(_ballCage.begin());
  _ballsChosen.push_back(curr);
  _currentBall = _ballsChosen.begin()+(_ballsChosen.size()-1);
  return true;
}

unsigned BingoCaller::getCurrentNumber() {
  if ( _ballsChosen.size() == 0 ) {
    throw invalid_size("No balls have been pulled");
  }
  return _currentBall == _ballsChosen.end()?0:*_currentBall;
}

bool BingoCaller::wasNumberCalled(unsigned number) {
  int size = -1;
  if ( _game == BingoTypes::BINGO50 ) {
    size = 50;
  }
  if ( _game == BingoTypes::BINGO75 ) {
    size = 75;
  }
  if ( number > size || number <= 0 ) {
    throw bad_input("Number out of valid range");
  }

  for (int i = 0 ; i < _ballsChosen.size(); i++) {
    if ( _ballsChosen[i] == number )
      return true;
  }

  return false;
}

void BingoCaller::resetGame() {
  for ( auto i : _ballsChosen ) {
    _ballCage.push_back(i);
  }
  _ballsChosen.clear();

  _currentBall = _ballsChosen.end();
}

std::string BingoCaller::makeList(const std::vector<unsigned>& balls) {
  if ( balls.size() == 0 ) {
    throw invalid_size("Not good");
  }

  std::string result = "";
  for ( int i = 0; i < balls.size(); i++ ) {
    result += getLetter(balls[i]);
    result += ":";
    if (balls[i] < 10) result += ("0"+std::to_string(balls[i]));
    else
      result += std::to_string(balls[i]);
    if ( i < balls.size() - 1) result += ',';
  }
  return result;
}

char BingoCaller::getLetter(unsigned value) {
  int size = -1;
  if ( _game == BingoTypes::BINGO50 ) {
    size = 10;
  }
  if ( _game == BingoTypes::BINGO75 ) {
    size = 15;
  }

  std::string bingo = "BINGO";
  for (int i = 0 ; i < 5; i++) {
    int upperLimit = (i+1) * size;
    int lowerLimit = i*size + 1;

    if ( value <= upperLimit && value >= lowerLimit ) {
      return bingo[i];
    }
  }
  return 'B';
}

Bingo50Caller::Bingo50Caller(BingoTypes::victoryType victory)
  : Bingo50Caller{"data/bingo50calls.csv", victory} {}

Bingo50Caller::Bingo50Caller(std::string cluesFile,
                             BingoTypes::victoryType victory)
  : BingoCaller{victory} {
  _game = BingoTypes::BINGO50;
  _clues = new std::string*[50] {nullptr};
  try {
    readClues(cluesFile);
  } catch (bad_input) {
    for (int i = 0; _clues[i] != nullptr; i++) {
    delete []_clues[i];
    _clues[i] = nullptr;
  }
    delete []_clues;
    _clues = nullptr;
    throw bad_input("Bingo caller failed due to failed read clues ");
  }
  for (int i = 1; i < 51; i++) {
    _ballCage.push_back(i);
}
}

Bingo50Caller::~Bingo50Caller() {
  for (int i = 0; i < 50; i++) {
    delete []_clues[i];
    _clues[i] = nullptr;
  }
  delete []_clues;
  _clues = nullptr;
}

std::string Bingo50Caller::getAnnouncement() {
  if (_ballsChosen.size() == 0) {
    throw invalid_size("balls chosen is empty");
  }
  return _clues[_ballsChosen[_ballsChosen.size()-1]][0];
}

void Bingo50Caller::readClues(std::string cluesFile) {
  std::ifstream fin;
  std::stringstream streamPerLine;
  std::string toReadFromFile, tokens;
  std::vector<std::string> bufferForTokens;

  fin.open(cluesFile, std::ios_base::in);

  if (!fin.is_open()) {
    throw bad_input("File cannot be opened");
  }

  getline(fin, toReadFromFile);

  streamPerLine << toReadFromFile;

  bufferForTokens.clear();

  while (getline(streamPerLine, tokens, ',')) {
    bufferForTokens.push_back(tokens);
  }

  if (bufferForTokens.size() == 0 || bufferForTokens[0] != "50") {
    throw bad_input("The clue value must be 50");
  }
  int value;
  try {
    value = std::stoi(bufferForTokens[1]);
  } catch (std::invalid_argument) {
    throw bad_input("Not valid format");
  }
  if ( value <= 0 || value >= 10 ) {
    throw bad_input("The value is not between 0 and 10");
  }

  int count = 0;

  while (getline(fin, toReadFromFile)) {
    bufferForTokens.clear();
    std::stringstream ss(toReadFromFile);

    while (getline(ss, tokens, ','))
      bufferForTokens.push_back(tokens);

    if (bufferForTokens.size() != value+1) {
      throw bad_input("Value is not valid");
    }

    int temp;
    try {
      temp = std::stoi(bufferForTokens[0]);
    } catch (std::invalid_argument) {
      throw bad_input("Not good count");
    }
    if ( temp != (count +1) ) {
      throw bad_input("Not equal count");
    }

    _clues[count] = new std::string[value];

    for (int i = 1; i <= value; i++) {
      _clues[count][i-1] = bufferForTokens[i];
    }
    ++count;
  }
  if (count != 50) {
    throw bad_input("Too few clue lines");
  }
  fin.close();
}

Bingo75Caller::Bingo75Caller(BingoTypes::victoryType victory)
  : BingoCaller{victory} {
  _game = BingoTypes::BINGO75;
  for ( int i = 1; i < 76; i++ ) {
    _ballCage.push_back(i);
  }
  _ballsChosen.clear();
  _description = "New bingo 75 game";
}

Bingo75Caller::~Bingo75Caller() {}

std::string Bingo75Caller::getAnnouncement() {
  if ( _currentBall == _ballsChosen.end() || _ballsChosen.empty() ) {
    throw invalid_size("Current ball is 0 or balls chosen is empty");
  }
  std::string number =
  *_currentBall < 10 ?
  "0"+std::to_string(*_currentBall):
  std::to_string(*_currentBall);
  std::string result =
  getLetter(*_currentBall) +":"+number;
  return result;
}
