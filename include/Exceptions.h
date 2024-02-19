/**
* @author Dr. Anvik [john.anvik@uleth.ca], L. Nicole  Wilson [n.wilson@uleth.ca]
* @date 2018-09, 2023-09
*/

#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <stdexcept>


/**
* @brief Unusable input from user.
*/
class bad_input: public std::runtime_error {
 public:
  /**
  * @param errMessage An error message.
  */
  explicit bad_input(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

/**
* @brief The given bingo card cannot be used for this game.
*/
class card_to_game_mismatch: public std::runtime_error {
 public:
  /**
  * @param errMessage An error message.
  */
  explicit card_to_game_mismatch(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

/**
* @brief The action cannot be taken at this time.
*/
class function_unavailable: public std::runtime_error {
 public:
  /**
  * @param errMessage An error message.
  */
  explicit function_unavailable(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

/**
* @brief Trying to use methods that require settings that are not made.
*/
class incomplete_settings: public std::runtime_error {
 public:
  /**
  * @param errMessage An error message.
  */
  explicit incomplete_settings(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

/**
* @brief The player's identifier doesn't meet requirements.
*/
class invalid_identifier: public std::runtime_error {
 public:
  /**
  * @param errMessage An error message.
  */
  explicit invalid_identifier(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

/**
* @brief The size of the object is incorrect.
*/
class invalid_size: public std::runtime_error {
 public:
  /**
  * @param errMessage An error message.
  */
  explicit invalid_size(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};

/**
* @brief Square has the wrong value for its location.
*/
class invalid_square: public std::runtime_error {
 public:
  /**
  * @param errMessage An error message.
  */
  explicit invalid_square(const char* errMessage) :
    std::runtime_error(errMessage) {
  }
};
#endif // EXCEPTIONS_H_INCLUDED
