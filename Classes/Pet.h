//
//  Pet.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/11/16.
//
//

#ifndef Pet_h
#define Pet_h

#include <cocos2d.h>
USING_NS_CC;
#include "Hero.h"

class Pet : public Sprite {
public:
    enum PetKind {
        en_trash_talk = 1,  // ?
        en_find_money, // ok
        en_double_coin, // ok
        en_saver, // ok
    };
    enum State {
        en_state_idle,
        en_state_flying
    };
    static Pet* createPet(int kind);
    virtual bool init(int kind);
    Pet();
    ~Pet();
    void doFly();
    void doSave();
    void doFindCoin();
    void doCreateCloud();
    void Talk(std::string text);
    void processAI(float dt);
    CC_SYNTHESIZE(int, _kind, Kind);
    CC_SYNTHESIZE(int, _state, State);
    CC_SYNTHESIZE(Hero*, _hero, Hero);
private:
    Animation* _fly;
};
#endif /* Pet_h */
