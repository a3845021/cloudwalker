//
//  WingItem.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/11/16.
//
//

#include "WingItem.h"

WingItem* WingItem::createItem(int id) {
    auto item = new WingItem();
    if (item && item->init(id)) {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    return item;
}

bool WingItem::init(int id) {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Sprite::init());
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void WingItem::onEnter() {
    Sprite::onEnter();
}

void WingItem::onExit() {
    Sprite::onExit();
}

void WingItem::updateView() {
    if (!_show) {
        auto spr = Sprite::create("res/shop/wingslot.png");
        spr->setAnchorPoint(Vec2::ZERO);
        addChild(spr);
    }
}