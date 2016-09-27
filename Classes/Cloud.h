//
//  Cloud.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#ifndef Cloud_hpp
#define Cloud_hpp

#include <cocos2d.h>
USING_NS_CC;

class Cloud : public Sprite {
public:
    static Cloud* createCloud(int type,ActionInterval* act);
    static ActionInterval* genMove(float speed);
protected:
    virtual bool init(int type,ActionInterval* act);
    
    virtual void onEnter()override;
    
    virtual void onExit()override;
    
};

#endif /* Cloud_hpp */
