#include <iostream>
#include <cstdlib>
#include <exception>

#include "Application.hpp"

int main(int argc, char** argv)
{
	try {
		Application app;
		app.start();
	} catch (std::exception& ex) {
		std::cout << "Application Exception: " << ex.what() << std::endl;
	}

    return EXIT_SUCCESS;
} // main