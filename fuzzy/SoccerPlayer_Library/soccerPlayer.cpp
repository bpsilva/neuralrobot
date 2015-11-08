//------------------------------------------------------------------------------
#define _USE_MATH_DEFINES

// Inclusão da biblioteca que implementa a interface com o SoccerMatch.
#include "environm.h"
#include "fis.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>   

using namespace fis;
using namespace environm;
using namespace std;


float getBallAngle(point<float> ball, robotBox r) {
   	float alpha;

    alpha = (ball - r.pos ).angle() - r.angle;
    if ( alpha > M_PI ) {
        alpha -= 2 * M_PI;
    }
    else
    if ( alpha < -M_PI ) {
        alpha += 2 * M_PI;
    }

    return alpha;
}

float getObstacleAngle(robotBox r) {

    float gamma;

    gamma = ( r.obstacle -r.pos ).angle() - r.angle;
    if ( gamma > M_PI ) {
        gamma -= 2 * M_PI;
    }
    else
    if ( gamma < -M_PI ) {
        gamma += 2 * M_PI;
    }

    return gamma;
}

float getSpin(robotBox r) {

    float   spin;

    spin = ( r.angle - r.oldAngle );
    if ( spin > M_PI ) {
        spin -= 2 * M_PI;
    }
    if ( spin < -M_PI ) {
        spin += 2 * M_PI;
    }

    return spin;
}

float getTargetAngle(robotBox r, point<float> ball, point<float> pos) {
    float beta;

    beta = ( pos - ball ).angle() - ( ball - r.pos ).angle();
    if ( beta > M_PI ) {
        beta -= 2 * M_PI;
    }
    else
    if ( beta < -M_PI ) {
        beta += 2 * M_PI;
    }

    return beta;
}

int main( int argc, char* argv[] ) {

    float ballAngle, targetAngle, ballDistance;

    // Declaração do objeto que representa o ambiente.
    environm::soccer::clientEnvironm environment;

    if ( argc != 3 ) {
        printf( "\nInvalid parameters. Expecting:" );
        printf( "\nSoccerPlayer SERVER_ADDRESS_STRING SERVER_PORT_NUMBER\n" );
        printf( "\nSoccerPlayer localhost 1024\n" );
        return 0;
    }

    // Conecta-se ao SoccerMatch. Supõe que SoccerMatch está rodando na máquina
    // local e que um dos robôs esteja na porta 1024. Porta e local podem mudar.
    if ( ! environment.connect( argv[1], atoi( argv[2] ) ) ) {
        printf( "\nFail connecting to the SoccerMatch.\n" );
        return 0;  // Cancela operação se não conseguiu conectar-se.
    }

    // Laço de execução de ações.
    printf( "\nRunning..." );

	// float ball_distance_n;
	// float ball_angle_n;
	// float target_angle_n;
	// float obstacle_distance_n;
	// float obstacle_angle_n;
	// float spin_n;
	// float last_left_motor_n;
	// float last_right_motor_n;
	// float actual_left_motor_n;
	// float actual_right_motor_n;

    Fis f;
    robotBox r2;
    point<float> ball;

    float lastLeftMotorR1 = 0.0f;
    float lastRightMotorR1 = 0.0f;

    float lastLeftMotorR2 = 0.0f;
    float lastRightMotorR2 = 0.0f;

    stringstream bufferR1;
    stringstream bufferR2;

    int i = 0;
    int currentScoreR1 = 0;
    int currentScoreR2 = 0;

    ofstream myfileR1;
    ofstream myfileR2;
    myfileR1.open ("outRobot1", ios::ate | ios::app);
    myfileR2.open ("outRobot2", ios::ate | ios::app);

    while ( 1 ) {
        // Deve obter os dados desejados do ambiente. Métodos do clientEnvironm.
        // Exemplos de métodos que podem ser utilizados.
        r2 = environment.getRivalRobot();
    	ball = environment.getBall();

        ballAngle = environment.getBallAngle();
        targetAngle = environment.getTargetAngle( environment.getOwnGoal() );
        ballDistance = environment.getDistance();

        f.fuzzify(ballAngle * (180/M_PI), targetAngle * (180/M_PI), ballDistance);
        f.infer();
        f.defuzzify();

        //std::cout<< "left : " << f.getLeftMotor() << " right: " << f.getRightMotor()<<"\n";

        // Transmite ação do robô ao ambiente. Fica bloqueado até que todos os
        // robôs joguem. Se erro, retorna false (neste exemplo, sai do laco).
        if (!environment.act(f.getLeftMotor(), f.getRightMotor())) {
            break; // Termina a execução se falha ao agir.
        }

        bufferR1 << environment.getDistance()		                    	<< " "
               	 << environment.getBallAngle()                           	<< " "
               	 << environment.getTargetAngle(environment.getOwnGoal()) 	<< " "
               	 << environment.getCollision()                           	<< " "
               	 << environment.getObstacleAngle()                       	<< " "
               	 << environment.getSpin()			                    	<< " "
               	 << lastLeftMotorR1		                                	<< " "
               	 << lastRightMotorR1                                       	<< " "
               	 << f.getLeftMotor()	                                    << " "
               	 << f.getRightMotor()	                                	<< endl;

        bufferR2 << (ball - r2.pos).size() - environment.getRobotRadius() 			<< " "
               	 << getBallAngle(ball, r2) 											<< " "
               	 << getTargetAngle(r2, ball, environment.getRivalGoal()) 			<< " "
               	 << (r2.obstacle - r2.pos).size() - environment.getRobotRadius()    << " "
               	 << getObstacleAngle(r2)          			             			<< " "
               	 << getSpin(r2)						                    			<< " "
               	 << lastLeftMotorR2		                                			<< " "
               	 << lastRightMotorR2                                       			<< " "
               	 << r2.force[0]	                                   					<< " "
               	 << r2.force[1]	                                					<< endl;

        if (currentScoreR1 < environment.getOwnScore()) {		// if our guy scored
    		currentScoreR1 = environment.getOwnScore();		// updates the score

    		myfileR1 << bufferR1.str();							// writes his movements
    		bufferR1.str(std::string());						// flushes the buffer
    		bufferR2.str(std::string());
    		i = 0;												// resets counter
        }

        if (currentScoreR2 < environment.getRivalScore()) {		// if our guy scored
    		currentScoreR2 = environment.getRivalScore();		// updates the score

    		myfileR2 << bufferR2.str();							// writes his movements
    		bufferR2.str(std::string());						// flushes the buffer
    		bufferR1.str(std::string());
    		i = 0;												// resets counter
        }

	    if (i >= 4999) {										// if both guy stay 5000 steps whithout scoring
	    	bufferR1.str(std::string());						// flushes the buffer and breaks, cause something is wrong
	    	bufferR2.str(std::string());
	    	break;
	    }

        lastLeftMotorR1 = f.getLeftMotor();
        lastRightMotorR1 = f.getRightMotor();
        lastLeftMotorR2 = r2.force[0];
        lastRightMotorR2 = r2.force[1];
        i++;
    }

    myfileR1.close();
    myfileR2.close();

    return 0;
}




//------------------------------------------------------------------------------
