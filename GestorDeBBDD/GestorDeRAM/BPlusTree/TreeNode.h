#ifndef _TREE_NODE_H_
#define _TREE_NODE_H_

#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
#include <ctime>
const int DEGREE = 4;
using namespace std;
class TreeNode
{
public:
    bool is_leaf;
    std::vector<int> keys;

    std::vector<TreeNode *> children;
    
    std::vector<int> values; // Punteros a los valores (solo en nodos hoja)
    std::vector<std::string> directions;
    TreeNode(bool leaf = true) : is_leaf(leaf)
    {
        if (leaf)
        {
            values.resize(2 * DEGREE - 1); // Inicializar el vector de valores en nodos hoja
        }
    }
};


#endif