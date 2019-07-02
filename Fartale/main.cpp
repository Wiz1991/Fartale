#include "Application.h"
#include  <exception>
#include <iostream>
int main() {
	try {
		Application app;
		app.run();
	}
	catch (std::exception& exception) {
		std::cout << "An error occured! " << exception.what() << std::endl;
	}
}