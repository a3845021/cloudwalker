//
//  PetItem.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/13/16.
//
//

#ifndef PetItem_hpp
#define PetItem_hpp

#include <cocos2d.h>
USING_NS_CC;

class PetItem : public Sprite {
public:
    static PetItem* createItem(int id);
protected:
       virtual bool init(int id);
    
    virtual void onEnter()override;
    
    virtual void onExit()override;
private:
    CC_SYNTHESIZE(bool,_show, Show);
    CC_SYNTHESIZE(int,_id, Id);
    CC_SYNTHESIZE(int,_price, Price);
    CC_SYNTHESIZE(bool,_buyed, Buyed);
};

#endif /* PetItem_hpp */
