#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>
#include <map>

// NODE STRUCTURE
struct Node
{
    unsigned char character;
    int frequency;
    Node *left;
    Node *right;

    Node(unsigned char c, int f) : character(c), frequency(f), left(nullptr), right(nullptr) {}
};

Node *huffmanTree(const std::map<unsigned char, int> &frequencyMap);
void printHuffmanTree(Node *root, const std::string &code, std::map<unsigned char, std::string> &characters_codes);
void printHuffmanTreeDebug(Node *root, const std::string &prefix = "");
std::string decodeHuffmanCode(Node *root, const std::string &encoded_text);

#endif