#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, std::string> ArgumentMap;

class ArgumentParser {
public:
	// Constructor
	ArgumentParser(int, char**);
	
	// Public methods
	void add_argument(std::string, std::string = "", std::string = "");
	std::map<std::string, std::string> parse_args(void);

private:
	// Private variables
	int argc;
	char** argv;
	uint8_t argOrder;
	int argsNum;
	std::map<std::string, std::string> argumentMap;
	std::vector<std::string> keywordArgsInfo;
	std::vector<std::string> nonKeywordArgsInfo;
	std::string usage;
	std::vector<std::string> nonKeywordArgs;
	std::vector<std::vector<std::string>> keywordArgs;
	std::vector<int> unrecognizedArgID;

	// Private methods
	void printArgsList(void);
	void printUsage(void);
	void checkHelpCommand(void);
	void checkValidArgs(void);
	void addInfo(std::string, std::string, std::string);
	void addNonKeywordArg(std::string);
	void addKeywordArg(std::string, std::string);
	void parseNonKeywordArgs();
	void parseKeywordArgs();
};
