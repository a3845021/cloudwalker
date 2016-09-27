//
//  HeroItem.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/11/16.
//
//

#include "HeroItem.h"

HeroItem* HeroItem::createItem(int id) {
    auto item = new HeroItem();
    if (item && item->init(id)) {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    return item;
}

bool HeroItem::init(int id) {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Sprite::init());
        
        _id = id;
       
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void HeroItem::addListener() {
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();
        log("clicked me");
        if(rect.containsPoint(p))
        {
            
            return true; // to indicate that we have consumed it.
        }
        
        return false; // we did not consume this event, pass thru.
    };
    
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);

}

void HeroItem::onEnter() {
    Sprite::onEnter();
}

void HeroItem::onExit() {
    Sprite::onExit();
}
