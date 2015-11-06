#include "environm.h"

namespace soccerData
{



	class SoccerData{
	public:
		float ball_distance;
		float ball_angle;
		float target_angle;
		float obstacle_distance;
		float spin;
		float last_left_motor;
		float last_right_motor;
		float actual_left_motor;
		float actual_right_motor;
		void generate_neural_data();
		void generate(environm::soccer::clientEnvironm environment);
	};


};
