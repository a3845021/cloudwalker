//
//  MenuLayer.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#include "MenuLayer.h"
#include "HelpLayer.h"
#include "SoundUtil.h"
#include "ShopLayer.h"
#include "GameScene.h"
#include "GameManager.h"

#define TAG_PLAY 1
#define TAG_SOUND 2
#define TAG_HELP 3
#define TAG_SHOP 4
#define TAG_SHARE 5
bool MenuLayer::init() {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        //background.png // normal
        //charico.png // left center
        //helpbtn.png  // left right
        //shopbtn.png  // right left
        //soundbtn.png  // left right
        //title.png   - top fall
        
        auto winSize = Director::getInstance()->getWinSize();
        // init position
        _background = Sprite::createWithSpriteFrameName("background.png"); // normal
        _background->setAnchorPoint(Vec2::ZERO);
        addChild(_background);
//        _title = Sprite::createWithSpriteFrameName("title.png"); // top fall
//        _title->setPosition(Vec2(winSize.width/2,winSize.height));
//        addChild(_title);
        _title = Label::createWithTTF("Clouds\nJumper", "fonts/AlphaClouds.ttf", 113);
        _title->setPosition(Vec2(winSize.width/2,winSize.height));
        addChild(_title);
        

        _playbtn = Button::create("play.png","","",TextureResType::PLIST); // left to right
        _playbtn->setPosition(Vec2(- _playbtn->getContentSize().width/2,winSize.height/2));
        _playbtn->setTag(TAG_PLAY);
        addChild(_playbtn);
        _playbtn->addTouchEventListener(CC_CALLBACK_2(MenuLayer::TouchEventCallback, this));
        
        
        
//        _charicon = Sprite::createWithSpriteFrameName("charico.png");
//        _charicon->setPosition(Vec2(winSize.width/2,_playbtn->getPositionY()- _playbtn->getContentSize().height));
//        addChild(_charicon);
//        
//        
//        _cloud = Sprite::createWithSpriteFrameName("playbtn.png");
//        _cloud->setPosition(Vec2(winSize.width/2,_charicon->getPositionY()- _charicon->getContentSize().height/2 -_cloud->getContentSize().height/2 ));
//        addChild(_cloud);
        
        _sun = Sprite::createWithSpriteFrameName("sun_1.png"); // normal
        _sun->setPosition(Vec2(500,650));
        _sun->setScale(0.5f);
        addChild(_sun);
        auto face =Sprite::createWithSpriteFrameName(__String::createWithFormat("face_%d.png",random(1, 58))->getCString());
        face->setPosition(Vec2(_sun->getContentSize().width/2,_sun->getContentSize().height/2));
        face->setTag(1);
        _sun->addChild(face);

        
        _helpbtn = Button::create("ask.png","","",TextureResType::PLIST); // left
        _helpbtn->setPosition(Vec2(winSize.width/4,winSize.height/4));
        _helpbtn->setTag(TAG_HELP);
        addChild(_helpbtn);
        _helpbtn->addTouchEventListener(CC_CALLBACK_2(MenuLayer::TouchEventCallback, this));
        
        _soundbtn = Button::create("sound_on.png","sound_off.png","",TextureResType::PLIST); // left
   
        _soundbtn->setPosition(Vec2(winSize.width/2,winSize.height/4));
        _soundbtn->setTag(TAG_SOUND);
        addChild(_soundbtn);
        _soundbtn->addTouchEventListener(CC_CALLBACK_2(MenuLayer::TouchEventCallback, this));
        
        
        _shopbtn = Button::create("wing.png","","",TextureResType::PLIST); // right
        _shopbtn->setTag(TAG_SHOP);
        _shopbtn->addTouchEventListener(CC_CALLBACK_2(MenuLayer::TouchEventCallback, this));
        _shopbtn->setPosition(Vec2(winSize.width*3/4,winSize.height/4));
        addChild(_shopbtn);
        
        
        _sharebtn = Button::create("more.png","","",TextureResType::PLIST); // right
        _sharebtn->setPosition(Vec2(winSize.width + _sharebtn->getContentSize().width/2,_shopbtn->getPositionY() - _sharebtn->getContentSize().height*1.5));
        _sharebtn->setTag(TAG_SHARE);
      //  addChild(_sharebtn);
       // _sharebtn->addTouchEventListener(CC_CALLBACK_2(MenuLayer::TouchEventCallback, this));
        
        _title_ani = MoveBy::create(0.5f, Vec2(0,-_title->getContentSize().height/2-50));
        _title_ani->retain();
        _playbtn_ani = MoveBy::create(0.5f, Vec2(winSize.width/2+_playbtn->getContentSize().width/2,0));
        _playbtn_ani->retain();
        _helpbtn_ani = MoveBy::create(0.5f, Vec2(winSize.width/8+_helpbtn->getContentSize().width/2,0));
        _helpbtn_ani->retain();
        _soundbtn_ani = MoveBy::create(0.5f, Vec2(winSize.width/8+_soundbtn->getContentSize().width/2,0));
        _soundbtn->retain();
        _shopbtn_ani = MoveBy::create(0.5f, Vec2(-(winSize.width/8+_shopbtn->getContentSize().width/2),0));
        _shopbtn_ani->retain();
        _sharebtn_ani = MoveBy::create(0.5f, Vec2(-(winSize.width/8+_sharebtn->getContentSize().width/2),0));
        _sharebtn_ani->retain();
        
        
        // end position

        
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void MenuLayer::onEnter() {
    Layer::onEnter();
    updateUi();
    _title->runAction(_title_ani);
//    _helpbtn->runAction(_helpbtn_ani);
//    _soundbtn->runAction(_soundbtn_ani);
//    _shopbtn->runAction(_shopbtn_ani);
//    _sharebtn->runAction(_sharebtn_ani);
    _playbtn->runAction(Sequence::create(EaseExponentialOut::create(_playbtn_ani),CallFunc::create([&](){
    //    NotificationCenter::getInstance()->postNotification(CMD_GAME_LOAD_FINISH);
        log("load finish");
    }),NULL));
    
}

void MenuLayer::onExit() {
    Layer::onExit();
}

void MenuLayer::updateUi() {
    // update sound
    bool bSound = UserDefault::getInstance()->getBoolForKey("sound",true);
    SoundUtil::getInstance()->setIsBackGroundSound(bSound);
    SoundUtil::getInstance()->setIsEffectSound(bSound);
    if(bSound)
        _soundbtn->setBrightStyle(cocos2d::ui::Widget::BrightStyle::NORMAL);
    else {
        _soundbtn->setBrightStyle(cocos2d::ui::Widget::BrightStyle::HIGHLIGHT);
    }
}

void MenuLayer::TouchEventCallback(Ref *pSender, Widget::TouchEventType type)
{
    if (type != Widget::TouchEventType::ENDED)
        return;
    Button * btn = (Button*)pSender;
    switch (btn->getTag()) {
        case TAG_PLAY:
        {
                        log("enter game scene");
            auto pTransScene = TransitionFade::create(0.2f,GameScene::create());
            Director::getInstance()->replaceScene(pTransScene);

        }
            break;
        case TAG_SHOP:
        {
            auto winSize = Director::getInstance()->getWinSize();
            auto shop = ShopLayer::create();
            shop->setPosition(Vec2(winSize.width/2,winSize.height/2));
            addChild(shop);
        }
            break;
        case TAG_HELP:
        {
            auto helpLayer = HelpLayer::create();
            helpLayer->setAnchorPoint(Vec2::ZERO);
            addChild(helpLayer);
        }
            break;

        case TAG_SOUND:
        {
            
            bool bSound = UserDefault::getInstance()->getBoolForKey("sound",true);
            UserDefault::getInstance()->setBoolForKey("sound",!bSound);
            bSound = !bSound;
            SoundUtil::getInstance()->setIsBackGroundSound(bSound);
            SoundUtil::getInstance()->setIsEffectSound(bSound);
            if(bSound)
                _soundbtn->setBrightStyle(cocos2d::ui::Widget::BrightStyle::NORMAL);
            else {
                 _soundbtn->setBrightStyle(cocos2d::ui::Widget::BrightStyle::HIGHLIGHT);
            }
        }
            break;
        case TAG_SHARE:
        {
            GameManager::getInstance()->moreGames();
        }
            break;
        default:
            break;
    }
}