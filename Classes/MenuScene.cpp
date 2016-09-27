//
//  MenuScene.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#include "MenuScene.h"
#include "MenuLayer.h"
#include "GameManager.h"

MenuScene::~MenuScene() {
    CC_SAFE_RELEASE(_pMenuSceneLayer);
}


bool MenuScene::init() {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Scene::init());
        

        _resourceCount = 0;
        _pResource = new std::vector<std::string>;
        preloadSources();
        
        auto  m_keyBoardListener = EventListenerKeyboard::create();
        m_keyBoardListener->retain();
        m_keyBoardListener->onKeyReleased = CC_CALLBACK_2(MenuScene::onKeyReleased,this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(m_keyBoardListener,this);
        
        bRet = true;
        
    }
    while (0);
    
    return bRet;
}

void MenuScene::onEnter() {
    Scene::onEnter();
    
}
void MenuScene::onKeyReleased(EventKeyboard::KeyCode code, Event *event)
{
    if (code == EventKeyboard::KeyCode::KEY_BACK)
    {
        
        if (_exit)
        {
            Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
#endif
        }
        else
        {
            // œ‘ æÃ· æ
            _exit = true;
            showTips("Back to exit",1.0f);
        }
    }
}
void MenuScene::showTips(std::string tip, float sec) {
    auto winSize= Director::getInstance()->getWinSize();
    auto tips = Label::createWithTTF(tip, "fonts/arial.ttf", 32);
    tips->setPosition(winSize.width/2,winSize.height*0.1f);
    this->addChild(tips,999);
    
    auto moveBy = MoveBy::create(0.5f,Vec2(0,100));
    
    auto ease = EaseBackOut::create(moveBy);
    auto fadeIn = FadeIn::create(0.5f);
    auto spawn = Spawn::createWithTwoActions(fadeIn,ease);
    
    auto callfunc = CallFunc::create([=](){
        auto fadeout = FadeOut::create(0.5f);
        tips->runAction(Sequence::create(fadeout,RemoveSelf::create(),NULL));
        _exit = false;
    });
    
    tips->runAction(Sequence::create(spawn,DelayTime::create(1.0f),callfunc,NULL));
}
void MenuScene::preloadSources() {
    _pResource->push_back("game");
    _pResource->push_back("res/facespr");
    _pResource->push_back("res/herospr");
    _pResource->push_back("res/petspr");
    _pResource->push_back("res/objspr");
    _pResource->push_back("res/shopspr");
    for(auto &iterSourceName : *_pResource)
        Director::getInstance()->getTextureCache()->addImageAsync(iterSourceName + ".png", [&](Texture2D *pTexture)
        {
            log("load %s",(iterSourceName + ".png").c_str());
          ++this->_resourceCount;
          SpriteFrameCache::getInstance()->addSpriteFramesWithFile(iterSourceName + ".plist" , pTexture);
            GameManager::getInstance()->initPets();
            GameManager::getInstance()->initHeroes();
            
            
            
            
          if(this->_resourceCount == _pResource->size())
           {
             this->addLayers();
             __NotificationCenter::getInstance()->postNotification("loadFinish", static_cast<Ref*>(this));
            }
        });
}

void MenuScene::addLayers() {
    _pMenuSceneLayer = MenuLayer::create();
    _pMenuSceneLayer->retain();
    addChild(_pMenuSceneLayer);
}