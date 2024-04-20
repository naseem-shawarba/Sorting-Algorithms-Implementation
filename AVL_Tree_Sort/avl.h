// Definition of a node in an AVL tree
struct AVLNode
{
	struct AVLNode *left;	// Pointer to the left child node
	struct AVLNode *right;	// Pointer to the right child node
	struct AVLNode *parent; // Pointer to the parent node
	int value;				// Value stored in the node
	int height;				// Height of the node in the tree
};

// A binary search tree with a root node 'root' and the number of elements in the tree (this value must be kept up-to-date!)
struct AVLTree
{
	struct AVLNode *root; // Pointer to the root node of the AVL tree
	int numberOfNodes;	  // Number of nodes in the AVL tree
};

// Typedefs to avoid using 'struct' in the declarations
typedef struct AVLNode AVLNode;
typedef struct AVLTree AVLTree;

// Outputs the entire AVL tree in in-order traversal order
void AVL_in_order_walk(AVLTree *avlt);

// Performs a left rotation on the specified node
void AVL_rotate_left(AVLTree *avlt, AVLNode *x);

// Performs a right rotation on the specified node
void AVL_rotate_right(AVLTree *avlt, AVLNode *y);

// Balances the subtree rooted at 'node'.
void AVL_balance(AVLTree *avlt, AVLNode *node);

// Inserts the value 'value' into the tree.
void AVL_insert_value(AVLTree *avlt, int value);

// Deletes the entire AVL tree and frees the memory of all nodes.
void AVL_remove_all_elements(AVLTree *avlt);

// Prints the given AVL tree to stdout.
void print_AVL_tree(AVLTree *avlt);

// Parses the input from the given file and performs the corresponding operations on the tree 'avlt'.
void execute_operations(AVLTree *avlt, FILE *input);
