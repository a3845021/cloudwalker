//
//  ShopLayer.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#ifndef ShopLayer_hpp
#define ShopLayer_hpp

#include <cocos2d.h>
USING_NS_CC;

#include "HeroItem.h"
#include "WingItem.h"

class ShopLayer : public Layer {
public:
    CREATE_FUNC(ShopLayer);
protected:
    virtual bool init()override;
    
    virtual void onEnter()override;
    
    virtual void onExit()override;
private:
  void  buyItem(int idx);
    void  heroTip(int idx);
    Vector<HeroItem*> *_heroitems;
    Sprite* currentHero;
};

#endif /* ShopLayer_hpp */
