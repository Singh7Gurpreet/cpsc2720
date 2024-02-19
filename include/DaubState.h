/**
* @author L. Nicole  Wilson [n.wilson@uleth.ca]
* @date 2023-09
*/
#ifndef DAUB_STATE_H_INCLUDED
#define DAUB_STATE_H_INCLUDED

/**
* @class DaubState DaubState.h "DaubState.h"
* @brief Interface for the possible outcomes of daubing a square.
*/
class DaubState {
 public:
  /**
  * @brief Default constructor.
  */
  DaubState();

  /**
  * @brief Destructor.
  */
  virtual ~DaubState();

  /**
  * @brief Used to determine whether the square has been daubed.
  * @return true, if it has been daubed, false otherwise.
  */
  virtual bool isDaubed() = 0;

  /**
  * @brief Used to determine whether the square is correctly marked.
  * @return true, if it is correct, false otherwise.
  */
  virtual bool isCorrect() = 0;
};

/**
* @class NoDaub DaubState.h "DaubState.h"
* @brief State of a square that correctly has not been daubed.
*/
class NoDaub : public DaubState {
 public:
  /**
  * @brief Default constructor.
  */
  NoDaub();

  /**
  * @brief Destructor.
  */
  virtual ~NoDaub();

  /**
   * @brief In this state the square has not been daubed.
   * @return false.
   */
  bool isDaubed();

  /**
   * @brief In this state the square is marked correctly.
   * @return true.
   */
  bool isCorrect();
};

/**
* @class GoodDaub DaubState.h "DaubState.h"
* @brief State of a square that correctly has been daubed.
*/
class GoodDaub : public DaubState {
 public:
  /**
  * @brief Default constructor.
  */
  GoodDaub();

  /**
  * @brief Destructor.
  */
  virtual ~GoodDaub();

  /**
   * @brief In this state the square has been daubed.
   * @return true.
   */
  bool isDaubed();

  /**
   * @brief In this state the square is marked correctly.
   * @return true.
   */
  bool isCorrect();
};


/**
* @class BadDaub DaubState.h "DaubState.h"
* @brief State of a square that incorrectly has been daubed.
*/
class BadDaub : public DaubState {
 public:
  /**
  * @brief Default constructor.
  */
  BadDaub();

  /**
  * @brief Destructor.
  */
  virtual ~BadDaub();

  /**
   * @brief In this state the square has been daubed.
   * @return true.
   */
  bool isDaubed();

  /**
   * @brief In this state the square is marked incorrectly.
   * @return false.
   */
  bool isCorrect();
};

/**
* @class NeedsDaub DaubState.h "DaubState.h"
* @brief State of a square that has incorrectly not been daubed.
*/
class NeedsDaub : public DaubState {
 public:
  /**
  * @brief Default constructor.
  */
  NeedsDaub();

  /**
  * @brief Destructor.
  */
  virtual ~NeedsDaub();

  /**
   * @brief In this state the square has not been daubed.
   * @return false.
   */
  bool isDaubed();

  /**
   * @brief In this state the square is marked incorrectly.
   * @return false.
   */
  bool isCorrect();
};


#endif // DAUB_STATE_H_INCLUDED
