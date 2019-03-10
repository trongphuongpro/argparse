#include <iostream>
#include <locale>
#include <algorithm>
#include "argparse.h"

using namespace std;

ArgumentParser::ArgumentParser(int _argc, char** _argv) {
	argc = _argc;
	argv = _argv;
	argOrder = 1;
	argsNum = 0;

	// pre-process usage string, keywordArgsInfo vector and unrecognizedArgID vector
	usage = "usage: " + string(argv[0]).substr(2, string(argv[0]).size()-2) + " [-h] ";
	keywordArgsInfo.push_back(" -h/--help\n\t\t\t==> show this help message and exit");

	for (int i = 1; i < argc; i++)
		unrecognizedArgID.push_back(i);
}


void ArgumentParser::add_argument(string argName, string accessName, string helpMsg) {

	addInfo(argName, accessName, helpMsg);

	// if this is non-keyword argument
	if (argName[0] != '-') {
		addNonKeywordArg(argName);
	}
	else {
		addKeywordArg(argName, accessName);
	}
}


void ArgumentParser::addInfo(string argName, string accessName, string helpMsg) {
	// if this is keyword argument
	if (argName[0] == '-') {
		keywordArgsInfo.push_back(	' ' + argName + " [" + accessName.substr(2, accessName.size()-2) + "], " +
									accessName + " [" + accessName.substr(2, accessName.size()-2) + "]\n\t\t\t" +
									"==> " + helpMsg);

		usage += ' ' + argName + " <" + accessName.substr(2, accessName.size()-2) + "> ";
	}
	else {
		nonKeywordArgsInfo.push_back(' ' + argName + "\n\t\t\t" + "==> " + helpMsg);

		usage += " <" + argName + "> ";
	}
}


void ArgumentParser::addNonKeywordArg(string argName) {
	argsNum++;
	nonKeywordArgs.push_back(argName);
}


void ArgumentParser::addKeywordArg(string argName, string accessName) {
	argsNum += 2;

	vector<string> v;
	v.push_back(argName);
	v.push_back(accessName);

	keywordArgs.push_back(v);
}


map<string, string> ArgumentParser::parse_args() {
	checkHelpCommand();
	parseKeywordArgs();
	parseNonKeywordArgs();
	checkValidArgs();

	return argumentMap;
}


void ArgumentParser::checkHelpCommand() {
	// if no argument is given
	if (argc == 1) {
		printUsage();
		exit(0);
	}

	for (uint8_t i = 1; i < argc; i++) {
		if (argv[i] == string("-h") || argv[i] == string("--help")) {
			printUsage();
			printArgsList();
			exit(0);
		}
	}

}


void ArgumentParser::printUsage() {
	cout << usage << '\n' << endl;
}


void ArgumentParser::printArgsList() {
	cout << ">> non-keyword argument(s):" << endl;
	for (const auto& e : nonKeywordArgsInfo)
		cout << e << endl;

	cout << "\n>> keyword argument(s):" << endl;
	for (const auto& e : keywordArgsInfo)
		cout << e << endl;
}


void ArgumentParser::checkValidArgs() {
	if (argsNum < argc-1) {
		cout << "Error: too many arguments, accept " << argsNum << " but " << argc-1 << " were given." << endl;
		cout << "Error: unrecognized argument(s): ";

		for (int i = 0; i < argc-1-argsNum; i++)
			cout << argv[unrecognizedArgID[i]] << " ";
		cout << endl;

		exit(1);
	}
}


void ArgumentParser::parseNonKeywordArgs() {
	for (const auto& argName : nonKeywordArgs) {
		for (argOrder; argOrder < argc; argOrder++) {
			if ((argv[argOrder-1][0] != '-') && (argv[argOrder][0] != '-')) {
				remove(unrecognizedArgID.begin(), unrecognizedArgID.end(), argOrder);
				argumentMap[argName] = argv[argOrder++];
				break;
			}
		}

		if (argumentMap[argName] == "") {
			cout << "Error: missing argument for [" + argName + "]" << endl;
			exit(1);
		}
	}
}


void ArgumentParser::parseKeywordArgs() {
	for (const auto& e : keywordArgs) {
		string argName = e[0];
		string accessName = e[1];
		string key = accessName.substr(2, accessName.size()-2);

		for (uint8_t i = 1; i < argc-1; i+=1) {
			if (argv[i] == argName || argv[i] == accessName) {
				if (argv[i+1][0] != '-') {
					argumentMap[key] = argv[i+1];
					remove(unrecognizedArgID.begin(), unrecognizedArgID.end(), i);
					remove(unrecognizedArgID.begin(), unrecognizedArgID.end(), i+1);
					break;
				}
			}
		}

		if (argumentMap[key] == "") {
			cout << "Error: missing argument for [" + argName + "/" + accessName + "]" << endl;
			exit(1);
		}
	}
}