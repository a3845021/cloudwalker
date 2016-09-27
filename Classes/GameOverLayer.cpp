//
//  GameOverLayer.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/10/16.
//
//

#include "GameOverLayer.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "SdkUtil.h"
#include "GameManager.h"

bool GameOverLayer::init() {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());

        auto winSize =Director::getInstance()->getWinSize();
        this->setPosition(Vec2(-640,0));
        _bg = LayerColor::create(Color4B::BLACK);
        _bg->setAnchorPoint(Vec2::ZERO);
        _bg->setOpacity(30);
        addChild(_bg);
        
     
        _pad = Sprite::createWithSpriteFrameName("pad.png");
        _pad->setPosition(winSize.width/2,winSize.height/2);
        addChild(_pad);
        
        _title = Label::createWithTTF("GAME OVER !", "fonts/arial.ttf", 72);
        _title->setPosition(Vec2(winSize.width/2,_pad->getBoundingBox().getMaxY()+ _title->getContentSize().height/2));
        addChild(_title);
        
        _highScore = Label::createWithTTF("100", "fonts/arial.ttf", 60);
        _highScore->setColor(Color3B::BLACK);
        _highScore->setAnchorPoint(Vec2(0.5,0.5));
        _highScore->setPosition(_bg->getContentSize().width/2- _highScore->getContentSize().width, 50);
        _pad->addChild(_highScore);
        
        _score =Label::createWithTTF("200", "fonts/arial.ttf", 60);;
                _score->setAnchorPoint(Vec2(0.5,0.5));
        _score->setPosition(_bg->getContentSize().width/2- _score->getContentSize().width, 160);
        _score->setColor(Color3B::BLACK);
        _pad->addChild(_score);
        //_new = Sprite::create("res/game/new.png");
        
        _homebtn = Button::create("home.png","","",cocos2d::ui::Button::TextureResType::PLIST);
        _homebtn->setPosition(Vec2(_pad->getBoundingBox().getMinX()+_homebtn->getContentSize().width,_pad->getBoundingBox().getMinY() - _homebtn->getContentSize().height));
        _homebtn->addTouchEventListener([&](Ref* pSender,Widget::TouchEventType tt){
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
            this->removeFromParentAndCleanup(true);
            auto pTransScene = TransitionFade::create(0.2f, MenuScene::create());
            Director::getInstance()->replaceScene(pTransScene);
        });
        addChild(_homebtn);
        _ratebtn = Button::create("rank.png","","",cocos2d::ui::Button::TextureResType::PLIST);
        _ratebtn->setPosition(Vec2(_homebtn->getPositionX()+ _homebtn->getContentSize().width*1.2,_homebtn->getPositionY()));
        _ratebtn->addTouchEventListener([&](Ref* pSender,Widget::TouchEventType tt){
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
            log("open link to rate");
          //  Ads::signin();

            SdkUtil::getInstance()->submitScore("topscore",GameManager::getInstance()->getHighScore());
            SdkUtil::getInstance()->showLeaderboard("topscore");
            
        });
        addChild(_ratebtn);
        _sharebtn = Button::create("more2.png","","",cocos2d::ui::Button::TextureResType::PLIST);
        _sharebtn->setPosition(Vec2(_ratebtn->getPositionX()+ _ratebtn->getContentSize().width*1.2,_homebtn->getPositionY()));
        _sharebtn->addTouchEventListener([&](Ref* pSender,Widget::TouchEventType tt){
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
            log("open link to share");
            GameManager::getInstance()->moreGames();
        });
       // addChild(_sharebtn);
        _restartbtn = Button::create("restart.png","","",cocos2d::ui::Button::TextureResType::PLIST);
        _restartbtn->setPosition(Vec2(_ratebtn->getPositionX()+ _ratebtn->getContentSize().width*1.2,_homebtn->getPositionY()));
        _restartbtn->addTouchEventListener([&](Ref* pSender,Widget::TouchEventType tt){
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
            __NotificationCenter::getInstance()->postNotification("restartGame");
            this->flyOut();
//
//            auto pTransScene = TransitionFade::create(0.1f,GameScene::create());
//            Director::getInstance()->replaceScene(pTransScene);
            
        });
        addChild(_restartbtn);
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void GameOverLayer::onEnter() {
    Layer::onEnter();
    

}

void GameOverLayer::onExit() {
    Layer::onExit();
}
