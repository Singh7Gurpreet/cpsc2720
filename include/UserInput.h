/**
* @author L. Nicole  Wilson [n.wilson@uleth.ca]
* @date 2023-09
*/
#ifndef USER_INPUT_H_INCLUDED
#define USER_INPUT_H_INCLUDED

#include <iostream>
#include <string>

#include "BingoTypes.h"

/**
* @class UserInput UserInput.h "UserInput.h"
* @brief Implements text based user interface.
*/
class UserInput {
 public:
  /**
  * @brief Default constructor.
  */
  UserInput();

  /**
  * @brief Destructor.
  */
  ~UserInput();

  /**
  * @brief Read yes/no or true/false information.
  * @param [in] in Extract from this input stream.
  * @return true, if yes or true is chosen, false otherwise.
  * @throw bad_input If the user doesn't choose a valid response.
  */
  bool getDoYouResponse(std::istream& in);

  /**
  * @brief Read a non-negative integer response between a given max and min.
  * @param [inout] in Extract from this input stream.
  * @param [in] max The maximum acceptable value.
  * @param [in] min The minimum acceptable value.
  * @return The unsigned integer read.
  * @throw bad_input If the min is greater than the max.
  * @throw bad_input If the user doesn't enter a valid response.
  */
  unsigned getNumberResponse(std::istream& in, unsigned max,
                             unsigned min = 0);

  /**
  * @brief Read the desired gameType.
  * @param [in] in Extract from this input stream.
  * @return The gameType read.
  * @throw bad_input If the user doesn't choose a valid response.
  */
  BingoTypes::gameType getGameType(std::istream& in);

  /**
  * @brief Read the desired victoryType.
  * @param [in] in Extract from this input stream.
  * @return The victoryType read.
  * @throw bad_input If the user doesn't choose a valid response.
  */
  BingoTypes::victoryType getVictoryType(std::istream& in);

  /**
  * @brief Read the desired moveType.
  * @param [in] in Extract from this input stream.
  * @return The moveType read.
  * @throw bad_input If the user doesn't choose a valid response.
  */
  BingoTypes::moveType getMoveType(std::istream& in);

  /**
  * @brief Read the desired square address (row, column, and card).
  * @param [in] in Extract from this input stream.
  * @return The squarePos read.
  * @throw bad_input If the user doesn't choose a valid response.
  */
  BingoTypes::squarePos getSquarePosition(std::istream& in);

  /**
  * @brief Read a non-empty, non-blank string with no spaces.
  * @param [in] in Extract from this input stream.
  * @return The id read read.
  * @throw invalid_identifier If the user enters an empty or blank string.
  */
  std::string getPlayerId(std::istream& in);
};
#endif // USER_INPUT_H_INCLUDED
