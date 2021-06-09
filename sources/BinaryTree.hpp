#pragma once

#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include <fstream>
#include <stack>
#include <string>
/*
written by Liron Asaraf
sources: geeksforgeeks, stack overflow

*/

using namespace std;
namespace ariel
{
    

    template <typename T>
    class BinaryTree
    {
        enum iterator_type { PREORDER, INORDER, POSTORDER };
    

        struct Node {
            T value;                                                                                                                                                                                            //kepasion
            Node *right, *left;
            Node(T k) : value(k), right(nullptr), left(nullptr){}
            Node(const Node* o) : value(0), right(nullptr), left(nullptr){
            }
        };
        Node *root =  nullptr;
   
        Node* findNode(Node *n ,T key) {
            if(!n) {return nullptr;}
            if(n->value == key) { return n; }
            Node* found = findNode(n->left, key);
            if(found) { return found;}
            return findNode(n->right, key);
        }
        class iterator
        {
        private:
            Node *current_node;
            std::stack<Node*> ordered;
            iterator_type t;




        public:

            iterator(iterator_type type, Node* ptr) 
            {
                ordered.push(nullptr);
            
                if (type == PREORDER){

                    putPreorder(ptr,ordered);
                    
                    
                    }
                

                
                else if (type == INORDER){
                    putInorder(ptr,ordered);

                }
                else{ 
                    putPostorder(ptr,ordered);

                } 

                if(!ordered.empty()){
                    current_node = ordered.top();
                    ordered.pop();
                }




            }


            T &operator*() const
            {
                return current_node->value;
            }

            T *operator->() const
            {
                return &(current_node->value);
            }

		    bool operator==(const iterator& rhs) const {
			return current_node == rhs.current_node;
		    }
		    bool operator!=(const iterator& rhs) const {
			return current_node != rhs.current_node;
		    }

            iterator &operator++()
            {
                if(ordered.empty()){ current_node = nullptr; }
                else {
                    current_node = ordered.top();
                    ordered.pop();
                }
                return *this;
            


            }

            iterator operator++(int)
            {
                iterator tmp = *this;
                if(ordered.empty()){ current_node = nullptr;
                }
                else { 
                    current_node = ordered.top();
                    ordered.pop();
                }
                return tmp;


            }



        };


    public:
        BinaryTree<T>()
        {
            root = nullptr;
        }
        //discractor
        ~BinaryTree<T>()
        {
            delete root;
        }
        // static void putPreorder(Node* n, stack<Node*> &s);
        // static void putInorder(Node* n, stack<Node*> &s);
        // static void putPostorder(Node* n, stack<Node*> &s);
        auto begin_preorder() {
             return iterator(PREORDER, root); }
        auto end_preorder() {
             return iterator(PREORDER, nullptr); }
        auto begin_inorder() {
             return iterator(INORDER, root);}
        auto end_inorder() {
             return iterator(INORDER, nullptr);}
        auto begin_postorder(){
             return iterator(POSTORDER, root); }
        auto end_postorder(){
             return iterator(POSTORDER, nullptr);}
        auto begin(){
             return begin_inorder(); }
        auto end(){
             return end_inorder(); }
        
        BinaryTree<T>(const BinaryTree<T> &t)
        {
            if (this->root != nullptr)
            {this->root = nullptr; }
            copyRoot(t.root);
        }
        BinaryTree<T>(BinaryTree<T> &&t) noexcept
        {
            root = t.root;
            t.root = nullptr;
        }

        BinaryTree<T> &operator=(BinaryTree<T> &&t) noexcept
        {
            delete root;
            root = t.root;
            t.root = nullptr;
        }

        BinaryTree<T> &operator=(const BinaryTree<T> c)
        {
            if (this != &c)
            {
                delete root;
                copyRoot(c.root);
            }
            return *this; }



        void copyRoot(Node *cRoot)
        {
            if (cRoot == nullptr)
            {root = nullptr;}
            else
            {
                root = new Node(cRoot->value);

                copyTree(root, cRoot);
            }
        }
        void copyTree(Node *node, Node *t)
        {
            if (t == nullptr)
            {root = nullptr;}
            else
            {
                if (t->left != nullptr)
                {node->left = new Node(t->left->value);}
                if (t->right != nullptr)
                { node->right = new Node(t->right->value);}
                if (t->left != nullptr)
                {copyTree(node->left, t->left);}
                if (t->right != nullptr)
                {copyTree(node->right, t->right);}
            }
        }
        BinaryTree<T> &add_root(T r) { 
              if(root == nullptr)
              {
                  root = new Node(r);

            
              }
              else {
                  root -> value = r;

              }
              return *this;
        }

        BinaryTree<T> &add_left(T val, T node) { 

            Node *n = findNode(root, val);
                if (n == nullptr){
                    throw std::invalid_argument{"node does not exist"};
                }
                if(n->left == nullptr){
                    n->left = new Node(node);
                } else{
                    n->left->value = node;
                }
                return *this;
        }

            
        
            
            
            
            
          

        BinaryTree<T> &add_right(T val, T node) { 
            Node *n = findNode(root, val);
                if (n == nullptr){
                    throw std::invalid_argument{"node does not exist"};
                }
                if(n->right == nullptr){
                    n->right = new Node(node);
                } else{
                    n->right->value = node;
                }
                return *this;
        }
        



        friend std::ostream &operator<<(std::ostream &output, const BinaryTree<T> &bt)
        {
            return output;
        }

        static void putPreorder(Node* n, stack<Node*> &s){
            if (n!=nullptr){
                putPreorder(n->right,s);
                putPreorder(n->left,s);
                s.push(n);

            }else{
            return;}
        }
        static void putPostorder(Node* n, stack<Node*> &s){
            if(n!=nullptr){
                s.push(n);
                putPostorder(n->right,s);
                putPostorder(n->left,s);
            }
            else{
            return;}
        }
        static void putInorder(Node* n, stack<Node*> &s){
            if(n!=nullptr){
                putInorder(n->right, s);
                s.push(n);
                putInorder(n->left,s);
            }
            else{
            return; }
        }
   



    };
    
}