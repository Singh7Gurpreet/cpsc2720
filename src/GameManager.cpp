


#include "GameManager.h"

#include <algorithm>  // for std::find
#include <cstdlib>    // for rand() and srand()
#include <ctime>
#include <iostream>

#include "Environment.h"
#include "FlamePartItem.h"
#include "Claws.h"
#include "Oxygen.h"
#include "Bandages.h"
#include "Inventory.h"
#include "Note.h"
#include "MainPlayer.h"
#include "Pipe.h"
#include "FlameItem.h"
#include "Opponent.h"


GameManager::GameManager(int countDownStart) {
  countDown = countDownStart;
  selfDistructStatus = true;
}

GameManager::~GameManager() {
  selfDestructorRoom = nullptr;
  for (int i = 0; i < map.size(); i++) {
       std::vector<Environment* > test = {};
       map[i]->setRoutes(test);
       delete map[i];
  }
  map.clear();
  for (int i = 0; i< characters.size(); i++) {
     characters[i]->setLocation(nullptr);
     delete characters[i];
  }
  characters.clear();
}

void GameManager::countDownUpdate() {
  // Check countdownStatus
  // If on, countdown
  //Check selfDestructRoom
  // If off, dont

  if (!selfDestructorRoom->getSolved() && (countDown != 0)) {
    countDown--;
  }

  if (!selfDestructorRoom->getSolved()) {
    disableCountDown();
    std::string msg = "Self Distruct Status: ";
    msg += std::to_string(countDown);
    msg += " Turns";
    std::cout << msg << std::endl;
  } else {  // disabled status
    std::cout << "Self Distruct Status: Disabled" << std::endl;
  }
}


void GameManager::startMsg() {
  std::string GameTitle = "Beyond Isolation: By Group Project E \n";
  std::cout << GameTitle << std::endl;

  std::string startMsg = "As the cryopod's fogged glass slowly cleared,\n"
"You could feel the chill of anticipation coursing through your veins.\n"
"With a hiss, the pod door swung open,\n"
"and you emerge into the dimly lit chamber,\n"
"muscles stiff and protesting.\n"
"The faint hum of the spaceship's systems greets you,\n"
"<WARNING: Alien lifeform detected, self destruct imminent>\n"
"loudly echoing off the metal walls.\n"
"Shadows danced in the corners,\n"
"whispering of the unknown that awaited beyond.\n"
"With a deep breath, you step forward,\n"
"ready to face the alien world that had \n"
"stirred from its slumber alongside you.\n"
"Build a flamethrower to defend yourself and kill the alien,\n"
"You need 5 parts, good luck";
  std::cout << startMsg << std::endl;
}

Item* GameManager::giveQuestItem(Player* user) {
  //Remove items
  std::vector<Item* > list = user->getBag().getItems();
  std::vector<Item* > toRemoves = {};
  for (int i = 0; i < list.size(); i++) {
    if (list[i]->getName() == "Flame Part") {
      toRemoves.push_back(list[i]);
    }
  }
  Inventory tempBag = user->getBag();
  for (int x = 0; x < toRemoves.size(); x++) {
    tempBag.rmItem(toRemoves[x]);
  }
  user->setBag(tempBag);
  return new FlameItem("FlameThrower", "This will do");
}

void GameManager::disableCountDown() { selfDistructStatus = true; }

void GameManager::warningMsg(std::istream& in) {
  // In your Room
  if (characters[1]->getHP() > 0) {
    if (characters[0]->getLocation() == characters[1]->getLocation()) {
      std::cout << "You see the alien rush you out of nowhere" << std::endl;
      std::cout << "Press Enter to Continue" << std::endl;
      in.get();
    }
    // Adjacent
    Environment* playerLocation = characters[0]->getLocation();
    std::vector<Environment*> adjacencies =
        characters[1]->getLocation()->getRoutes();

    auto it = std::find(adjacencies.begin(), adjacencies.end(), playerLocation);
    if (it != adjacencies.end()) {
      std::cout << "You hear noise down the hall labled: "
              << characters[1]->getLocation()->getName() << std::endl;
      std::cout << "Press Enter to Continue" << std::endl;
      std::cin.get();
    }
  }
}

void GameManager::createMap() {
  // Makes all the nodes, then adds the routes to them
  // 15 Total Rooms
  std::string StartingRoomDesc = "As you step down the\n"
" hallway you find yourself\n"
" familiar, the cryo room unfolds before you like\n"
" a realm frozen in time. Rows of gleaming pods, their surfaces\n"
" glistening with condensation,\n"
" some untouched, some with the pod clearly smashed into\n"
" by some unknown force. \n"
" Each pod stands as a silent guardian, promising respite\n"
" from the passage of time within its icy embrace. Within this\n"
" hushed sanctuary, the very air\n"
" seems suspended in anticipation, whispering\n"
" secrets of dreams yet to be realized.";

  std::string CrewQuarterDesc = " As you step further\n"
" the crew quarters unveil themselves\n"
" as a labyrinth of personal sanctuaries amidst\n"
" the cold steel corridors. Each room,\n"
" a glimpse into the lives of those who\n"
" called this outpost home, echoes with\n"
" whispers of memories and the lingering \n"
" warmth of departed souls. Within these\n"
" chambers, the solitude of space is softened\n"
" by the remnants of human presence,\n"
" offering a glimpse of the resilience and\n"
" camaraderie that once thrived here.";

  std::string MessHallDesc = " In the desolate \n"
"expanse of the remote station,\n"
"the mess hall stands as a haunting relic\n"
" of communal gatherings long past. Empty tables\n"
" and silent serving stations paint\n"
" a solemn picture of isolation, where the only company \n"
" is the lingering scent of forgotten meals.\n"
" Within these barren walls, echoes of laughter\n"
" and camaraderie resonate like ghosts\n"
" of a bygone era, serving as a haunting reminder of \n"
" the solitude that envelopes this forsaken outpost.";
  //Puzzle room - done
  std::string LockerRoomDesc = "As you enter the locker room, rows of\n"
"metallic compartments greet you,\n"
"each bearing the weight of countless stories. \n"
"Amidst the open lockers and\n"
"scattered belongings, one stands out: a\n"
"lone locker, firmly sealed shut with a 4 digit lock.\n"
"Its presence looms over the room, \n"
"a silent enigma amidst the otherwise\n"
"familiar surroundings, enticing curiosity\n"
"with its stubborn refusal to reveal\n"
"its secrets.";

  std::string BriefingRoomDesc = "Entering the \n"
"briefing room, you're met with\n"
"an atmosphere of solemn anticipation.\n"
"Rows of empty chairs face a large central \n"
"display screen, its surface dormant for\n"
"now. The air is charged with a sense of purpose,\n"
"as if the very walls themselves\n"
"yearn to impart vital information. In this room of \n"
"quiet anticipation, the weight\n"
"of impending decisions hangs heavy, each seat a \n"
"silent testament to the lives and\n"
"fates that will soon be discussed.";

//Hazard room - done
  std::string RoboticsLabDesc ="Entering the core of the station, you\n"
"find yourself in the robotics lab, a\n"
"sanctum of mechanical marvels amidst the cold\n"
"expanse. Rows of sleek machines\n"
"line the room, their metallic forms humming with latent potential. However,\n"
"your attention is drawn to the pooling water seeping from a cracked pipe, \n"
"creating a hazardous mix with exposed wires. The air is charged with the\n"
"promise of innovation, yet tinged with a subtle sense of danger, urging\n"
"caution as you navigate through this treacherous workshop.";

//Robot npc present
  std::string ObservDeckDesc = "Stepping into one of the wider wings of\n"
"the station, you arrive at the observation deck,\n"
"a panoramic vista suspended amidst the stars. Floor-to-ceiling windows\n"
"reveal the vast cosmos stretching out before you, a breathtaking tapestry\n"
"of celestial wonders. The air is tinged with the hushed reverence of\n"
"astronomical contemplation, inviting reflection upon the mysteries of\n"
"the universe unfolding beyond the glass.There's one of the robot janitors\n"
"that appears to be struggling to fix something nearbye.";

  std::string EngineDesc = "Descending into the depths of the station,\n"
"you arrive at the engine room,\n"
"the pulsating heart of this cosmic vessel. Massive turbines and intricate\n"
"machinery dominate the space, their rhythmic hum resonating through the\n"
"metallic corridors. The air crackles with static energy, infused with the\n"
"promise of power and propulsion. Here, amidst the controlled chaos of\n"
"mechanical marvels, the very essence of the ship's existence is forged.";

  //Puzzle room
  std::string DestructDesc = "Stepping into the core of the station,\n"
"you find yourself in the heart of\n"
"desperation — the self-destruct room. Stark panels line the walls, their\n"
"glowing displays casting an eerie hue over the chamber. The air crackles\n"
"with tension as warnings blare, echoing off cold metal surfaces. With every\n"
"pulse of the countdown, the gravity of the\n"
"situation becomes painfully clear.\n"
"Theres a large touchscreen\n"
"requesting a 4 digit passcode to disable\n"
"this with a sticky note near it that reads\n"
"<Updated the disable code to the year the ship was made for those wondering>";

  std::string ReactorDesc = "As you step into the reactor room, a symphony\n"
"of energy unfolds before you.\n"
"Glowing conduits snake along the walls, pulsating with raw power. The hum\n"
"of the reactor core reverberates through the chamber, casting an ethereal\n"
"light that dances across the metallic surfaces. In the center of it all, the\n"
"core radiates with a mesmerizing glow, its energy harnessed to propel the\n"
"station through the void.";

  std::string SecurityDesc = "Entering the security room, a sense of\n"
"abandonment permeates the air.\n"
"Dusty monitors flicker sporadically, casting eerie shadows across the\n"
"bare walls. A single chair sits overturned in the corner, a silent\n"
"reminder of the room's neglected state. Among the remnants of outdated\n"
"technology, the faint echo of past vigilance lingers, now engulfed in\n"
"the solitude of disuse.";

//npc room
  std::string InfirmaryDesc = "As you cautiously enter the infirmary,\n"
"the air is heavy with the scent of\n"
"aged antiseptic and lingering despair. Tattered curtains sway gently in the\n"
"stale breeze, revealing shattered equipment and bloodstained walls. The\n"
"once-white tiles beneath your feet bear the marks of a violent struggle,\n"
"testament to the horrors that unfolded within these forsaken walls long ago.\n"
"Though time has passed, the echoes of suffering linger, haunting the silent\n"
"halls of this grim hint of whats to come.You see an injured man that appears\n"
"to be poorly hiding in the corner.";

  std::string ScienceDesc = "Entering the science lab, you're greeted\n"
"by an array of gleaming equipment\n"
"and intricate instruments, each whispering of discoveries yet to be made.\n"
"Soft light filters through the windows, casting a tranquil glow over the\n"
"meticulously organized workstations. Papers and notebooks lie scattered,\n"
"filled with scribbled calculations and hypotheses. In this haven of\n"
"curiosity and exploration, the pursuit of knowledge is palpable, inviting\n"
"you to unravel the mysteries of the universe.";

//Hazard Room - Done
// NOLINTNEXTLINE(runtime/string)
std::string BotanicalDesc = "Stepping into the botanical gardens,\n"
"you're enveloped by an eerie stillness\n"
"amidst the cold metal of the station. Lush foliage casts long, twisting\n"
"shadows that seem to dance in the dim light. The air hangs heavy with a\n"
"palpable tension, as if the very plants themselves are watching, waiting.\n"
"In this seemingly tranquil sanctuary, a sense of foreboding whispers of\n"
"unseen dangers lurking just beyond the vibrant facade.";

  std::string UnmarkedDesc = "Venturing into the depths of the unknown,\n"
"the environment morphs into a surreal\n"
"landscape of twisted, organic forms.\n"
"Sinister tendrils weave through the space,\n"
"eliciting an uneasy curiosity.\n"
"The air grows heavy with an ominous aura, each\n"
"step deeper revealing the chilling realization of stumbling into something\n"
"beyond comprehension. It becomes increasingly apparent:\n"
"this is no mere cavern,\n"
"but a nest of some alien horror.";

  //Add NPC's
  std::string robotMsg = "Hey there, I'm TechSweep 2000.\n"
  "I've got a proposition\n"
  "for you. I need a solid pipe for some repairs. How about trading it for\n"
  "a whatever I have on hand?";
  NPC* JanitorRobot = new NPC("TechSweep 2000", "Pipe", robotMsg);
  FlamePartItem* npcItem = new FlamePartItem("Flame Part", "Not much here");
  JanitorRobot->addItem(npcItem);
  std::string woundedManMsg = "Hey, I'm in bad shape here.\n"
  "Desperately need\n"
  "some bandages, can barely move. Willing to make a deal—I'll give you my\n"
  "locker combo in exchange for some medical help.\n"
  "Its in a wing near cryo...please.";
  NPC* WoundedMan = new NPC("James", "Bandages", woundedManMsg);
  //trades a bandage for a locker hint
  WoundedMan->setHint("My locker code is 2122, now get out of here.");


  // Starting Rooms
  GeneralRoom* StartingRoom1 = new GeneralRoom("Cryo Room", StartingRoomDesc);
  // 1
  GeneralRoom* miscRoom2 = new GeneralRoom("Crew Quarters", CrewQuarterDesc);
  GeneralRoom* pendingRoom3 = new GeneralRoom("Mess Hall", MessHallDesc);
  PuzzleRoom* LockerRoom4 = new PuzzleRoom("Locker Room", LockerRoomDesc);
  GeneralRoom* miscRoom5 = new GeneralRoom("Briefing Room", BriefingRoomDesc);
  HazardRoom* hazRoom6 = new HazardRoom("Robotics Lab", RoboticsLabDesc);
  NpcRoom* pending7 = new NpcRoom("Observation Deck", ObservDeckDesc);
  GeneralRoom* miscRoom8 = new GeneralRoom("Engine Room", EngineDesc);
  PuzzleRoom* SelfDestructRoom9 =
      new PuzzleRoom("SelfDestruct Control Room", DestructDesc);  // 9
  PuzzleRoom* pendinPuzzle10 = new PuzzleRoom("Reactor Core", ReactorDesc);
  GeneralRoom* miscRoom11 = new GeneralRoom("Security Room", SecurityDesc);
  NpcRoom* pending12 = new NpcRoom("Infirmary", InfirmaryDesc);
  GeneralRoom* miscRoom13 = new GeneralRoom("Science Lab", ScienceDesc);
  HazardRoom* hazRoom14 = new HazardRoom("Botanical Garden", BotanicalDesc);
  GeneralRoom* EnemyStartingRoom15 =
       new GeneralRoom("UnMarked Hallway", UnmarkedDesc);  // 15
  // General rooms with not much. swappable
  //add npcs
  pending7->setNPC(JanitorRobot);
  pending12->setNPC(WoundedMan);
  // Create Routes acording to map design
  // Routes for each of 15 rooms

  std::vector<Environment*> toAddRoutes = {miscRoom2, pendingRoom3};
  StartingRoom1->setRoutes(toAddRoutes);
  toAddRoutes = {StartingRoom1, LockerRoom4, miscRoom5};
  miscRoom2->setRoutes(toAddRoutes);
  toAddRoutes = {StartingRoom1, miscRoom5, miscRoom8};
  pendingRoom3->setRoutes(toAddRoutes);
  toAddRoutes = {miscRoom2};
  LockerRoom4->setRoutes(toAddRoutes);
  toAddRoutes = {miscRoom2, pendingRoom3, hazRoom6};
  miscRoom5->setRoutes(toAddRoutes);
  toAddRoutes = {miscRoom5, pending7, miscRoom11};
  hazRoom6->setRoutes(toAddRoutes);
  toAddRoutes = {hazRoom6, miscRoom8};
  pending7->setRoutes(toAddRoutes);
  toAddRoutes = {pendingRoom3, pending7, SelfDestructRoom9, pendinPuzzle10};
  miscRoom8->setRoutes(toAddRoutes);
  toAddRoutes = {miscRoom8, pendinPuzzle10};
  SelfDestructRoom9->setRoutes(toAddRoutes);
  toAddRoutes = {miscRoom8, SelfDestructRoom9};
  pendinPuzzle10->setRoutes(toAddRoutes);
  toAddRoutes = {hazRoom6, pending12, miscRoom13};
  miscRoom11->setRoutes(toAddRoutes);
  toAddRoutes = {miscRoom11, EnemyStartingRoom15};
  pending12->setRoutes(toAddRoutes);
  toAddRoutes = {miscRoom11, hazRoom14};
  miscRoom13->setRoutes(toAddRoutes);
  toAddRoutes = {miscRoom13, EnemyStartingRoom15};
  hazRoom14->setRoutes(toAddRoutes);
  toAddRoutes = {hazRoom14, pending12};
  EnemyStartingRoom15->setRoutes(toAddRoutes);

  // Add rand Items to players + flamer parts
  srand(static_cast<unsigned int>(time(nullptr)));
  //one for how many items, one for what kind
  StartingRoom1->setInventory(createRoomItems(false, std::rand() % 3));
  miscRoom2->setInventory(createRoomItems(false, std::rand() % 3));
  pendingRoom3->setInventory(createRoomItems(true, std::rand() % 3));
  LockerRoom4->setInventory(createRoomItems(false, std::rand() % 3));
  miscRoom5->setInventory(createRoomItems(false, std::rand() % 3));
  hazRoom6->setInventory(createRoomItems(false, std::rand() % 3));
  pending7->setInventory(createRoomItems(false, std::rand() % 3));
  miscRoom8->setInventory(createRoomItems(false, std::rand() % 3));
  SelfDestructRoom9->setInventory(createRoomItems(false, std::rand() % 3));
  pendinPuzzle10->setInventory(createRoomItems(false, std::rand() % 3));
  miscRoom11->setInventory(createRoomItems(false, std::rand() % 3));
  pending12->setInventory(createRoomItems(false, std::rand() % 3));
  miscRoom13->setInventory(createRoomItems(true, std::rand() % 3));
  hazRoom14->setInventory(createRoomItems(false, std::rand() % 3));
  EnemyStartingRoom15->setInventory(createRoomItems(true, std::rand() % 3));

  //Mandatory items
  //Notes
  std::string noteMsg = "In the not-so-distant future,\n"
  "humanity took its first daring steps\n"
  "beyond the confines of Earth in the not so distant year 1979.\n"
  "Amidst the backdrop of interstellar exploration,\n"
  "the iconic spaceship Nostromo emerged—a beacon\n"
  "of human ingenuity and ambition. ";
  Note* destructCodeNote = new Note("Ripped Page", noteMsg);
  miscRoom8->addItem(destructCodeNote);



  //Add configure puzzles
  std::string selfdestructPrompt = "As you approach the self-destruct\n"
"control panel, a sense of urgency grips your\n"
"heart. The metallic console looms before you, adorned with a digital keypad,\n"
"its surface bearing the weight of imminent decisions. Each button glows with\n"
"a faint luminescence, beckoning for input. With every passing moment, the\n"
"ominous countdown intensifies, driving home the gravity of your mission.\n"
"Your hand trembles slightly as you prepare\n"
"to input the crucial 4-digit code,\n"
"knowing that the fate of the entire station hangs in the balance.";
  SelfDestructRoom9->setPuzzle(selfdestructPrompt);
  SelfDestructRoom9->setAnswer("1979");
  SelfDestructRoom9->setRewardMsg("The Alarms fade as you see,\n"
  "Self destruct disabled on the screen");

  std::string lockerRoomPrompt = "You approach the locked locker,\n"
  "clearly mangled from someone or something trying\n"
  "to get in prior. A simple 4 digit code is needed";
  LockerRoom4->setPuzzle(lockerRoomPrompt);
  LockerRoom4->setAnswer("2122");
  LockerRoom4->setRewardMsg("The lock pops open, as the locker\n"
  "creaks open reveealing whats inside");
  FlamePartItem* roomRew = new FlamePartItem("Flame Part", "Not much here");
  LockerRoom4->setReward(roomRew);

  //add configure hazards
  hazRoom6->setHazardDmg(40);
  hazRoom6->setHazardDesc("You try to salvage some\n"
  "scraps, but unfortunatly you slip\n"
  "and your arm dips slightly into the water,\n"
  "electrocuting you slightly as you pull away");

  hazRoom14->setHazardDmg(30);
  hazRoom14->setHazardDesc("As you start sifting through flora,\n"
  "you bump into what looks like a harmless plant\n"
  "But your arm shoots into immediate pain, after \n"
  "getting out of the flora it seems to calm down");

  // Push All to vector
  map.push_back(StartingRoom1);
  map.push_back(miscRoom2);
  map.push_back(pendingRoom3);
  map.push_back(LockerRoom4);
  map.push_back(miscRoom5);
  map.push_back(hazRoom6);
  map.push_back(pending7);
  map.push_back(miscRoom8);
  map.push_back(SelfDestructRoom9);
  map.push_back(pendinPuzzle10);
  map.push_back(miscRoom11);
  map.push_back(pending12);
  map.push_back(miscRoom13);
  map.push_back(hazRoom14);
  map.push_back(EnemyStartingRoom15);
  selfDestructorRoom = SelfDestructRoom9;
}
Player* GameManager::getUser() { return characters[0]; }
Player* GameManager::getAlien() { return characters[1]; }

void GameManager::createCharacters() {
  // Creates needed Characters with needed items
  MainPlayer* User = new MainPlayer("Ripley", map[0]);
  characters.push_back(User);
  Opponent* Alien = new Opponent("XenoMorph", map[14]);
  Alien->addItem(new Claws("Claws", "They are claws"));
  characters.push_back(Alien);
}

// Is called by a room by room basis
Inventory* GameManager::createRoomItems(bool fPresent, int toAdd) {
  //Items to be random, pipe,bandages,oxy,
  Inventory* toAddItems = new Inventory();

  if (fPresent) {
    std::string name = "Flame Part";
    std::string desc =
        "This is only a piece of what I need to beat the monster";
    FlamePartItem* flameItemPlaceHolder = new FlamePartItem(name, desc);
    toAddItems->addItem(flameItemPlaceHolder);  // needs to be fire part
  }
  for (int i = 0; i < toAdd; i++) {
    switch (std::rand() % 5) {
    case 0: { //Pipe
      Pipe* newPipe = new Pipe("Pipe", "is loud");
      toAddItems->addItem(newPipe);
      break;
    }
    case 1: { // Bandages
      Bandages* newBandage = new Bandages("Bandages", "patch you up");
      toAddItems->addItem(newBandage);
      break;
    }
    case 2: { // Oxygen
      Oxygen* newTank = new Oxygen("Oxygen Tank", "Looks full enough");
      toAddItems->addItem(newTank);
      break;
    }
    }
  }
  // Items that are allowed to be found
  // int randomIndex = rand() % SP.size();
  return toAddItems;
}

bool GameManager::winLossCheck() {
  // If bug is defeated
  // Oxygen out
  // Hp = 0
  // selfDestructGoes off

  if (characters[0]->getHP() <= 0) {
    //cout how died here
    std::cout << "Died of wounds" << std::endl;
    std::cout << "GAME OVER" << std::endl;
    return true;
  }
  if (characters[0]->getOxygen() <= 0) {
    std::cout << "Ran out of oxygen" << std::endl;
    std::cout << "GAME OVER" << std::endl;
    return true;
  }
  if (countDown == 0) {
    std::cout << "Self Destruct Activated" << std::endl;
    std::cout << "GAME OVER" << std::endl;
    return true;
  }
  if ((characters[1]->getHP() <= 0) && selfDestructorRoom->getSolved()) {
    std::cout << "The alien lies dead and the ship is saved" << std::endl;
    std::cout << "You won" << std::endl;
    return true;
  }
  return false;
}

void GameManager::gameSetup() {
  createMap();
  createCharacters();
}
