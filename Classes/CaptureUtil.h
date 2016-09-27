//
//  CaptureUtil.h
//  CloudWalker
//
//  Created by Pham Thanh on 7/21/16.
//
//

#ifndef CaptureUtil_h
#define CaptureUtil_h

#include "define.h"


class CaptureUtil : public Ref {
public:
    CREATE_INSTANCE_FUNC(CaptureUtil);
    DESTROY_INSTANCE_FUNC();
    void capture();
    void afterCaptured(bool succeed, const std::string& outputFile);
protected:
    virtual bool init();
private:
    int _num = 0;
};
#endif /* CaptureUtil_h */
