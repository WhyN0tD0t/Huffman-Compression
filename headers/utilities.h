#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <unordered_map>
#include <map>

// Function declarations
std::string readFile(const std::string &filename);
void writeFile(const std::string &filename, const std::string &content);
std::map<unsigned char, int> calculateFrequencies(const std::string &text);
std::map<unsigned char, int> getDictionaryFrequencies(const std::string &filename);
void WriteCompressedFile(const std::string &filename, std::string &bitstream);

void writeCompressed(const std::string &bitStream, const std::string &filenameWithoutExtension);
std::string readCompressed(const std::string &filename);

#endif