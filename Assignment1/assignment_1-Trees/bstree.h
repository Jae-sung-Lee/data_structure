#include <iostream>
#include <optional>

template <typename T, typename U>
class BSNode{
    
    public :
        T key;
        U value;
        BSNode<T,U> * left;
        BSNode<T,U> * right;

        BSNode<T,U>(const T& k, const U& v)
        {
            key = k;
            value = v;
            left = nullptr;
            right = nullptr;
        }

};

template<typename T, typename U>
class BSTree {

    public : 
        BSNode<T,U> * root = nullptr;
        ~BSTree() {
            removeall(root);
        }

        bool insert(const T& key, const U& value);
        U search(const T& key);
        bool remove(const T& key);
        
        //for checking
        void preorder(BSNode<T,U>*& node){
            if(!node) return;

            std::cout<<node->key<<": "<<node->value<<std::endl;
            preorder(node->left);
            preorder(node->right);
        }
        void inorder(BSNode<T,U>*& node){
            if(!node) return;

            inorder(node->left);
            std::cout<<node->key<<": "<<node->value<<std::endl;
            inorder(node->right);
        }

    private :
	    BSNode<T,U>* findMin(BSNode<T,U>* node) const;    //Finding the node that has minimum key in: the subtree
        bool insert(BSNode<T,U>*& node, const T& key, const U& value);
        U search(BSNode<T,U>*& node, const T& key);
        BSNode<T,U>* remove(BSNode<T,U>*& node, const T& key);
        void removeall(BSNode<T,U>*& node);
};

template<typename T, typename U>
bool BSTree<T,U>::insert(const T& key, const U& value) {
    return insert(root, key, value);
}

template<typename T, typename U>
U BSTree<T,U>::search(const T& key) {
    return search(root, key);
}

template<typename T, typename U>
bool BSTree<T,U>::remove(const T& key) {
	if(!search(root,key)) return false;
    remove(root, key);
    return true;
}

template<typename T, typename U>
BSNode<T,U>* BSTree<T,U>::findMin(BSNode<T,U>* node) const{
	if(node==nullptr)
		return nullptr;
	if(node->left==nullptr)
		return node;
	return findMin(node->left);
}

template<typename T, typename U>
bool BSTree<T,U>::insert(BSNode<T,U>*& node, const T& key, const U& value) {
    if(node==nullptr)
       node=new BSNode<T,U>(key,value);
    if(key>node->key)
       {
	       if(node->right==nullptr)
	          node->right=new BSNode<T,U>(key,value);
           else 
		       return insert(node->right,key,value);
       }
    else if(key<node->key)
       {
	       if(node->left==nullptr)
	          node->left=new BSNode<T,U>(key,value);
	       else
		       return insert(node->left,key, value);
       }
    else 
       { 
	       node->value=value;
           return false;
       }
     return true;
}

template<typename T, typename U>
U BSTree<T,U>::search(BSNode<T,U>*& node, const T& key) { 
         if(node==nullptr)
            return 0;          
         else if(key>node->key)
	        return search(node->right, key);
	     else if(key<node->key)
		    return search(node->left, key);
	     else
		    return node->value;
}

template<typename T, typename U>
BSNode<T,U>* BSTree<T,U>::remove(BSNode<T,U>*& node, const T& key) {
    if(node==nullptr)
	   return node;
    else if(key>node->key)
       node->right=remove(node->right,key);
    else if(key<node->key)
	   node->left=remove(node->left,key);
    else
       {
          if(node->left==nullptr&&node->right==nullptr)
	        {
		      delete node;
              node=nullptr;
	        }
	      else if(node->right==nullptr)
	        { 
		      BSNode<T,U>* trashnode=node;
		      node=node->left;
		      delete trashnode;
              trashnode=nullptr;		   
	        }
	       else if(node->left==nullptr)
	        {
		      BSNode<T,U>* trashnode=node;
              node=node->right;
		      delete trashnode;
              trashnode=nullptr;		   
	        }
	       else
	        {  
		      node->key=findMin(node->right)->key;
		      node->value=findMin(node->right)->value;
		      node->right=remove(node->right,node->key);
		    }
       }
           return node;
}

template<typename T, typename U>
void BSTree<T,U>::removeall(BSNode<T,U>*& node) {
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
