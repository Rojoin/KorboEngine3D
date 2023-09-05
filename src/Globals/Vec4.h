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
    Vec4(float x)
    {
        this.x = x;
        this.y = 0f;
        this.z = 0f;
        this.w = 0f;
    }
    Vec4(float x,float y)
    {
        this.x = x;
        this.y = y;
        this.z = 0f;
        this.w = 0f;
    }
    Vec4(float x,float y,float z)
    {
        this.x = x;
        this.y = y;
        this.z = z;
        this.w = 0f;
    }
    Vec4(float x,float y,float z , float w)
    {
        this.x = x;
        this.y = y;
        this.z = z;
        this.w = w;
    }
    Vec4(Vec4 newVec)
    {
        x = newVec.x;
        y = newVec.y;
        z = newVec.z;
        w = newVec.w;
    }
};
