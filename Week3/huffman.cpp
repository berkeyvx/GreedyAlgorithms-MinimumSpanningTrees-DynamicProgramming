/*
 huffman.txt file describes an instance of the problem. It has the following format:

number_of_symbols
weight of symbol 1
weight of symbol 2

task in this problem is to run the Huffman coding algorithm from lecture on this data set. 
What is the maximum length of a codeword in the resulting Huffman code?

*/



#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>


typedef struct node{
    struct node *left,*right;
    char m_data;
    int m_freq;

    node(char data, int freq)
    {
        left = nullptr;
        right = nullptr;
        m_data = data;
        m_freq = freq;
    }

    ~node(){
        delete left;
        delete right;
    }

    // what if in the future we want to make max heap
    // therefore i gave up on this idea
    bool operator<(const struct node& other) const{
        return this->m_freq > other.m_freq;
    }
}node;


struct comparator
{
    bool operator()(node *l, node *r)
    {
        return l->m_freq > r->m_freq;
    }
};

typedef std::priority_queue<node *, std::vector<node *>, comparator> min_pq;
typedef std::vector<std::pair<char, int>> vec_pair_char_int;

min_pq huffman(std::vector<std::pair<char, int>> data_freq)
{
    min_pq min_priority_queue;
    for (auto &&d_f : data_freq)
    {
        min_priority_queue.push(new node(d_f.first, d_f.second));
    }

    node *top,*left,*right;
    while(min_priority_queue.size() != 1){
        left = min_priority_queue.top();
        min_priority_queue.pop();

        right = min_priority_queue.top();
        min_priority_queue.pop();

        top = new node('*', left->m_freq + right->m_freq);
        top->left = left;
        top->right = right;

        min_priority_queue.push(top);
    }

    return min_priority_queue;
}



vec_pair_char_int decodeHuffman(node* root, std::string str, vec_pair_char_int &vp) 
{ 
    if (!root) 
        return vp;
  
    if (root->m_data != '*')
    { 
        //std::cout << root->m_data << ": " << str << "\n"; 
        vp.push_back(std::make_pair('-',str.size()));
    }
    vp = decodeHuffman(root->left, str + "0", vp); 
    vp = decodeHuffman(root->right, str + "1", vp); 

    return vp;
} 


vec_pair_char_int readFile(){
    std::string line;
    std::fstream file("huffman.txt");
    // getting number of symbols is redundant so we just take it and do nothing with this line
    std::getline(file, line, '\n');
    
    // return variable
    vec_pair_char_int file_vec_pair;

    int temp;
    while(getline(file, line, '\n')){
        temp = std::stoi(line);
        file_vec_pair.push_back(std::make_pair('-', temp));
    }

    return file_vec_pair;
}


int main(int argc, char const *argv[])
{
    auto v = readFile();
    
    auto pq = huffman(v);

    vec_pair_char_int vp;
    auto res = decodeHuffman(pq.top(), "", vp);
    auto it = std::max_element(res.begin(), res.end(), [](const auto &l, const auto &r){
                                                            return l.second < r.second;
    });

    auto it2 = std::min_element(res.begin(), res.end(), [](const auto &l, const auto &r){
                                                           return l.second < r.second;
    });
    
    std::cout << it->second << " " << it2->second;; 
    return 0;
}

