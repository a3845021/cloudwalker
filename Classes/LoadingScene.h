//
//  LoadingScene.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#ifndef LoadingScene_hpp
#define LoadingScene_hpp

#include <cocos2d.h>
USING_NS_CC;
class MenuScene;
class LoadingScene : public Scene {
public:
    CREATE_FUNC(LoadingScene);
    virtual ~LoadingScene();
    MenuScene* getMenuScene() {
        return _pMenuScene;
    }
protected:
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    void sourceLoadCallBack(Ref *pData);
private:
    MenuScene* _pMenuScene;
};

#endif /* LoadingScene_hpp */
