/**
 * @author L. Nicole  Wilson [n.wilson@uleth.ca]
 * @date 2023-09, 2023-10
 */
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "ScreenDisplay.h"
#include "UserInput.h"
#include "Square.h"
#include "BingoTypes.h"
#include "BingoCard.h"

#include "Exceptions.h"

ScreenDisplay::ScreenDisplay() {}

ScreenDisplay::~ScreenDisplay() {}

void ScreenDisplay::displayGrid(std::ostream& out,
                                const std::vector<Square*>& grid) {
  drawBingoCardTop(out, ScreenDisplay::COL_WIDTH);

  for (unsigned i = 0; i < 5; ++i) {
    out << '|';
    for (unsigned k = 0; k < 5; ++k) {
      std::string displaySqu = grid[i + 5 * k]->toString();
      unsigned gap = (ScreenDisplay::COL_WIDTH - displaySqu.size()) / 2;
      out << std::setw(gap + displaySqu.size())
          << std::right << displaySqu;
      if ((grid[i + 5 * k]->getDaubState())->isCorrect()) {
        out << std::setw(gap + 1) << std::right
            << '|';
      } else {
        out << 'x' << std::setw(gap) << std::right
            << '|';
      }
    }
    out << '\n';
  }

  drawHorizontalBorder(out, ScreenDisplay::COL_WIDTH);
  out << '\n';
}

void ScreenDisplay::displayValidity(std::ostream& out, BingoCard* card) {
  drawBingoCardTop(out, ScreenDisplay::COL_WIDTH);

  for (unsigned i = 1; i <= 5; ++i) {
    out << '|';
    for (unsigned k = 1; k <= 5; ++k) {
      BingoTypes::squarePos pos;
      pos.row = i;
      pos.col = k;
      std::string displaySqu = (card->getSquare(pos))->toString();
      unsigned gap = (ScreenDisplay::COL_WIDTH - displaySqu.size()) / 2;
      out << std::setw(gap + displaySqu.size())
          << std::right << displaySqu;
      if (((card->getSquare(pos))->getDaubState())->isCorrect()) {
        out << std::setw(gap + 1) << std::right << '|';
      } else {
        out << 'x' << std::setw(gap) << std::right << '|';
      }
    }
    out << '\n';
  }

  drawHorizontalBorder(out, ScreenDisplay::COL_WIDTH);
  out << '\n';
}

void ScreenDisplay::displayBingoCard(std::ostream& out, BingoCard* card) {
  drawBingoCardTop(out, ScreenDisplay::COL_WIDTH);

  for (unsigned i = 1; i <= 5; ++i) {
    out << '|';
    for (unsigned k = 1; k <= 5; ++k) {
      BingoTypes::squarePos pos;
      pos.row = i;
      pos.col = k;
      std::string displaySqu = (card->getSquare(pos))->toString();
      unsigned gap = (ScreenDisplay::COL_WIDTH - displaySqu.size()) / 2;
      out << std::setw(gap + displaySqu.size())
          << std::right << displaySqu
          << std::setw(gap + 1) << std::right
          << '|';
    }
    out << '\n';
  }

  drawHorizontalBorder(out, ScreenDisplay::COL_WIDTH);
  out << '\n';
}

void ScreenDisplay::displayCallerMessage(std::ostream& out, std::string msg) {
  out << msg;
}

void ScreenDisplay::displayGameInfo(std::ostream& out, BingoCaller* caller) {
  if (caller == nullptr) {
    throw bad_input("Cannot display info without a valid caller.");
  }
  displayGameType(out, caller->getGameType());
  out << " Game : ";
  displayVictoryType(out, caller->getVictoryType());
  out << " Victory Condition";
}

void ScreenDisplay::displayGameBoard(std::ostream& out, BingoCaller* caller) {
  if (caller == nullptr) {
    throw bad_input("Cannot display game board without a valied caller.");
  }
  out << caller->listPulledBalls() << '\n';
}

void ScreenDisplay::displayGameInstructions(std::ostream& out,
    std::string filename,
    std::string tag) {
  std::ifstream fin(filename);

  if (!fin.is_open()) {
    throw bad_input("Game instructions file not found.");
  }

  std::string tagIn = "";
  int numLines = 0;

  fin >> tagIn;

  while (!fin.eof()) {
    if (tag == tagIn) {
      fin >> numLines;
      std::string line = "";
      getline(fin, line, '\n');
      for (; !fin.eof() && numLines > 0; --numLines) {
        out << line << '\n';
        getline(fin, line, '\n');
      }
      out << line << '\n';
      fin.close();
      return;
    } else {
      if (!fin.eof()) {
        fin.ignore(128, '\n');
        fin >> tagIn;
      }
    }
  }
  fin.close();
  std::string msg = "The tag, " + tag + ", was not found in " + filename + ".";
  throw bad_input(msg.c_str());
}

void ScreenDisplay::displayGameType(std::ostream& out,
                                    const BingoTypes::gameType& game) {
  std::string gameStr = gameToString(game);
  out << gameStr;
}

void ScreenDisplay::displayGameTypePrompt(std::ostream& out) {
  out << " Game Type Menu\n"
      << "----------------\n"
      << "50 : Educational bingo with 50 balls\n"
      << "75 : Regular bingo with 75 balls\n"
      << "50/75? ";
}

void ScreenDisplay::displayMoveType(std::ostream& out,
                                    const BingoTypes::moveType& playerMove) {
  out << moveToString(playerMove);
}

void ScreenDisplay::displayMoveTypePrompt(std::ostream& out) {
  out << "Move Type (1 : "
      << moveToString(static_cast<BingoTypes::moveType>(1));

  for (unsigned i = 2; i <= BingoTypes::NUM_MOVE_TYPES; ++i) {
    out << ", " << i << " : "
        << moveToString(static_cast<BingoTypes::moveType>(i));
  }

  out << ")? ";
}

void ScreenDisplay::displaySquarePositionPrompt(std::ostream& out) {
  out << "Which square (enter row column)? ";
}

void ScreenDisplay::displayPlayerIdPrompt(std::ostream& out,
  const std::map<std::string, BingoCard*>& players) {
  out << "Which player (";
  auto it = players.begin();
  out << it->first;
  ++it;
  for (; it != players.end(); ++it) {
    out << ", " << it->first;
  }
  out << ")? ";
}

void ScreenDisplay::displayValidityCheck(std::ostream& out,
                                         const std::vector<Square*>& grid) {
  out << "Daubing errors are marked with an x.\n";

  drawBingoCardTop(out, ScreenDisplay::COL_WIDTH);

  for (unsigned i = 0; i < 5; ++i) {
    out << '|';
    for (unsigned k = 0; k < 5; ++k) {
      std::string displaySqu = grid[i + 5 * k]->toString();
      unsigned gap = (ScreenDisplay::COL_WIDTH - displaySqu.size()) / 2;
      out << std::setw(gap + displaySqu.size())
          << std::right << displaySqu;
      if (grid[i + 5 * k]->getDaubState()->isCorrect())
        out << std::setw(gap + 1) << std::right << '|';
      else
        out << 'x' << std::setw(gap) << std::right << '|';
    }
    out << '\n';
  }

  drawHorizontalBorder(out, ScreenDisplay::COL_WIDTH);
}

void ScreenDisplay::displayVictoryType(std::ostream& out,
                                       const BingoTypes::victoryType& victory) {
  out << victoryToString(victory);
}

void ScreenDisplay::displayVictoryTypePrompt(std::ostream& out) {
  out << "Victory Condition (1 : "
      << victoryToString(static_cast<BingoTypes::victoryType>(1));

  for (unsigned i = 2; i <= BingoTypes::NUM_VICTORY_TYPES; ++i) {
    out << ", " << i << " : "
        << victoryToString(static_cast<BingoTypes::victoryType>(i));
  }

  out << ")? ";
}

void ScreenDisplay::displayVictoryDescription(std::ostream& out,
                                 const BingoTypes::victoryType& victory) {
  out << victoryToString(victory) << '\n'
      << victoryToDescription(victory) << '\n';
}

std::string ScreenDisplay::gameToString(BingoTypes::gameType game) {
  switch (game) {
    case BingoTypes::BINGO75:
      return "Bingo 75";
    case BingoTypes::BINGO50:
      return "Bingo 50";
    default:
      return "Not defined";
  }
}

std::string ScreenDisplay::victoryToString(BingoTypes::victoryType victory) {
  switch (victory) {
    case BingoTypes::HORIZONTAL_LINE:
      return "Horizontal line";
    case BingoTypes::VERTICAL_LINE:
      return "Vertical line";
    case BingoTypes::ANY_LINE:
      return "Any line";
    case BingoTypes::BLACKOUT:
      return "Blackout";
    default:
      return "Not defined";
  }
}

std::string ScreenDisplay::victoryToDescription
  (BingoTypes::victoryType victory) {
  VictoryCondition* victoryCondition;

  switch (victory) {
    case BingoTypes::HORIZONTAL_LINE:
      victoryCondition = new HorizontalLine();
      break;
    case BingoTypes::VERTICAL_LINE:
      victoryCondition = new VerticalLine();
      break;
    case BingoTypes::ANY_LINE:
      victoryCondition = new AnyLine();
      break;
    case BingoTypes::BLACKOUT:
      victoryCondition = new Blackout();
      break;
    default:
      return "Not defined";
  }
  std::string desc = victoryCondition->getDescription();
  delete victoryCondition;

  return desc;
}

std::string ScreenDisplay::moveToString(BingoTypes::moveType playerMove) {
  switch (playerMove) {
    case BingoTypes::DAUB:
      return "Daub Square";
    case BingoTypes::BINGO:
      return "Bingo";
    case BingoTypes::SHOW_CARD:
      return "Show Card";
    case BingoTypes::CHECK_CARD:
      return "Check Card";
    case BingoTypes::SHOW_GAME:
      return "Show Game Info";
    case BingoTypes::SHOW_BOARD:
      return "Show Board";
    case BingoTypes::HELP:
      return "Help/Instructions";
    case BingoTypes::QUIT_GAME:
      return "Quit Game";
    default:
      return "Not defined";
  }
}

void ScreenDisplay::drawHorizontalBorder(std::ostream& out,
                                         unsigned colWidth) {
  out << '+' << std::setfill('-');
  for (unsigned i = 0; i < 5; ++i) {
    out << std::setw(colWidth + 1) << std::right << '+';
  }
  out << std::setfill(' ');
}

void ScreenDisplay::drawBingoCardTop(std::ostream& out,
                                     unsigned colWidth) {
    int j = 0;
    int counter = 0;
    std::string bingo = "BINGO";
    for (int i = 0; i <= 35; i++) {
        if (i%7 == 0) {
            out <<"+";
        } else {
            out <<"-";
        }
    }
    out << std::endl;
    for (int i = 0; i <= 35; i++) {
        if (i%7 == 0) {
            out <<"|";
            j = 0;
        } else if (j == 3) {
            out << bingo[counter++];
                j++;
        } else {
        out << " ";
        j++;
        }
    }
    out << std::endl;
    for (int i = 0; i <= 35; i++) {
        if (i%7 == 0) {
            out <<"+";
        } else {
            out <<"-";
        }
    }
    out << std::endl;
}
