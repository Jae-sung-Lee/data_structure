#include <iostream>
#include <algorithm>
#include <optional>
#include <unistd.h>

template <typename T, typename U>
class AVLNode{
    
    public :
        T key;
        U value;
        AVLNode<T,U> * left;
        AVLNode<T,U> * right;
        int height;

        AVLNode<T,U>(const T& k, const U& v)
        {
            key = k;
            value = v;
            left = nullptr;
            right = nullptr;
            height = 1;
        }        
        
};

template <typename T, typename U>
class AVLTree {
    public : 
        AVLNode<T,U> * root = nullptr;
        ~AVLTree() {
            removeall(root);
        }

        void insert(const T& key, const U& value);
        U search(const T& key);
        bool remove(const T& key);

        //for checking
        void preorder(AVLNode<T,U>*& node){
            if(!node) return;
	        		
            std::cout<<node->key<<": "<<node->value<<std::endl;
            preorder(node->left);
            preorder(node->right);
        }
        void inorder(AVLNode<T,U>*& node){
            if(!node) return;

            inorder(node->left);
            std::cout<<node->key<<": "<<node->value<<std::endl;
            inorder(node->right);
        }

    private :
        AVLNode<T,U>* findMin(AVLNode<T,U>* node) const;     //Finding the node that has mimnimum key in the subtree
        int getHeight(AVLNode<T,U>*& node);
        int getBalance(AVLNode<T,U>*& node);
        AVLNode<T,U>* rotate_left(AVLNode<T,U>* node);
        AVLNode<T,U>* rotate_right(AVLNode<T,U>* node);

        AVLNode<T,U>* insert(AVLNode<T,U>*& node, const T& key, const U& value);
        U search(AVLNode<T,U>*& node, const T& key);
        AVLNode<T,U>* remove(AVLNode<T,U>*& node, const T& key);
        void removeall(AVLNode<T,U>*& node);

};

template <typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::findMin(AVLNode<T,U>* node) const{
     if(node==nullptr)
       return nullptr;
     if(node->left==nullptr)
       return node;
     return findMin(node->left);
}          

template <typename T, typename U>
int AVLTree<T,U>::getHeight(AVLNode<T,U>*& node){
    if(!node) return 0;
    return node->height;
}

template <typename T, typename U>
int AVLTree<T,U>::getBalance(AVLNode<T,U>*& node){
    if(!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

template<typename T, typename U>
void AVLTree<T,U>::insert(const T& key, const U& value) {
    root = insert(root, key, value);
}

template<typename T, typename U>
U AVLTree<T,U>::search(const T& key) {
    return search(root, key);
}

template<typename T, typename U>
bool AVLTree<T,U>::remove(const T& key) {
    if(!search(root,key)) return false;
    root = remove(root, key);
    return true;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::rotate_left(AVLNode<T,U>* node){
     AVLNode<T,U>* newnode=node->right;
     AVLNode<T,U>* left_newnode=newnode->left;

     node->right=left_newnode;
     newnode->left=node;
     
     if(getHeight(node->left)>getHeight(node->right))
        node->height=(getHeight(node->left))+1;
     else
        node->height=(getHeight(node->right))+1;
     if(getHeight(newnode->left)>getHeight(newnode->right))
        newnode->height=(getHeight(newnode->left)+1);
     else 
        newnode->height=(getHeight(newnode->right))+1;

     return newnode;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::rotate_right(AVLNode<T,U>* node){
     AVLNode<T,U>* newnode=node->left;
     AVLNode<T,U>* right_newnode=newnode->right;

     node->left=right_newnode;
     newnode->right=node;

     if(getHeight(node->left)>getHeight(node->right))
         node->height=(getHeight(node->left))+1;
     else
         node->height=(getHeight(node->right))+1;
     if(getHeight(newnode->left)>getHeight(newnode->right))
        newnode->height=(getHeight(newnode->left))+1;
     else
        newnode->height=(getHeight(newnode->right))+1;

     return newnode;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::insert(AVLNode<T,U>*& node, const T& key, const U& value) {
       if(node==nullptr) 
           node= new AVLNode<T,U>(key,value);
       if(key>node->key)
           node->right= insert(node->right,key,value);
       else if(key<node->key)
           node->left= insert(node->left,key,value);
       else
         {  
           node->value=value;
           return node;
         }
         
       if(getHeight(node->left)>getHeight(node->right))
           node->height=(getHeight(node->left))+1;
       else
           node->height=(getHeight(node->right))+1;
         
       if(node->left!=nullptr && getBalance(node)>1 && key<node->left->key)
            return rotate_right(node);
       if(node->left!=nullptr && getBalance(node)>1 && key>node->left->key)
         {  
            node->left=rotate_left(node->left);
            return rotate_right(node);
         }
       if(node->right!=nullptr && getBalance(node)<-1 && key>node->right->key)
            return rotate_left(node);
       if(node->right!=nullptr && getBalance(node)<-1 && key<node->right->key)
           {
             node->right=rotate_right(node->right);
             return rotate_left(node);
           }

       return node;    
}
template<typename T, typename U>
U AVLTree<T, U>::search(AVLNode<T, U>*& node, const T& key) {
       if(node==nullptr)
             return 0;
       else if(key>node->key)
             return search(node->right,key);
       else if(key<node->key)
             return search(node->left,key);
       else
             return node->value;
}

template<typename T, typename U>
AVLNode<T,U>* AVLTree<T,U>::remove(AVLNode<T,U>*& node, const T& key) {
         
          if(node==nullptr)
             return node;
          else if(key>node->key)
             node->right=remove(node->right,key);
          else if(key<node->key)
             node->left=remove(node->left,key);
          else
          {
            if(node->left==nullptr && node->right==nullptr)
              {
               delete node;
               node=nullptr;
              }
            else if(node->right==nullptr)
              { 
               AVLNode<T,U>* trashnode=node;
               node=node->left;
               delete trashnode;
               trashnode=nullptr;
              }
            else if(node->left==nullptr)
              {
               AVLNode<T,U>* trashnode=node;
               node=node->right;
               delete trashnode;
               trashnode=nullptr;
              }
            else
              {
               node->key=findMin(node->right)->key;
               node->value=findMin(node->right)->value;
               node->right=remove(node->right, node->key);
              }
          }

            if(node==nullptr)
              return node;
  
            if(getHeight(node->left)>getHeight(node->right))
               node->height= (getHeight(node->left))+1;
            else
               node->height=(getHeight(node->right))+1;
       
           
            if(node->left!=nullptr && getBalance(node)>1 && (getBalance(node->left)>=0))
               return rotate_right(node);
            if(node->left!= nullptr && getBalance(node)>1 && (getBalance(node->left)<0))
             {
               node->left=rotate_left(node->left);
               return rotate_right(node);
             }
            if(node->right!=nullptr && getBalance(node)<-1 && (getBalance(node->right)<=0))
               return rotate_left(node);
            if(node->right!=nullptr && getBalance(node)<-1 && (getBalance(node->right)>0))
             {
               node->right=rotate_right(node->right);
               return rotate_left(node);
             }       
         
       return node; 
}

template<typename T, typename U>
void AVLTree<T,U>::removeall(AVLNode<T,U>*& node) {
          if(node!=nullptr)
          { 
            if(node->right!=nullptr)
               removeall(node->right);
            if(node->left!=nullptr)
              removeall(node->left);
           
            delete node;
          }
          node=nullptr;
}
