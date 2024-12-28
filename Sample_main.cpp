#include <iostream>
#include "BoardResponder.h"
#include "BoardSolver.h"

int main()
{
	bool launch_solver;

	std::cin >> launch_solver;
	std::cout << "Enter W, H, N, R: ";
	int W, H, N, R;
	scanf("%d %d %d %d", &W, &H, &N, &R);

	if (launch_solver)
	{
		std::cout << "Solver:\n";
		BoardSolver solver(W, H, N, R);
		solver.solve();
	}
	else
	{
		std::cout << "Responder:\n";
		BoardResponder responder(W, H, N, R);
		responder.respond();
	}
}