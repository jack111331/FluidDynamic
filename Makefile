main: fluid optimize

optimize: Optimization.o NavierStokes.o Density.o Velocity.o Solver.o
	g++ -Wall -o optimize $(CFLAGS) optimize.cpp Optimization.o NavierStokes.o Density.o Velocity.o Solver.o
fluid: fluid.cpp NavierStokes.o Density.o Velocity.o Shader.o Solver.o
	g++ -Wall -o fluid $(CFLAGS) fluid.cpp NavierStokes.o Density.o Velocity.o Solver.o Shader.o

	
NavierStokes.o: NavierStokes.cpp NavierStokes.h
	g++ -Wall -c NavierStokes.cpp

Density.o: Density.cpp Density.h
	g++ -Wall -c Density.cpp

Velocity.o: Velocity.cpp Velocity.h
	g++ -Wall -c Velocity.cpp

Solver.o: Solver.cpp Solver.h
	g++ -Wall -c Solver.cpp
	
Shader.o: Shader.cpp Shader.h
	g++ -Wall -c Shader.cpp

Optimization.o: Optimization.cpp Optimization.h
	g++ -Wall -c Optimization.cpp
	
CFLAGS = -lGL -lglfw -lGLEW
