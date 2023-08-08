// Implementación de las clases
#include "arbolBPlus.h"
// Constructor de ArbolBPlus
ArbolBPlus::ArbolBPlus(int order) : order_(order), root_(nullptr){}

// Método para insertar una clave y valor en el árbol B+
void ArbolBPlus::insert(int key, const std::string &value)
{
    if (root_ == nullptr)
    {
        root_ = new NodeBPlus();
        root_->is_leaf_ = true;
        root_->order_ = order_;
        root_->keys_.push_back(key);
        root_->values_.push_back(new std::string(value));
    }
    else
    {
        if (root_->keys_.size() == 2 * order_ - 1)
        {
            // El nodo raíz está lleno, se necesita crear un nuevo nodo raíz.
            NodeBPlus *new_root = new NodeBPlus();
            new_root->is_leaf_ = false;
            new_root->order_ = order_;
            new_root->children_.push_back(root_);
            splitChild(new_root, 0);
            root_ = new_root;
        }
        insertNonFull(root_, key, value);
    }
}

// Método auxiliar para insertar en un nodo no lleno
void ArbolBPlus::insertNonFull(NodeBPlus *node, int key, const std::string &value)
{
    int i = node->keys_.size() - 1;
    if (node->is_leaf_)
    {
        // Si es una hoja, insertamos la clave en su posición correcta manteniendo el orden
        node->keys_.resize(node->keys_.size() + 1);
        node->values_.resize(node->values_.size() + 1);
        while (i >= 0 && key < node->keys_[i])
        {
            node->keys_[i + 1] = node->keys_[i];
            node->values_[i + 1] = node->values_[i];
            i--;
        }
        node->keys_[i + 1] = key;
        node->values_[i + 1] = new std::string(value);
    }
    else
    {
        // Si no es una hoja, encontramos el hijo donde se debe insertar la clave y verificamos si está lleno
        while (i >= 0 && key < node->keys_[i])
        {
            i--;
        }
        i++;
        if (node->children_[i]->keys_.size() == 2 * order_ - 1)
        {
            splitChild(node, i);
            if (key > node->keys_[i])
            {
                i++;
            }
        }
        insertNonFull(node->children_[i], key, value);
    }
}

// Método auxiliar para dividir un nodo hijo
void ArbolBPlus::splitChild(NodeBPlus *parent, int child_index)
{
    NodeBPlus *new_child = new NodeBPlus();
    NodeBPlus *child = parent->children_[child_index];
    new_child->is_leaf_ = child->is_leaf_;
    new_child->order_ = order_;

    // Mover las últimas (order_ - 1) claves del hijo al nuevo hijo
    new_child->keys_.resize(order_ - 1);
    new_child->values_.resize(order_ - 1);
    for (int i = 0; i < order_ - 1; i++)
    {
        new_child->keys_[i] = child->keys_[i + order_];
        new_child->values_[i] = new std::string(*(child->values_[i + order_]));
    }

    if (!child->is_leaf_)
    {
        // Si el hijo no es una hoja, también debemos mover sus últimos (order_) hijos al nuevo hijo
        new_child->children_.resize(order_);
        for (int i = 0; i < order_; i++)
        {
            new_child->children_[i] = child->children_[i + order_];
        }
    }

    // Ajustar el número de claves del hijo original
    child->keys_.resize(order_ - 1);
    child->values_.resize(order_ - 1);

    // Insertar el nuevo hijo en el padre
    parent->children_.insert(parent->children_.begin() + child_index + 1, new_child);

    // Insertar la clave media del hijo en el padre
    parent->keys_.insert(parent->keys_.begin() + child_index, child->keys_[order_ - 1]);
}

// Método para buscar una clave en el árbol B+
bool ArbolBPlus::search(int key, std::string &value) const
{
    return searchInNode(root_, key, value);
}

// Método auxiliar para buscar una clave en un nodo
bool ArbolBPlus::searchInNode(const NodeBPlus *node, int key, std::string &value) const
{
    int i = 0;
    while (i < node->keys_.size() && key > node->keys_[i])
    {
        i++;
    }
    if (i < node->keys_.size() && key == node->keys_[i])
    {
        value = *(node->values_[i]);
        return true;
    }
    else if (node->is_leaf_)
    {
        return false;
    }
    else
    {
        return searchInNode(node->children_[i], key, value);
    }
}

// Destructor de ArbolBPlus
ArbolBPlus::~ArbolBPlus(){}