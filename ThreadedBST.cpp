////////////////////////////////////////////////////////////////////////////////////////////
/*
  Algorithms and Data Structures
  Threaded BST - C++ DS LAB 5
  Contributors:
  Muhammed Suwaneh - 152120181098
  Department of Computer Engineering
  Eskisehir Osmangazi University, December 2020
  Eskisehir, Turkey 
 */
 ////////////////////////////////////////////////////////////////////////////////////////////

#include "ThreadedBST.h"
#include <iostream>
#include <algorithm>
///-----------------------------------------------
/// Erases all nodes in the tree
/// 
void ThreadedBST::eraseTreeNodes(BSTNode* node) {

	BSTNode* curr = this->min();

	while (curr != NULL) {

		BSTNode* n = this->next(curr);

		delete curr;

		curr = n;
	}
} //end-eraseTreeNodes

///-----------------------------------------------
/// Adds a given key to the BST
/// 
void ThreadedBST::add(int key) {

	BSTNode* node = root;
	BSTNode* parentNode = NULL;

	// search and set threads 
	while (node != NULL) {

		if (key == (node->key)) {
			throw std::exception("ThreadedBST::Add() Key already exist");
			return;
		}

		parentNode = node;

		if (key < (node->key)) {

			if (node->leftLinkType == CHILD)
				node = node->left;
			else
				break;
		}

		else {

			if ((node->rightLinkType) == CHILD)
				node = node->right;
			else
				break;
		}
	}

	// set 
	BSTNode* tempNode = new BSTNode(key);

	// set left and right pointers and threads
	if (parentNode == NULL) {

		root = tempNode;
		tempNode->left = NULL;
		tempNode->right = NULL;	
	}

	else {

		// traverse to the left branch tree
		if (key < (parentNode->key)) {

			tempNode->left = parentNode->left;
			tempNode->right = parentNode;
			parentNode->leftLinkType = CHILD;
			parentNode->left = tempNode;
		}
		// traverse to the right branch of tree
		else {

			tempNode->left = parentNode;
			tempNode->right = parentNode->right;
			parentNode->rightLinkType = CHILD;
			parentNode->right = tempNode;
		}
	}

} // end-add

///-----------------------------------------------
/// Removes a given key from the BST (if it exists)
/// 
void ThreadedBST::remove(int key) {

	BSTNode* parentNode = root, *tempNode = root;

	// check for empty trees
	if (parentNode == NULL)
		return;

	else {

		while (1) {

			// traverse to right for bigger keys
			if (tempNode->key < key) {

				if (tempNode->rightLinkType == THREAD) return;
				// reassign parentNode
				parentNode = tempNode;

				// traverse to right tree nodes
				tempNode = tempNode->right;
			}

			// traverse to left for smaller keys
			else if (tempNode->key > key) {

				if (tempNode->leftLinkType == THREAD) return;

				parentNode = tempNode;

				// traverse to the left
				tempNode = tempNode->left;
			}

			else {

				break;
			}

		}//end-while

		BSTNode* node = tempNode;
		if (tempNode->rightLinkType != THREAD && tempNode->leftLinkType != THREAD) {

			parentNode = tempNode;

			// get max node 
			node = tempNode->left;

			while(node->rightLinkType != THREAD) {
				parentNode = node;
				node = node->right;
			}//end-while

			tempNode->key = node->key;
		}

		// left side traversals
		if (parentNode->key >= node->key) {

			if (node->rightLinkType== THREAD && node->leftLinkType == THREAD) {

				parentNode->left = node->left;
				parentNode->leftLinkType = THREAD;
			}

			else if (node->rightLinkType == THREAD) {

				BSTNode* maxNode = node->left;
				while (maxNode->rightLinkType != THREAD) {
					maxNode = maxNode->right;

				}//end-while
				maxNode->right = parentNode;
				parentNode->left = node->left;
			}

			else {

				BSTNode* minNode = node->right;
				while (minNode->leftLinkType!= THREAD) {
					minNode = minNode->left;
				
				}//end-while

				minNode->left = node->left;
				parentNode->left = node->right;
			}
		}

		else {

			if(node->rightLinkType == THREAD && node->leftLinkType == THREAD) {

				parentNode->right = node->right;
				parentNode->rightLinkType = THREAD;
			}
			else if(node->rightLinkType == THREAD) {

				BSTNode* maxNode = node->left;

				while(maxNode->rightLinkType != THREAD) {
					maxNode = maxNode->right;
				}
				maxNode->right = node->right;
				parentNode->right = node->left;
			}
			else {

				BSTNode* minNode = node->right;
				while (minNode->leftLinkType != THREAD) {

					minNode = minNode->left;
				}
				minNode->left = parentNode;
				parentNode->right = node->right;
			}
		}

	}//end-else
} // end-remove

///-----------------------------------------------
/// Searches a given key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode *ThreadedBST::find(int key) {

	BSTNode* temp = root;
	
	while (1) {

		if (temp->key == key) {

			return temp;
		}
		else if (temp->key > key) {

			temp = temp->left;
		}

		else if (temp->key < key) {
			temp = temp->right;
		}
		else {
			return NULL;
			break;
		}
 	}
} // end-find

///-----------------------------------------------
/// Returns the minimum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::min() {
	BSTNode* currNode = root;

	while(currNode != NULL) {
	
		if (currNode->left == NULL) {

			return currNode;
		}	

		currNode = currNode->left;
	}

	return NULL;
} // end-min

///-----------------------------------------------
/// Returns the maximum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::max() {

	BSTNode* currNode = root;

	while (currNode != NULL) {

		if (currNode->right == NULL) {

			return currNode;
		}

		currNode = currNode->right;
	}

	return NULL;
} // end-max

///-----------------------------------------------
/// Given a valid pointer to a node in ThreadedBST,
/// returns a pointer to the node that contains the inorder predecessor
/// If the inorder predecessor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::previous(BSTNode* node) { 

	BSTNode* parentNode = node;

	if (node->leftLinkType == THREAD)
		node = node->left;

	else {

		node = node->left;
		while (node->right != parentNode) {

			node = node->right;
		}
	}

	return node;
} // end-previous

///-----------------------------------------------
/// Given a valid pointer to a node in the ThreadedBST,
/// returns a pointer to the node that contains the inorder successor
/// If the inorder successor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::next(BSTNode* node) {

	BSTNode* parentNode = node;

	if (node->rightLinkType == THREAD)
		node = node->right;

	else {

		node = node->right;
		while (node->left != parentNode) {

			node = node->left;
		}
	}

	return node;
} // end-next