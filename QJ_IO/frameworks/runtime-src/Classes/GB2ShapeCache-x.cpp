//
//  GB2ShapeCache-x.cpp
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

#include "GB2ShapeCache-x.h"

#include "base/CCNS.h"

using namespace cocos2d;

/**
 * Internal class to hold the fixtures
 */
class FixtureDef {
public:
    FixtureDef()
    : next(NULL) {}

    ~FixtureDef() {
        delete next;
        delete fixture.shape;
    }

    FixtureDef *next;
    b2FixtureDef fixture;
    int callbackData;
};

class BodyDef {
public:
	BodyDef()
	: fixtures(NULL) {}

	~BodyDef() {
		if (fixtures)
			delete fixtures;
	}

	FixtureDef *fixtures;
	CCPoint anchorPoint;
};

static GB2ShapeCache *_sharedGB2ShapeCache = NULL;

GB2ShapeCache* GB2ShapeCache::sharedGB2ShapeCache(void) {
	if (!_sharedGB2ShapeCache) {
		_sharedGB2ShapeCache = new GB2ShapeCache();
        _sharedGB2ShapeCache->init();
	}

	return _sharedGB2ShapeCache;
}

bool GB2ShapeCache::init() {
	return true;
}

void GB2ShapeCache::reset() {
	std::map<std::string, BodyDef *>::iterator iter;
	for (iter = shapeObjects.begin() ; iter != shapeObjects.end() ; ++iter) {
		delete iter->second;
	}
	shapeObjects.clear();
}

void GB2ShapeCache::addFixturesToBody(b2Body *body, const std::string &shape, float scale) {
	std::map<std::string, BodyDef *>::iterator pos = shapeObjects.find(shape);
	assert(pos != shapeObjects.end());
    
    std::map<std::string,std::vector<ShapeVertexData>>::iterator pos2 = _shapeVertexData.find(shape);
    assert(pos2 != _shapeVertexData.end());
    

	BodyDef *so = (*pos).second;
    std::vector<ShapeVertexData> ShapeVertexData_vec = (*pos2).second;

    int index = 0;
    
    
    
	FixtureDef *fix = so->fixtures;
    
    if (fix->fixture.shape->GetType() == b2Shape::Type::e_circle) {
        auto  shapeData = _circleObjects[shape];
       
        
        b2CircleShape *circleshape = new b2CircleShape();

        circleshape->m_radius = shapeData.radis * scale/2.0; //shape->m_radius;
        circleshape->m_p =  b2Vec2(shapeData.point.x *scale, shapeData.point.y *scale);
        
        
        fix->fixture.shape = circleshape;
        fix->fixture.density = 10.0;
        fix->fixture.isSensor = true;
        body->CreateFixture(&fix->fixture);

    }
    else{
        while (fix) {
            b2Vec2 vertices[b2_maxPolygonVertices];
            //int idx_num = 0;
            if (ShapeVertexData_vec.size()>index) {
                auto shapeVertexData = ShapeVertexData_vec.at(index);
                auto points = shapeVertexData.vertices;
                auto idx_num = shapeVertexData.idx;
                
                for(int i=0;i<idx_num;i++){
                    vertices[i].x = points[i].x*scale;
                    vertices[i].y = points[i].y*scale;
                }
                
                b2PolygonShape *polyshape = new b2PolygonShape();
                polyshape->Set(vertices, idx_num);
                //fix->fixture.filter.categoryBits = 0x0002;
                //fix->fixture.filter.maskBits = 0x0004;
                fix->fixture.shape = polyshape;
                fix->fixture.density = 10.0;
                fix->fixture.isSensor = true;
                body->CreateFixture(&fix->fixture);
                fix = fix->next;
                
                index++;
            }
            
            
        }
        
    }
    
    
    
}

BodyDef* GB2ShapeCache::GetBodyDef(const std::string &skey){
    return nullptr;
}
BodyDef* GB2ShapeCache::GetBodyDefWithScale(const std::string &skey, float scale){
    return nullptr;
}

cocos2d::CCPoint GB2ShapeCache::anchorPointForShape(const std::string &shape) {
	std::map<std::string, BodyDef *>::iterator pos = shapeObjects.find(shape);
	assert(pos != shapeObjects.end());

	BodyDef *bd = (*pos).second;
	return bd->anchorPoint;
}

typedef std::unordered_map<std::string, Value> ObjectDict;

void GB2ShapeCache::addShapesWithFile(const std::string &plist) {
    
    auto fullName = cocos2d::FileUtils::getInstance()->fullPathForFilename(plist); //cocos2d::FileUtils::fullPathFromRelativePath(plist.c_str());
	ObjectDict dict = FileUtils::getInstance()->getValueMapFromFile(fullName);
//	CCAssert(dict.isNull() != false, "Shape-file not found"); // not triggered - cocos2dx delivers empty dict if non was found
    CCAssert(dict.size() != 0, "plist file empty or not existing");

	ObjectDict metadataDict = dict["metadata"].asValueMap();//(ObjectDict *)dict.objectForKey("metadata");
    int format = (metadataDict["format"]).asInt(); //static_cast<CCString *>(metadataDict->objectForKey("format"))->toInt();
    if ((metadataDict["ptm_ratio"]).isNull() ) {
        ptmRatio = 32;
    }
    else{
        ptmRatio = (metadataDict["ptm_ratio"]).asFloat();
    }
	CCAssert(format == 1, "Format not supported");

	ObjectDict bodyDict = dict["bodies"].asValueMap();//(ObjectDict *)dict->objectForKey("bodies");

    b2Vec2 vertices[b2_maxPolygonVertices];
    
    

	//ObjectDict::CCObjectMapIter iter;
    std::string bodyName;
    std::vector<ShapeVertexData> shapeVerterDataVector;
    
    ShapeCircleData shapeCircleData;
    
   
    
    for (auto iter = bodyDict.begin(); iter!= bodyDict.end(); iter++) {
        bodyName = iter->first;
        ObjectDict bodyData = (iter->second).asValueMap();
        BodyDef *bodyDef = new BodyDef();
        bodyDef->anchorPoint = PointFromString((bodyData["anchorpoint"]).asString().c_str());//  static_cast<CCString *>(bodyData->objectForKey("anchorpoint"))->toStdString().c_str());
        ValueVector fixtureList = (bodyData["fixtures"]).asValueVector();
       // CCMutableArray<ObjectDict *> *fixtureList = (CCMutableArray<ObjectDict *> *)(bodyData->objectForKey("fixtures"));
        FixtureDef **nextFixtureDef = &(bodyDef->fixtures);
        
        
        
        
        
        
        for (auto iter_ = fixtureList.begin(); iter_ != fixtureList.end(); iter_++) {
            
            ShapeVertexData shapeVertexData;
          //  std::vector<std::vector<b2Vec2>> points ;
           // std::vector<int> idx ;
            
            b2FixtureDef basicData;
            ObjectDict fixtureData = (*iter_).asValueMap();
            
            basicData.filter.categoryBits = (fixtureData["category_mask"]).asInt();// static_cast<CCString *>(fixtureData->objectForKey("filter_categoryBits"))->toInt();
            basicData.filter.maskBits = (fixtureData["collision_mask"]).asInt(); //static_cast<CCString *>(fixtureData->objectForKey("filter_maskBits"))->toInt();
          //  basicData.filter.groupIndex = (fixtureData["filter_groupIndex"]).asInt();//static_cast<CCString *>(fixtureData->objectForKey("filter_groupIndex"))->toInt();
          //  basicData.friction = (fixtureData["friction"]).asInt(); //static_cast<CCString *>(fixtureData->objectForKey("friction"))->toFloat();
            basicData.density = (fixtureData["density"]).asInt();//static_cast<CCString *>(fixtureData->objectForKey("density"))->toFloat();
           // basicData.restitution = (fixtureData["restitution"]).asInt();//static_cast<CCString *>(fixtureData->objectForKey("restitution"))->toFloat();
            basicData.isSensor = (fixtureData["isSensor"]).asInt();//(bool)static_cast<CCString *>(fixtureData->objectForKey("isSensor"))->toInt();
            
            Value cb = fixtureData["userdataCbValue"];
            //CCString *cb = static_cast<CCString *>(fixtureData->objectForKey("userdataCbValue"));
            
            int callbackData = 0;
            
            if (cb.isNull())
                callbackData = cb.asInt();
            
            std::string fixtureType = fixtureData["fixture_type"].asString();// static_cast<CCString *>(fixtureData->objectForKey("fixture_type"))->toStdString();
           
            if (fixtureType == "POLYGON") {
                ValueVector polygonsArray = fixtureData["polygons"].asValueVector();
                //CCMutableArray<ObjectDict *> *polygonsArray = (CCMutableArray<ObjectDict *> *)(fixtureData->objectForKey("polygons"));
                
                for (auto iter = polygonsArray.begin(); iter!=polygonsArray.end(); iter++) {
                    FixtureDef *fix = new FixtureDef();
                    fix->fixture = basicData; // copy basic data
                    fix->callbackData = callbackData;
                    
                    b2PolygonShape *polyshape = new b2PolygonShape();
                    int vindex = 0;
                    
                    ValueVector polygonArray = (*iter).asValueVector();
                    
                   // CCMutableArray<CCString *> *polygonArray = (CCMutableArray<CCString *> *)(*iter);
                    
                    assert(polygonArray.size() <= b2_maxPolygonVertices);
                    
                    std::vector<b2Vec2> vector_p;
                    for(auto piter = polygonArray.begin();piter != polygonArray.end();piter++){
                        Point offset = PointFromString((*piter).asString());
                        vertices[vindex].x = (offset.x / ptmRatio) ;
                        vertices[vindex].y = (offset.y / ptmRatio) ;
                        vector_p.push_back(b2Vec2(vertices[vindex].x, vertices[vindex].y));
                        vindex++;
                        

                    }
                    //points.push_back(vector_p);
                    //idx.push_back(vindex);
                    
                    shapeVertexData.vertices = vector_p;
                    shapeVertexData.idx = vindex;
                    
                    shapeVerterDataVector.push_back(shapeVertexData);
                    
                    
                    polyshape->Set(vertices, vindex);
                    
                    
                    fix->fixture.shape = polyshape;
                    
                    
                    
                    // create a list
                    *nextFixtureDef = fix;
                    nextFixtureDef = &(fix->next);

                }
                
            } else if (fixtureType == "CIRCLE") {
                FixtureDef *fix = new FixtureDef();
                fix->fixture = basicData; // copy basic data
                fix->callbackData = callbackData;
                
                ObjectDict circleData = fixtureData["circle"].asValueMap();// (ObjectDict )fixtureData->objectForKey("circle");
                
                b2CircleShape *circleShape = new b2CircleShape();
                
                circleShape->m_radius = circleData["radius"].asFloat() / ptmRatio;//static_cast<CCString *>(circleData->objectForKey("radius"))->toFloat() / ptmRatio;
                Point p = PointFromString((circleData["position"]).asString());//CCPointFromString(static_cast<CCString *>(circleData->objectForKey("position"))->toStdString().c_str());
                
                
                
                circleShape->m_p = b2Vec2(p.x / ptmRatio, p.y / ptmRatio);
                fix->fixture.shape = circleShape;
                
                shapeCircleData.radis =  circleShape->m_radius;
                shapeCircleData.point = circleShape->m_p;
                
                // create a list
                *nextFixtureDef = fix;
                nextFixtureDef = &(fix->next);
                
            } else {
                CCAssert(0, "Unknown fixtureType");
            }
            
            
            
        }
        // add the body element to the hash
        //_idx[bodyName] = idx;
        _shapeVertexData[bodyName] = shapeVerterDataVector;
        _circleObjects[bodyName] = shapeCircleData;
        shapeObjects[bodyName] = bodyDef;
    
	}
}
