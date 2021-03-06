#ifndef hashed_tree_h_included__
#define hashed_tree_h_included__

#include "node.h"

template <class Hash>
class HashedTree {
	public:
		Node* root;

	public:
		HashedTree() : root(0) {}

		static hash_t get(const string_t string) {
			return Hash::get(string);
		}

		bool insert(const string_t string) {
			return insert_hashed(get(string), string);
		}

		bool insert_hashed(const hash_t hash, const string_t string) {
			if (!root) {
				root = new Node(hash, string);
				return true;
			}

			Node* node = root;
			while (true) {
				if (hash < node->hash) {
					if (node->left)
						node = node->left;
					else {
						Node* new_leaf = new Node(hash, string);
						node->left = new_leaf;

						return true;
					}
				} else
				if (hash > node->hash) {
					if (node->right)
						node = node->right;
					else {
						Node* new_leaf = new Node(hash, string);
						node->right = new_leaf;

						return true;
					}
				} else {
					// collisions are not handled yet
					return false;
				}
			}
		}

		Node* find(const string_t string) {
			return find_hashed(get(string), string);
		}

		Node* find_hashed(const hash_t hash, const string_t string) {
			Node* node = root;

			while (node) {
				if (hash < node->hash) {
					node = node->left;
				} else
				if (hash > node->hash) {
					node = node->right;
				} else
					break;
			}
			
			return node;
		}
};

#endif
