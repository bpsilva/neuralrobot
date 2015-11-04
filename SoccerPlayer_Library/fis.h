#ifndef FIS_H
#define FIS_H

#include <iostream>
#include "geom.hpp"
#include "environm.h"

#define LEFT 0
#define FRONT 1
#define RIGHT 2

#define CLOSE 0
#define MEDIUM 1
#define FAR 2

#define STEPSIZE 10

namespace fis	{

	using namespace std;
	using namespace geom;
	using namespace environm;
	using namespace soccer;

	class Fis {

		private:
			float ballSet[3]; // Left, Front, Right, in that order
			float targetSet[3]; // Left, Front, Right, in that order
			float distanceSet[3]; // Close, Medium, Far, in that order

			float cut[3];

			float rules[3][3][3];
			float leftMotor, rightMotor; //[-1 , +1]

		public:
			void setBallSet(float left, float front, float right);
			void setTargetSet(float left, float front, float right);
			void setDistanceSet(float close, float medium, float far);

			void fuzzify(float ballAngle, float targetAngle, float ballDistance);
			void infer();
			void defuzzify();

			float getLeftMotor();
			float getRightMotor();

		private:
			float getTriangleValue(float input, float alfa, float beta, float gama);

		protected:

			float getBallSetLeft(float ballAngle);
			float getBallSetFront(float ballAngle);
			float getBallSetRight(float ballAngle);

			float getTargetSetLeft(float targetAngle);
			float getTargetSetFront(float targetAngle);
			float getTargetSetRight(float targetAngle);

			float getDistanceSetClose(float ballDistance);
			float getDistanceSetMedium(float ballDistance);
			float getDistanceSetFar(float ballDistance);

			float getOutputSetLeft(float angle);
			float getOutputSetFront(float angle);
			float getOutputSetRight(float angle);

			float min(float a, float b);
			float max(float a, float b, float c);

			void setMotorValues(float centroid);
	};
};//end namespace fis

#endif
