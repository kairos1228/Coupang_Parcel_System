// tree.h
#ifndef TREE_H
#define TREE_H

#include "list.h"

typedef struct TreeNode {
    char* gu_name;                     // �� �̸� (��: "����")
    Parcel* parcel_list_head;             // ���� ����Ʈ�� ���� ������
    struct TreeNode* left;                // ���� �ڽ�
    struct TreeNode* right;               // ������ �ڽ�
} TreeNode;

TreeNode* create_tree_node(const char* gu_name);
void insert_parcel_to_tree(TreeNode** root, const char* gu_name, Parcel* parcel);
TreeNode* find_tree_node(TreeNode* root, const char* gu_name);
void print_tree(TreeNode* root);
void print_all_parcels(TreeNode* root);

#endif