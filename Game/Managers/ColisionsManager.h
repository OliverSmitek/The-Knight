//
// Created by Oliver Šmítek on 10.07.2026.
//

#ifndef COLISIONSMANAGER_H
#define COLISIONSMANAGER_H
#include "../CustomClasses/HitBox.h"
#include "../Tools/HitBoxDefinition/HitBoxDefinitionAttacking.h"
#include "../Tools/HitBoxDefinition/HitBoxDefinitionResevingAndColision.h"


class ColisionsManager {
  public:

  static ColisionsManager& getInstance(){
    static ColisionsManager theInstance;
    return theInstance;
  }

  std::unordered_map<std::string, HitBoxDefinitionAttacking> HitBoxDefinitionAttackingUndM;
  std::unordered_map<std::string, HitBoxDefinitionResevingAndColision> HitBoxDefinitionResevingUndM;

  void registerAttackingHitBoxType(const std::string& typeName, HitBoxDefinitionAttacking def);
  void registerResevingHitBoxType(const std::string& typeName, HitBoxDefinitionResevingAndColision def);

  void spawnAttackingHitBox(const std::string &typeName, Entity *owner);
  void spawnResevingHitBox(const std::string &typeName, Entity *owner);

  std::vector<HitBox*> uMOfHitBoxs;
  std::vector<HitBox*> uMOfHitBoxsToKill;

  int perryMultiplayer = 2;

  ColisionsManager();

  void chackForHitBoxesColisions(HitBox *atcHitBox, HitBox *reshitBox);

  void drawHitBoxes(sf::RenderWindow *window);

  void insetHitBoxTouMOfHitBoxs(HitBox *insertHitBox);
  void chackGlobalHitBoxColisions();
  void updateTransformationForHitBoxes();

  void disableHitBoxsOutOfLifeTime();

  void killAllHitBoxesSetToDie();
  void changeHitBoxScale(sf::Vector2f newScale, Entity *owner, HitBox *hitBoxToChange);


  void updateAndChackForHitBoxes(sf::RenderWindow *window);

  void getRidOfHitBoxsOfOwner(Entity *owner);
  void intaraptAttack(Entity *owner);

  void preperHitBoxForKill(HitBox *owner);

  void killAllResevingHitBoxIsOfOwner(Entity *owner);

  void ColidebleHitBoxesColided(ResevingHitBox *first, ResevingHitBox *secondColided);

  void ChackForPhysicColisions();
};



#endif //COLISIONSMANAGER_H
