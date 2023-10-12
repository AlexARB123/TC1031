/**
 * Nombre: Alejandro Rodriguez
 * Matrícula: A01722329
 * 
 * El program crea clases de Binary Search Tree y operaciones basicas de este.
 */

#include <iostream>
using namespace std;


template<class T>
class Node{
    public:
        T data;
        Node* left;
        Node* right;

        Node(T input){
            data = input;
            left = nullptr;
            right = nullptr;
        }
};

template<class T>
class BST{
    
    private:
        Node<T>* root;
        void AddLeafPrivate(T data, Node<T>* Ptr){
            if(root == nullptr){
                root = createLeaf(data);
            }
            else if(data < Ptr->data){
                if(Ptr->left != nullptr){
                    AddLeafPrivate(data, Ptr->left);
                }
                else{
                    Ptr->left = createLeaf(data);
                }
            }
            else if(data > Ptr->data){
                if(Ptr->right != nullptr){
                    AddLeafPrivate(data, Ptr->right);
                }
                else{
                    Ptr->right = createLeaf(data);
                }
            }
            else{
                cout << "Input already inside BST" << endl;
            }
        }

        void Preorder(Node<T>* Ptr){
            if(Ptr == nullptr){
                return;
            }

            cout<< Ptr->data << " ";

            Preorder(Ptr->left);
            Preorder(Ptr->right);
        }
        void Inorder(Node<T>* Ptr){
            if(Ptr->left != nullptr){
                Inorder(Ptr->left);
            }
            cout << Ptr->data << " ";
            if(Ptr->right != nullptr){
                Inorder(Ptr->right);
            }
        }
        void Postorder(Node<T>* Ptr){
            if(Ptr == nullptr){
                return;
            }

            Postorder(Ptr->left);
            Postorder(Ptr->right);

            cout << Ptr->data << " ";
        }
        
        void LevelByLevel(Node<T>* Ptr){
            int h = calculateHeight(root);
            for(int i = 1; i <= h; i++){
                printCurrentLevel(root, i);
                cout << endl;
            }
        }
        void printCurrentLevel(Node<T>* Ptr, int level){
            if(Ptr == nullptr){
                return;
            }
            if(level == 1){
                cout << Ptr->data << " ";
            }
            else if(level > 1) {
                printCurrentLevel(Ptr->left, level - 1);
                printCurrentLevel(Ptr->right, level - 1);
            }
        }

        int calculateHeight(Node<T>* Ptr){
            if(Ptr == nullptr){
                return 0;
            }

            int lheight = calculateHeight(Ptr->left);
            int rheight = calculateHeight(Ptr->right);
            
            if(lheight > rheight){
                return (lheight + 1);
            }
            else{
                return (rheight + 1);
            }
        }

        void printAncestorPrivate(T data, Node<T>* Ptr){
            if(Ptr == nullptr){
                cout << "Entry not in BST" << endl;
                return;
            }
            else if(Ptr->data == data){
                return;
            }
            else if(Ptr->data > data){
                printAncestorPrivate(data, Ptr->left);
                cout << Ptr->data << " " << endl;
            }
            else if(Ptr->data < data){
                printAncestorPrivate(data, Ptr->right);
                cout << Ptr->data << " " << endl;
            }
        }

        int whatLevelAmIPrivate(T data, Node<T>* Ptr){
            if(Ptr == nullptr){
                return -1;
            }
            else if(Ptr->data == data){
                return 1;
            }
            else if(Ptr->data > data){
                int currLevel = whatLevelAmIPrivate(data, Ptr->left);
                return currLevel + 1;
            }
            else{
                int currLevel = whatLevelAmIPrivate(data, Ptr->right);
                return currLevel + 1;
            }

        }
    public:
        BST(){
            root = nullptr;
        }
        Node<T>* createLeaf(T data){
            Node<T>* n = new Node<T>(data);
            return n;
        }
        void AddLeaf(T data){
            AddLeafPrivate(data, root);
            cout << "Inserted " << data << endl;

            Inorder(root);
            cout << endl;
        }
        /**
        * @brief Imprime el BST en el orden elegido con el numero entero
        * @param numero de condicion a imprimir
        * @return sin retorno
        * 
        * Complejidad O(n)
        */
        void visit(int order){
            if(root == nullptr){
                cout << "Binary Tree Empty, nothing to display" << endl;
            }
            else{
                switch(order){
                    case 1:
                        Preorder(root);
                        break;
                    case 2:
                        Inorder(root);
                        break;
                    case 3:
                        Postorder(root);
                        break;
                    case 4:
                        LevelByLevel(root);
                        break;
                    default:
                        cout << "Error, not a valid input" << endl;
                        break;
                }
            }
        }
        
        /**
        * @brief Regresa la altura maxima del BST
        * @param sin param
        * @return Altura maxima del BST
        * 
        * Complejidad O(n)
        */
        int height(){
            int ans = calculateHeight(root);
            return ans;
        }

        /**
        * @brief Imprime los ancestros del valor seleccionado
        * @param Dato al cual buscar
        * @return Sin retorno
        * 
        * Complejidad O(log n)
        */
        void printAncestor(T data){
            printAncestorPrivate(data, root);
        }
        
        /**
        * @brief Regresa el nivel en el cual se encuentra el dato proporcionado
        * @param Dato al cual buscar
        * @return entero representando el nivel en que se encuentra
        * 
        * Complejidad O(log n)
        */
        int whatLevelAmI(T data){
            return whatLevelAmIPrivate(data, root);
        }
};

int main(){
    int Dats[] = {5,3,7,4,6,2,8,9};
    BST<int> myTree;

    int length = sizeof(Dats) / sizeof(Dats[0]);

    cout << "Empty Tree" << endl;
    myTree.visit(2);

    cout << "Populating and re-printing tree" << endl;
    for(int i = 0; i < length; i++){
        myTree.AddLeaf(Dats[i]);
    }
    cout << "Preorder: " << endl;
    myTree.visit(1);
    cout << endl;

    cout << "Inorder: " << endl;
    myTree.visit(2);
    cout << endl;

    cout << "Postorder: " << endl;
    myTree.visit(3);
    cout << endl;

    cout << "Level By Level: " << endl;
    myTree.visit(4);
    cout << endl;

    cout << "Height: " << myTree.height() << endl;

    cout << "Ancestors of 2" << endl;
    myTree.printAncestor(2);

    cout << "Level of 2: " << myTree.whatLevelAmI(2) << endl;
}