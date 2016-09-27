//
//  GameScene.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#include "GameScene.h"
#include "Cloud.h"
#include "GameOverLayer.h"
#include "GameManager.h"
#include "MenuScene.h"
#include "BgObj.h"
#include "Pet.h"
#include "SdkUtil.h"
#include "SoundUtil.h"
#include "CaptureUtil.h"

GameScene::~GameScene() {
    CC_SAFE_RELEASE(_pGameSceneLayer);
}


bool GameScene::init() {
    bool bRet = false;
    SdkUtil::getInstance()->showAdmob("home");
    do
    {
        CC_BREAK_IF(!Scene::init());
        _pGameSceneLayer = Layer::create();
        _pGameSceneLayer->retain();
        
        _background = Sprite::create(__String::createWithFormat("res/bg/bg%d.png",random(1, 4))->getCString()); // normal
        _background->setAnchorPoint(Vec2::ZERO);
        addChild(_background,-1);
        
        auto winSize = Director::getInstance()->getWinSize();
        _homebtn = Button::create("home_small.png","","",cocos2d::ui::Button::TextureResType::PLIST);
        _homebtn->setPosition(Vec2(winSize.width - _homebtn->getContentSize().width, winSize.height - _homebtn->getContentSize().height));
        _homebtn->addTouchEventListener([&](Ref* pSender,Widget::TouchEventType tt){
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
            this->removeFromParentAndCleanup(true);
            auto pTransScene = TransitionFade::create(0.2f, MenuScene::create());
            Director::getInstance()->replaceScene(pTransScene);
        });

        addChild(_homebtn);
        _sun = Sprite::createWithSpriteFrameName("sun_1.png"); // normal
        _sun->setPosition(Vec2(500,800));
        _sun->setScale(0.5f);
        addChild(_sun);
        auto face =Sprite::createWithSpriteFrameName(__String::createWithFormat("face_%d.png",random(1, 58))->getCString());
        face->setPosition(Vec2(_sun->getContentSize().width/2,_sun->getContentSize().height/2));
        face->setTag(1);
        _sun->addChild(face);
        _gameover = GameOverLayer::create();
        _gameover->setPosition(Vec2(-640,0));
   
        _draw = DrawNode::create();

        this->addChild(_draw);
     
        _score = Label::createWithTTF("0", "fonts/arial.ttf", 128);
        _score->setColor(Color3B::WHITE);
        _score->setAnchorPoint(Vec2(0.5,0.5));
        _score->setPosition(_background->getContentSize().width/2,_background->getContentSize().height- _score->getContentSize().height*1.5);
        addChild(_score);
        
        
        _coinicon = Sprite::create("res/coin.png");
        _coinicon->setPosition(Vec2(50,_background->getContentSize().height - _coinicon->getContentSize().height));
        addChild(_coinicon);
        _coin = Label::createWithTTF(__String::createWithFormat("%d",GameManager::getInstance()->getCoin())->getCString(), "fonts/arial.ttf", 30);
        _coin->setColor(Color3B::YELLOW);
        _coin->setAnchorPoint(Vec2(0,0.5));
        _coin->setPosition(50 + _coinicon->getContentSize().width, _background->getContentSize().height - _coin->getContentSize().height);
        addChild(_coin);
        
       auto listener = EventListenerTouchOneByOne::create();
       // listener->setSwallowTouches(true);
        listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
        listener->retain();
        
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        listener->setEnabled(true); // This method is used to enable/disable the touch whenever required
    
       auto  m_keyBoardListener = EventListenerKeyboard::create();
        m_keyBoardListener->retain();
        m_keyBoardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased,this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(m_keyBoardListener,this);
        
        __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::restartGame), "restartGame", nullptr);
        __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::addCoin), "addCoin", nullptr);
             addChild(_gameover,999999);
        _gameState = en_idle;
        bRet = true;
        
        
        ///
        

    }
    while (0);
    
    return bRet;
}
bool GameScene::onTouchBegan(Touch *touch, Event *unused_event) {
    if ( _gameState != en_idle) {
        return true;
    }
    if(_cloudVec->size()>2) {
        _cloudVec->front()->removeFromParent();
        _cloudVec->eraseObject(_cloudVec->front());
    }
    _draw->clear();
    Color4F blue(0, 0, 1, 1);
      Vec2 point = _hero->getPosition() + Vec2(250,80);
    auto mid = Vec2((_hero->getPositionX()+100),770);
    _draw->drawQuadBezier( _hero->getPosition(), mid,point, 18, blue);
    _point[0] = _hero->getPosition();

    for (int i=0;i< _coinVec->size(); i++) {
        if (_coinVec->at(i)->getPositionX() < 0) {
            _coinVec->at(i)->removeFromParent();
            _coinVec->eraseObject( _coinVec->at(i));
        }
    }
    
    return true;
}
void GameScene::onTouchMoved(Touch *touch, Event *unused_event) {
    if ( _gameState != en_idle) {
        return ;
    }
     _draw->clear();
    Color4F blue(0, 0, 1, 1);
    Vec2 point = touch->getLocation()+ Vec2(250,80);
    auto mid = Vec2((_hero->getPositionX()+100),770);
        _point[1] = mid;
        _point[2] = point;
    _draw->drawQuadBezier( _hero->getPosition(), mid,point, 18, blue);
}
void GameScene::onTouchEnded(Touch *touch, Event *unused_event) {
    if (_gameState != en_idle) {
        return;
    }
    _gameState = en_flying;
    
   // _hero->getPhysicsBody()->setEnabled(false);
            _draw->clear();

    auto Jump = JumpTo::create(1.0f,_point[2], 150, 1);
    auto Jump1 = JumpTo::create(1.0f, Vec2(_point[2].x+120,-100), 50, 1);
    _hero->runAction(Sequence::create(Jump,Jump1,nullptr));
    SoundUtil::getInstance()->playEffect("sound/jump.mp3");
    _hero->jump();
    
}
void GameScene::faceChange(float dt) {
        _sun->removeChildByTag(1);
        auto face =Sprite::createWithSpriteFrameName(__String::createWithFormat("face_%d.png",random(1, 58))->getCString());
        face->setPosition(Vec2(_sun->getContentSize().width/2,_sun->getContentSize().height/2));
        face->setTag(1);
        _sun->addChild(face);
}
void GameScene::collisionUpdate(float dt) {
    if (random(1, 100)>99) {
        addChild(BgObj::createObj(random(1,3)));
    }


    
    if (_gameState == en_gameover || _gameState == en_saving) {
        return;
    }
    for (int i=0;i < _petVec->size(); i++) {
        auto pet = _petVec->at(i);
        if (pet->getKind() == Pet::en_find_money) {
            for(int j=0;j < _coinVec->size();j ++ ) {
                if(_coinVec->at(j)->isVisible()&&IsInScreen(_coinVec->at(j)->getPosition()) ) {
                    pet->stopActionByTag(123);
                    auto getcoin = MoveTo::create(1.0f, _coinVec->at(j)->getPosition());
                    getcoin->setTag(123);
                    pet->runAction(getcoin);
                      pet->Talk("omg ! i got a coin");
                    break;
                }
            }
        }
    }
    if (_hero->getPositionY() < 0) {
        
        for (int i=0;i < _petVec->size(); i++) {
            auto pet = _petVec->at(i);
            if (pet->getState() == Pet::en_state_flying) {
                break;
            }
            if (pet->getKind() == Pet::en_saver) {
                pet->stopActionByTag(123);
                
                pet->setState(Pet::en_state_flying);
                
                pet->Talk("i will save you !");
                
                
                
                _cloudVec->back()->stopAllActions();
                auto gotoHero = MoveTo::create(1.0f, _hero->getPosition());
                auto gotoCloud = CallFuncN::create([&](Node* mypet) {
                    auto endsave = CallFuncN::create([&](Node* hero){
                          _hero->stand();
                        _gameState = en_idle;
                    });
                    auto killpet = CallFuncN::create([&](Node* sender){
                        _petVec->eraseObject((Pet*)sender);
                        sender->removeFromParentAndCleanup(true);
                     
                    });
                    auto gogo =  MoveTo::create(2.0f, _cloudVec->back()->getPosition()+Vec2(0,_cloudVec->back()->getContentSize().height/2 + _hero->getContentSize().height/2 -1 ));
                    _hero->runAction(Sequence::createWithTwoActions(gogo,endsave));
                    gogo =  MoveTo::create(2.0f, _cloudVec->back()->getPosition());
                    gogo->setTag(123);
                    ((Pet*)mypet)->Talk("i have to go :(( see you later ");
                    mypet->runAction(Sequence::create(gogo,FadeOut::create(3.0f),killpet, nullptr));
                
                });
                pet->runAction(Sequence::createWithTwoActions(gotoHero, gotoCloud));
                _gameState = en_saving;
                return;
            }
        }
        
        _gameState = en_gameover;
        
        

        _gameover->getHighScore()->setString(__String::createWithFormat("%d",GameManager::getInstance()->getHighScore())->getCString());
        _gameover->getScore()->setString(__String::createWithFormat("%d",GameManager::getInstance()->getScore())->getCString());
        _gameover->flyIn();
        
        SdkUtil::getInstance()->showAdmob("gameover");
            SoundUtil::getInstance()->playEffect("sound/fail.mp3");
        log("game over");
        // game over thi soa
        
    } else {
        for (int i=0;i< _coinVec->size(); i++) {
            if (_hero->getBoundingBox().intersectsRect(_coinVec->at(i)->getBoundingBox())) {
                if(_coinVec->at(i)->getTag() != 1) {
                    _coinVec->at(i)->setTag(1);
                    _coinVec->at(i)->flyUp();
                    SoundUtil::getInstance()->playEffect("sound/eatcoin.mp3");
                }
            }
        }
        for (int i=0;i< _petVec->size(); i++) {
            for (int j=0; j < _coinVec->size(); j++) {
                if (_petVec->at(i)->getBoundingBox().intersectsRect(_coinVec->at(j)->getBoundingBox())) {
                    if(_coinVec->at(j)->getTag() != 1) {
                        _coinVec->at(j)->setTag(1);
                        _coinVec->at(j)->flyUp();
                            SoundUtil::getInstance()->playEffect("sound/eatcoin.mp3");
                    }
                }
            }
        }
        
        if (_hero->getBoundingBox().intersectsRect(_cloudVec->back()->getBoundingBox())&& _hero->getPosition().y > _cloudVec->back()->getPosition().y) {
                _hero->stand();
            // add score
            GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+1);
            _score->setString(__String::createWithFormat("%d",GameManager::getInstance()->getScore())->getCString());
         

            
            if (GameManager::getInstance()->getScore() > GameManager::getInstance()->getHighScore()) {
                GameManager::getInstance()->setHighScore(GameManager::getInstance()->getScore());
                if(_newhighscore == false ) {
                    _newhighscore = true;
                auto _emitter = ParticleFireworks::create();
                _emitter->retain();
                _emitter->setScaleX(2);
                _background->addChild(_emitter, 10);
                
                _emitter->setTexture( Director::getInstance()->getTextureCache()->addImage("res/effect/stars2.png") );
                
                _emitter->setPosition(Vec2(_score->getPositionX(),_score->getPositionY()-_score->getContentSize().height));
                _emitter->runAction(Sequence::createWithTwoActions(FadeOut::create(3.0f), RemoveSelf::create()));
                }
                
            }
                
              _gameState = en_idle;
            _hero->stopAllActions();
            _cloudVec->back()->stopAllActions();
            _hero->setPositionY(_cloudVec->back()->getBoundingBox().getMaxY()+ _hero->getContentSize().height/2);
            
            int offsetX = _hero->getPositionX()-120;
            auto moveBy = MoveBy::create(1.0f, Vec2(-offsetX,0));
            _hero->runAction(moveBy);

            _cloudVec->pushBack(Cloud::createCloud(1, nullptr));
            _cloudVec->back()->setPosition(Vec2(640+120,cocos2d::random(100, 600)));
            addChild(_cloudVec->back());
            for (int i=0;i< _cloudVec->size()-1; i++) {
                auto moveBy = MoveBy::create(1.0f, Vec2(-offsetX,0));
                _cloudVec->at(i)->runAction(moveBy);
            }
            // if (random(1, 100)>10)
            {
                auto coin = Coin::create();
                coin->setPosition(Vec2(640 + random(120, 400),random(200, 800)));
                addChild(coin,9999);
                _coinVec->pushBack(coin);
                //  log("num coin =%d",_coinVec->size())    ;
            }
            
            for (int i=0;i< _coinVec->size()-1; i++) {
                auto moveBy = MoveBy::create(1.0f, Vec2(-offsetX,0));
                _coinVec->at(i)->runAction(moveBy);
            }


            
            
            moveBy = MoveBy::create(1.0f, Vec2(-offsetX,0));
            auto cb = CallFuncN::create([&](Node* psender){
                psender->stopAllActions();
                psender->runAction(Cloud::genMove(GameManager::getInstance()->getScore()/2 + 100));
            });
            _cloudVec->back()->runAction(Sequence::create(moveBy,cb,nullptr));
        }
    }
}
bool GameScene::IsInScreen(const Vec2 &vec) {
    if (vec.x < 0  || vec.x > Director::getInstance()->getWinSize().width || vec.y < 0 || vec.y > Director::getInstance()->getWinSize().height ) {
        return false;
    }
    return true;
}
void GameScene::restartGame(Ref* data) {
    if (_hero == nullptr) {
        _hero = Hero::createHero(UserDefault::getInstance()->getIntegerForKey("hero",1));
        addChild(_hero);
    }

    
    _background->setTexture(__String::createWithFormat("res/bg/bg%d.png",random(1, 4))->getCString());
    _background->setAnchorPoint(Vec2::ZERO);
 
    
    _hero->setPosition(Vec2(120,960/2));
    if(_petVec == nullptr) {
        _petVec = new Vector<Pet*>();
    }
    if(_coinVec == nullptr) {
        _coinVec = new Vector<Coin*>();
    }
    if(_cloudVec == nullptr) {
        _cloudVec = new Vector<Cloud *>();
    }
    for (int i=0;i< _cloudVec->size(); i++) {
        _cloudVec->at(i)->removeFromParentAndCleanup(true);
    }
    for (int i=0;i< _coinVec->size(); i++) {
        _coinVec->at(i)->removeFromParentAndCleanup(true);
    }
    for (int i=0;i< _petVec->size(); i++) {
        _petVec->at(i)->removeFromParentAndCleanup(true);
    }
    _petVec->clear();
    _coinVec->clear();
    _cloudVec->clear();
    _cloudVec->pushBack(Cloud::createCloud(1, nullptr));
    _cloudVec->back()->setPosition(Vec2(120,960/2- _hero->getContentSize().height/2- _cloudVec->back()->getContentSize().height/2));
    addChild(_cloudVec->back());
    _cloudVec->pushBack(Cloud::createCloud(1, nullptr));
    _cloudVec->back()->setPosition(Vec2(460,960/2- _hero->getContentSize().height/2 - _cloudVec->back()->getContentSize().height/2));
    addChild(_cloudVec->back());
    _score->setString("0");
    GameManager::getInstance()->setScore(0);
    _newhighscore = false;
    
    GameManager::getInstance()->initPets();
    for (int i=0; i< GameManager::getInstance()->getPets().size(); i++) {
        if (UserDefault::getInstance()->getBoolForKey(__String::createWithFormat("pet%d",GameManager::getInstance()->getPets().at(i).asValueMap().at("id").asInt())->getCString(),false)) {
            auto pet = Pet::createPet(GameManager::getInstance()->getPets().at(i).asValueMap().at("id").asInt());
            pet->setHero(_hero);
            pet->setPosition(Vec2(300,300));
            _petVec->pushBack(pet);
            this->addChild(pet);
            
        }
    }
    
    
    
    
    
    _gameState = en_idle;
}
void GameScene::onEnter() {
    Scene::onEnter();
    addChild(_pGameSceneLayer);
    this->restartGame(nullptr);
    schedule(schedule_selector(GameScene::collisionUpdate), 0.1f);
    
    
    schedule(schedule_selector(GameScene::faceChange), 10.0f);
}

void GameScene::onExit() {
    SdkUtil::getInstance()->hideAdmob("home");
     Scene::onExit();
    __NotificationCenter::getInstance()->removeAllObservers(this);
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode code, Event *event)
{
    if (code == EventKeyboard::KeyCode::KEY_BACK)
    {
        
        if (_exit)
        {
            auto pTransScene = TransitionFade::create(0.2f, MenuScene::create());
            Director::getInstance()->replaceScene(pTransScene);
        }
        else
        {
            // œ‘ æÃ· æ
            _exit = true;
            showTips("Back to exit",1.0f);
        }
    }
}
// neu chet ma con saver chua die thi bi bug
// ko game over dc :D
// fix vao sang mai
void GameScene::showTips(std::string tip, float sec) {
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

void GameScene::addCoin(Ref* data) {
    int add = 1;
    for (int i=0;i < _petVec->size(); i++) {
        auto pet = _petVec->at(i);
        if (pet->getKind() == Pet::en_double_coin) {
            add = add*2;
        }
    }
    
    GameManager::getInstance()->setCoin(GameManager::getInstance()->getCoin()+add);
    _coin->setString(__String::createWithFormat("%d",GameManager::getInstance()->getCoin())->getCString());
}