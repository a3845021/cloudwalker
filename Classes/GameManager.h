//
//  GameManager.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/10/16.
//
//

#ifndef GameManager_h
#define GameManager_h

#include <cocos2d.h>
USING_NS_CC;
#include "Define.h"

class GameManager : public Ref {
public:
    virtual ~GameManager();
    CREATE_INSTANCE_FUNC(GameManager);
    DESTROY_INSTANCE_FUNC();
    
    int getHighScore();
    void setHighScore(int val);
    void setCoin(int val);
    int getCoin();
    void initHeroes();
    void initWings();
    void initPets();
    ValueVector& getHeroes();
    ValueVector& getWings();
    ValueVector& getPets();
    ValueMap& getPetById(int id);
    ValueMap& getHeroById(int id) ;
    
    void moreGames();
protected:
    virtual bool init();
private:
    int _highScore;
    int _coin;
    CC_SYNTHESIZE(int, _score, Score);
    ValueVector _heroes;
    ValueVector _wings;
    ValueVector _pets;
};
#endif /* GameManager_h */
