# Huffman-Compression
C++ application that compresses and decompresses text files and generates .huff compressed files

## Usage:
this is a command line application run ./huffman
when started with no parameters, instruction will appear.
All the flags need to be provided:
-i <input_file>
-o <output_file> (with .huff extension)
-m <mode> 
  c : compress
  d: decompress
-d <dictionary_file> (standard .txt extension)
# FOR EXAMPLE:
./huffman -i text.txt -o compressed.huff -m c -d dictionary.txt (for compression)

./huffman -i compressed.huff -o decompressed.txt -m d -d dictionary.txt (for decompression)

# WARNING !!!
The program can only decompress the files compressed using this application, 
this is because of HUFF signature added at the begining of every compressed file.
