#pragma config(Sensor, S3,     lightSensor,    sensorLightActive)
#pragma config(Motor,  motorA,          rightWheel,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftWheel,     tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define LIGHT_THRESH 45

#define COUNT_MAX_L 100
#define COUNT_MAX_R 500

#define FWD_POWER 30


task main()
{
	wait1Msec(50);                        // The program waits 50 milliseconds to initialize the light sensor.

	int counter = 0;
	bool onLine = SensorValue(lightSensor) < LIGHT_THRESH;

	int rOffset = 0;

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
				motor[rightWheel] = 30;
				motor[leftWheel] = -30;

				// we just made massive left correction,
				rOffset = -20;
			}
			else
			{
				// (no so) slight left
				rOffset += 2;

				motor[rightWheel] = FWD_POWER + rOffset / 10;
				motor[leftWheel] = FWD_POWER - rOffset / 10;
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
				// we've been going slight right too long, make hard right correction
				motor[rightWheel] = -30;
				motor[leftWheel] = 30;

				rOffset = 10;
			}
			else
			{
				// slight right (decrease right wheel power)

				rOffset -= 1;


				motor[rightWheel] = FWD_POWER + rOffset / 10;
				motor[leftWheel] = FWD_POWER - rOffset / 10;

				counter++;
			}
		}
	}
}
