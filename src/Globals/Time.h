#pragma once

static class Time
{

public:
 static double oldTime;
 static float timeSinceStart;
 
 static float getDeltaTime();
 static float getTime();
};
