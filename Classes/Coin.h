//
//  Coin.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/11/16.
//
//

#ifndef Coin_hpp
#define Coin_hpp

#include <cocos2d.h>
USING_NS_CC;

class Coin : public Sprite {
public:
    CREATE_FUNC(Coin);
    void flyUp();
protected:
    virtual bool init()override;
    
    virtual void onEnter()override;
    
    virtual void onExit()override;
    
};

#endif /* Coin_hpp */
