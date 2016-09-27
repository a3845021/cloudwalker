//
//  HelpLayer.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#ifndef HelpLayer_hpp
#define HelpLayer_hpp

#include <cocos2d.h>
USING_NS_CC;

class HelpLayer : public Layer {
public:
    CREATE_FUNC(HelpLayer);
protected:
    virtual bool init()override;
    
    virtual void onEnter()override;
    
    virtual void onExit()override;
    
};

#endif /* HelpLayer_hpp */
