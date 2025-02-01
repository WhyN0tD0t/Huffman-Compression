/**
 * @file main.cpp
 * @brief Main entry point for the Huffman compression and decompression program.
 *
 * This file handles command-line arguments, file I/O, and calls
 * the Huffman encoding and decoding functions accordingly.
 */

#include <iostream>
#include <iomanip>
#include <map>

#include "huffman.h"
#include "utilities.h"

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * @brief Prints help information for using the program.
 */
void printHelp()
{
    std::cout << "\nUsage: ./huffman -i <input_file> -o <output_file> -m <mode> -d <dictionary_file>\n";
    std::cout << "Modes:\n  c : compress\n  d : decompress\n";
    std::cout << "Example:\n  ./huffman -i input.txt -o compressed.huff -m c -d Dictionary.txt\n";
    std::cout << "Please REMEMBER that the compressed file must have the .huff extension!\n";
}

/**
 * @brief Main function handling command-line arguments and program execution.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on success, 1 on failure.
 */
int main(int argc, char *argv[])
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    if (argc == 1)
    {
        printHelp();
        return 0;
    }

    // Command-line argument parsing
    std::string inputFile, outputFile, dictionaryFile, mode;
    for (int i = 1; i < argc; i += 2)
    {
        std::string flag = argv[i];
        if (i + 1 >= argc)
        {
            std::cerr << "Error: missing value for " << flag << "\n";
            return 1;
        }
        if (flag == "-i")
        {
            inputFile = argv[i + 1];
        }
        else if (flag == "-o")
        {
            outputFile = argv[i + 1];
        }
        else if (flag == "-d")
        {
            dictionaryFile = argv[i + 1];
        }
        else if (flag == "-m")
        {
            mode = argv[i + 1];
        }
        else
        {
            std::cerr << "Error: Unknown flag " << flag << "\n";
            return 1;
        }
    }

    // Validate arguments
    if (inputFile.empty() || outputFile.empty() || mode.empty())
    {
        std::cerr << "Error: Missing required arguments\n";
        printHelp();
        return 1;
    }

    // Compression Mode
    if (mode == "c")
    {
        std::string buffer = readFile(inputFile);
        auto characters_frequency = calculateFrequencies(buffer);
        Node *root = huffmanTree(characters_frequency);
        std::map<unsigned char, std::string> characters_codes;
        printHuffmanTree(root, "", characters_codes);

        std::string encoded_text;
        for (unsigned char ch : buffer)
        {
            encoded_text += characters_codes[ch];
        }
        WriteCompressedFile(outputFile, encoded_text);
    }
    // Decompression Mode
    else if (mode == "d")
    {
        std::map<unsigned char, int> dictionary_frequencies = getDictionaryFrequencies(dictionaryFile);
        Node *root = huffmanTree(dictionary_frequencies);
        std::string DECODING = readCompressed(inputFile);
        std::string decoded_text = decodeHuffmanCode(root, DECODING);
        writeFile(outputFile, decoded_text);
    }
    else
    {
        std::cerr << "Error: Invalid mode. Use 'c' for compress or 'd' for decompress.\n";
        printHelp();
        return 1;
    }
}
