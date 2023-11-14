struct Vec3
{
public:
    float x;
    float y;
    float z;

    Vec3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

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

    Vec3(glm::vec3& newVec)
    {
        x = newVec.x;
        y = newVec.y;
        z = newVec.z;
    }

    Vec3(glm::vec3 newVec)
    {
        x = newVec.x;
        y = newVec.y;
        z = newVec.z;
    }

    
};
