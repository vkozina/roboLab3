#pragma config(Sensor, S3,     lightSensor,    sensorLightActive)
#pragma config(Motor,  motorA,          rightWheel,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftWheel,     tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define COUNT_THRESHOLD 200
#define COUNT_R 800

task main()
{
	wait1Msec(50);                        // The program waits 50 milliseconds to initialize the light sensor.

	int counter = 0;
	bool onLine = SensorValue(lightSensor) < 55;

	bPlaySounds = true;

	while(true)                           // Infinite loop
	{
		nxtDisplayTextLine(3, "Counter: %d", counter);
		nxtDisplayTextLine(4, "onLine: %d", onLine);

		if (SensorValue(lightSensor) < 55)
		{
			// We are INSIDE the line
			if (!onLine)
			{
				// if we were outside the line before, reset the counter
				counter = 0;
				onLine = true;
			}

			if (counter > COUNT_THRESHOLD)
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
				motor[rightWheel] = 40;
				motor[leftWheel] = 10;
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

			if (counter > COUNT_R)
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
				motor[rightWheel] = 10;
				motor[leftWheel] = 40;
				counter++;
			}
		}
	}
}
