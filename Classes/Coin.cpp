//
//  Coin.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/11/16.
//
//

#include "Coin.h"

bool Coin::init() {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Sprite::initWithFile("res/coin.png"));
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void Coin::onEnter() {
    Sprite::onEnter();
}

void Coin::onExit() {
    Sprite::onExit();
}

void Coin::flyUp() {
    auto mv = MoveTo::create(2.0f, Vec2(50,960-this->getContentSize().height));
    auto callback = CallFuncN::create([&](Node* pSender){

        this->setVisible(false);
                __NotificationCenter::getInstance()->postNotification("addCoin");
    });
    auto seq = Sequence::create(mv,callback, NULL)  ;
    this->runAction(seq);
}