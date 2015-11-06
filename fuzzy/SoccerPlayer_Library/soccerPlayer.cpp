//------------------------------------------------------------------------------
#define _USE_MATH_DEFINES

// Inclusão da biblioteca que implementa a interface com o SoccerMatch.
#include "environm.h"
#include "fis.h"
#include "soccerData.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace fis;
using namespace soccerData;
using namespace std;


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

    Fis f;

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

    SoccerData sd;

    while ( 1 ) {




        // Deve obter os dados desejados do ambiente. Métodos do clientEnvironm.
        // Exemplos de métodos que podem ser utilizados.
        ballAngle = environment.getBallAngle();
        targetAngle = environment.getTargetAngle( environment.getOwnGoal() );
        ballDistance = environment.getDistance();

        f.fuzzify(ballAngle * (180/M_PI), targetAngle * (180/M_PI), ballDistance);
        f.infer();
        f.defuzzify();


        //std::cout<< "left : " << f.getLeftMotor() << " right: " << f.getRightMotor()<<"\n";

        // Transmite ação do robô ao ambiente. Fica bloqueado até que todos os
        // robôs joguem. Se erro, retorna false (neste exemplo, sai do laco).
        if ( ! environment.act( f.getLeftMotor(), f.getRightMotor() ) ) {
            break; // Termina a execução se falha ao agir.
        }
        
        sd.generate(environment);
          
        
    }


    return 0;
}




//------------------------------------------------------------------------------
