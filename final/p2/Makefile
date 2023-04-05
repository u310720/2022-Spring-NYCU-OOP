# 2022 ICCAD contest problem A compiler
.PHONY: all clean

CFLAG = g++ -std=c++11 -g -c

SRC_DIR = ./
SRC     = $(wildcard $(SRC_DIR)*.cpp)
OBJ     = $(SRC:%.cpp=%.o)

all: $(OBJ)
	g++ $^

food.o: food.cpp food.h
	$(CFLAG) $<
person.o: person.cpp person.h
	$(CFLAG) $<
basket.o: basket.cpp basket.h food.h
	$(CFLAG) $<
cashier.o: cashier.cpp cashier.h person.h customer.h
	$(CFLAG) $<
customer.o: customer.cpp customer.h person.h basket.h food.h cashier.h
	$(CFLAG) $<
shop.o: shop.cpp shop.h food.h cashier.h customer.h food.h
	$(CFLAG) $<
main.o: main.cpp shop.h
	$(CFLAG) $<

clean:
	del *.exe *.o *.gch