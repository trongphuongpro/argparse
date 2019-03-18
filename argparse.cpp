#include <iostream>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include "argparse.h"

using namespace std;

ArgumentParser::ArgumentParser(int _argc, 
							   char** _argv, 
							   const string& _description) {
	argc = _argc;
	argv = _argv;
	description = _description;

	argOrder = 1;
	argsNum = 0;

	// pre-process usage string, optionalArgsInfo vector and unrecognizedArgID vector
	usage = "usage: " 
			+ string(argv[0]).substr(2, string(argv[0]).size()-2) 
			+ " [-h] ";

	optionalArgsInfo.push_back(" -h/--help"
							   "\n\t\t\t" 
							   "==> show this help message and exit");

	for (int i = 1; i < argc; i++)
		unrecognizedArgID.push_back(i);
}


// add positional argument
void ArgumentParser::add_argument(const string& argName, 
								  const string& helpMsg) {

	if (argName[0] != '-') {
		addPositionalArg(argName);
		addInfo(argName, helpMsg);
	}
	else {
		cout << "Error: positional argument [" 
				+ argName 
				+ "] can't contain -/-- symbol." 
			<< endl;

		exit(0);
	}
}


// add optional argument
void ArgumentParser::add_argument(const string& argName, 
								  const string& accessName, 
								  const string& defaultValue, 
								  const string& helpMsg) {

	if (argName[0] != '-' || accessName.substr(0,2) != "--") {
		cout << "Error: optional argument [" 
				+ argName + "/" 
				+ accessName 
				+ "] must contain -/-- symbol." 
			<< endl;

		exit(0);
	}
	else {
		addOptionalArg(argName, accessName, defaultValue);
		addInfo(argName, accessName, defaultValue, helpMsg);
	}
}


void ArgumentParser::addInfo(const string& argName, const string& helpMsg) {
	positionalArgsInfo.push_back(' ' + argName 
									 + "\n\t\t\t" 
									 + "==> " + helpMsg);

	usage += " <" + argName + "> ";
}

void ArgumentParser::addInfo(const string& argName, 
							 const string& accessName, 
							 const string& defaultValue, 
							 const string& helpMsg) {

	optionalArgsInfo.push_back(	
					' ' + argName 
					+ " [" 
					+ accessName.substr(2, accessName.size()-2) 
					+ "], " 
					+ accessName 
					+ " [" 
					+ accessName.substr(2, accessName.size()-2) 
					+ "], " 
					+ "default = " 
					+ defaultValue + "\n\t\t\t" + "==> " + helpMsg);

	usage += ' ' + argName 
				 + " <" + accessName.substr(2, accessName.size()-2) 
				 + "> ";
}


void ArgumentParser::addPositionalArg(const string& argName) {
	positionalArgs.push_back(argName);
}


void ArgumentParser::addOptionalArg(const string& argName, 
									const string& accessName, 
									const string& defaultValue) {

	vector<string> v;
	v.push_back(argName);
	v.push_back(accessName);
	v.push_back(defaultValue);

	optionalArgs.push_back(v);
}


void ArgumentParser::parse_args() {
	checkHelpCommand();
	parseOptionalArgs();
	parsePositionalArgs();
	checkValidArgs();
}


void ArgumentParser::checkHelpCommand() {
	
	for (uint8_t i = 1; i < argc; i++) {
		if (argv[i] == string("-h") || argv[i] == string("--help")) {
			printUsage();
			printArgsList();
			exit(0);
		}
	}

}


void ArgumentParser::printUsage() {
	usage += "\n\n\t" + description;
	cout << usage << '\n' << endl;
}


void ArgumentParser::printArgsList() {
	cout << ">> positional argument(s):" << endl;
	for (const auto& e : positionalArgsInfo)
		cout << e << endl;

	cout << "\n>> optional argument(s):" << endl;
	for (const auto& e : optionalArgsInfo)
		cout << e << endl;
}


void ArgumentParser::checkValidArgs() {
	if (argsNum < argc-1) {
		cout << "Error: unrecognized argument(s): ";

		for (int i = 0; i < argc-1-argsNum; i++)
			cout << argv[unrecognizedArgID[i]] << " ";
		cout << endl;

		exit(1);
	}
}


void ArgumentParser::parsePositionalArgs() {
	for (const auto& argName : positionalArgs) {
		argsNum++;

		for (argOrder; argOrder < argc; argOrder++) {
			if ((argv[argOrder-1][0] != '-') && (argv[argOrder][0] != '-')) {
				remove(unrecognizedArgID.begin(), 
					   unrecognizedArgID.end(), 
					   argOrder);
				argumentMap[argName] = argv[argOrder++];
				break;
			}
		}

		if (argumentMap[argName] == "") {
			cout << "Error: missing argument for [" 
					+ argName + "]" 
				<< endl;

			exit(1);
		}
	}
}


void ArgumentParser::parseOptionalArgs() {
	for (const auto& e : optionalArgs) {
		string argName = e[0];
		string accessName = e[1];
		string defaultValue = e[2];
		string key = accessName.substr(2, accessName.size()-2);

		uint8_t i;
		for (i = 1; i < argc; i+=1) {
			if (argv[i] == argName || argv[i] == accessName) {
				if (i < argc-1) {
					if (argv[i+1][0] != '-') {
						argumentMap[key] = argv[i+1];
						remove(unrecognizedArgID.begin(), 
							   unrecognizedArgID.end(), 
							   i);
						remove(unrecognizedArgID.begin(), 
							   unrecognizedArgID.end(), 
							   i+1);
						argsNum += 2;
						break;
					}
					else {
						cout << "Error: missing argument for [" 
								+ argName + "/" 
								+ accessName + "]" 
							<< endl;

						exit(1);
					}
				}
				else {
					cout << "Error: missing argument for [" 
							+ argName + "/" 
							+ accessName + "]" 
						<< endl;

					exit(1);
				}
			}
		}

		if (argumentMap[key] == "")
			argumentMap[key] = defaultValue;
	}
}

const string& ArgumentParser::get(const string& key) {
	try {
		return argumentMap.at(key);
	} catch (out_of_range& e) {
		cout << "Error: invalid key: " << key << e.what() << endl;
		exit(1);
	}
}

template<typename T>
T ArgumentParser::get(const string& key) {
	try {
		// cast to integer
		if (is_same<T, int>::value)
			return stoi(argumentMap.at(key));
		// cast to float
		if (is_same<T, float>::value)
			return stof(argumentMap.at(key));
	} 
	catch (out_of_range& e) {
		cout << "Error: invalid key: " << key << endl;
		exit(1);
	}
	catch (invalid_argument& e) {
		cout << "Error: couldn't convert \"" 
				+ argumentMap.at(key) 
				+ "\" to integer/float number." 
			<< endl;
			
		exit(1);
	}
}

template int ArgumentParser::get<int>(const string&);
template float ArgumentParser::get<float>(const string&);
