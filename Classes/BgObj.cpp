//
//  BgObj.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#include "BgObj.h"

BgObj::~BgObj() {
    
}
bool BgObj::init(int kind) {
    
    
    if (kind == 1) {
        Sprite::initWithSpriteFrameName(__String::createWithFormat("cloud%d.png",random(1, 7))->getCString());
        this->setScale(random(0.1f, 0.5f));
        this->setOpacity(random(1, 75));
        this->setPosition(Vec2(640+Sprite::getContentSize().width/2,random(200,960)));
        this->runAction(Sequence::createWithTwoActions(MoveTo::create(random(20, 60), Vec2(-Sprite::getContentSize().width/2,random(200, 960))), RemoveSelf::create()));
    } else if (kind == 2 ) {
        Sprite::initWithSpriteFrameName(__String::createWithFormat("ufo%d.png",random(1, 6))->getCString());
        this->setScale(random(0.1f, 0.5f));
        this->setOpacity(random(1, 75));
        this->setPosition(Vec2(640+Sprite::getContentSize().width/2,random(200,960)));
        
        this->runAction(RepeatForever::create(Sequence::createWithTwoActions(SkewBy::create(1.0f, 10, 0),SkewBy::create(1.0f, -10, 0))));
        this->runAction(Sequence::createWithTwoActions(MoveTo::create(random(20, 60), Vec2(-Sprite::getContentSize().width/2,random(200, 960))), RemoveSelf::create()));
    } else if (kind == 3) { // fire ball
        Sprite::initWithSpriteFrameName(__String::createWithFormat("fireball%d.png",random(1, 2))->getCString());
        this->setScale(random(0.1f, 0.5f));
        this->setOpacity(random(50, 80));
        this->setPosition(Vec2(random(1, 640),960 + this->getContentSize().height/2));
        this->runAction(Sequence::createWithTwoActions(MoveTo::create(random(10, 20), Vec2(random(1, 640),-this->getContentSize().height/2)), RemoveSelf::create()));
    } else if (kind ==4) {
        
    } else if (kind ==5) {
        
    }
        

    
    return true;
}
BgObj* BgObj::createObj(int id) {
    auto obj = new BgObj();
    if (obj && obj->init(id)) {
        obj->autorelease();
        return obj;
    }
    CC_SAFE_DELETE(obj);
    return nullptr;
}
