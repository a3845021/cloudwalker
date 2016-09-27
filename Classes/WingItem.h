//
//  WingItem.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/11/16.
//
//

#ifndef WingItem_hpp
#define WingItem_hpp

#include <cocos2d.h>
USING_NS_CC;

class WingItem : public Sprite {
public:
    static WingItem* createItem(int id);
    void updateView();
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

#endif /* WingItem_hpp */
