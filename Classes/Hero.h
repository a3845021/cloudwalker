//
//  Hero.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#ifndef Hero_h
#define Hero_h

#include <cocos2d.h>
USING_NS_CC;

class Hero : public Sprite {
public:
    virtual ~Hero();
    static Hero* createHero(int id);
    virtual bool init(int id);
    void jump();
    void stand();
    
private:
    std::string alias;
};
#endif /* Hero_h */
