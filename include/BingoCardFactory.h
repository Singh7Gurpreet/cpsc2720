/**
 * @author L. Nicole Wilson [n.wilson@uleth.ca]
 * @date 2023-09, 2023-12
 */
#ifndef BINGO_CARD_FACTORY_H_INCLUDED
#define BINGO_CARD_FACTORY_H_INCLUDED

#include <vector>

#include "BingoCard.h"
#include "BingoTypes.h"
#include "VictoryCondition.h"

/**
 * @class BingoCardFactory BingoCardFactory.h "BingoCardFactory.h"
 * @brief Creates random BingoCards.
 */
class BingoCardFactory {
 public:
  /**
   * @brief Default constructor.
   */
  BingoCardFactory();

  /**
   * @brief Destructor.
   */
  virtual ~BingoCardFactory();

  /**
   * @brief Create a BingoCard, uses copyVictoryCondition.
   * @param [in] game The gameType desired.
   * @param [in] victory A pointer to a victory condition.
   * @return A pointer to a BingoCard for the given game type with the given
   *   victory condition.
   * @throw incomplete_settings If victory is a nullptr
   * @throw invalid_size If game isn't a valid gameType.
   */
  BingoCard* makeBingoCard(BingoTypes::gameType game,
                           VictoryCondition* victory);

 private:
  /**
   * @brief Make n distinct squares with values in a [min, max].
   * @param [in] max The maximum value for a Square.
   * @param [in] min The minimum value for a Square.
   * @param [in] n the number of Squares desired, default value is 5.
   * @return A vector of Square pointers with n distinct values.
   * @throw invalid_size if can't make n distinct values in the desired range.
   */
  std::vector<Square*> makeSquares(unsigned min, unsigned max, unsigned n = 5);

  /**
   * @brief Copy a VictoryCondition.
   * @param [in] victory A victory condition pointer.
   * @return A victory condition pointer.
   */
  VictoryCondition* copyVictoryCondition(VictoryCondition* victory);
};

#endif // BINGO_CARD_FACTORY_H_INCLUDED
