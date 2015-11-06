#include "fis.h"

namespace fis
{
	void Fis::fuzzify(float ballAngle, float targetAngle, float ballDistance)
	{
			ballSet[LEFT] 			= getBallSetLeft(ballAngle);
			ballSet[FRONT] 			= getBallSetFront(ballAngle);
			ballSet[RIGHT] 			= getBallSetRight(ballAngle);

			targetSet[LEFT] 		= getTargetSetLeft(targetAngle);
			targetSet[FRONT] 		= getTargetSetFront(targetAngle);
			targetSet[RIGHT] 		= getTargetSetRight(targetAngle);

			distanceSet[CLOSE] 	= getDistanceSetClose(ballDistance);
			distanceSet[MEDIUM] = getDistanceSetMedium(ballDistance);
			distanceSet[FAR] 		= getDistanceSetFar(ballDistance);
	}

	float Fis::min(float a, float b)
	{
		return ((a < b) ? a : b);
	}

	float Fis::max(float a, float b, float c)
	{
		float max_ab = ((a > b) ? a : b);
		return ((c > max_ab) ? c : max_ab);
	}

	void Fis::infer()
	{
		for(int i = 0 ; i < 3 ; i++)
		{
			for(int j = 0 ; j < 3 ; j++)
			{
				for(int k = 0 ; k < 3 ; k++)
				{
					rules[i][j][k] = min(min(ballSet[i] , targetSet[j]), distanceSet[k]);
				}
			}
		}

		float distanceCut[3][3];

		distanceCut[0][0] = max(rules[0][0][1], rules[0][0][2], rules[0][1][2]);
		distanceCut[0][1] = max(rules[0][0][0], rules[0][1][1], rules[0][2][2]);
		distanceCut[0][2] = max(rules[0][1][0], rules[0][2][0], rules[0][2][1]);

		distanceCut[1][0] = max(rules[1][0][1], rules[1][0][2], rules[1][1][2]);
		distanceCut[1][1] = max(rules[1][0][0], rules[1][1][1], rules[1][2][2]);
		distanceCut[1][2] = max(rules[1][1][0], rules[1][2][0], rules[1][2][1]);

		distanceCut[2][0] = max(rules[2][0][1], rules[2][0][2], rules[2][1][2]);
		distanceCut[2][1] = max(rules[2][0][0], rules[2][1][1], rules[2][2][2]);
		distanceCut[2][2] = max(rules[2][1][0], rules[2][2][0], rules[2][2][1]);

		cut[0] = max(distanceCut[0][1], distanceCut[0][2], distanceCut[1][2]);
		cut[1] = max(distanceCut[0][0], distanceCut[1][1], distanceCut[2][2]);
		cut[2] = max(distanceCut[1][0], distanceCut[2][0], distanceCut[2][1]);
	}

	void Fis::defuzzify()
	{
		int steps = ((180-(-180))/STEPSIZE) + 1;
		float left[steps], front[steps], right[steps];
		float unionSet[steps];
		float angle;

		for(int i = 0 ; i < steps ; i++)
		{
			angle = -180 + (i * STEPSIZE);

			left[i]  = min(getOutputSetLeft(angle), cut[0]);
			front[i] = min(getOutputSetFront(angle), cut[1]);
			right[i] = min(getOutputSetRight(angle), cut[2]);

			unionSet[i] = max(left[i], front[i], right[i]);
		}


		float ac = 0.0f;
		float d = 0.0f;

		for(int i = 0 ; i < steps ; i++)
		{
			ac += unionSet[i] * (-180.0f + (float) (i * STEPSIZE));
			d += unionSet[i];
		}

		float centroid = ac/d;

		setMotorValues(centroid);
	}

	void Fis::setMotorValues(float centroid)
	{
		centroid = centroid*(M_PI/180);
		std::cout << "centroid: " << centroid << std::endl;

		leftMotor  = (cos(centroid) - sin(centroid))/2.5;
    rightMotor = (cos(centroid) + sin(centroid))/2.5;
	}

	float Fis::getRightMotor()
	{
		return rightMotor;
	}

	float Fis::getLeftMotor()
	{
		return leftMotor;
	}

	float Fis::getBallSetLeft(float ballAngle)
	{
		return getTriangleValue(ballAngle, -190.0f, -180.0f, 0.0f);
	}

	float Fis::getBallSetFront(float ballAngle)
	{
		return getTriangleValue(ballAngle, -90.0f, 0.0f, 90.0f);
	}

	float Fis::getBallSetRight(float ballAngle)
	{
		return getTriangleValue(ballAngle, 0.0f, 180.0f, 190.0f);
	}

	float Fis::getTargetSetLeft(float targetAngle)
	{
		return getTriangleValue(targetAngle, -190.0f, -180.0f, 0.0f);
	}

	float Fis::getTargetSetFront(float targetAngle)
	{
		return getTriangleValue(targetAngle, -90.0f, 0.0f, 90.0f);
	}

	float Fis::getTargetSetRight(float targetAngle)
	{
		return getTriangleValue(targetAngle, 0.0f, 180.0f, 190.0f);
	}

	float Fis::getDistanceSetClose(float ballDistance)
	{
		return getTriangleValue(ballDistance, 0.0f, 50.0f, 50.0f);
	}

	float Fis::getDistanceSetMedium(float ballDistance)
	{
		return getTriangleValue(ballDistance, 50.0f, 1000.0f, 1000.0f);
	}

	float Fis::getDistanceSetFar(float ballDistance)
	{
		return getTriangleValue(ballDistance, 1000.0f, 4000.0f, 4000.0f);
	}

	float Fis::getOutputSetLeft(float angle)
	{
		return getTriangleValue(angle, -190.0f, -180.0f, 0.0f);
	}

	float Fis::getOutputSetFront(float angle)
	{
		return getTriangleValue(angle, -90.0f, 0.0f, 90.0f);
	}

	float Fis::getOutputSetRight(float angle)
	{
		return getTriangleValue(angle, 0.0f, 180.0f, 190.0f);
	}

	float Fis::getTriangleValue(float input, float alpha, float beta, float gamma)
	{
		if (input <= alpha || input >= gamma)
			return 0;

		if (input >= alpha && input <= beta)
			return ((input - alpha)/(beta - alpha));

		if (input > beta && input < gamma)
			return ((gamma - input)/(gamma - beta));


		return 0.0;
	}
};
