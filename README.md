# Huffman-Compression
C++ application that compresses and decompresses text files and generates .huff compressed files

## Usage:
this is a command line application run ./huffman
when started with no parameters, instruction will appear.
All the flags need to be provided: <br>
-i <input_file> <br>
-o <output_file> (with .huff extension) <br>
-m <mode> <br>
  c : compress <br>
  d: decompress <br>
-d <dictionary_file> (standard .txt extension) <br>
## For example:
./huffman -i text.txt -o compressed.huff -m c -d dictionary.txt (for compression)

./huffman -i compressed.huff -o decompressed.txt -m d -d dictionary.txt (for decompression)

# WARNING !!!
The program can only decompress the files compressed using this application, 
this is because of HUFF signature added at the begining of every compressed file.

## How it works?
### Compression
The program takes the input file and calculates the frequency of every character included in input text file. <br>
Based off of those frequencies the Binary tree withing the huffman algorithm is made, which then indicates the new binary codes for every character. <br>
The higher is the frequency the less amount of bits is assigned for a character. <br>
This idea provides us with fewer bits used when storing such a file. IT's compressed.
<br>
<br>
### Decompression
Decompression works similarly. <br>
To decompress the file the same binary codes are needed, therefore during the compression the additional dictionary file is created.<br>
It contains the frequencies of all characters used in file.
When decompressing, the new binary tree is created using the dictionary text file. <br>
When all this is done the bit extraction of compressed file begins. <br> 
In that moment every character is recreated and then rewritten to the new file "output-file" <br>

