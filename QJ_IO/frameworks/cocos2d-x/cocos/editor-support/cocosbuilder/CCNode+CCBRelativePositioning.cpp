#include "editor-support/cocosbuilder/CCNode+CCBRelativePositioning.h"
#include "editor-support/cocosbuilder/CCBReader.h"

using namespace cocos2d;

namespace cocosbuilder {

CC_DLL Vec2 getAbsolutePosition(const Vec2 &pt, CCBReader::PositionType type, const Size &containerSize, const std::string& propName)
{
    Vec2 absPt;
    if (type == CCBReader::PositionType::RELATIVE_BOTTOM_LEFT)
    {
        absPt = pt;
    }
    else if (type == CCBReader::PositionType::RELATIVE_TOP_LEFT)
    {
        absPt.x = pt.x;
        absPt.y = containerSize.height - pt.y;
    }
    else if (type == CCBReader::PositionType::RELATIVE_TOP_RIGHT)
    {
        absPt.x = containerSize.width - pt.x;
        absPt.y = containerSize.height - pt.y;
    }
    else if (type == CCBReader::PositionType::RELATIVE_BOTTOM_RIGHT)
    {
        absPt.x = containerSize.width - pt.x;
        absPt.y = pt.y;
    }
    else if (type == CCBReader::PositionType::PERCENT)
    {
        absPt.x = (int)(containerSize.width * pt.x / 100.0f);
        absPt.y = (int)(containerSize.height * pt.y / 100.0f);
    }
    else if (type == CCBReader::PositionType::MULTIPLY_RESOLUTION)
    {
        float resolutionScale = CCBReader::getResolutionScale();
        
        absPt.x = pt.x * resolutionScale;
        absPt.y = pt.y * resolutionScale;
    }
    else if (type == CCBReader::PositionType::RELATIVE_CENTER)    //jy <--
    {
        absPt.x = pt.x + containerSize.width*0.5f;
        absPt.y = pt.y + containerSize.height*0.5f;
    }
    else if (type == CCBReader::PositionType::RELATIVE_TOPCENTER)
    {
        absPt.x = pt.x + containerSize.width*0.5f;
        absPt.y = containerSize.height - pt.y;
    }
    else if (type == CCBReader::PositionType::RELATIVE_BOTTOMCENTER)
    {
        absPt.x = pt.x + containerSize.width*0.5f;
        absPt.y = pt.y;
    }
    else if (type == CCBReader::PositionType::RELATIVE_LEFTCENTER)
    {
        absPt.x = pt.x;
        absPt.y = pt.y + containerSize.height*0.5f;
    }
    else if (type == CCBReader::PositionType::RELATIVE_RIGHTCENTER)
    {
        absPt.x = containerSize.width - pt.x;
        absPt.y = pt.y + containerSize.height*0.5f;
    }   //jy -->

    
    return absPt;
}

CC_DLL void setRelativeScale(Node *pNode, float scaleX, float scaleY, CCBReader::ScaleType type, const std::string& propName)
{
    CCASSERT(pNode, "pNode should not be null");
    
    if (type == CCBReader::ScaleType::MULTIPLY_RESOLUTION)
    {
        float resolutionScale = CCBReader::getResolutionScale();
        
        scaleX *= resolutionScale;
        scaleY *= resolutionScale;
    }
    
    pNode->setScaleX(scaleX);
    pNode->setScaleY(scaleY);
}

}
