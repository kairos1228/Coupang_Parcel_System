// JSON �ļ� ��� 
#ifndef PARSER_H
#define PARSER_H

#include "tree.h"  // TreeNode ���� ���Ե�
#include "list.h"  // Parcel ���� ���Ե�

// ���������� cJSON ���
#include "cJSON.h"  // ���� cJSON ���̺귯�� ��� ����

// JSON ���� �� Ʈ�� ���� �Լ�
void load_parcels_from_file(const char* filename, TreeNode** root);

#endif
