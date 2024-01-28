#include<stdio.h>
#include<stdlib.h>


// Student Name: Bar�� Giray Akman
// Student ID: 150121822

typedef struct AVLTree{
	int height;
	int val;
	struct AVLTree *left;
	struct AVLTree *right;
	
	
	
}AVLTree;

// Global variables for computing costs.
int rotation_count_avl = 0;
int rotation_count_splay = 0;
int comparison_count_splay = 0;
int comparison_count_avl = 0;

int validator = 0;
typedef struct SplayTree{
	
	int val;
	struct SplayTree* parent;
	struct SplayTree *left;
	struct SplayTree *right;
	
	
}SplayTree;

SplayTree* temp_for_splay=NULL;

// Function to find the height.
int findHeight(AVLTree* root){
	if(root==NULL)
		return 0;
	
	return root->height;
}


AVLTree* createNode(int val){
	AVLTree *new_node = (AVLTree*)malloc(sizeof(AVLTree));
	new_node->height = 0;
	new_node->val = val;
	new_node->left=NULL;
	new_node->right= NULL;
	return new_node;
	
}

// It creates a node for Splay Tree.
SplayTree* createNodeSplayTree(int val){
	SplayTree *new_node = (SplayTree*)malloc(sizeof(SplayTree));
	new_node->val = val;
	new_node->left=NULL;
	new_node->right= NULL;
	return new_node;
	
}

// It searchs the node entered as a num.
int searchNode(AVLTree* root, int num){
	
	if(num>root->val && root->right)
	   searchNode(root->right, num);
	
	else if(num<root->val && root->left)
	   searchNode(root->left, num);
	
	if(num==root->val)
		return 1;
		
	
}



AVLTree* left_rotateAVLTree(AVLTree* root){
	
	// Right will be our new root.
	AVLTree* right = root->right;
	AVLTree* right_left = right->left;
	
	
	right->left = root;
	root->right = right_left;
	
	// Updating the height values.
	if(!root->left && !root->right) root->height = 0;
	else if(findHeight(root->left) > findHeight(root->right))
		root->height = findHeight(root->left) + 1;
	else root->height = findHeight(root->right) + 1;
	
	// Updating the height values.
	if(!right->left && !right->right) root->height = 0;
	else if(findHeight(right->right) > findHeight(right->left))
		right->height = findHeight(right->right) +1 ;
	
	else right->height = findHeight(right->left) +1;

	rotation_count_avl++;
	return right;
	
}

// It rotates our AVL tree to the leftern side.
AVLTree* right_rotateAVLTree(AVLTree* root){
	
	// Left will be our new root.
	AVLTree* left = root->left;
	
	AVLTree* left_right = left->right;
	AVLTree* right= root->right;
	left->right = root;
	root->left = left_right;
	
	if(!root->left && !root->right) root->height = 0;
	
	else if(findHeight(root->left) > findHeight(root->right))
		root->height = findHeight(root->left) + 1;
	else root->height = findHeight(root->right) + 1;

	if(!left->left && !left->right) root->height = 0;

	else if(findHeight(left->right) > findHeight(left->left))
		left->height = findHeight(left->right) +1 ;
	
	else left->height = findHeight(left->left) +1;
	
	rotation_count_avl++;
	return left;
	
}

// It inserts a new node to AVL Tree then handle the rotating operations.
AVLTree* insertNodeAVLTree(AVLTree *root, AVLTree* new_leaf){
	
	
	// Those if structures will maintain depending on the new node which will be inserted.
	if(root && root->val<new_leaf->val){
		comparison_count_avl++;
		root->right= insertNodeAVLTree(root->right, new_leaf);
		
	}
	
	else if(root && root->val>new_leaf->val){
		comparison_count_avl++;
		root->left = insertNodeAVLTree(root->left, new_leaf);
		
	}
		
	
	else if(root && root->val == new_leaf->val){
		comparison_count_avl++;
		return root;
	}
		
	else if(!root) return new_leaf;
	
	
	
	if(findHeight(root->left) > findHeight(root->right))
		root->height = 1+ findHeight(root->left);
	else root->height = 1 + findHeight(root->right);
	
	int balance = 0;
	// Operations to achieve the balance
	if(root->left)
	   balance = findHeight(root->left)+1;

	if(root->right)
		balance = balance - 1 -findHeight(root->right);
	
	// Right Rotation
	if(balance>1 && new_leaf->val<root->left->val){
		
		root = right_rotateAVLTree(root);
		return root;
	}
		
	// Left Rotation
	else if(balance<-1 && new_leaf->val > root->right->val){
		
		root = left_rotateAVLTree(root);
		return root;
	}
		
	// Left-Right Rotation
	else if(balance>1 && new_leaf->val>root->left->val){
		

		
		root->left = left_rotateAVLTree(root->left);
		root = right_rotateAVLTree(root);
		
		return root;
		
	}
	// Right-Left Rotation
	else if(balance<-1 && new_leaf->val<root->right->val){

		root->right = right_rotateAVLTree(root->right);
		root = left_rotateAVLTree(root);
		return root;
		
	}
	return root;
}

// Pre Order traversal for Splay Tree.
void pre_order_traversal_avl(AVLTree* root){
	if(root){
		printf("%d ", root->val);
		pre_order_traversal_avl(root->left);
		pre_order_traversal_avl(root->right);
	}
	
}

// It reads file and creates an AVL Tree according to that.
AVLTree* readFileandCreateAVL(FILE* fPtr){
	
	AVLTree* root=NULL;

	int i=0;
 	while(fscanf(fPtr, "%d", &i)== 1){
 		AVLTree* new_node =createNode(i); 
		root = insertNodeAVLTree(root, new_node);
	}
	fclose(fPtr);
	return root;
}

// Pre Order traversal for Splay Tree.
void pre_order_traversal_splay(SplayTree* root){
	
	if(root){
		
	
		printf("%d ", root->val);
		pre_order_traversal_splay(root->left);
		pre_order_traversal_splay(root->right);
	}
	
}



// Insertion operation for node.
SplayTree* insertNodeSplayTree(SplayTree* root, SplayTree* new_node, SplayTree* parent){


	if(!root){
		
		new_node->parent = parent;
		return new_node;
	}
		
	else if(root->val > new_node->val){
		comparison_count_splay++;
		root->parent = parent;
	
		root->left = insertNodeSplayTree(root->left, new_node, root);
	
	}
		
	else if(root->val < new_node->val){
		comparison_count_splay++;
		root->parent = parent;
		root->right = insertNodeSplayTree(root->right, new_node, root);
	}	
		
	else if(root->val == new_node->val){
		comparison_count_splay++;
		temp_for_splay= root;
		validator = 1;
		return root;
	}
	
}

	// An operation to rotate the node to the rightern side for splay tree.
	SplayTree* right_rotateSplayTree(SplayTree* root){
		// Left will be our new root.
		SplayTree* left = root->left;
		SplayTree* left_right = left->right;
		left->right = root;
		root->left = left_right;
		if(left_right && left_right->parent)
			left_right->parent = root;
		SplayTree* temp2= root->parent;
		root->parent = left;
		left->parent = temp2;
		rotation_count_splay++;
		return left;
		
	}
	
	// An operation to rotate the node to the leftern side for splay tree.
	SplayTree* left_rotateSplayTree(SplayTree* root){
		
		// Right will be our new root.
		SplayTree* right = root->right;
		SplayTree* right_left = right->left;
		right->left = root;
		root->right = right_left;
		if(right_left && right_left->parent)
			right_left->parent = root;
		SplayTree* temp2 = root->parent;
		root->parent = right;
		right->parent = temp2;
		rotation_count_splay++;
		return right;
		
	}
	// Splaying Operation for Splay Tree.
	SplayTree* splay(SplayTree* root, SplayTree* new_node, SplayTree* parent){
	
		SplayTree* temp;
		
		if(!root) return NULL;
		
		temp = new_node;
		
	
		while(temp->parent) {

			if(temp->parent && temp->parent->parent && temp->parent->parent->left && temp->parent->parent->left->right && temp->parent->parent->left->right->val == temp->val){
				left_rotateSplayTree(temp->parent);
				temp->parent->left = temp;
				
				SplayTree* temp2 = temp->parent;
				temp = right_rotateSplayTree(temp->parent);
				
				
				if(temp->parent && temp->parent->left  && temp->parent->left->val == temp2->val)
					temp->parent->left = temp;
				
				else if(temp->parent && temp->parent->right && temp->parent->right->val == temp2->val)
					temp->parent->right = temp;
			}

			else if( temp->parent && temp->parent->parent && temp->parent->parent->right && temp->parent->parent->right->left && temp->parent->parent->right->left->val == temp->val){

				right_rotateSplayTree(temp->parent);
				temp->parent->right = temp;
				SplayTree* temp2 = temp->parent;
				
				temp= left_rotateSplayTree(temp->parent);

				if(temp->parent && temp->parent->left && temp->parent->left->val == temp2->val)
					temp->parent->left = temp;
				
				else if(temp->parent && temp->parent->right && temp->parent->right->val == temp2->val)
					temp->parent->right = temp;
			}
			
			else if(temp->parent &&  temp->parent->parent && temp->parent->parent->right && temp->parent->parent->right->right && temp->parent->parent->right->right->val == temp->val){
				SplayTree* temp3=NULL;
				SplayTree* temp4 = temp->parent->parent;
				if(temp->parent->parent->parent)
					temp3 = temp->parent->parent->parent;
				temp->parent = left_rotateSplayTree(temp->parent->parent);
				temp = left_rotateSplayTree(temp->parent);
				if(temp3 && temp3->right && temp3->right->val == temp4->val)
					temp3->right = temp;
				else if(temp3 && temp3->left && temp3->left->val == temp4->val)
					temp3->left = temp;
			}
			
			else if(temp->parent &&  temp->parent->parent && temp->parent->parent->left && temp->parent->parent->left->left && temp->parent->parent->left->left->val == temp->val){

				SplayTree* temp3= NULL;
				SplayTree* temp4 =temp->parent->parent;
				if(temp->parent->parent->parent)
					temp3 = temp->parent->parent->parent;
				temp->parent = right_rotateSplayTree(temp->parent->parent);
				
				
				temp = right_rotateSplayTree(temp->parent);
				if(temp3 && temp3->right && temp3->right->val == temp4->val)
					temp3->right = temp;
				else if(temp3 && temp3->left && temp3->left->val == temp4->val)
					temp3->left = temp;
				
			}
			else if(temp->parent && !temp->parent->parent&& temp->parent->left && temp->parent->left->val == temp->val){

				temp = right_rotateSplayTree(temp->parent);
			
			}
			else if(temp->parent && !temp->parent->parent && temp->parent->right && temp->parent->right->val == temp->val){
				temp = left_rotateSplayTree(temp->parent);
				
			
			}
			
		}
		
		return temp;
	}
	
void readFileAndCreateAndPrintTrees(FILE* fPtr){
	
	AVLTree* root = NULL;
	SplayTree* root2 = NULL;
	AVLTree* new_node;
	SplayTree* new_node2;
	int i;
	while(fscanf(fPtr, "%d", &i)== 1){
		new_node = createNode(i);
		new_node2 = createNodeSplayTree(i);
		
		root = insertNodeAVLTree(root, new_node);
		root2 = insertNodeSplayTree(root2, new_node2, NULL);
		if(temp_for_splay)
			new_node2 = temp_for_splay;
		
		root2 = splay(root2, new_node2, NULL);
		temp_for_splay = NULL;
	}
	
	printf("\n");
	printf("AVL Tree:\n");
	pre_order_traversal_avl(root);
	printf("\nTotal Cost: %d\n", rotation_count_avl + comparison_count_avl);
	printf("\nSplay Tree:\n");
	pre_order_traversal_splay(root2);
	printf("\nTotal Cost: %d", rotation_count_splay + comparison_count_splay);
	
	
}

SplayTree* readFileandCreateSplayTree(FILE* fPtr){
	
	SplayTree* root;

	int i=0;
	root = NULL;
	SplayTree* new_node;
 	while(fscanf(fPtr, "%d", &i)== 1){
 		
 		new_node =createNodeSplayTree(i);
		root = insertNodeSplayTree(root, new_node, NULL);
		if(temp_for_splay)
			new_node = temp_for_splay;
		root = splay(root, new_node, NULL);
		validator = 0;
		temp_for_splay = NULL;
	}
	fclose(fPtr);
	return root;
}

int main(int argc,char* argv[]){
		// In that part, I have used argument as it is wanted. But also, I have written an additional else if file reading process is unsuccessful.
		FILE *fPtr;
		// Initially, file is read according to txt file name entered.
	 	if(argc==1)
        	printf("Error message!\n");
    
    	if(argc>=2){
	    	
			fPtr = fopen(argv[1], "r");
		}
		else fPtr = fopen("input2.txt", "r");
		
		
		readFileAndCreateAndPrintTrees(fPtr);
		
}



























