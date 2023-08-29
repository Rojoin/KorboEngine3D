struct Vec3
{
public:
    float x;
    float y;
    float z;

    Vec3(float newX, float newY, float newZ)
    {
        x = newX;
        y = newY;
        z = newZ;
    }

    Vec3(Vec3& newVec)
    {
        x = newVec.x;
        y = newVec.y;
        z = newVec.z;
    }
};
