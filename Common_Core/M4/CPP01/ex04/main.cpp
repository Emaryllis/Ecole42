#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

void replace(std::ofstream &re, std::ifstream &fs,
			const std::string &oldStr,
			const std::string &newStr) {
	std::string line;
	bool firstLine = true;
	while (std::getline(fs, line)) {
		if (!firstLine)
			re << "\n";
		size_t index = 0;

		// Replace all occurrences of oldStr with newStr in the line
		while ((index = line.find(oldStr, index)) != std::string::npos) {
			line.erase(index, oldStr.length());
			line.insert(index, newStr);
			index += newStr.length();
		}
		re << line; // Write the modified line to the output file
		firstLine = false;
	}
}

int main(int argc, char **argv) {
	if (argc != 4) {
		std::cout << "Please provide 3 arguments." << std::endl;
		return 1;
	}

	if (std::strlen(argv[2]) == 0) {
		std::cout << "Please provide a valid string to replace." << std::endl;
		return 1;
	}

	// Open input file stream
	std::ifstream fs(argv[1]);
	if (!fs.is_open()) {
		std::cout << "Please provide a valid filename." << std::endl;
		return 1;
	}

	// Create & open output file stream
	const std::string reFile = std::string(argv[1]) + ".replace";
	std::ofstream re(reFile.c_str(), std::ios::out | std::ios::trunc);
	if (!re.is_open()) {
		std::cout << "Failed to create output file." << std::endl;
		return 1;
	}

	replace(re, fs, argv[2], argv[3]);

	// Add trailing newline if the original file had one
	fs.clear();
	fs.seekg(0, std::ios::end);
	fs.seekg(-1, std::ios::end);
	char lastChar;
	fs.get(lastChar);
	if (lastChar == '\n')
		re << "\n";

	// Close file streams
	fs.close();
	re.close();

	return 0;
}
