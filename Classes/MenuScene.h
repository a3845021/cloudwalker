//
//  MenuScene.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#ifndef MenuScene_hpp
#define MenuScene_hpp

#include <cocos2d.h>
USING_NS_CC;

class MenuScene : public Scene {
public:
    CREATE_FUNC(MenuScene);
    virtual ~MenuScene();
    Layer* _pMenuSceneLayer;
    std::vector<std::string> *_pResource;
    void preloadSources();
    void addLayers();
    
protected:
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onKeyReleased(EventKeyboard::KeyCode code, Event *event);
    void showTips(std::string tip, float sec);
private:
    bool _exit =false;
    int _resourceCount = 0 ;
};

#endif /* MenuScene_hpp */
