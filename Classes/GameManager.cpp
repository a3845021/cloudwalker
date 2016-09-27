//
//  GameManager.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/10/16.
//
//

#include "GameManager.h"
 GameManager* GameManager::_gInstance;
GameManager::~GameManager() {
    
}

bool GameManager::init() {
    setHighScore(UserDefault::getInstance()->getIntegerForKey("highscore", 0));
    setCoin(UserDefault::getInstance()->getIntegerForKey("coin", 0));
    setScore(0);
    return true;
}

void GameManager::setHighScore(int val) {
    UserDefault::getInstance()->setIntegerForKey("highscore", val);
    _highScore = val;
}
void  GameManager::setCoin(int val) {
    UserDefault::getInstance()->setIntegerForKey("coin", val);
    _coin = val;
}
int  GameManager::getCoin() {
    return _coin;
}

int GameManager::getHighScore() {
    return _highScore;
}

ValueVector& GameManager::getHeroes() {
    return _heroes;
}

ValueVector& GameManager::getWings() {
    return _wings;
}

ValueVector& GameManager::getPets() {
    return _pets;
}
ValueMap& GameManager::getPetById(int id) {
    
    for (int i=0; i<_pets.size(); i++) {
        if (_pets.at(i).asValueMap().at("id").asInt() == id) {
            return _pets.at(i).asValueMap();
        }
    }
    
}
ValueMap& GameManager::getHeroById(int id) {
    for (int i=0; i<_heroes.size(); i++) {
        if (_heroes.at(i).asValueMap().at("id").asInt() == id) {
            return _heroes.at(i).asValueMap();
        }
    }
}
void GameManager::initHeroes() {
    _heroes = FileUtils::getInstance()->getValueVectorFromFile("hero.plist");
 
}

void GameManager::initWings() {
      //  _wings = FileUtils::getInstance()->getValueVectorFromFile("wing.plist");
}

void GameManager::initPets() {
    _pets = FileUtils::getInstance()->getValueVectorFromFile("pet.plist");
}

void GameManager::moreGames() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Application::getInstance()->openURL("https://play.google.com/store/apps/developer?id=VuaMobi");
#else 
#if  (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        Application::getInstance()->openURL("https://itunes.apple.com/us/developer/pham-thanh/id1106485064");
#else
    Application::getInstance()->openURL("http://vuamobi.com");
#endif
#endif
    
    log("%d",CC_TARGET_PLATFORM);

}