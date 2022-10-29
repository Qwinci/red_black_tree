#pragma once
#include <stdint.h>
#include <stddef.h>

#define CONCAT_IMPL(a, b) a ## b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

#define RBTREE_DECL_STRUCTS(Name, NodeName, K, T) \
typedef struct Node { \
	K key; \
	T value; \
	struct Node* left; \
	struct Node* right; \
	struct Node* parent; \
	char color; \
} Node; \
typedef struct { \
	Node* root; \
	Node null; \
} Name;

#ifdef __cplusplus
#define RBTREE_DECL_FUNCTIONS(Name, NodeName, K, T) \
extern "C" { \
Name CONCAT(Name, _new)(void); \
\
void CONCAT(Name, _insert)(Name* self, K key, T value, Node* node); \
\
Node* CONCAT(Name, _remove)(Name* self, Node* node); \
\
Node* CONCAT(Name, _search)(Name* self, K key); \
\
Node* CONCAT(Name, _successor)(Name* self, Node* node); \
\
Node* CONCAT(Name, _predecessor)(Name* self, Node* node); \
\
intmax_t CONCAT(Name, _height)(Name* self); \
}
#else
#define RBTREE_DECL_FUNCTIONS(Name, NodeName, K, T) \
Name CONCAT(Name, _new)(void); \
\
void CONCAT(Name, _insert)(Name* self, K key, T value, Node* node); \
\
Node* CONCAT(Name, _remove)(Name* self, Node* node); \
\
Node* CONCAT(Name, _search)(Name* self, K key); \
\
Node* CONCAT(Name, _successor)(Name* self, Node* node); \
\
Node* CONCAT(Name, _predecessor)(Name* self, Node* node); \
\
intmax_t CONCAT(Name, _height)(Name* self);
#endif