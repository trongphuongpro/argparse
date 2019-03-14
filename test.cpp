#include <iostream>
#include <vector>
#include "argparse.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	ArgumentParser ap(argc, argv, "Demo program");

	ap.add_argument("program", "path to trainer");
	ap.add_argument("-i", "--image", "None", "path to image");
	ap.add_argument("-v", "--value", "0.01", "path to model");
	ap.add_argument("tester", "path to tester");
	ap.parse_args();

	cout << "image: " << ap.get("image") << endl;
	cout << "value: " << ap.get<int>("value") << endl;
	cout << "program: " << ap.get("program") << endl;
	cout << "tester: " << ap.get("tester") << endl;
	
	return 0;
}
