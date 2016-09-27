//
//  HeroItem.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/11/16.
//
//

#ifndef HeroItem_hpp
#define HeroItem_hpp

#include <cocos2d.h>
USING_NS_CC;
#include "Define.h"

class HeroItem : public Sprite {
public:
    static HeroItem* createItem(int id);
        void addListener();
protected:
    virtual bool init(int id);
    
    virtual void onEnter()override;
    
    virtual void onExit()override;
     CC_SYNTHESIZE(Button*,_select, SelectBtn);
    
    CC_SYNTHESIZE(bool,_show, Show);
    CC_SYNTHESIZE(int,_id, Id);
    CC_SYNTHESIZE(int,_price, Price);
    
};

#endif /* HeroItem_hpp */
