//
//  Define.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#ifndef Define_h
#define Define_h

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <cocostudio/CocoStudio.h>

using namespace cocos2d;
using namespace ui;
using namespace cocostudio;

#define CREATE_INSTANCE_FUNC(__CLASS__) \
private:\
static __CLASS__ *_gInstance;\
public:\
static __CLASS__* getInstance()\
{\
if(!_gInstance)\
{\
_gInstance = new __CLASS__();\
if(_gInstance && _gInstance->init())\
{\
_gInstance->autorelease();\
_gInstance->retain();\
}\
else\
{\
CC_SAFE_DELETE(_gInstance);\
}\
}\
return _gInstance;\
}

#define DESTROY_INSTANCE_FUNC()\
static void destroyInstance()\
{\
CC_SAFE_RELEASE_NULL(_gInstance);\
}

#define NOTIFY cocos2d::__NotificationCenter::getInstance()



static char tankdata[68][128] = {
    "i'm so bored",
    "i bet you will miss this turn",
    "let see how far can we get",
    "lonely, i'm so lonely",
    "daddy where we are going ?",
    "yummy",
    "we are on haven",
    "good job",
    "hello is'nt me you looking for ?",
    "becareful ",
    "nooooo !",
    "why you are following me :( ",
    "i'm hurry ",
    "it's not funny",
    "what would happen if we fail ",
    "what is going on ",
    "this cloud is running so fast",
    "i can play better than you with closed eyes",
    "i can do it by one hand",
    "do you forgot doing home work ?",
    "no not today",
    "i'm so lucky",
    "what do you feel ?",
    "do you rated this game ? can we get five star :(",
    "i like this feel",
    "we have 5 brothers",
    "we don't scare anything",
    "don't give up",
    "it's so closed",
    "this is really crazy",
    "rose are red",
    "violet are fine",
    "you can do better",
    "i trusth you",
    "jumping on the cloud is not easy ",
    "can you fly ?",
    "where is the sun i have not saw it for along time",
    "when can we see the moon ?",
    "why sky is blue ?",
    "why cloud has more colors ?",
    "what do you do in your free time ?",
    "how old are you ?",
    "i miss you so much ?",
    "i will never leave you alone ?",
    "feel so bored ? play with me !",
    "meet you at 8.PM",
    "can you reach global leaderboard ?",
    "yes you did it really good ?",
    "what time is it ?",
    "it's really cool if invite your friend play together :)",
    "i'm so tired can we take a rest",
    "i like tomato ? which fruit do you like most",
    "what do you do in your freetime ?",
    "i hope we have more time together",
    "i like to play with  you",
    "i want to have a name but the guy maked me with no name ? can you send him a request ",
    "if i was you i will rate this game for 1 star.",
    ":( i'm so sad i don't have real mind",
    "hope some day we can meet in real life",
    "i like green ",
    "i like blue",
    "i have never see a chicken",
    "the shark is so big",
    "i have never see the ocean",
    "do you known Viet Nam ?",
    "i was born in July 2016",
    "i have never meet a girl",
    "i hope i can jump out the screen ",
};

#endif /* Define_h */
