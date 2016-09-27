//
//  BgObj.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#ifndef BgObj_h
#define BgObj_h

#include <cocos2d.h>
USING_NS_CC;

class BgObj : public Sprite {
public:
    virtual ~BgObj();
    virtual bool init(int kind);
    static BgObj* createObj(int id);
};
#endif /* BgObj_h */
