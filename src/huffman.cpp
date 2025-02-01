/**
 * @file huffman.cpp
 * @brief Implements Huffman coding tree construction and decoding.
 *
 * This file contains the implementation of Huffman tree creation,
 * encoding, and decoding functions for compressing and decompressing text.
 */

#include "huffman.h"
#include <queue>
#include <iostream>

/**
 * @struct Compare
 * @brief Comparator for priority queue ordering Huffman tree nodes.
 */
struct Compare
{
    /**
     * @brief Comparison operator for Huffman tree node priority.
     * @param left Pointer to left node.
     * @param right Pointer to right node.
     * @return True if left node has higher frequency or same frequency but higher ASCII value.
     */
    bool operator()(Node *left, Node *right)
    {
        if (left->frequency != right->frequency)
        {
            return left->frequency > right->frequency;
        }
        return left->character > right->character;
    }
};

/**
 * @brief Builds the Huffman tree from a frequency map.
 * @param frequencyMap Map of character frequencies.
 * @return Root node of the constructed Huffman tree.
 */
Node *huffmanTree(const std::map<unsigned char, int> &frequencyMap)
{
    std::priority_queue<Node *, std::vector<Node *>, Compare> heap;

    for (const auto &pair : frequencyMap)
    {
        heap.push(new Node(pair.first, pair.second));
    }

    while (heap.size() > 1)
    {
        Node *left = heap.top();
        heap.pop();
        Node *right = heap.top();
        heap.pop();

        Node *internalNode = new Node('\0', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        heap.push(internalNode);
    }

    return heap.empty() ? nullptr : heap.top();
}

/**
 * @brief Generates Huffman codes for characters by traversing the tree.
 * @param root Pointer to the root node of the Huffman tree.
 * @param code Current binary string representation of the character.
 * @param characters_codes Output map storing character-to-code mappings.
 */
void printHuffmanTree(Node *root, const std::string &code, std::map<unsigned char, std::string> &characters_codes)
{
    if (!root)
        return;

    if (!root->left && !root->right)
    {
        characters_codes[root->character] = code;
    }

    printHuffmanTree(root->left, code + "0", characters_codes);
    printHuffmanTree(root->right, code + "1", characters_codes);
}

/**
 * @brief Debugging function to print Huffman tree structure.
 * @param root Pointer to the root of the Huffman tree.
 * @param prefix String representing the current tree path.
 */
void printHuffmanTreeDebug(Node *root, const std::string &prefix)
{
    if (!root)
        return;

    if (!root->left && !root->right)
    {
        std::cout << "Leaf: " << root->character << " Code: " << prefix << std::endl;
    }

    printHuffmanTreeDebug(root->left, prefix + "0");
    printHuffmanTreeDebug(root->right, prefix + "1");
}

/**
 * @brief Decodes a Huffman-encoded bitstream.
 * @param root Pointer to the root of the Huffman tree.
 * @param encoded_text The encoded string of bits.
 * @return Decoded original text.
 */
std::string decodeHuffmanCode(Node *root, const std::string &encoded_text)
{
    if (!root)
        return "";

    Node *current = root;
    std::string decoded_text = "";

    for (char bit : encoded_text)
    {
        if (bit == '0')
        {
            current = current->left;
        }
        else if (bit == '1')
        {
            current = current->right;
        }
        else
        {
            std::cerr << "Invalid bit in encoded text: " << bit << std::endl;
            return "";
        }

        if (!current->left && !current->right)
        {
            decoded_text += current->character;
            current = root;
        }
    }

    return decoded_text;
}
