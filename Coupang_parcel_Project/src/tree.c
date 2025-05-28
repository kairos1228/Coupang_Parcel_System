#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "list.h"

// �� Ʈ�� ��� ����
TreeNode* create_tree_node(const char* gu_name) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (new_node == NULL) {
        fprintf(stderr, "Ʈ�� ��� �޸� �Ҵ� ����\n");
        exit(EXIT_FAILURE);
    }

    new_node->gu_name = (char*)malloc(strlen(gu_name) + 1);
    if (new_node->gu_name == NULL) {
        fprintf(stderr, "�� �̸� �޸� �Ҵ� ����\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->gu_name, gu_name);

    new_node->parcel_list_head = NULL;
    new_node->left = new_node->right = NULL;

    return new_node;
}

// �� �̸����� Ʈ�� Ž��
TreeNode* find_tree_node(TreeNode* root, const char* gu_name) {
    if (root == NULL) return NULL;

    int cmp = strcmp(gu_name, root->gu_name);
    if (cmp == 0) return root;
    else if (cmp < 0) return find_tree_node(root->left, gu_name);
    else return find_tree_node(root->right, gu_name);
}

// Ʈ���� �ù� ����
void insert_parcel_to_tree(TreeNode** root, const char* gu_name, Parcel* p) {
    if (*root == NULL) {
        *root = create_tree_node(gu_name);
    }

    int cmp = strcmp(gu_name, (*root)->gu_name);
    if (cmp == 0) {
        insert_parcel(&((*root)->parcel_list_head), p);
    }
    else if (cmp < 0) {
        insert_parcel_to_tree(&((*root)->left), gu_name, p);
    }
    else {
        insert_parcel_to_tree(&((*root)->right), gu_name, p);
    }
}

// ���� ��ȸ�� Ʈ�� ��� (�� �̸� ����)
void print_tree(TreeNode* root) {
    if (root == NULL) return;
    print_tree(root->left);
    printf("��: %s\n", root->gu_name);
    print_tree(root->right);
}

// Ʈ�� ��ü �ù� ���
void print_all_parcels(TreeNode* root) {
    if (root == NULL) return;
    print_all_parcels(root->left);

    printf("\n[ %s ��]\n", root->gu_name);
    if (root->parcel_list_head == NULL)
        printf("  �ù� ����\n");
    else
        print_parcels(root->parcel_list_head);

    print_all_parcels(root->right);
}

