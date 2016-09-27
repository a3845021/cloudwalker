//
//  MenuLayer.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#ifndef MenuLayer_hpp
#define MenuLayer_hpp

#include <cocos2d.h>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

class MenuLayer : public Layer {
public:
    CREATE_FUNC(MenuLayer);
    void updateUi();
protected:
    virtual bool init()override;
    
    virtual void onEnter()override;
    
    virtual void onExit()override;
    
    void TouchEventCallback(Ref *pSender, Widget::TouchEventType type);
private:
    Sprite* _background; // normal
  //  Sprite* _title; // top fall
    Sprite* _charicon;
    Sprite* _cloud;
    Sprite* _sun;
    Label* _title;
    
    Button* _playbtn; // left to right
    
    Button* _helpbtn; // left
    Button* _soundbtn; // left
    
    Button* _shopbtn; // right
    Button* _sharebtn; // right
    
    
    ActionInterval* _title_ani;
    ActionInterval* _playbtn_ani;
    ActionInterval* _helpbtn_ani;
    ActionInterval* _soundbtn_ani;
    ActionInterval* _shopbtn_ani;
    ActionInterval* _sharebtn_ani;
    
};

#endif /* MenuLayer_hpp */
