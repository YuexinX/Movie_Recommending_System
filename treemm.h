//
//  treemulti.h
//  Project 4
//
//  Created by Time Thief on 3/14/23.
//

#ifndef treemm_h
#define treemm_h

#include <iostream>
#include <list>
#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator()
        :curr(0)
        {
            // Replace this line with correct code.
        }
        Iterator(std::vector<ValueType>* p)
        {
            value = p;
            curr = 0;
        }

        ValueType& get_value() const
        {
            return (*value)[curr];
        }

        bool is_valid() const
        {
            if(value == nullptr)
                return false;
            return curr<value->size();
        }

        void advance()
        {
            curr++;
        }

      private:
        std::vector<ValueType>* value = nullptr;
        int curr;
    };

    TreeMultimap()
    :root(nullptr)
    {
    }

    ~TreeMultimap()
    {
        clear(root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        //if the list is empty, create new node
        if(root == nullptr)
        {
            root = new Node(key, value);
            return;
        }
        Node *cur = root;
        for(;;)
        {
            if(key == cur->key)
            {
                    cur->val.push_back(value);
                    return;
            }
            if(key<cur->key)
            {
                if(cur->left != nullptr)
                    cur = cur->left;
                else
                {
                    cur->left = new Node(key, value);
                    return;
                }
            }
            else if(key>cur->key)
            {
                if(cur->right != nullptr)
                    cur = cur->right;
                else
                {
                    cur->right = new Node(key, value);
                    return;
                }
            }
        }
    }

    Iterator find(const KeyType& key) const
    {
       Node *p=root;
        while(p != nullptr)
        {
            if(key == p->key)
                return Iterator(&p->val);
            if(key < p->key)
                p = p->left;
            else if(key > p->key)
                p = p->right;
        }
        return Iterator(); // Replace this line with correct code.
    }

    
    
  private:
    struct Node
    {
        Node(KeyType k, ValueType v)
        {
            key = k;
            val.push_back(v);
            left = right = nullptr;
        }
        KeyType key;
        std::vector<ValueType> val;
        Node* left, *right;
    };
    void clear(Node * node)
    {
        if(node == nullptr)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
       node = nullptr;
    }
    Node* root;
};


#endif /* treemulti_h */
