FLAGS=-O2

CXX=g++

RM=rm -f

EXEC=raytracer

all: $(EXEC)

$(EXEC):
	$(CXX) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o -fopenmp
	$(CXX) $(FLAGS) $(EXEC).o -o $(EXEC) -fopenmp

clean:
	$(RM) $(EXEC).o $(EXEC)
