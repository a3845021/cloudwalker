//
//  HelpLayer.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#include "HelpLayer.h"
#include <cocos-ext.h>
USING_NS_CC_EXT;

bool HelpLayer::init() {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        auto winSize = Director::getInstance()->getWinSize();
        auto spr = Sprite::create("res/help/helplayer.png");
        spr->setAnchorPoint(Vec2::ZERO);
        addChild(spr);
        
        auto okBtn = cocos2d::ui::Button::create("check.png","","",cocos2d::ui::Button::TextureResType::PLIST);
        okBtn->addTouchEventListener([&](Ref* pSender,cocos2d::ui::Widget::TouchEventType touchtype){
            if (touchtype != cocos2d::ui::Widget::TouchEventType::ENDED) {
                return;
            }
            this->removeFromParent();
        });
        okBtn->setPosition(Vec2(winSize.width*3/4,winSize.height/10));
        addChild(okBtn);
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void HelpLayer::onEnter() {
    Layer::onEnter();
}

void HelpLayer::onExit() {
    Layer::onExit();
}
