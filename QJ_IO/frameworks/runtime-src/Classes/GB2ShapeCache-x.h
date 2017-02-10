//
//  GB2ShapeCache-x.h
//
//  Loads physics sprites created with https://www.codeandweb.com/physicseditor
//  To be used with cocos2d-x
//
//  Generic Shape Cache for box2d
//
//  Created by Thomas Broquist
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#ifndef GB2ShapeCache_x_h
#define GB2ShapeCache_x_h

#include "cocos2d.h"
#include "Box2D/Box2D.h"
class BodyDef;
class b2Body;

namespace cocos2d {
	class GB2ShapeCache {
	public:
		// Static interface
		static GB2ShapeCache* sharedGB2ShapeCache(void);

	public:
        
        struct  ShapeVertexData{
            std::vector<b2Vec2> vertices;
            int idx;
        };
        struct ShapeCircleData{
            float radis;
            b2Vec2 point;
        };
        
		bool init();
		void addShapesWithFile(const std::string &plist);
		void addFixturesToBody(b2Body *body, const std::string &shape, float scale);
		cocos2d::CCPoint anchorPointForShape(const std::string &shape);
		void reset();
		float getPtmRatio() { return ptmRatio; }
		~GB2ShapeCache() {}
        
        BodyDef* GetBodyDef(const std::string &skey);
        BodyDef* GetBodyDefWithScale(const std::string &skey, float scale);

	private:
		std::map<std::string, BodyDef *> shapeObjects;
        std::map<std::string, ShapeCircleData> _circleObjects;
        std::map<std::string, std::vector<ShapeVertexData>> _shapeVertexData;
        //std::map<std::string,std::vector<std::vector<b2Vec2>>> _vertices;
       // std::map<std::string,std::vector<int>> _idx;
		GB2ShapeCache(void) {}
		float ptmRatio;
	};
}

#endif
