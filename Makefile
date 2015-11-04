target: all

all: 
	g++ SoccerPlayer_Library/fis.cpp SoccerPlayer_Library/soccerPlayer.cpp SoccerPlayer_Library/sock.cpp SoccerPlayer_Library/environm.cpp -I./ -o SoccerPlayer

test: 
	g++ SoccerPlayer_Library/fis.cpp SoccerPlayer_Library/fis_test.cpp -I./ -o SoccerPlayerTest

clean: 
	rm SoccerPlayer
	rm SoccerPlayerTest