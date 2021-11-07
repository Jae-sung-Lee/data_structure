#include <algorithm>
#include <iterator>
#include <vector>
#include <random>
#include <string>
#include "bstree.h"
#include "avltree.h"
#include <iostream>

using namespace std;

int main () {

    BSTree<string,int> tree;

    tree.insert("david",1215);
   tree.insert("hannah",5412);
   tree.insert("emma",3234);
   tree.insert("paul",3345);
   tree.insert("james",1123);
   tree.insert("lee",6643);
   tree.insert("summer",5543);
   tree.remove("hannah");
    tree.insert("scarlett",5415);
    tree.insert("alice",5121);
    tree.remove("james");
      
	std::cout << ("print inorder") << std::endl;
	std::cout << ("------------------------") << std::endl;
    tree.inorder(tree.root);
    cout<<endl;
	std::cout << ("print preorder") << std::endl;
	std::cout << ("------------------------") << std::endl;
    tree.preorder(tree.root);
    cout<<endl;

   cout<<"Search david: "<<tree.search("david")<<endl;
    
   // print 0 if none
   cout<<"Search james: "<<tree.search("james")<<endl;

    return 0;
}
