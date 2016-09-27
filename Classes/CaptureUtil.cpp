//
//  CaptureUtil.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/21/16.
//
//

#include "CaptureUtil.h"
static cocos2d::Size iphone4s = cocos2d::Size(640, 960);
static cocos2d::Size iphone5 = cocos2d::Size(640, 1136);
static cocos2d::Size iphone6 = cocos2d::Size(750, 1334);
static cocos2d::Size iphone6plus = cocos2d::Size(1242, 2208);
static cocos2d::Size ipadpro = cocos2d::Size(1536, 2048);
static cocos2d::Size ipadair = cocos2d::Size(2048, 2732);


CaptureUtil* CaptureUtil::_gInstance;

void CaptureUtil::capture() {
    std::string savePath = "";
    Size ws = Director::getInstance()->getWinSize();
    if (ws.equals(iphone4s)) {
        savePath = __String::createWithFormat("iphone4s_%d.png",_num++)->getCString();
    } else if (ws.equals(iphone5)) {
        savePath = __String::createWithFormat("iphone5_%d.png",_num++)->getCString();
    } else if (ws.equals(iphone6)) {
        savePath = __String::createWithFormat("iphone6_%d.png",_num++)->getCString();
    } else if (ws.equals(iphone6plus)) {
        savePath = __String::createWithFormat("iphone6plus_%d.png",_num++)->getCString();
    } else if (ws.equals(ipadair)) {
        savePath = __String::createWithFormat("ipad_air_%d.png",_num++)->getCString();
    } else if (ws.equals(ipadpro)) {
        savePath = __String::createWithFormat("ipad_pro_%d.png",_num++)->getCString();
    }
    utils::captureScreen(CC_CALLBACK_2(CaptureUtil::afterCaptured, this),savePath);
}
void CaptureUtil::afterCaptured(bool succeed, const std::string& outputFile) {
    
}
bool CaptureUtil::init() {
    return true;
}