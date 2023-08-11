#ifndef __BTREE_H__
#define __BTREE_H__

#include "TreeNode.h"

#include <iostream>
#include <string>

using namespace std;

class BTree
{
public:
    TreeNode *root;
    BTree()
    {
        root = new TreeNode();
    }

    void insert(int key, std::string value)
    {
        if (root->keys.size() == 2 * DEGREE - 1)
        {
            TreeNode *new_root = new TreeNode(false);
            new_root->children.push_back(root);
            split_child(new_root, 0);
            insert_non_full(new_root, key, value);
            root = new_root;
        }
        else
        {
            insert_non_full(root, key, value);
        }
    }

    void insert_non_full(TreeNode *node, int key, std::string value)
    {
        int i = node->keys.size() - 1;
        if (node->is_leaf)
        {
            node->keys.push_back(0);
            node->values.push_back(""); // Inicializar el valor
            while (i >= 0 && key < node->keys[i])
            {
                node->keys[i + 1] = node->keys[i];
                node->values[i + 1] = node->values[i];
                i--;
            }
            node->keys[i + 1] = key;
            node->values[i + 1] = value;
        }
        else
        {
            while (i >= 0 && key < node->keys[i])
            {
                i--;
            }
            i++;
            if (node->children[i]->keys.size() == 2 * DEGREE - 1)
            {
                split_child(node, i);
                if (key > node->keys[i])
                {
                    i++;
                }
            }
            insert_non_full(node->children[i], key, value);
        }
    }

    void split_child(TreeNode *parent, int index)
    {
        TreeNode *child = parent->children[index];
        TreeNode *new_child = new TreeNode(child->is_leaf);
        parent->keys.insert(parent->keys.begin() + index, child->keys[DEGREE - 1]);
        parent->values.insert(parent->values.begin() + index, child->values[DEGREE - 1]);
        parent->children.insert(parent->children.begin() + index + 1, new_child);
        new_child->keys.assign(child->keys.begin() + DEGREE, child->keys.end());
        new_child->values.assign(child->values.begin() + DEGREE, child->values.end());
        child->keys.resize(DEGREE - 1);
        child->values.resize(DEGREE - 1);
        if (!child->is_leaf)
        {
            new_child->children.assign(child->children.begin() + DEGREE, child->children.end());
            child->children.resize(DEGREE);
        }
    }

    bool search(int key)
    {
        return search_key(root, key);
    }


    std::string search_values(int key)
    {
        return search_key_value(root, key);
    }



    void remove(int key)
    {
        if (!root->keys.empty())
        {
            remove_from_node(root, key);
            if (root->keys.empty() && !root->is_leaf)
            {
                TreeNode *new_root = root->children[0];
                delete root;
                root = new_root;
            }
        }
    }

    void remove_from_node(TreeNode *node, int key)
    {
        int idx = 0;
        while (idx < node->keys.size() && key > node->keys[idx])
        {
            idx++;
        }

        if (idx < node->keys.size() && key == node->keys[idx])
        {
            if (node->is_leaf)
            {
                node->keys.erase(node->keys.begin() + idx);
                node->values.erase(node->values.begin() + idx);
            }
            else
            {
                TreeNode *pred = get_predecessor(node, idx);
                node->keys[idx] = pred->keys.back();
                node->values[idx] = pred->values.back();
                remove_from_node(pred, pred->keys.back());
            }
        }
        else
        {
            if (node->is_leaf)
            {
                std::cout << "Key " << key << " not found in the tree." << std::endl;
                return;
            }

            bool is_last = (idx == node->keys.size());
            TreeNode *child = node->children[idx];

            if (child->keys.size() < DEGREE)
            {
                fill_child(node, idx);
            }

            if (is_last && idx > node->keys.size())
            {
                remove_from_node(node->children[idx - 1], key);
            }
            else
            {
                remove_from_node(node->children[idx], key);
            }
        }
    }

    TreeNode *get_predecessor(TreeNode *node, int idx)
    {
        TreeNode *current = node->children[idx];
        while (!current->is_leaf)
        {
            current = current->children.back();
        }
        return current;
    }

    void fill_child(TreeNode *node, int idx)
    {
        if (idx != 0 && node->children[idx - 1]->keys.size() >= DEGREE)
        {
            borrow_from_prev(node, idx);
        }
        else if (idx != node->keys.size() && node->children[idx + 1]->keys.size() >= DEGREE)
        {
            borrow_from_next(node, idx);
        }
        else
        {
            if (idx != node->keys.size())
            {
                merge_nodes(node, idx);
            }
            else
            {
                merge_nodes(node, idx - 1);
            }
        }
    }

    void borrow_from_prev(TreeNode *node, int idx)
    {
        TreeNode *child = node->children[idx];
        TreeNode *sibling = node->children[idx - 1];

        child->keys.insert(child->keys.begin(), node->keys[idx - 1]);
        node->keys[idx - 1] = sibling->keys.back();
        node->values[idx - 1] = sibling->values.back();
        if (!sibling->is_leaf)
        {
            child->children.insert(child->children.begin(), sibling->children.back());
            sibling->children.pop_back();
        }

        sibling->keys.pop_back();
    }

    void borrow_from_next(TreeNode *node, int idx)
    {
        TreeNode *child = node->children[idx];
        TreeNode *sibling = node->children[idx + 1];

        child->keys.push_back(node->keys[idx]);
        node->keys[idx] = sibling->keys.front();

        if (!sibling->is_leaf)
        {
            child->children.push_back(sibling->children.front());
            sibling->children.erase(sibling->children.begin());
        }

        sibling->keys.erase(sibling->keys.begin());
    }

    void merge_nodes(TreeNode *node, int idx)
    {
        TreeNode *child = node->children[idx];
        TreeNode *sibling = node->children[idx + 1];

        child->keys.push_back(node->keys[idx]);
        child->values.push_back(node->values[idx]);
        child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());
        child->values.insert(child->values.end(), sibling->values.begin(), sibling->values.end());
        if (!child->is_leaf)
        {
            child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());
        }

        node->keys.erase(node->keys.begin() + idx);
        node->values.erase(node->values.begin() + idx);
        node->children.erase(node->children.begin() + idx + 1);

        delete sibling;
    }

    // Agregar este método dentro de la clase BTree en el archivo BPlusTree.h

    void cargarArchivoEnArbol(const std::string &archivoEstructura)
    {
        std::ifstream archivo(archivoEstructura);
        if (!archivo.is_open())
        {
            std::cout << "Error al abrir el archivo " << archivoEstructura << std::endl;
            return;
        }

        std::map<int, std::string> diccionario;

        std::string linea;
        while (std::getline(archivo, linea))
        {
            std::istringstream ss(linea);
            int key;
            std::string value;
            ss >> key >> value;

            insert(key, value); // Llama al método insert del árbol
            diccionario[key] = value;
        }

        archivo.close();

    }
private:
    std::string search_key_value(TreeNode *node, int key)
    {
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i])
        {
            i++;
        }
        if (i < node->keys.size() && key == node->keys[i])
        {
            return node->values[i];
        }
        else if (node->is_leaf)
        {
            std::cout << "No se encontro ese valor";
            return "false";
        }
        else
        {
            return search_key_value(node->children[i], key);
        }
    }
    bool search_key(TreeNode *node, int key)
    {
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i])
        {
            i++;
        }
        if (i < node->keys.size() && key == node->keys[i])
        {
            return true;
        }
        else if (node->is_leaf)
        {
            return false;
        }
        else
        {
            return search_key(node->children[i], key);
        }
    }

};

#endif