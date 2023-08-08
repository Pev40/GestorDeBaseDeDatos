class BPlusTreeNode {
public:
    BPlusTreeNode(int order) : is_leaf_(true), order_(order) {}
  
private:
    bool is_leaf_;
    int order_;
    std::vector<int> keys_;
    std::vector<BPlusTreeNode*> children_; 
    std::vector<std::string> values_;
  
    friend class BPlusTree;
};

class BPlusTree {
public:
    BPlusTree(int order);
    ~BPlusTree();
    void insert(int key, const std::string& value);
    bool search(int key, std::string& value) const;
    std::string generateDot() const;
    void insertNonFull(BPlusTreeNode* node, int key, const std::string& value);
    void splitChild(BPlusTreeNode* parent, int child_index);
    bool searchInNode(const BPlusTreeNode* node, int key, std::string& value) const;
    std::string generateDotHelper(const BPlusTreeNode* node, int& node_count) const;

private:
    int order_;
    BPlusTreeNode* root_;
};

// Constructor de BPlusTree
BPlusTree::BPlusTree(int order) : order_(order), root_(nullptr) {}

// Destructor de BPlusTree
BPlusTree::~BPlusTree() {
    // Aquí se debe implementar la lógica para liberar la memoria utilizada por el árbol.
    // No lo incluyo en esta implementación simplificada.
}

// Método para insertar una clave y valor en el árbol B+
void BPlusTree::insert(int key, const std::string& value) {
    if (root_ == nullptr) {
        root_ = new BPlusTreeNode(order_);
        root_->keys_.push_back(key);
        root_->values_.push_back(value);
    } else {
        if (root_->keys_.size() == order_) {
            BPlusTreeNode* new_root = new BPlusTreeNode(order_);
            new_root->children_.push_back(root_);
            splitChild(new_root, 0);
            root_ = new_root;
        }
        insertNonFull(root_, key, value);
    }
}

// Método auxiliar para insertar en un nodo no lleno
void BPlusTree::insertNonFull(BPlusTreeNode* node, int key, const std::string& value) {
    int i = node->keys_.size() - 1;
    if (node->is_leaf_) {
        // Si es una hoja, insertamos la clave en su posición correcta manteniendo el orden
        node->keys_.resize(node->keys_.size() + 1);
        node->values_.resize(node->values_.size() + 1);
        while (i >= 0 && key < node->keys_[i]) {
            node->keys_[i + 1] = node->keys_[i];
            node->values_[i + 1] = node->values_[i];
            i--;
        }
        node->keys_[i + 1] = key;
        node->values_[i + 1] = value;
    } else {
        // Si no es una hoja, encontramos el hijo donde se debe insertar la clave y verificamos si está lleno
    while (i >= 0 && key < node->keys_[i] && i < node->children_.size()) {
      i--;
    }

    if(i < node->children_.size() && 
       node->children_[i] != nullptr &&
       node->children_[i]->keys_.size() == order_) {
            splitChild(node, i); // split si hijo lleno
            if (key > node->keys_[i]) {
                i++;
            }
        }
      insertNonFull(node->children_[i], key, value);    
    }
}

// Método auxiliar para dividir un nodo hijo
void BPlusTree::splitChild(BPlusTreeNode* parent, int child_index) {

  // Verificar que el índice sea válido
  if(child_index < parent->children_.size()) {

    BPlusTreeNode* child = parent->children_[child_index];
    
    // Crear nuevo hijo  
    BPlusTreeNode* newChild = new BPlusTreeNode();

    // Igualar atributos
    newChild->is_leaf_ = child->is_leaf_;
    newChild->order_ = order_; 

    // Verificar que el hijo tenga claves antes de acceder
    if(!child->keys_.empty()) {

      // Calcular mitad del orden
      int mid = order_ / 2;

      // Mover la mitad de claves a nuevo hijo
      newChild->keys_.resize(mid);
      for(int i = 0; i < mid; i++) {
        newChild->keys_[i] = child->keys_[i + mid];  
      }

      // Si no es hoja, tambien mover hijos
      if(!newChild->is_leaf_) {

        newChild->children_.resize(mid + 1);
        for(int i = 0; i <= mid; i++) {
          newChild->children_[i] = child->children_[i + mid];
        }
      }

      // Ajustar las claves en el hijo original
      child->keys_.resize(mid); 

      if(!child->is_leaf_) {
        child->children_.resize(mid + 1); 
      }

    } else {
      // Caso: hijo sin claves 
      // Manejar error 
    }

    // Insertar nuevo hijo  
    parent->children_.insert(parent->children_.begin()+child_index+1, newChild);

    // Insertar clave de promoción
    parent->keys_.insert(parent->keys_.begin()+child_index, child->keys_[order_/2]);

  } else {
    // Índice inválido, arrojar excepción
  }

}
// Método para buscar una clave en el árbol B+
bool BPlusTree::search(int key, std::string& value) const {
    return searchInNode(root_, key, value);
}

// Método auxiliar para buscar una clave en un nodo
bool BPlusTree::searchInNode(const BPlusTreeNode* node, int key, std::string& value) const {
    int i = 0;
    while (i < node->keys_.size() && key > node->keys_[i]) {
        i++;
    }
    if (i < node->keys_.size() && key == node->keys_[i]) {
        value = node->values_[i];
        return true;
    } else if (node->is_leaf_) {
        return false;
    } else {
        return searchInNode(node->children_[i], key, value);
    }
}


// Método para generar una descripción en lenguaje DOT del árbol B+


// Función para generar un valor aleatorio como una cadena de caracteres
std::string generateRandomValue() {
    const int length = 6; // Longitud del valor generado
    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string value;
    for (int i = 0; i < length; i++) {
        value += charset[rand() % charset.length()];
    }
    return value;
}

int main() {

  srand(time(NULL));

  BPlusTree tree(4);

  // Insertamos algunas claves y valores
  tree.insert(10, "Valor 1");
  tree.insert(15, "Valor 2"); 
  tree.insert(25, "Valor 3");
  tree.insert(35, "Valor 4");
  tree.insert(45, "Valor 5");
  tree.insert(55, "Valor 6");

  // El árbol quedaría así:
  //        15
  //       /  \
  // [10]     [25, 35]
  //           / \
  //        [45] [55]


  return 0;
}