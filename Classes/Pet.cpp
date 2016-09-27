//
//  Pet.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/11/16.
//
//

#include "Pet.h"
#include "GameManager.h"
#include "Define.h"

Pet* Pet::createPet(int kind) {
    auto pet = new Pet();
    if (pet && pet->init(kind)) {
        pet->autorelease();
        return pet;
    }
    CC_SAFE_DELETE(pet);
    return nullptr;
}

bool Pet::init(int kind) {
  GameManager::getInstance()->initPets();
    // kind kind kind
    ValueMap pet = GameManager::getInstance()->getPetById(kind);
  
    Sprite::initWithSpriteFrameName(pet.at("img").asString());
    
    Vector<cocos2d::SpriteFrame *> arrayOfSpriteFrameNames(pet.at("frames").asInt());
    for (int i =1; i<= pet.at("frames").asInt(); i++) {
        //arrayOfSpriteFrameNames.pushBack(SpriteFrame::create(__String::createWithFormat("res/pets/%s_%d.png",pet.at("alias").asString().c_str(),i)->getCString(), Rect(0,0,pet.at("width").asInt(),pet.at("height").asInt())));
//        SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("res/pets/%s_%d.png",pet.at("alias").asString().c_str(),i)->getCString());
        arrayOfSpriteFrameNames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("%s_%d.png",pet.at("alias").asString().c_str(),i)->getCString()));
    }
    
    _fly = Animation::createWithSpriteFrames(arrayOfSpriteFrameNames,0.3);
    _fly->setLoops(999999);
    _fly->setRestoreOriginalFrame(true);
    _fly->retain();
    auto animate = Animate::create(_fly);
    
    this->runAction(animate);
    _kind = kind;
    
    schedule(schedule_selector(Pet::processAI), 1.0f);
       return true;
}

Pet::Pet() {
    
}

Pet::~Pet() {
    
}

void Pet::doFly() {
    
}

void Pet::doSave() {
 
}

void Pet::doFindCoin() {
    
}
void Pet::doCreateCloud() {
    
}

// bay ngau nhien ko co chuc nang gi
// cuu nguoi khi rot
// tu dong kiem tien
// tu dong hut' tien
// tu dong nhan 2 tien
// hold the cloud
void Pet::processAI(float dt) {
    auto tar = _hero->getPosition();
//    Change Y by N * SIN(A)
//    Change X by N * COS(A)
    if (this->getActionByTag(123)!= nullptr && !this->getActionByTag(123)->isDone()) {
        return;
    }
       int agel = random(0, 360);
    auto moveTo = MoveTo::create(random(1, 10), Vec2(tar.x+100*sin(agel),tar.y + 100*cos(agel)));
    moveTo->setTag(123);
    if(random(1, 100)> 90)
    Talk(tankdata[random(0, 68)]);
    this->runAction(moveTo);
}

void Pet::Talk(std::string text) {
    if(this->getChildByTag(321))
    this->removeChildByTag(321);
    auto label = Label::createWithTTF(text, "fonts/arial.ttf", 24);
    label->setTag(321);
    label->setAnchorPoint(Vec2(0.5,0.5));
    label->setPosition(Vec2( this->getContentSize().width/2,this->getContentSize().height));
    auto fadeOut = FadeOut::create(6.0f);
    addChild(label);
    label->runAction(Sequence::create(fadeOut,RemoveSelf::create(), NULL));
}