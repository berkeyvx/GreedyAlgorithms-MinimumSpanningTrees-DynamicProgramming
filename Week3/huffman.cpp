#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <string>

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



void decodeHuffman(node* root, std::string str) 
{ 
  
    if (!root) 
        return; 
  
    if (root->m_data != '*') 
        std::cout << root->m_data << ": " << str << "\n"; 
  
    decodeHuffman(root->left, str + "0"); 
    decodeHuffman(root->right, str + "1"); 
} 


int main(int argc, char const *argv[])
{
    min_pq p;
    vec_pair_char_int v;
    v.push_back(std::make_pair('b',3));
    v.push_back(std::make_pair('m',8));
    v.push_back(std::make_pair('g',13));
    v.push_back(std::make_pair('e',24));
    v.push_back(std::make_pair('c',23));
    v.push_back(std::make_pair('h',2));
    auto ret = huffman(v);
    decodeHuffman(ret.top(), "");
    
    return 0;
}


