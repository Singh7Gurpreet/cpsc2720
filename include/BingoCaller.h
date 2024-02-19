/**
* @author L. Nicole Wilson [n.wilson@uleth.ca]
* @date 2023-09, 2023-10
*/
#ifndef BINGOCALLER_H_INCLUDED
#define BINGOCALLER_H_INCLUDED

#include <string>
#include <vector>

#include "BingoTypes.h"

/**
 * @class BingoCaller BingoCaller.h "BingoCaller.h"
 * @brief Abstract superclass for bingo caller implementations.
 */
class BingoCaller {
 public:
  /**
  * @brief Default constructor.
  * @details Sets victoryType from parameter, sets _currentBall to the end of
  *   the _ballsChosen list.
  * @param [in] victory The victoryType for this game.
  */
  BingoCaller(BingoTypes::victoryType victory = BingoTypes::HORIZONTAL_LINE);

  /**
  * @brief Destructor.
  */
  virtual ~BingoCaller();

  /**
  * @brief Access the victoryType.
  * @return The victory type.
  */
  BingoTypes::victoryType getVictoryType();

  /**
  * @brief Access the gameType.
  * @return The game type.
  */
  BingoTypes::gameType getGameType();

  /**
  * @brief Access the number of balls used for this gameType.
  * @return The number of balls in the game.
  */
  unsigned getNumBalls();

  /**
  * @brief Access the number of balls pulled from the cage.
  * @return The number of balls pulled from the cage.
  */
  unsigned getNumBallsPulled();

  /**
  * @brief Access the number of balls left in the cage.
  * @return The number of balls left in the cage.
  */
  unsigned getNumBallsInCage();

  /**
  * @brief Get the announcement.
  * @return The caller's announcement for the current ball.
  * @throw invalid_size if _ballsChosen is empty.
  */
  virtual std::string getAnnouncement() = 0;

  /**
  * @brief Get the most recent numberCalled.
  * @return The value of the current ball.
  * @throw invalid_size if no balls have been chosen.
  */
  unsigned getCurrentNumber();

  /**
  * @brief Determine if a number was called.
  * @param [in] number The number of interest.
  * @return true, if the number was found in balls chosen, otherwise false.
  * @throw bad_input If the number is outside the range of
  *   valid numbers.
  */
  bool wasNumberCalled(unsigned number);

  /**
  * @brief Make a list of all the balls for called numbers, use makeList.
  * @return A list in a string.
  */
  std::string listPulledBalls();

  /**
  * @brief Make a list of all the balls in the cage, use makeList.
  * @return A list in a string.
  */
  std::string listUnpulledBalls();

  /**
  * @brief Update the victory type.
  * @param [in] victory A victoryType.
  * @throw function_unavailable If a game is in progress
  *   that is, if balls chosen is not empty.
  */
  void setVictoryType(BingoTypes::victoryType victory);

  /**
  * @brief Pull a ball from the ballCage.
  * @details Randomly select a ball from the cage, remove the item from the
  *   ballCage and add it to the ballsChosen, then update the currentBall.
  * @return true, if a ball was pulled, false if no balls are left.
  */
  bool pullBall();

  /**
  * @brief Reset the caller to start a new game.
  * @details Move all the balls into the cage, set the current ball to 0.
  */
  void resetGame();

 protected:
  std::vector<unsigned> _ballCage;
  std::vector<unsigned> _ballsChosen;
  std::vector<unsigned>::iterator _currentBall;
  std::string _description;
  BingoTypes::gameType _game;
  BingoTypes::victoryType _victory;

  /**
  * @brief Make a list of the balls in the given list with at least one entry.
  * @details A comma delimited list each item given in X:99 format. ie: B:01.
  * @param [in] balls The list containing the balls to be listed.
  * @return A string containing the list.
  * @throw invalid_size if the list is empty.
  */
  std::string makeList(const std::vector<unsigned>& balls);

  /**
  * @brief Returns the appropriate letter of BINGO for the given value.
  * @details The value letter relationship is dependant on the gameType.
  *   The first fifth of the valid number range is under the B, the second
  *   fifth is under I and so on.
  * @param [in] value the value of a number square or ball
  * @return The appropriate letter of BINGO.
  * @throw bad_input If the value is not in the valid number range for the gameType.
  */
  char getLetter(unsigned value);
};


/**
 * @class Bingo50Caller BingoCaller.h "BingoCaller.h"
 * @brief Bingo caller for a game with 50 balls that reads the clues from a file.
 * @details The bingo caller's announcements are randomly selected from all the
 *   possible "clue" announcements for that value, as read from the clue file.
 */
class Bingo50Caller : public BingoCaller {
 public:
  /**
  * @brief Default constructor.
  * @details Calls the other constructor with default value for
  *   cluesFile of "data/bingo50calls.csv".
  * @param [in] victory The victoryType for this game.
  */
  Bingo50Caller(BingoTypes::victoryType victory = BingoTypes::HORIZONTAL_LINE);

  /**
  * @brief Constructor.
  * @details Creates all the balls for this game and stores them in _ballCage.
  *   Sets _description, and _game, calls readClues to populate _clues.
  * @param [in] clueFile The relative address of the clueFile.
  * @param [in] victory The victoryType for this game.
  */
  Bingo50Caller(std::string clueFile,
                BingoTypes::victoryType victory = BingoTypes::HORIZONTAL_LINE);

  /**
  * @brief Destructor, deallocates the 2 dimensional dynamic array _clues.
  */
  virtual ~Bingo50Caller();

  /**
  * @brief Creates a message regarding the current ball.
  * @details The message is in the form "B : 4 + 6." There are four possible
  * equations for each number stored in a file with the relative address
  * data/bingo50calls.csv. This file contains 50 lines. Example line:
  * "10,B : 5 x 2,B : 20 / 2,B : 4 + 6,B: 15 - 5"
  * @return The message to be displayed.
  * @throw invalid_size if _ballsChosen is empty.
  */
  std::string getAnnouncement();

  /**
  * @brief Read the clues from the file into the _clues dynamic array.
  * @details The file must be comma delimited. The first line indicates the
  *   number of values for which clues are provided (must be 50) and
  *   the second line indicates the number of clues for each value (must be
  *   between 1 and 10). Each subsequent line contains a value, followed by
  *   the indicated number of clues.
  * @param cluesFile The relative address of the file containing the clues.
  * @throw bad_input If the input file cannot be open or the format is incorrect.
  */
  void readClues(std::string cluesFile);

 private:
  std::string** _clues;
  unsigned _numClues;
};

/**
 * @class Bingo75Caller BingoCaller.h "BingoCaller.h"
 * @brief Bingo caller for a game with 75 balls.
 */
class Bingo75Caller : public BingoCaller {
 public:
  /**
  * @brief Default constructor.
  * @details Creates all the balls for this game and stores them in _ballCage.
  *   Sets _description, and _game.
  * @param [in] victory The victoryType for this game.
  */
  Bingo75Caller(BingoTypes::victoryType victory = BingoTypes::HORIZONTAL_LINE);

  /**
  * @brief Destructor.
  */
  virtual ~Bingo75Caller();


  /**
  * @brief Constructs a string on the form X:##. is: O:72 or B:03.
  * @return The message to be displayed.
  * @throw invalid_size if _ballsChosen is empty or _currentBall is 0.
  */
  std::string getAnnouncement();
};
#endif // BINGOCALLER_H_INCLUDED
