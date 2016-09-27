//
//  GameOverLayer.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/10/16.
//
//

#ifndef GameOverLayer_hpp
#define GameOverLayer_hpp

#include <cocos2d.h>
USING_NS_CC;
#include <cocos-ext.h>
USING_NS_CC_EXT;
using namespace cocos2d::ui;
class GameOverLayer : public Layer {
public:
    CREATE_FUNC(GameOverLayer);
    void flyIn() {
        this->setPosition(Vec2(-640,0));
        this->runAction(EaseExponentialOut::create(MoveTo::create(1.0f,Vec2(0,0))));
    }
    void flyOut() {
        this->runAction(EaseExponentialOut::create(MoveTo::create(1.0f,Vec2(640,0))));
    }
protected:
    virtual bool init()override;
    
    virtual void onEnter()override;
    
    virtual void onExit()override;
    
    Button* getRestartBtn() {
        return _restartbtn;
    }

private:
    LayerColor* _bg;
    Sprite* _pad;
    Sprite* _new;
    CC_SYNTHESIZE(Label*, _title, Title);
    CC_SYNTHESIZE(Label*, _score, Score);
    CC_SYNTHESIZE(Label*, _highScore, HighScore);
    // button home
    Button* _homebtn;
    Button* _ratebtn;
    Button* _sharebtn;
    Button* _restartbtn;
    // button rate
    // button share
    // button restart
};

#endif /* GameOverLayer_hpp */
