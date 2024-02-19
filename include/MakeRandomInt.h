/**
 * @author L. Nicole  Wilson [n.wilson@uleth.ca]
 * @date 2022-12, 2023-10
 */
#ifndef MAKE_RANDOM_INT_H_INCLUDED
#define MAKE_RANDOM_INT_H_INCLUDED

#include <random>

/**
 * @class MakeRandomInt MakeRandomInt.h "MakeRandomInt.h"
 * @brief A class for generating a random int in the range [0, max).
 * @details This class uses the Singleton design pattern to prevent
 * the same list of "random values" from being created by multiple
 * objects within a project.
 */
class MakeRandomInt {
 public:
  /**
   * @brief Copy constructor, disabled.
   * @param rv a MakeRandomInt class object.
   */
  MakeRandomInt(const MakeRandomInt& rv) = delete;

  /**
   * @brief Assignment operator, disabled.
   * @param rv a MakeRandomInt class object.
   */
  void operator=(const MakeRandomInt& rv) = delete;

  /**
   * @brief Destructor
   */
  virtual ~MakeRandomInt();

  /**
   * @brief Method used to create or obtain the random value object
   * @return a reference to a random value maker.
   */
  static MakeRandomInt& getInstance();

  /**
   * @brief Get a random int in the range [0, max).
   * @param max the upper bound for the range of possible values.
   * @return an integer in the range [0, max).
   */
  int getValue(int max = 10);

 private:
//  static MakeRandomInt* _instance;
  unsigned _seed;
  std::default_random_engine _generator;
  std::uniform_int_distribution<int> _distribution;

  /**
   * @brief The default constructor called by getInstance.
   */
  MakeRandomInt();
};

#endif // MAKE_RANDOM_INT_H_INCLUDED
