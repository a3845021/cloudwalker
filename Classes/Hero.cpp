//
//  Hero.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#include "Hero.h"
#include "GameManager.h"

Hero::~Hero() {
    
}

Hero* Hero::createHero(int id) {
    auto hero = new Hero();
    if (hero && hero->init(id)) {
        hero->autorelease();
        return hero;
    }
    CC_SAFE_DELETE(hero);
    return nullptr;
}

bool Hero::init(int id) {
    bool bRet = false;
    do {
      ValueMap hero =  GameManager::getInstance()->getHeroById(id);
     
        alias =hero.at("alias").asString().c_str();
        CC_BREAK_IF(!Sprite::initWithSpriteFrameName(__String::createWithFormat("%s%d.png",alias.c_str(),1)->getCString()));
        
        
        bRet = true;
    }while(0);
    return bRet;
}

void Hero::jump() {
    this->setSpriteFrame(__String::createWithFormat("%s%d.png",alias.c_str(),2)->getCString());
}
void Hero::stand() {
     this->setSpriteFrame(__String::createWithFormat("%s%d.png",alias.c_str(),1)->getCString());
}