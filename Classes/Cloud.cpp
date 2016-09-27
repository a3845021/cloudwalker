//
//  Cloud.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#include "Cloud.h"

Cloud* Cloud::createCloud(int type,ActionInterval* act) {
    auto cloud = new Cloud();
    if (cloud && cloud->init(type, act)) {
        cloud->autorelease();
        return cloud;
    }
    CC_SAFE_DELETE(cloud);
    return nullptr;
}
bool Cloud::init(int type,ActionInterval* act) {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Sprite::initWithFile(__String::createWithFormat("res/cloud/cloud_%d.png",random(1, 3))->getCString()));
//        CC_BREAK_IF(!Sprite::initWithSpriteFrameName(__String::createWithFormat("cloud_%d.png",random(1, 3))->getCString()));
        if (act != nullptr) {
            this->runAction(act);
        }
        
        
//        PhysicsBody* body = PhysicsBody::createBox(Sprite::getContentSize());
//        body->setDynamic(false);
//        body->setContactTestBitmask(0xFFFFFFFF);
//        this->setPhysicsBody(body);
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

ActionInterval* Cloud::genMove(float speed) {
    // left -> right
    // up -> down
    // brezzier
    
    
    // width : 520  / 3
    // height : 960/5 + 200
   
    ActionInterval* act = nullptr;
    
    int kind = random(1, 6);
    switch (kind) {
        case 1: // left - right
        {
            int posY = random(200, 700);
            auto pos1 = Vec2(random(200, 300),posY);
            auto pos2 = Vec2(random(300, 600),posY);
            
            auto mv1 = MoveTo::create(pos2.getDistance(pos1)/speed, pos1);
            auto mv2 = MoveTo::create(pos1.getDistance(pos2)/speed, pos2);
            act = RepeatForever::create(Sequence::create(mv1,mv2, NULL));
            
        }
            break;
        case 2:
        {
            int posX = random(200, 600);
            auto pos1 = Vec2(posX,random(200, 400));
            auto pos2 = Vec2(posX,random(400, 700));
            
            auto mv1 = MoveTo::create(pos2.getDistance(pos1)/speed, pos1);
            auto mv2 = MoveTo::create(pos1.getDistance(pos2)/speed, pos2);
            act = RepeatForever::create(Sequence::create(mv1,mv2, NULL));
        }
            break;
        case 3 :
        {
            int posX = random(200, 600);
            auto pos1 = Vec2(posX,random(200, 400));
            auto pos2 = Vec2(posX,random(400, 700));
            auto pos3 = Vec2(random(200, 600),random(200,700));
            
            auto mv1 = MoveTo::create(pos3.getDistance(pos1)/speed, pos1);
            auto mv2 = MoveTo::create(pos1.getDistance(pos2)/speed, pos2);
            auto mv3 = MoveTo::create(pos2.getDistance(pos3)/speed, pos3);
            act = RepeatForever::create(Sequence::create(mv1,mv2,mv3, NULL));
        }
            break;
        case 4:
        {
            int posX = random(200, 600);
            int posX2 = random(200, 600);
            int posY = random(200, 700);
            int posY2 = random(200, 700);
            auto pos1 = Vec2(posX,posY);
            auto pos2 = Vec2(posX,posY2);
            auto pos3 = Vec2(posX2,posY2);
            auto pos4 = Vec2(posX2,posY);
            auto mv1 = MoveTo::create(pos4.getDistance(pos1)/speed, pos1);
            auto mv2 = MoveTo::create(pos1.getDistance(pos2)/speed, pos2);
            auto mv3 = MoveTo::create(pos2.getDistance(pos3)/speed, pos3);
            auto mv4 = MoveTo::create(pos3.getDistance(pos4)/speed, pos4);
            act = RepeatForever::create(Sequence::create(mv1,mv2,mv3,mv4, NULL));
        }
            break;
        case 5:{
            int posY = random(200, 600);
            auto pos1 = Vec2(random(200, 400),posY);
            auto pos2 = Vec2(random(400,600),posY);
            auto pos3 = Vec2(random(200, 600),random(200,700));
            
            auto mv1 = MoveTo::create(pos3.getDistance(pos1)/speed, pos1);
            auto mv2 = MoveTo::create(pos1.getDistance(pos2)/speed, pos2);
            auto mv3 = MoveTo::create(pos2.getDistance(pos3)/speed, pos3);
            act = RepeatForever::create(Sequence::create(mv1,mv2,mv3, NULL));
        }
            break;
        case 6: {
            ccBezierConfig config;
            config.controlPoint_1 = Point(random(200, 600),random(200, 700));
            config.controlPoint_2 = Point(random(200, 600),random(200, 700));
            config.endPosition = Point(random(200, 600),random(200, 700));
            act = RepeatForever::create(BezierTo::create(random(1, 5), config));
        }
        default:
            break;
    }
    return act;
    
}
void Cloud::onEnter() {
    Sprite::onEnter();
}

void Cloud::onExit() {
    Sprite::onExit();
}
