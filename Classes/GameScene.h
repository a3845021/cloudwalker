//
//  GameScene.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <cocos2d.h>
USING_NS_CC;
#include "Cloud.h"
#include "Coin.h"
#include "Pet.h"
#include "Hero.h"
#include "GameOverLayer.h"
class GameScene : public Scene {
public:
    enum GameState {
        en_idle,
        en_flying,
        en_saving,
        en_gameover
    };
    CREATE_FUNC(GameScene);
    virtual ~GameScene();
    Layer* _pGameSceneLayer;
    
    void firstLaunch();
    void nextStage();
    void collisionUpdate(float dt);
        void faceChange(float dt);
    void restartGame(Ref* data);
     void addCoin(Ref* data);
    void showTips(std::string tip,float sec);
    bool IsInScreen(const Vec2 &vec);
protected:
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onKeyReleased(EventKeyboard::KeyCode code, Event *event);
private:
    Vector<Cloud*> *_cloudVec;
    Vector<Coin*> *_coinVec;
    Vector<Pet*> *_petVec;
    Vec2 _point[3];
    Hero* _hero;
    DrawNode* _draw;
    Label* _score;
    Label* _coin;
    Sprite* _coinicon;
    Button* _homebtn;
    int _stageIndex;
    int _gameState;
    GameOverLayer* _gameover;
    Sprite* _background;
    Sprite* _sun;
    bool _exit;
    bool _newhighscore = false;
};

#endif /* GameScene_hpp */
