//
// Created by Oliver Šmítek on 25.11.2025.
//

#include "Player.h"

#include "../../GameManager.h"
#include "../../Managers/ColisionsManager.h"
#include "../../UIdirectory/UI/PlayerUIHP.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Window/Keyboard.hpp"



Player::Player(sf::Vector2f position, sf::Vector2f velocity) : Entity(position, velocity, std::string("Player")){
    float x = 2.2f;
    float y = 2.2f;

    absortionPosition = position;
    trueScale = sf::Vector2f(x, y);
    //Docasne:{

    absortionFeeld = sf::CircleShape(absortionFeeldRadius);


    shadow.setTexture(TextureManager::getInstance().textures["shedowOfEntity"]);

    //docasne}

    scale = sf::Vector2f(x, y);
    facingDirection = "right";

    ColisionsManager::getInstance().spawnResevingHitBox("KnightResevingHitBox",this);


}

void Player::update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {
    entityFallManagment(environmenAndPhysicsManager);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        absorbSoul();
    }

    if (!freeze) {
        cooldowns_and_unIntraptebulActions();
        input();
        transformationSprite(currentTexture);
    }
    if (!freeze) {
        beingHitFunc();
        dashIsActive();
    }

    if (!freeze) {
        movmentUpdate();
    }
    hitBoxUpdateposition();
    shadowUpdate();
    transformShapes();

    colisionDetectionEntityExtention(name);

}

void Player::absorbSoul() {

}

void Player::transformShapes() {
    SpriteManager::getInstance().transformCircle(&absortionFeeld);
    absortionFeeld.setPosition(position.x,position.y);
}
void Player::hitBoxUpdateposition() {

}

void Player::cooldowns_and_unIntraptebulActions() {
    //cooldawns:

    //attack Cooldawn:
    if (attackCooldown.getElapsedTime().asMilliseconds() >= intervalBetweenAttacks) {
        coolDownIsOff = true;
    }
    if (slideCooldown.getElapsedTime().asMilliseconds() > intervalToSlide) {
        lastVelocityY = 0;
    }

    if (dashIsActiveClockCooldown.getElapsedTime().asSeconds() >= dashCuldownSecund) {
        if (dashNumOfUse < 2) {
            dashNumOfUse++;
            dashIsActiveClockCooldown.restart();
        }
    }
    if (dashNumOfUse >= 2) {
        dashIsActiveClockCooldown.restart();
    }

    //attack finish animacion
    if (uninterruptableAnimation) {
        if (spriteManager->getInstance().getIndexOfAnimation(&sprite) >= spriteManager->getInstance().
            getMaxIndexOfAnimation(&sprite) - 120) {
            uninterruptableAnimation = false;

            coolDownIsOff = false;
            passivActionStandStill();
            attackCooldown.restart();
            if (soulAbsortionIsInProcess) {
                GameManager::getInstance().setTimeToDefule();
                soulAbsortionIsInProcess = false;
                imunToTimeChange = false;
            }
        }
    }

    if (uninterruptableAnimLowPriority) {
        if (spriteManager->getInstance().getIndexOfAnimation(&sprite) >= spriteManager->getInstance().
            getMaxIndexOfAnimation(&sprite) - 120) {
            uninterruptableAnimLowPriority = false;
            }
    }


    if (velocity.x == 0) {
        slideIsActive = false;
    } else {
        slideIsActive = true;
    }
}

void Player::input() {
    if(gotHit) return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        passivActionStandStill();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && slideIsActive) {
        actionSlide();
    } else if (isSliding) {
            endSlide();
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && dashNumOfUse > 0) {
        actionDash();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        actionGroundSlam();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        actionWalkLeft();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        actionWalkRight();
    } else {
        passivActionStandStill();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        actionAttack();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
        actionJump();
    } else if (cancelJump) {
        if (velocity.y <= -10) {
            velocity.y = -10;
        }
        cancelJump = false;
    }
    passivActionStuck();
}

void Player::endSlide() {
    setTexture("SlideTransitionEndKnight");
    isSliding = false;
    uninterruptableAnimLowPriority = true;
    ColisionsManager::getInstance().spawnResevingHitBox("KnightResevingHitBox",this);
};

void Player::entityFallManagment(EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {
    if (!dashIsActiveBool) {
        impactBound();
        if (position.y + velocity.y + 1 < EnvironmenAndPhysicsManager::getInstance().floor) {
            isInAir = true;
        } else {
            setEntityOnFloor();
            if (velocity.y != 0) {
                lastVelocityY = velocity.y;
                slideCooldown.restart();
            }
            isFalling = false;
        }
        if (isCollidingWithPlatform) {
            velocity.y -= EnvironmenAndPhysicsManager::getInstance().gravityPower;
            if (velocity.y != 0) {
                lastVelocityY = velocity.y;
                slideCooldown.restart();
            }
            isInAir = false;
            isFalling = false;
            velocity.y = 0;
        }

        if (isInAir) {
            if (!isCollidingWithPlatform) {
                if (!gotHit) {
                    passivActionBetwenFalling();
                }
            } 
        }
    }
    gravityAndGround(environmenAndPhysicsManager);

}

//Action:
void Player::actionWalkRight() {
    if(uninterruptableAnimation) return;

    if (!isInAir) {
        if (!uninterruptableAnimLowPriority) {
            setTexture("runKnight");
        }
        facingDirection = "right";
        if (velocity.x > 7) {
            velocity.x = velocity.x - 0.8;
        } else {
            velocity.x = 7;
        }
    } else {
        facingDirection = "right";
        if (velocity.x <= 6) {
            velocity.x++;
        }
    }
}

void Player::actionWalkLeft() {
    if(uninterruptableAnimation) return;

    if (!isInAir) {
        setTexture("runKnight");
        facingDirection = "left";
        if (velocity.x < -7) {
            velocity.x = velocity.x + 0.8;
        } else {
            velocity.x = -7;
        }

    } else {
        facingDirection = "left";
        if (velocity.x >= -6) {
            velocity.x--;
        }
    }
}

void Player::actionAttack() {
    if(uninterruptableAnimation) return;

    if (coolDownIsOff) {
        uninterruptableAnimation = true;
        setTexture("attackKnight");
        if (!isInAir) {
            velocity.x = 0;
        }
        ColisionsManager::getInstance().spawnAttackingHitBox("KnightAttackHitBoxFirstVariant",this);
        SecondAttackActive = true;


    } else if (SecondAttackActive) {
        uninterruptableAnimation = true;
        setTexture("SaccendAttackKnight");
        SecondAttackActive = false;

        if (!isInAir) {
            velocity.x = 0;
        }
        ColisionsManager::getInstance().spawnAttackingHitBox("KnightResevingHitBoxSecendVariant",this);

    }
}


void Player::actionJump() {
    if(isInAir) return;

    if (isSliding) {
        endSlide();
    }

    velocity.y = -22;
    if (!uninterruptableAnimLowPriority) {
        setTexture("JumpKnight");
    }
    cancelJump = true;
    uninterruptableAnimLowPriority = true;
}


void Player::actionSlide() {
    if(uninterruptableAnimation || isInAir) return;

    if (isSliding) {
        if (!uninterruptableAnimLowPriority) {
            setTexture("SlideKnight");
        }
    }

    if (!isSliding) {
        if (!uninterruptableAnimLowPriority) {
            setTexture("SlideTransitionStartKnight");
            isSliding = true;
            uninterruptableAnimLowPriority = true;
            ColisionsManager::getInstance().spawnResevingHitBox("KnightResevingHitBoxSlide",this);
        }
    }

    if (velocity.x < 0.3 && velocity.x > -0.3) {

        if (isSliding) {
            if (!uninterruptableAnimLowPriority) {
                endSlide();
            }
        }
        if (!uninterruptableAnimLowPriority) {
            setTexture("idleKnight");

        }
        lastVelocityY = 0;
        velocity.x = 0;
    }

    if (facingDirection == "right") {
        velocity.x = velocity.x + lastVelocityY / 2.5;
    } else {
        velocity.x = velocity.x - lastVelocityY / 2.5;
    }
    lastVelocityY = 0;

    velocity.x = velocity.x / 1.02;
}

void Player::actionDash() {
    if(dashIsActiveBool) return;

    if (facingDirection == "right") {
        if (isInAir) {
            velocity.x = Dashspeed;
        }
        else {
            velocity.x = Dashspeed * 1.2;
        }
    }
    else if (facingDirection == "left") {
        if (isInAir) {
            velocity.x = - Dashspeed ;
        }
        else {
            velocity.x = - (Dashspeed * 1.2);
        }
    }
    dashIsActiveBool = true;
    dashIsActiveClock.restart();
    dashNumOfUse--;
}

void Player::actionGroundSlam() {
    if (isInAir) {
        if (!uninterruptableAnimation) {
            velocity.y = 30;
            setTexture("SlamKnight");
            transformHitBoxAttack2();

        }
    }
}


void Player::dashIsActive() {
    if(!dashIsActiveBool) return;

    if (dashIsActiveClock.getElapsedTime().asMilliseconds() <= 130){
        velocity.y = 0;

        setTexture("dashKnight");
        uninterruptableAnimation = true;
    }
    else {
        dashIsActiveBool =false;
    }
}

void Player::passivActionGetHit(std::string fecingDirection, int damage) {
    if(freeze || gotHit) return;

    ColisionsManager::getInstance().intaraptAttack(this);

    uninterruptableAnimation = false;
    setTexture("HitKnight");
    if (fecingDirection == "right") {
        velocity.x = 11;
    } else if (fecingDirection == "left") {
        velocity.x = -11;
    }
    beingHit.restart();
    gotHit = true;


    hp = hp - damage;

    if (hp <= 0) {
        passivActionDie();
    }
}

void Player::passivActionDie() {
}

void Player::beingHitFunc() {
    if(!gotHit) return;

    if (beingHit.getElapsedTime().asMilliseconds() <= beingHitPlayerIntervalKnight) {
        velocity.x = velocity.x / 1.1;
    } else {
        velocity.x = 0;
        gotHit = false;
    }
}


//passiv Actions:
void Player::passivActionStandStill() {
    if(uninterruptableAnimLowPriority || isInAir || uninterruptableAnimation || dashIsActiveBool) return;
    setTexture("idleKnight");
    velocity.x = 0;
}

void Player::passivActionBetwenFalling() {
    if(uninterruptableAnimation) return;
    if (!uninterruptableAnimLowPriority && !isFalling) {
        setTexture("JumpFallInbetweenKnight");
        uninterruptableAnimLowPriority = true;
    }
    else {
        isFalling = true;
        passivActionFalling();
    }

}

void Player::passivActionFalling() {
    if(uninterruptableAnimation || uninterruptableAnimLowPriority) return;
    setTexture("FallKnight");
}

void Player::movmentUpdate() {
    const float time = GameManager::getInstance().time;

    position += velocity * time;
    collisionBoxPosition += velocity * time;
    absortionPosition += velocity * time;
}





void Player::drawHitbox(sf::RenderWindow &window) {

}

void Player::drawAdditions(sf::RenderWindow &window) {

    playerUIHP->getInstance().updateHPbar(hp, window);
    playerUIStamina->getInstance().updateStaminabar(dashNumOfUse, dashIsActiveClockCooldown, window);
    SpriteManager::getInstance().speedBlurer(&sprite, window, 4, facingDirection, velocity.x,dashIsActiveBool );

    SpriteManager::getInstance().drawSprite(&shadow, shadowPosition.x, shadowPosition.y, window);
}

void Player::drawColisionHitBox(sf::RenderWindow &window) {
    SpriteManager::getInstance().drawSprite(&collisionHitBox, collisionBoxPosition.x,  collisionBoxPosition.y, window);
}

void Player::shadowUpdate() {
    if (facingDirection == "right") {
        shadowPosition.x = position.x - 12;
    }
    else if (facingDirection == "left") {
        shadowPosition.x = position.x + 12;
    }
    shadowPosition.y = EnvironmenAndPhysicsManager::getInstance().floor + 5;

    EntityManager::getInstance().shadowColisionDetection(shadowPosition,name, position);

    float heightOfShadow = EnvironmenAndPhysicsManager::getInstance().floor - position.y;

    float heightOfShadowNumY = 0.038;
    float heightOfShadowNumX = 0.18;
    if (heightOfShadow > 0) {
        heightOfShadowNumY = 0.038 - heightOfShadow / 25000 ;
        heightOfShadowNumX = 0.18 - heightOfShadow / 10000;
    }

    shadowScale = {heightOfShadowNumX, heightOfShadowNumY};
    SpriteManager::getInstance().shadowTransform(&shadow,shadowScale);

    shadow.setPosition(shadowPosition);
}