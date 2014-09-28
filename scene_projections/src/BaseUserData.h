//
//  BaseUserData.h
//  shissss
//
//  Created by Julien Bloit on 21/09/14.
//
//  A Generic class to hold user data stored in box2D bodies.
//  See the design pattern description at the bottom of this page :
//  http://www.iforce2d.net/b2dtut/collision-callbacks

#ifndef __shissss__BaseObjectData__
#define __shissss__BaseObjectData__

#include <iostream>


// Each body can store some user data as an arbitraty object.
// This is an enum for the possible objects:

class BaseUserData{

public:
    enum UserDataType {
            bounds = 0,
            blowpop_grain = 1,
            blowpop_nucleus = 2,
            blowpop_star = 3
    };
    
    UserDataType getType() const;
    UserDataType m_type;
};

inline BaseUserData::UserDataType BaseUserData::getType() const
{
	return m_type;
}


#endif /* defined(__shissss__BaseObjectData__) */
