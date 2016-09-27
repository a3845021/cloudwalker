//
//  LoadingScene.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#include "LoadingScene.h"
#include "MenuScene.h"

LoadingScene::~LoadingScene() {
    
}


bool LoadingScene::init() {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Scene::init());
        
        auto pBg = Sprite::create("res/loading.png");
        pBg->setAnchorPoint(Vec2::ZERO);
        addChild(pBg);
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void LoadingScene::onEnter() {
    Scene::onEnter();
     __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(LoadingScene::sourceLoadCallBack), "loadFinish", nullptr);
    _pMenuScene = MenuScene::create();
    _pMenuScene->retain();
    
    
}

void LoadingScene::sourceLoadCallBack(Ref *pData) {
    auto pTransScene = TransitionFade::create(0.2f, dynamic_cast<Scene*>(pData));
    Director::getInstance()->replaceScene(pTransScene);
}

void LoadingScene::onExit() {
    __NotificationCenter::getInstance()->removeAllObservers(this);
    CC_SAFE_RELEASE_NULL(_pMenuScene);
    Scene::onExit();
    
}