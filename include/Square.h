/**
* @author L. Nicole  Wilson [n.wilson@uleth.ca]
* @date 2023-09
*/
#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED

#include <string>

#include "DaubState.h"

/**
* @class Square Square.h "Square.h"
* @brief Abstract superclass for bingo card squares.
*/
class Square {
 public:
  /**
  * @brief Default constructor, initializes _daubed to NoDaub.
  * @param [in] value the numeric value of the square.
  */
  Square(unsigned value = 0);

  /**
  * @brief Destructor, deallocates _daubed.
  */
  virtual ~Square();

  /**
  * @brief Returns the numeric value of the square.
  * @return The unsigned numeric value of the square.
  */
  unsigned getValue();

  /**
  * @brief Gives access to this square's _daubed.
  * @return A pointer to this square's _daubed.
  */
  DaubState* getDaubState();

  /**
  * @brief May reset _daubed based on the square type, numberCalled and _value.
  * @param [in] numberCalled The number called by the BingoCaller.
  * @return true, if previously isDaubed was false and now it is true.
  */
  virtual bool daubSquare(unsigned numberCalled) = 0;

  /**
  * @brief May reset _daubed based on the square type, numberCalled and _value.
  * @param [in] numberCalled The number called by the BingoCaller.
  */
  virtual void shouldDaubSquare(unsigned numberCalled) = 0;

  /**
  * @brief Reset _daubed to initial state.
  */
  virtual void resetSquare() = 0;

  /**
  * @brief Creates a string representation of the Square's value and state.
  * @return Returns a string representation of the Square's value and state.
  */
  virtual std::string toString() = 0;

 protected:
  unsigned _value;
  DaubState* _daubed;
};

/**
* @class FreeSquare Square.h "Square.h"
* @brief Implements the free square of a bingo card.
*/
class FreeSquare : public Square {
 public:
  /**
  * @brief Default constructor, initializes _value to 0, _daubed to GoodDaub.
  */
  FreeSquare(unsigned value = 0);

  /**
  * @brief Destructor, doesn't deallocate _daubed because Square does that.
  */
  virtual ~FreeSquare();

  /**
  * @brief Doesn't change _daubed, because _doubed is always a GoodDaub pointer.
  * @param [in] numberCalled The number called by the BingoCaller.
  * @return true, always
  */
  bool daubSquare(unsigned numberCalled);

  /**
  * @brief Doesn't change _daubed, because _doubed is always a GoodDaub pointer.
  * @param [in] numberCalled The number called by the BingoCaller.
  */
  void shouldDaubSquare(unsigned numberCalled);

  /**
  * @brief Doesn't change _daubed, because _daubed is always a GoodDaub pointer.
  */
  void resetSquare();

  /**
  * @brief Returns the string "free"
  * @return Returns the string "free"
  */
  std::string toString();
};

/**
* @class IntSquare Square.h "Square.h"
* @brief Implements one square of a bingo game.
*/
class IntSquare : public Square {
 public:
  /**
  * @brief Default constructor, initializes _daubed to NoDaub.
  * @param [in] value the numeric value of the square.
  */
  IntSquare(unsigned value = 0);

  /**
  * @brief Destructor, doesn't deallocate _daubed because Square does that.
  */
  virtual ~IntSquare();

  /**
  * @brief Sets _daubed based on the numberCalled and _value.
  * @details If numberCalled is the same as _value then _daubed is set to GoodDaub.
  *   However, if they do not match, then _daubed is set to BadDaub.
  * @param [in] numberCalled The number called by the BingoCaller.
  * @return true, if the square was not previously daubed, false otherwise.
  */
  bool daubSquare(unsigned numberCalled);

  /**
  * @brief Sets _daubed appropriately based on the numberCalled and _value.
  * @details If numberCalled is the same as _value and this square
  *   is not currently daubed then _daubed is set to NeedsDaub.
  *   Otherwise, _daubed is not changed.
  * @param [in] numberCalled The number called by the BingoCaller.
  */
  void shouldDaubSquare(unsigned numberCalled);

  /**
  * @brief Deletes the previous _daubed, then sets _daubed to NoDaub.
  */
  void resetSquare();

  /**
   * @brief Creates a string representation of the square for output.
   * @details Numbers are always return in two digits, if this square is daubed,
   *   then the number is enclosed in braces.
  * @return Returns a string representation of the Square's value for output.
  */
  std::string toString();
};

#endif // SQUARE_H_INCLUDED
