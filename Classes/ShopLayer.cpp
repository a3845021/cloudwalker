//
//  ShopLayer.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#include "ShopLayer.h"
#include "GameManager.h"

bool ShopLayer::init() {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        // shop paid
        // money icon
        // money text
        
        // wing list [w]  [w]  [w]
        //           [w] <hero>[w]
        //           [w]  [w]  [w]

        auto winSize = Director::getInstance()->getWinSize();
        

        auto pListener = EventListenerTouchOneByOne::create();
        
        pListener->setSwallowTouches(true);
        pListener->onTouchBegan = [](Touch *pTouch, Event *pEvent){return true;};
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListener, this);
        
        auto bg = Sprite::createWithSpriteFrameName("shoppad.png");
        this->setContentSize(bg->getContentSize());
        addChild(bg);
        
        auto closeBtn = Button::create("close_s.png","","",TextureResType::PLIST);
        closeBtn->setPosition(Vec2(bg->getContentSize().width - closeBtn->getContentSize().width/2,bg->getContentSize().height - closeBtn->getContentSize().height/2));
        closeBtn->addTouchEventListener([&](Ref* node,Widget::TouchEventType tt){
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
            removeFromParent();
        });
        bg->addChild(closeBtn);
        
        
        
        
        auto _coinicon = Sprite::create("res/coin.png");
        _coinicon->setPosition(Vec2(50,bg->getContentSize().height - _coinicon->getContentSize().height));
       bg->addChild(_coinicon);
       auto _coin = Label::createWithTTF(__String::createWithFormat("%d",GameManager::getInstance()->getCoin())->getCString(), "fonts/arial.ttf", 30);
        _coin->setColor(Color3B::YELLOW);
        _coin->setAnchorPoint(Vec2(0.5,0.5));
        _coin->setPosition(55 + _coinicon->getContentSize().width, bg->getContentSize().height - _coin->getContentSize().height);
        bg->addChild(_coin);

        
        
        currentHero = Sprite::createWithSpriteFrameName("selectedhero.png");
        currentHero->setAnchorPoint(Vec2::ZERO);
        bg->addChild(currentHero,999);


        
        GameManager::getInstance()->initHeroes();
        GameManager::getInstance()->initWings();
        ValueVector heroes = GameManager::getInstance()->getHeroes();
        ValueMap hero;
        for(int i= 0;i < heroes.size();i++) {
            hero = heroes.at(i).asValueMap();
            int id = hero.at("id").asInt();
  
            
            auto selHero = Button::create(hero.at("img").asString(),"","",TextureResType::PLIST);
            selHero->setTag(i);
            selHero->setPosition(Vec2(50+ i* 100,500));
            selHero->addTouchEventListener([&](Ref* node,Widget::TouchEventType tt){
                if (tt != Widget::TouchEventType::ENDED) {
                    return;
                }
                ValueVector heroes = GameManager::getInstance()->getHeroes();
                int index = ((Button*)node)->getTag();
                UserDefault::getInstance()->setIntegerForKey("hero", heroes.at(index).asValueMap().at("id").asInt());
                auto moveTo = MoveTo::create(1.0f, ((Button*)node)->getPosition()-Vec2(((Button*)node)->getContentSize().width/2,((Button*)node)->getContentSize().height/2));
                currentHero->runAction(moveTo);
             });
            bg->addChild(selHero);
            
            if (UserDefault::getInstance()->getIntegerForKey("hero",0) == 0)
                UserDefault::getInstance()->setIntegerForKey("hero",1);
            
            if (id ==  UserDefault::getInstance()->getIntegerForKey("hero",1)) {
                currentHero->setPosition(selHero->getPosition()-Vec2(selHero->getContentSize().width/2,selHero->getContentSize().height/2));
            }
            
            
            
            
            int score = UserDefault::getInstance()->getIntegerForKey("highscore",0);
            
            if (score < hero.at("price").asInt()) {
                auto mask = Button::create("heromask.png","","",TextureResType::PLIST);
                mask->setTag(i);
                mask->setPosition(selHero->getPosition()-Vec2(1,10));
                mask->addTouchEventListener([&](Ref* node,Widget::TouchEventType tt){
                    if (tt != Widget::TouchEventType::ENDED) {
                        return;
                    }
                    heroTip(((Button*)node)->getTag());
                    
                });
                bg->addChild(mask);
            }

        }

        GameManager::getInstance()->initPets();
        ValueVector wings = GameManager::getInstance()->getPets();
        ValueMap wing;
        int col = 0;
        int row = 0;
      
        for(int i= 0;i < wings.size();i++) {
            wing = wings.at(i).asValueMap();
            int id = wing.at("id").asInt();
            auto w = WingItem::createItem(id);
            w->setSpriteFrame(wing.at("img").asString());
            w->setAnchorPoint(Vec2::ZERO);
            w->setPosition(Vec2(80+ 9 + col*252,50 + row* 132));
            
            bool buyed = UserDefault::getInstance()->getBoolForKey(__String::createWithFormat("pet%d",id)->getCString(),false);
            w->setBuyed(buyed);
            w->setPrice(wing.at("price").asInt());
            bg->addChild(w);
            
            if(!w->getBuyed()) {
                auto mask = Button::create("wingslot.png","","",TextureResType::PLIST);
                mask->setTag(i);
                mask->addTouchEventListener([&](Ref* node,Widget::TouchEventType tt){
                    if (tt != Widget::TouchEventType::ENDED) {
                        return;
                    }
                    buyItem(((Button*)node)->getTag());
                });
                mask->setAnchorPoint(Vec2::ZERO);
                mask->setPosition(Vec2(10 + col*252 ,50 + row* 122));
                bg->addChild(mask);
                auto price= Label::createWithTTF(wing.at("price").asString(), "fonts/arial.ttf", 64);
                price->setAnchorPoint(Vec2::ZERO);
                price->setPosition(Vec2(50 + col*252 ,50 + row* 122));
                price->setColor(Color3B::YELLOW);
                bg->addChild(price);
                
                
                auto coin= Sprite::create("res/coin.png");
                coin->setAnchorPoint(Vec2::ZERO);
                coin->setPosition(Vec2(10 + col*252 ,50 + row* 122));
                
                bg->addChild(coin);

                
            }
            
            col++;
            if (col!=0&&col % 2 == 0) {
                row++;
                col = 0;
            }
        }
        
        
        

        
        // x 9  y 55
        
        // x 261  y 187
        
        // x offset = 252
        // y offset = 132
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void ShopLayer::onEnter() {
    Layer::onEnter();
}

void ShopLayer::onExit() {
    Layer::onExit();
}

void ShopLayer::buyItem(int idx) {
    ValueVector pets = GameManager::getInstance()->getPets();
    ValueMap pet = pets.at(idx).asValueMap();
    if (UserDefault::getInstance()->getBoolForKey(__String::createWithFormat("pet%d",pet.at("id").asInt())->getCString(),false)) {
        auto label = Label::createWithTTF("You have bougth this pet", "fonts/arial.ttf", 24);
        label->setTag(321);
        label->setAnchorPoint(Vec2(0.5,0.5));
        label->setPosition(Vec2(this->getContentSize().width/2- label->getContentSize().width/2,this->getContentSize().height));
        auto fadeOut = FadeOut::create(3.0f);
        addChild(label);
        label->runAction(Sequence::create(fadeOut,RemoveSelf::create(), NULL));
        
        return;
    }
    int money = GameManager::getInstance()->getCoin();
    
    if (money < pet.at("price").asInt() ) {
//        if (getChildByTag(321))
//            removeChildByTag(321);
        auto label = Label::createWithTTF("Not enough coin", "fonts/arial.ttf", 32);
        label->setColor(Color3B::MAGENTA);
        label->setTag(321);
        label->setAnchorPoint(Vec2(0.5,0.5));
        label->setPosition(Vec2(0,0));
        auto fadeOut = FadeOut::create(2.0f);
        addChild(label);
        label->runAction(Sequence::create(fadeOut,RemoveSelf::create(), NULL));
        log("not enough money");
    } else {
        money -= pet.at("price").asInt();
        GameManager::getInstance()->setCoin(money);
        UserDefault::getInstance()->setBoolForKey(__String::createWithFormat("pet%d",pet.at("id").asInt())->getCString(), true);
    }
            // check money
            // if money is lower // show warning
            
            // else
            
            
            // sub moeny
            // open pet
            
            
    
}

void  ShopLayer::heroTip(int idx) {
    ValueVector heroes = GameManager::getInstance()->getHeroes();
    ValueMap hero = heroes.at(idx).asValueMap();
    if (getChildByTag(321))
        removeChildByTag(321);
    auto label = Label::createWithTTF(__String::createWithFormat("You have reach %d point to open this hero",hero.at("price").asInt())->getCString(), "fonts/arial.ttf", 32);
      label->setColor(Color3B::MAGENTA);
    label->setTag(321);
    label->setAnchorPoint(Vec2(0.5,0.5));
 //   label->setPosition(Vec2(this->getContentSize().width/2- label->getContentSize().width/2,this->getContentSize().height));
    auto fadeOut = FadeOut::create(2.0f);
    addChild(label);
     label->runAction(Sequence::create(fadeOut,RemoveSelf::create(), NULL));
}