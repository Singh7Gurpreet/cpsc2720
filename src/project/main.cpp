// Minimal source file that allows the pipeline to pass.

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "GameManager.h"
#include "MainPlayer.h"

int main() {
  GameManager* GM = new GameManager();
  GM->gameSetup();
  Player* User = GM->getUser();
  Player* Alien = GM->getAlien();
  // Opening Msg
  GM->startMsg();
  // GameLoop start
  while (true) {
    if (Alien->getLocation() == User->getLocation()) {
      Alien->useItem(std::cin, User);
    }
    Alien->move(std::cin);
    //Alien attack if needed
    if (Alien->getLocation() == User->getLocation()) {
      Alien->useItem(std::cin, User);
    }
    if (GM->winLossCheck()) {
      break;
    }
    // Breaker
    std::cout << "Press Enter to Continue" << std::endl;
    std::cin.ignore(1000, '\n');
    // Warning Runs here for precense
    GM->warningMsg();
    // PLAYER TURN
    User->actionSelect(std::cin, Alien);
    //Endstep
    GM->countDownUpdate();
    User->reduceOxygen();
    if (User->getBag().questCheck()) {
      //Completed 5 pieces, update bag
      User->addItem(GM->giveQuestItem(User));
    }
    if (GM->winLossCheck()) {
      break;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return 0;
}
