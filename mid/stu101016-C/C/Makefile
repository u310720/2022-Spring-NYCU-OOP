q1: Seq.cpp main.cpp
	@g++ -oq1 -DPCQ1 Seq.cpp main.cpp
q2: Seq.cpp main.cpp
	@g++ -oq2 -DPCQ1 -DPCQ2 Seq.cpp main.cpp
q3: Seq.cpp main.cpp
	@g++ -oq3 -DPCQ1 -DPCQ2 -DPCQ3 Seq.cpp main.cpp
t1: q1 1.dat 2.dat
	@./q1 1.dat 2.dat
t2: q2 1.dat 2.dat Q2.in
	@./q2 1.dat 2.dat < Q2.in
t3: q3 1.dat 2.dat Q3.in
	@./q3 1.dat 2.dat < Q3.in
clean:
	rm -rf *.o q1 q2 q3
