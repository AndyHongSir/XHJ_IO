//
//  CustomContactListener.hpp
//  Syn
//
//  Created by Andy Hong on 2016/12/12.
//
//

#ifndef CustomContactListener_hpp
#define CustomContactListener_hpp

#include "Box2D/Box2D.h"
#include <vector>
#include <algorithm>

struct MyContact {
    b2Fixture *fixtureA;
    b2Fixture *fixtureB;
    bool operator==(const MyContact& other) const
    {
        return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
    }
};

class MyContactListener : public b2ContactListener {
    
public:
    std::vector<MyContact>_contacts;
    
    MyContactListener();
    ~MyContactListener();
    
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
};

#endif /* CustomContactListener_hpp */
