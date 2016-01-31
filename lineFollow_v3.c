#pragma config(Sensor, S3,     lightSensor,    sensorLightActive)
#pragma config(Motor,  motorA,          rightWheel,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftWheel,     tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define COUNT_MAX_L 200
#define COUNT_MAX_R 1000


#define MAX_L_POWER
#define MIN_L_POWER
#define MAX_R_POWER
#define MIN_R_POWER

task main()
{
	wait1Msec(50);                        // The program waits 50 milliseconds to initialize the light sensor.

	int counter = 0;
	bool onLine = SensorValue(lightSensor) < 45;

	bPlaySounds = true;

	while(true)                           // Infinite loop
	{
		nxtDisplayTextLine(3, "Counter: %d", counter);
		nxtDisplayTextLine(4, "onLine: %d", onLine);

		if (SensorValue(lightSensor) < 45)
		{
			// We are INSIDE the line
			if (!onLine)
			{
				// if we were outside the line before, reset the counter
				counter = 0;
				onLine = true;
			}




			if (counter > COUNT_MAX_L)
			{
				if (!bSoundActive)
				{
					playSound(soundBlip);
				}
				// If we have been going left for too long
				motor[rightWheel] = 30;
				motor[leftWheel] = -30;
			}
			else
			{
				// slight left
				motor[rightWheel] = 30;
				motor[leftWheel] = 20 - (counter * counter) / 20000;
				counter++;
			}

		}
		else
		{
			// We are OUTSIDE the line
			if (onLine)
			{
				// if we were inside the line before, reset the counter
				counter = 0;
				onLine = false;
			}

			if (counter > COUNT_MAX_R)
			{
				if (!bSoundActive)
				{
					playSound(soundBlip);
				}
				// if we have been going right for too long
				motor[rightWheel] = -30;
				motor[leftWheel] = 30;
			}
			else
			{
				// slight right
				motor[rightWheel] = 20 - (counter * counter) / 10;
				motor[leftWheel] = 30;
				counter++;
			}
		}
	}
}