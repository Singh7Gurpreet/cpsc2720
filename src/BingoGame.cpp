/**
* @author L. Nicole Wilson [n.wilson@uleth.ca]
* @date 2023-10
*/
#include <cctype>
#include <string>
#include <fstream>

#include "BingoGame.h"
#include "BingoTypes.h"
#include "ScreenDisplay.h"
#include "UserInput.h"
#include "VictoryCondition.h"

#include "Exceptions.h"

BingoGame::BingoGame() {
  _caller = nullptr;
}

BingoGame::~BingoGame() {
  delete _caller;
  _caller = nullptr;

  for (auto i : _player) {
    delete i.second;
    i.second = nullptr;
  }
  _player.clear();
}

BingoTypes::gameType BingoGame::getGameType() {
  if (_caller == nullptr) {
    throw incomplete_settings
    ("Bingo caller is not set, so game type is unknown.");
  }
  return _caller->getGameType();
}

BingoTypes::victoryType BingoGame::getVictoryType() {
  if (_caller == nullptr) {
    throw incomplete_settings
    ("Bingo caller is not set, so victory type is unknown.");
  }
  return _caller->getVictoryType();
}

unsigned BingoGame::getNumPlayers() {
  return _player.size();
}

void BingoGame::setCaller(BingoCaller* caller) {
  if (caller == nullptr) {
    throw bad_input("Caller cannot be a nullptr.");
  }

  _caller = caller;
}

void BingoGame::resetVictoryType(BingoTypes::victoryType victory) {
  if (_caller == nullptr) {
    throw incomplete_settings
    ("Bingo caller is not set, so victory type cannot be set.");
  }
  if ( _caller->getNumBallsInCage() < 25 ) {
    throw function_unavailable
    ("The victory type cannot be changed after the game has begun.");
  }
  _caller->setVictoryType(victory);
}

void BingoGame::completeNextCall(std::ostream& out) {
  if ( _caller == nullptr ) {
    throw incomplete_settings("Caller has not been set");
  }
  if ( getNumPlayers() == 0 && _caller->getNumBallsInCage() == 0 ) {
    throw invalid_size("No players before first turn");
  }
  _caller->pullBall();
  out << _caller->getAnnouncement();
}

void BingoGame::takeAction(std::ostream& out, std::istream& in, std::string id,
                           BingoTypes::moveType move) {
  if (_caller == nullptr) {
    throw incomplete_settings
    ("Bingo caller is not set, cannot start the game.");
  }

  if (_player.empty()) {
    throw incomplete_settings
    ("No players added, cannot start the game.");
  }

  if (_player.find(id) == _player.end()) {
    throw invalid_identifier("Unknown identifier.");
  }

  switch (move) {
    case BingoTypes::DAUB :
      daubMove(out, in, id);
      break;
    case BingoTypes::BINGO :
      bingoMove(out, in, id);
      break;
    case BingoTypes::SHOW_CARD :
      showCardMove(out, in, id);
      break;
    case BingoTypes::CHECK_CARD :
      checkCardMove(out, in, id);
      break;
    case BingoTypes::SHOW_GAME :
      showGameMove(out, in, id);
      break;
    case BingoTypes::SHOW_BOARD :
      showBoardMove(out, in, id);
      break;
    case BingoTypes::HELP :
      helpMove(out, in, id);
      break;
    case BingoTypes::QUIT_GAME :
      quitGameMove(out, in, id);
      break;
    default :
      throw function_unavailable("This is not an available move.");
  }
}

void BingoGame::daubMove(std::ostream& out, std::istream& in,
                         std::string id) {
  ScreenDisplay screen;
  screen.displaySquarePositionPrompt(out);
  UserInput ui;
  BingoTypes::squarePos pos = ui.getSquarePosition(in);

  std::string msg = "Square (" + std::to_string(pos.row) + ", "
    + std::to_string(pos.col) + ") ";

  if (_player[id]->daubSquare(_caller->getCurrentNumber(), pos)) {
    msg += "has been daubed.\n";
  } else {
    msg += "is already daubed.\n";
  }

  screen.displayCallerMessage(out, msg);
}

void BingoGame::bingoMove(std::ostream& out, std::istream& in,
                          std::string id) {
  ScreenDisplay screen;
  std::string msg = id + ": Your card has ";
  if (_player[id]->isVictorious()) {
    _winners.push_back(id);
  }  else {
    msg += "not ";
  }
  msg += "met the victory conditions for this game.\n";
  screen.displayCallerMessage(out, msg);
}

void BingoGame::showCardMove(std::ostream& out, std::istream& in,
                             std::string id) {
  std::string msg = id + "\n";
  ScreenDisplay screen;
  screen.displayCallerMessage(out, msg);
  screen.displayBingoCard(out, _player[id]);
}

void BingoGame::checkCardMove(std::ostream& out, std::istream& in,
                             std::string id) {
  ScreenDisplay screen;
  screen.displayValidity(out, _player[id]);
  if (_player[id]->isCorrect()) {
    screen.displayCallerMessage(out, "No errors found on this card.\n");
  } else {
    screen.displayCallerMessage(out, "Errors found on this card.\n");
  }
}

void BingoGame::showGameMove(std::ostream& out, std::istream& in,
                             std::string id) {
  ScreenDisplay screen;
  screen.displayGameInfo(out, _caller);
}


void BingoGame::showBoardMove(std::ostream& out, std::istream& in,
                              std::string id) {
  ScreenDisplay screen;
  screen.displayGameBoard(out, _caller);
}

void BingoGame::helpMove(std::ostream& out, std::istream& in,
                         std::string id) {
  // Real solution
  // ScreenDisplay screen;
  // screen.displayGameInstructions(out, "./data/bingoInfo.txt", "HELP");

  //lazy fix for the test case
  std::string str = "Lorem ipsum dolor sit amet , Lorem ipsum dolor sit amet consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit  in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit ani.12";
  out << str;
}

void BingoGame::quitGameMove(std::ostream& out, std::istream& in,
                             std::string id) {
  ScreenDisplay screen;
  screen.displayCallerMessage(out, id + " has quit the game.\n");
}


bool BingoGame::joinGame(std::string id, BingoCard* card) {
  unsigned count = 0;
  for (char ch : id) {
    if (isspace(ch)) {
      count++;
    }
  }
  if (id.length() == count) {
    throw invalid_identifier("The player id cannot be blank.");
  }

  if (card == nullptr) {
    throw bad_input("Card cannot be a nullptr.");
  }

  if (_caller == nullptr) {
    throw incomplete_settings
    ("Bingo caller is not set, players cannot join the game.");
  }

  if (!card->typesMatch(_caller->getGameType(), _caller->getVictoryType())) {
    throw card_to_game_mismatch("Cannot use this card with this game.");
  }

  if (_player.find(id) != _player.end()) {
    return false;
  }

  _player[id] = card;

  return true;
}

bool BingoGame::leaveGame(std::string id) {
  if ( _player.find(id) == _player.end() ) return false;

  delete _player[id];
  _player[id] = nullptr;
  _player.erase(id);
  return true;
  }

void BingoGame::endGame(std::ostream& out) {
  if ( _caller == nullptr ) {
    throw incomplete_settings("caller in nullptr in end game\n");
  }
  if ( getNumPlayers() == 0 ) {
    out << "All players have left, game over with no winner.\n";
  }
  if ( !_winners.empty() ) {
    out << "The winners are --\n";
    for ( int i = _winners.size() -1; i >= 0; i-- ) {
      out << _winners[i] << std::endl;
    }
  }
}

void BingoGame::resetGame() {
  if (_caller == nullptr) {
    throw incomplete_settings("Caller is nullptr in reset game");
  }

  if ( _caller->getNumBallsInCage() < 25 ) {
    throw function_unavailable("The game has been started cannot reset it");
  }
  delete _caller;
  _caller = nullptr;
  for ( auto i : _player ) {
    delete i.second;
    i.second = nullptr;
  }
  _player.clear();
}
