# 2022 ICCAD contest problem A compiler
.PHONY: all clean

CFLAG = g++ -std=c++11 -g -c

SRC_DIR = ./
SRC     = $(wildcard $(SRC_DIR)*.cpp)
OBJ     = $(SRC:%.cpp=%.o)

all: $(OBJ)
	g++ $^

game_object.o: game_object.cpp game_object.h
	$(CFLAG) $<

building.o: building.cpp building.h game_object.h
	$(CFLAG) $<
human.o: human.cpp human.h game_object.h
	$(CFLAG) $<

barracks.o: barracks.cpp barracks.h building.h game_object.h
	$(CFLAG) $<
house.o: house.cpp house.h building.h game_object.h
	$(CFLAG) $<
farm.o: farm.cpp farm.h building.h game_object.h
	$(CFLAG) $<

villager.o: villager.cpp villager.h human.h game_object.h
	$(CFLAG) $<
soldier.o: soldier.cpp soldier.h human.h game_object.h
	$(CFLAG) $<

player.o: player.cpp player.h
	$(CFLAG) $<

main.o: main.cpp player.h
	$(CFLAG) $<

clean:
	del *.exe *.o *.gch