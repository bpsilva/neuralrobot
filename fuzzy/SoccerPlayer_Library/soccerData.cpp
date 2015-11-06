#include "soccerData.h"



namespace soccerdata
{

	void SoccerData::generate_neural_data(SoccerData data)
	{
	
    ofstream myfile;
  	myfile.open ("log", ios::ate | ios::app);
	myfile << data.ball_distance<<" "<< data.ball_angle<<" "<< data.target_angle<<" "<< data.obstacle_distance<<" "<< data.spin<<" "<< data.last_left_motor<<" "<< data.last_right_motor<<" "<< data.actual_left_motor<<" "<< data.actual_right_motor << endl;
	myfile.close();
	}
	
	void SoccerData::generate(environm::soccer::clientEnvironm environment)
	{
		SoccerData data;


		data.ball_distance = environment.getDistance();
		data.ball_angle = environment.getBallAngle();
		data.target_angle = environment.getTargetAngle();
		data.obstacle_distance = environment.getObstacleDistance();
		data.spin = environment.getSpin();
		data.last_left_motor = environment.getLastLeftMotor();
		data.last_right_motor = environment.getLastRightMotor();
		data.actual_left_motor = environment.getActualLeftMotor();
		data.actual_right_motor environment.getActualRightMotor();
	}

}