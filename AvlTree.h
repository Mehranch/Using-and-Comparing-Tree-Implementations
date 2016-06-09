#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream> 
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root_{ nullptr }
      { }
    
    AvlTree( const AvlTree & rhs ) : root_{ nullptr }
    {
        root_ = clone( rhs.root_ );
    }

    AvlTree( AvlTree && rhs ) : root_{ rhs.root_ }
    {
        rhs.root_ = nullptr;
    }
    
    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && rhs )
    {
        std::swap( root_, rhs.root_ );
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root_ )->element_;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root_ )->element_;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root_ );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root_ == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root_ );
	cout << endl;
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root_ );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root_ );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root_ );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root_ );
    }

    int heightOfTree() const {
      return heightOfNode(root_);
    }

    // ===== USER DEFINED FUNCTIONS =====

    Comparable* find(const Comparable &x) {
        int calls = 0;
        return find(x, root_, calls);
    }

    pair<Comparable*, int> find_count(const Comparable &x) {
        int calls = 0;
        return pair<Comparable*, int>(find(x, root_, calls), calls);
    }

    bool remove_count(const Comparable &x) {
        remove_calls = 0;
        return remove_count(x, root_);
    }

    size_t size() {
        if (isEmpty()) return 0;
        return size(root_) + 1;
    }

    int depth() {
        if (isEmpty()) return 0;
        return depth(root_, 1);
    }

    int get_remove_calls() {
        return remove_calls;
    }

    void range(Comparable left, Comparable right) {
        range(root_, left, right);
    }

    // ===== USER DEFINED FUNCTIONS END =====
  private:
    struct AvlNode
    {
        Comparable element_;
        AvlNode   *left_;
        AvlNode   *right_;
        int       height_;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element_{ ele }, left_{ lt }, right_{ rt }, height_{ h } { }
        
        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element_{ std::move( ele ) }, left_{ lt }, right_{ rt }, height_{ h } { }
    };

    AvlNode *root_;

    // USER VARS
    int remove_calls;

    // ===== USER DEFINED FUNCTIONS =====

    Comparable* find(const Comparable &x, AvlNode *t, int &calls) {
        if (t == nullptr) {
            return nullptr;
        } else if (x < t->element_) {
            calls++;
            return find(x, t->left_, calls);
        } else if (t->element_ < x) {
            calls++;
            return find(x, t->right_, calls);
        } else {
            return &(t->element_);
        }
    }

    bool remove_count( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            return false;   // Item not found; do nothing
        
        if( x < t->element_ ) {
            remove_calls++;
            remove_count( x, t->left_ );
        }
        else if( t->element_ < x ) {
            remove_calls++;
            remove_count( x, t->right_ );
        }
        else if( t->left_ != nullptr && t->right_ != nullptr ) // Two children
        {
            t->element_ = findMin( t->right_ )->element_;
            remove_calls++;
            remove_count( t->element_, t->right_ );
        }
        else
        {
            AvlNode *oldNode = t;
            t = ( t->left_ != nullptr ) ? t->left_ : t->right_;
            delete oldNode;
        }
        
        balance( t );
        return true;
    }

    size_t size(AvlNode *t) {
        if (t == nullptr) return 0;
        size_t left = 0, right = 0;
        if (t->left_ != nullptr)
            left = size(t->left_) + 1;
        if (t->right_ != nullptr)
            right = size(t->right_) + 1;
        return left + right;
    }

    int depth(AvlNode *t, int d) {
        if (t == nullptr) return 0;
        if (t->left_ == nullptr && t->right_ == nullptr) {
            return d + 1;
        }
        return d + depth(t->left_, d + 1) + depth(t->right_, d + 1);
    }

    void range(AvlNode *t, Comparable left, Comparable right) {
        if (t == nullptr) return;
        if (left < t->element_) range(t->left_, left, right);
        if (left < t->element_ && t->element_ < right) cout << t->element_ << endl;
        if (t->element_ < right) range(t->right_, left, right);
    }

    // ===== USER DEFINED FUNCTIONS END =====

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ x, nullptr, nullptr };
        else if( x < t->element_ )
            insert( x, t->left_ );
        else if( t->element_ < x )
            insert( x, t->right_ );
        else
            t->element_.merge(x);
        
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element_ )
            insert( std::move( x ), t->left_ );
        else if( t->element_ < x )
            insert( std::move( x ), t->right_ );
        else
            t->element_.merge(x);
        
        balance( t );
    }
     
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        
        if( x < t->element_ )
            remove( x, t->left_ );
        else if( t->element_ < x )
            remove( x, t->right_ );
        else if( t->left_ != nullptr && t->right_ != nullptr ) // Two children
        {
            t->element_ = findMin( t->right_ )->element_;
            remove( t->element_, t->right_ );
        }
        else
        {
            AvlNode *oldNode = t;
            t = ( t->left_ != nullptr ) ? t->left_ : t->right_;
            delete oldNode;
        }
        
        balance( t );
    }
    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( heightOfNode( t->left_ ) - heightOfNode( t->right_ ) > ALLOWED_IMBALANCE ) {
            if( heightOfNode( t->left_->left_ ) >= heightOfNode( t->left_->right_ ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        } else if( heightOfNode( t->right_ ) - heightOfNode( t->left_ ) > ALLOWED_IMBALANCE ) {
            if( heightOfNode( t->right_->right_ ) >= heightOfNode( t->right_->left_ ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
	}
        t->height_ = max( heightOfNode( t->left_ ), heightOfNode( t->right_ ) ) + 1;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left_ == nullptr )
            return t;
        return findMin( t->left_ );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right_ != nullptr )
                t = t->right_;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element_ )
            return contains( x, t->left_ );
        else if( t->element_ < x )
            return contains( x, t->right_ );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element_ )
                t = t->left_;
            else if( t->element_ < x )
                t = t->right_;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left_ );
            makeEmpty( t->right_ );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left_ );
            cout << t->element_ << " ";
            printTree( t->right_ );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element_, clone( t->left_ ), clone( t->right_ ), t->height_ };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int heightOfNode( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height_;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left_ child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left_;
        k2->left_ = k1->right_;
        k1->right_ = k2;
        k2->height_ = max( heightOfNode( k2->left_ ), heightOfNode( k2->right_ ) ) + 1;
        k1->height_ = max( heightOfNode( k1->left_ ), k2->height_ ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right_ child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right_;
        k1->right_ = k2->left_;
        k2->left_ = k1;
        k1->height_ = max( heightOfNode( k1->left_ ), heightOfNode( k1->right_ ) ) + 1;
        k2->height_ = max( heightOfNode( k2->right_ ), k1->height_ ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left_ child.
     * with its right child; then node k3 with new left_ child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left_ );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left_ child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right_ );
        rotateWithRightChild( k1 );
    }
};

#endif
