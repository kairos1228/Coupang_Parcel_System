// tree.h
#ifndef TREE_H
#define TREE_H

#include "list.h"

typedef struct TreeNode {
    char* gu_name;                     // 구 이름 (예: "강남")
    Parcel* parcel_list_head;             // 연결 리스트의 시작 포인터
    struct TreeNode* left;                // 왼쪽 자식
    struct TreeNode* right;               // 오른쪽 자식
} TreeNode;

TreeNode* create_tree_node(const char* gu_name);
void insert_parcel_to_tree(TreeNode** root, const char* gu_name, Parcel* parcel);
TreeNode* find_tree_node(TreeNode* root, const char* gu_name);
void print_tree(TreeNode* root);
void print_all_parcels(TreeNode* root);

#endif