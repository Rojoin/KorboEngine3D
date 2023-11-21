#pragma once


 static class Time
{

public:
 static double oldTime;
 static float timeSinceStart;
 static float currentTime;
 
 static float getDeltaTime();
 static void setTime();
 static float getTime();
};
