#ifndef GUARD_ARGPARSE_H
#define GUARD_ARGPARSE_H

#include <string>
#include <map>
#include <vector>


class ArgumentParser {
public:
	// Constructor
	ArgumentParser(int, 
				   char**, 
				   const std::string& = "");
	
	// Public methods
	void add_argument(const std::string&, 
					  const std::string&, 
					  const std::string&, 
					  const std::string&);
	void add_argument(const std::string&, 
					  const std::string&);
	void parse_args(void);
	const std::string& get(const std::string&);
	template<typename T>
	T get(const std::string&);


private:
	// Private variables
	int argc;
	char** argv;
	std::string description;
	uint8_t argOrder;
	int argsNum;
	std::map<std::string, std::string> argumentMap;
	std::vector<std::string> optionalArgsInfo;
	std::vector<std::string> positionalArgsInfo;
	std::string usage;
	std::vector<std::string> positionalArgs;
	std::vector<std::vector<std::string>> optionalArgs;
	std::vector<int> unrecognizedArgID;

	// Private methods
	void printArgsList(void);
	void printUsage(void);
	void checkHelpCommand(void);
	void checkValidArgs(void);
	void addInfo(const std::string&,
				 const std::string&);
	void addInfo(const std::string&, 
				 const std::string&, 
				 const std::string&, 
				 const std::string&);
	void addPositionalArg(const std::string&);
	void addOptionalArg(const std::string&, 
						const std::string&, 
						const std::string&);
	void parsePositionalArgs();
	void parseOptionalArgs();
};

#endif