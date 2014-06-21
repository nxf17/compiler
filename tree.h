#ifndef TREE_H
#define TREE_H

typedef struct TreeNode {
    char * state;
    int line;
	int productionRule;//第几个产生式
	int addr_sp;//栈区地址偏移量
    union {
	int intValue;
	float floatValue;
	char *idValue;
    }value;
    struct TreeNode *firstChild, *rightBrother;
}TreeNode;

#endif
