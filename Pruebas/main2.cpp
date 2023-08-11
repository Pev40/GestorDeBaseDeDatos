#include <iostream>
#include <vector>
#include <string>
class BPlusTreeNode
{
public:
  BPlusTreeNode() : is_leaf_(true), order_(1) {}
  BPlusTreeNode(int order) : is_leaf_(true), order_(order) {}
  bool is_leaf_;
  int order_;
  std::vector<int> keys_;
  std::vector<BPlusTreeNode *> children_;
  std::vector<std::string> values_;
  void print();
  friend class BPlusTree;
};

void BPlusTreeNode::print()
{
  std::cout << "Orden: " << order_ << " Es Hijo? " << is_leaf_ << std::endl;
}

class BPlusTree
{
public:
  BPlusTree(int order);
  ~BPlusTree();
  void insert(int key, const std::string &value);
  bool search(int key, std::string &value) const;
  std::string generateDot() const;
  void insertNonFull(BPlusTreeNode *node, int key, const std::string &value);
  void splitChild(BPlusTreeNode *parent, int child_index);
  bool searchInNode(const BPlusTreeNode *node, int key, std::string &value) const;
  std::string generateDotHelper(const BPlusTreeNode *node, int &node_count) const;

private:
  int order_;
  BPlusTreeNode *root_;
};

// Constructor de BPlusTree
BPlusTree::BPlusTree(int order) : order_(order), root_(nullptr) {}

// Destructor de BPlusTree
BPlusTree::~BPlusTree()
{
  // Aquí se debe implementar la lógica para liberar la memoria utilizada por el árbol.
  // No lo incluyo en esta implementación simplificada.
}

// Método para insertar una clave y valor en el árbol B+
void BPlusTree::insert(int key, const std::string &value)
{
  std::cout << "Clave:" << key << " Valor: " << value << std::endl;
  if (root_ == nullptr)
  {
    std::cout << "Inicio" << std::endl;
    root_ = new BPlusTreeNode(order_);
    root_->keys_.push_back(key);
    root_->values_.push_back(value);
  }
  else
  {
    std::cout << "Insertar" << std::endl;
    if (root_->keys_.size() == order_)
    {
      BPlusTreeNode *new_root = new BPlusTreeNode(order_);
      new_root->print();
      new_root->children_.push_back(root_);
      splitChild(new_root, 0);
      root_ = new_root;
    }
    
    // Inicializar i con el valor correcto
    int i = root_->keys_.size() - 1;
    insertNonFull(root_, key, value);
  }
}

// Método insertNoLleno 
// Método para insertar en un nodo no lleno
void BPlusTree::insertNonFull(BPlusTreeNode* node, int key, const std::string& value) {
  int i = node->keys_.size() - 1; // Inicializar 'i' aquí

  if (node->is_leaf_)
  {
    std::cout << "Soy una Hoja" << std::endl;
    // Si es una hoja, insertamos la clave en su posición correcta manteniendo el orden
    node->keys_.resize(node->keys_.size() + 1);
    node->values_.resize(node->values_.size() + 1);

    // Inicializar i
    i = node->keys_.size() - 2;
    std::cout <<"Indice 0 : "<<i<<std::endl;
    // Corregir bucle para acceder a elementos válidos
    while (i >= 0 && key < node->keys_[i])
    {
      std::cout <<"Indice: "<<i<<std::endl;
      node->keys_[i + 1] = node->keys_[i];
      node->values_[i + 1] = node->values_[i];
      i--;
    }

    node->keys_[i + 1] = key;
    node->values_[i + 1] = value;
  }else {

    // Validar índice 
    i = node->keys_.size() - 1;
    while(i >= 0 && i < node->keys_.size() && key < node->keys_[i]) {
      i--; 
    }

    // Verificar puntero hijo y tamaño
    if(i >= 0 && i < node->children_.size()) {
      
      BPlusTreeNode* child = node->children_[i];
      
      // Verificar hijo no nulo y lleno
      if(child != nullptr && child->keys_.size() == order_) {
      
        splitChild(node, i);
        
        if(key > node->keys_[i]) {
          i++; 
        }
      }

      // Llamada recursiva si hijo no nulo
      if(child != nullptr) {
        insertNonFull(child, key, value);
      }

    }

  }

}


// Método para dividir un nodo hijo
void BPlusTree::splitChild(BPlusTreeNode* parent, int child_index) {

  // Verificar índice válido
  if(child_index >= 0 && child_index < parent->children_.size()) {
    std::cout<<"Me divido"<<std::endl;
    BPlusTreeNode* child = parent->children_[child_index];

    // Verificar que el hijo tenga claves 
    if(child != nullptr && child->keys_.size() > 0) {
          std::cout<<"Me divido2"<<std::endl;
      // Crear nuevo hijo
      BPlusTreeNode* newChild = new BPlusTreeNode(order_);

      // Igualar atributos  
      newChild->is_leaf_ = child->is_leaf_;
      newChild->order_ = order_;

      // Calcular mitad del orden
      int mid = order_ / 2;
      std::cout<<"La mitad es: "<<mid<<std::endl;
      // Mover mitad de claves a nuevo hijo
      newChild->keys_.assign(child->keys_.begin() + mid, child->keys_.end());
      child->keys_.resize(mid);

      // Mover hijos si no es hoja
      if(!newChild->is_leaf_) {
        newChild->children_.assign(child->children_.begin() + mid, child->children_.end());
        child->children_.resize(mid);
      }

      // Insertar nuevo hijo y clave de promoción
      newChild->print();
      parent->children_.insert(parent->children_.begin() + child_index + 1, newChild);
      std::cout<<"Es Aqui: "<<std::endl;
      parent->keys_.insert(parent->keys_.begin() + child_index, child->keys_[mid]); 
 std::cout<<"Es Aqui:2 "<<std::endl;
    } else {
      // Hijo no válido, manejar error
    }

  } else {
    // Índice inválido, manejar error
  }

}


// Método para buscar una clave en el árbol B+
bool BPlusTree::search(int key, std::string &value) const
{
  return searchInNode(root_, key, value);
}

// Método auxiliar para buscar una clave en un nodo
bool BPlusTree::searchInNode(const BPlusTreeNode *node, int key, std::string &value) const
{
  int i = 0;
  while (i < node->keys_.size() && key > node->keys_[i])
  {
    i++;
  }
  if (i < node->keys_.size() && key == node->keys_[i])
  {
    value = node->values_[i];
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

// Método para generar una descripción en lenguaje DOT del árbol B+

// Función para generar un valor aleatorio como una cadena de caracteres
std::string generateRandomValue()
{
  const int length = 6; // Longitud del valor generado
  const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  std::string value;
  for (int i = 0; i < length; i++)
  {
    value += charset[rand() % charset.length()];
  }
  return value;
}

// Función para imprimir el árbol




int main()
{

  //srand(time(NULL));

  BPlusTree tree(4);

  // Insertamos algunas claves y valores
  tree.insert(10, "Valor 1");
  tree.insert(15, "Valor 2");
  tree.insert(25, "Valor 3");
  tree.insert(35, "Valor 4");
  tree.insert(45, "Valor 5");
  tree.insert(55, "Valor 6");
  tree.insert(55, "Valor 6");
  tree.insert(55, "Valor 6");
  tree.insert(65, "Valor 6");
  tree.insert(75, "Valor 6");
  tree.insert(85, "Valor 6");
  tree.insert(95, "Valor 6");
  tree.insert(105, "Valor 6");
  tree.insert(115, "Valor 6");  
  // El árbol quedaría así:
  //        15
  //       /  \
  // [10]     [25, 35]
  //           / \
  //        [45] [55]

  return 0;
}