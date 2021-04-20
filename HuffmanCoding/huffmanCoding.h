/*
	HuffmanCoding
	This file contains the self-implemented
	Huffman coding algorithm for array of
	unsigned characters.
*/

#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

#include <string>
#include <vector>

namespace c173 {
	
	template <typename T>
	class Binary_Node {
		public:
			Binary_Node(T data);
			Binary_Node();
			~Binary_Node();

			// getters and setters
			bool isEmpty();
			Binary_Node<T>* get_left_node();
			Binary_Node<T>* get_right_node();
			void set_left_node(Binary_Node<T>* node);
			void set_right_node(Binary_Node<T>* node);
			
			// DEBUG
			void print_binary_node();

			void set_data(T data);
			T get_data();
			void clear_data();

		private:
			T data;
			Binary_Node<T> *left, *right;
			bool flag_empty;
	};
	
	typedef Binary_Node<unsigned char> Binary_Node_uchar;
	
	class Huffman_Coding_uchar {
		public:
			Huffman_Coding_uchar();
			Huffman_Coding_uchar(unsigned char* raw_data_array, int array_size);
			
			std::vector<unsigned char> make_tree_stream();
			void interprut_tree(unsigned char* tree_stream, int tree_stream_size);
			void evaluate_codec(unsigned char *raw_data_array, int array_size);
			Binary_Node_uchar* construct_tree(unsigned char *code_book, int *frequency, int cnt_code);
			Binary_Node_uchar* construct_tree(unsigned char* raw_data_array, int array_size);
			
			// DEBUG
			void print_huffman_tree();
			
			std::string encode(unsigned char raw_data);
			unsigned char decode(std::string code);
			void decode_stream(unsigned char* code_stream, int code_stream_size, unsigned char* decode_stream, int decode_stream_size);

		private:
			std::string codec[256];
			Binary_Node_uchar* huffman_tree;
			
			void evaluate_codec();
			void helper_traverse_tree(Binary_Node_uchar* node, std::string code);
			void helper_make_tree_stream(Binary_Node_uchar* node, std::string &tree_struct, std::vector<unsigned char>& data_stream);
	};

	
}

#endif
