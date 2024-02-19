/**
 * @author L. Nicole Wilson [n.wilson@uleth.ca]
 * @date 2023-10
 */
#ifndef BINGOGAME_H_INCLUDED
#define BINGOGAME_H_INCLUDED

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "BingoCaller.h"
#include "BingoCard.h"
#include "VictoryCondition.h"

/**
 * @class BingoGame BingoGame.h "BingoGame.h"
 * @brief Implements the bingo card for a game of bingo.
 */
class BingoGame {
 public:
  /**
   * @brief Default constructor.
   * @details Sets _caller to nullptr.
   */
  BingoGame();

  /**
   * @brief Destructor, deallocates memory allocated to caller and bingo cards.
   */
  virtual ~BingoGame();

  /**
   * @brief Access the game type.
   * @return The game type.
   * @throw incomplete_settings If the caller hasn't been set.
   */
  BingoTypes::gameType getGameType();

  /**
   * @brief Access the victory type.
   * @return The victory type.
   * @throw incomplete_settings If the caller hasn't been set.
   */
  BingoTypes::victoryType getVictoryType();

  /**
   * @brief Access the number of players.
   * @return The number of players.
   */
  unsigned getNumPlayers();

  /**
   * @brief Set the bingo caller.
   * @param [in] caller A pointer to a bingo caller.
   * @throw bad_input if the caller is a nullptr.
   */
  void setCaller(BingoCaller* caller);

  /**
   * @brief Change the victory type.
   * @param [in] victory - a victory type
   * @throw incomplete_settings If the caller hasn't been set.
   * @throw function_unavailable If a game has started by not ended.
   */
  void resetVictoryType(BingoTypes::victoryType victory);

  /**
   * @brief If there are any winners or there are no more players then
   *   the game ends, otherwise another ball is pulled and announced.
   * @param [inout] out Insert prompts and information in this ostream.
   * @throw incomplete_settings If the caller hasn't been set.
   * @throw invalid_size If there are no players before the first turn.
   */
  void completeNextCall(std::ostream& out);

  /**
   * @brief Complete a daub square user action.
   * @details This method will be patched in the 2024 release.<ul>
   *   <li>For the 2024 release use the following crunch time fix.<br>
   *   Use a switch to choose the appropriate moveType.</li>
   *   <li>2025 release include in the patch:<br>
   *   Create an abstract MoveAction class with appropriate
   *   subclasses for each of the moveTypes.<br>
   *   Remove the ___Move functions from this class.<br>
   *   Change the move parameter from moveType to MoveAction*.</li></ul>
   * @param [inout] out Insert prompts and information in this ostream.
   * @param [inout] in Extract data from this istream.
   * @param [in] id The id of the player requesting this action.
   * @param [in] move a pointer to a move function the moveType to be completed.
   * @throw incomplete_settings If the caller hasn't been set.
   * @throw invalid_size If there are no players.
   * @throw invalid_identifier If the id isn't in _player
   */
  void takeAction(std::ostream& out, std::istream& in,
                  std::string id, BingoTypes::moveType move);

  /**
   * @brief Complete a daub square user action.
   * @param [inout] out Insert prompts and information in this ostream.
   * @param [inout] in Extract data from this istream.
   * @param [in] id The id of the player requesting this action.
   */
  void daubMove(std::ostream& out, std::istream& in, std::string id);

  /**
   * @brief Complete a say bingo user action.
   * @param [inout] out Insert prompts and information in this ostream.
   * @param [inout] in Extract data from this istream.
   * @param [in] id The id of the player requesting this action.
   */
  void bingoMove(std::ostream& out, std::istream& in, std::string id);

  /**
   * @brief Complete a request for card display user action.
   * @param [inout] out Insert prompts and information in this ostream.
   * @param [inout] in Extract data from this istream.
   * @param [in] id The id of the player requesting this action.
   */
  void showCardMove(std::ostream& out, std::istream& in, std::string id);

  /**
   * @brief Complete a request card checked for validity user action.
   * @param [inout] out Insert prompts and information in this ostream.
   * @param [inout] in Extract data from this istream.
   * @param [in] id The id of the player requesting this action.
   */
  void checkCardMove(std::ostream& out, std::istream& in, std::string id);

  /**
   * @brief Complete a request for game and victory type for this game.
   * @param [inout] out Insert prompts and information in this ostream.
   * @param [inout] in Extract data from this istream.
   * @param [in] id The id of the player requesting this action.
   */
  void showGameMove(std::ostream& out, std::istream& in, std::string id);

  /**
   * @brief Complete a request to see all the pulled balls user action.
   * @param [inout] out Insert prompts and information in this ostream.
   * @param [inout] in Extract data from this istream.
   * @param [in] id The id of the player requesting this action.
   */
  void showBoardMove(std::ostream& out, std::istream& in, std::string id);

  /**
   * @brief Complete a request to see the help data user action.
   * @param [inout] out Insert prompts and information in this ostream.
   * @param [inout] in Extract data from this istream.
   * @param [in] id The id of the player requesting this action.
   */
  void helpMove(std::ostream& out, std::istream& in, std::string id);

  /**
   * @brief Complete a player has quit action.
   * @param [inout] out Insert prompts and information in this ostream.
   * @param [inout] in Extract data from this istream.
   * @param [in] id The id of the player requesting this action.
   */
  void quitGameMove(std::ostream& out, std::istream& in, std::string id);

  /**
   * @brief Add a player to the caller's current game.
   * @details The identifier must be distinct in the player list, and the id
   *   must not be blank. The bingo card must be the correct type for the
   *   bingo caller's current game.
   * @param [in] id An identifier for the player.
   * @param [in] card A pointer to a bingo card.
   * @return true if the player is added, false otherwise
   * @throw invalid_identifier if the id is blank.
   * @throw card_to_game_mismatch if the card isn't for this game.
   */
  bool joinGame(std::string id, BingoCard* card);

  /**
   * @brief Remove the entry for this id from the players.
   * @details The memory allocated for the player's bingo card is deallocated.
   * @param [in] id The id of the player leaving.
   * @return true if the player is found and removed, false otherwise.
   */
  bool leaveGame(std::string id);

  /**
   * @brief Makes an appropriate end of game announcement.
   * @details The game ends if there are no players or there are one or
   *   more players that called bingo and have met the victory conditions.
   * @param [inout] out Insert prompts and information in this ostream.
   * @throw incomplete_settings If the caller hasn't been set
   */
  void endGame(std::ostream& out);

  /**
   * @brief Reset the bingo caller, and clear the player list.
   * @throw incomplete_settings If the caller hasn't been set
   */
  void resetGame();

 private:
  BingoCaller* _caller;
  std::map<std::string, BingoCard*> _player;
  std::vector<std::string> _winners;
};
#endif // BINGOGAME_H_INCLUDED
