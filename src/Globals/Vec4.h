#pragma once

struct Vec4
{
public:
    float x;
    float y;
    float z;
    float w;
    
    Vec4()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }
    Vec4(float newX)
    {
        x = newX;
        y = 0.0f;
        z = 0.0f;
        w = 0.0f;
    }
    Vec4(float newX,float newY)
    {
        x = newX;
        y = newY;
        z = 0.0f;
        w = 0.0f;
    }
    Vec4(float newX,float newY,float newZ)
    {
        x = newX;
        y = newY;
        z = newZ;
        w = 0.0f;
    }
    Vec4(float newX,float newY,float newZ , float newW)
    {
        x = newX;
        y = newY;
        z = newZ;
        w = newW;
    }
    Vec4(Vec4& newVec)
    {
        x = newVec.x;
        y = newVec.y;
        z = newVec.z;
        w = newVec.w;
    }
};