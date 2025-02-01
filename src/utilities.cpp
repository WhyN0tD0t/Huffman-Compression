/**
 * @file utilities.cpp
 * @brief Utility functions for file handling, frequency calculations, and Huffman encoding support.
 */

#include "utilities.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdint>

/**
 * @brief Reads an entire file into a string.
 * @param filename The name of the file to read.
 * @return The contents of the file as a string.
 */
std::string readFile(const std::string &filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

/**
 * @brief Writes a string to a file.
 * @param filename The name of the file to write.
 * @param content The content to write into the file.
 */
void writeFile(const std::string &filename, const std::string &content)
{
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    file << content;
}

/**
 * @brief Calculates the frequency of each character in a given text.
 * @param text The input text.
 * @return A map containing character frequencies.
 */
std::map<unsigned char, int> calculateFrequencies(const std::string &text)
{
    std::map<unsigned char, int> frequencies;
    for (unsigned char ch : text)
    {
        frequencies[ch]++;
    }
    return frequencies;
}

/**
 * @brief Reads character frequencies from a dictionary file.
 * @param filename The name of the dictionary file.
 * @return A map of character frequencies.
 */
std::map<unsigned char, int> getDictionaryFrequencies(const std::string &filename)
{
    std::map<unsigned char, int> dictionary_frequencies;
    int charac;
    int freq;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open dictionary file\n";
        return dictionary_frequencies;
    }
    while (file >> charac >> freq)
    {
        unsigned char character = static_cast<unsigned char>(charac);
        dictionary_frequencies[character] = freq;
    }
    file.close();
    return dictionary_frequencies;
}

const std::string HUFF = "HUFF";

/**
 * @brief Writes a compressed bitstream to a file with a magic header.
 * @param filename The name of the output file.
 * @param bitstream The compressed bitstream to write.
 */
void WriteCompressedFile(const std::string &filename, std::string &bitstream)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open the file for writing\n";
        return;
    }
    file.write(HUFF.c_str(), HUFF.size());
    char buffer = 0;
    int bitCount = 0;
    for (char bit : bitstream)
    {
        buffer = (buffer << 1) | (bit - '0');
        bitCount++;
        if (bitCount == 8)
        {
            file.put(buffer);
            buffer = 0;
            bitCount = 0;
        }
    }
    if (bitCount > 0)
    {
        buffer <<= (8 - bitCount);
        file.put(buffer);
    }
    file.close();
}

/**
 * @brief Reads a compressed file and returns the extracted bitstream.
 * @param filename The name of the compressed file.
 * @return The extracted bitstream as a string.
 */
std::string readCompressed(const std::string &filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in)
        throw std::runtime_error("Unable to open file for reading.");

    uint32_t bitCount = 0;
    in.read(reinterpret_cast<char *>(&bitCount), sizeof(bitCount));

    std::string bitStream;
    bitStream.reserve(bitCount);

    unsigned char byte;
    while (in.read(reinterpret_cast<char *>(&byte), 1))
    {
        for (int i = 7; i >= 0; --i)
        {
            if (bitStream.size() < bitCount)
            {
                bitStream.push_back((byte & (1 << i)) ? '1' : '0');
            }
            else
            {
                break;
            }
        }
    }
    return bitStream;
}
