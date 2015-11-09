target: all

all: 
	g++ SoccerPlayer_Library/fis.cpp SoccerPlayer_Library/principal.cpp SoccerPlayer_Library/sock.cpp SoccerPlayer_Library/stlfn.c SoccerPlayer_Library/environm.cpp -I./ -o SoccerPlayer -Wall

test: 
	g++ SoccerPlayer_Library/fis.cpp SoccerPlayer_Library/fis_test.cpp -I./ -o SoccerPlayerTest

clean: 
	rm SoccerPlayer
	rm SoccerPlayerTest
