#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, std::string>& ArgumentMap;

class ArgumentParser {
public:
	// Constructor
	ArgumentParser(int, char**, std::string = "");
	
	// Public methods
	void add_argument(std::string, std::string, std::string, std::string);
	void add_argument(std::string, std::string);
	void parse_args(void);
	const std::string& get(const std::string);
	template<typename T>
	T get(const std::string);


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
	void addInfo(std::string& argName, std::string& helpMsg);
	void addInfo(std::string&, std::string&, std::string&, std::string&);
	void addPositionalArg(std::string&);
	void addOptionalArg(std::string&, std::string&, std::string&);
	void parsePositionalArgs();
	void parseOptionalArgs();
};
