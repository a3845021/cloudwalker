//
//  PetItem.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/13/16.
//
//

#include "PetItem.h"


PetItem* PetItem::createItem(int id) {
    auto item = new PetItem();
    if (item && item->init(id)) {
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    return item;
}

bool PetItem::init(int id) {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Sprite::init());
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void PetItem::onEnter() {
    Sprite::onEnter();
}

void PetItem::onExit() {
    Sprite::onExit();
}