// JSON �Ľ� ���� 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cJSON.h"
#include "list.h"
#include "tree.h"

void load_parcels_from_file(const char* filename, TreeNode** root) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "���� ���� ����: %s\n", filename);
        return;
    }

    // ���� ũ�� ���ϱ�
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    // ���� ���� �б�
    char* data = (char*)malloc(length + 1);
    if (!data) {
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        fclose(file);
        return;
    }
    fread(data, 1, length, file);
    data[length] = '\0';  // ���ڿ� �� ǥ��
    fclose(file);

    // cJSON �Ľ� ����
    cJSON* json = cJSON_Parse(data);
    if (!json) {
        fprintf(stderr, "JSON �Ľ� ����\n");
        free(data);
        return;
    }

    int count = cJSON_GetArraySize(json);
    for (int i = 0; i < count; ++i) {
        cJSON* item = cJSON_GetArrayItem(json, i);
        cJSON* name_json = cJSON_GetObjectItem(item, "name");
        cJSON* address_json = cJSON_GetObjectItem(item, "address");
        cJSON* is_wow_json = cJSON_GetObjectItem(item, "is_wow");

        if (!cJSON_IsString(name_json) || !cJSON_IsString(address_json) || !cJSON_IsBool(is_wow_json)) {
            continue; // ���� ���� �� �ǳʶ�
        }

        const char* name = name_json->valuestring;
        const char* address = address_json->valuestring;
        bool is_wow = cJSON_IsTrue(is_wow_json);

        // �� �̸� ���� (��: "����Ư���� ������ ..." �� "������")
        char gu_name[50] = { 0 };
        const char* gu_start = strstr(address, "��");
        if (gu_start != NULL) {
            // "������" ã���� ��, �տ� �ִ� "����" ����
            const char* space_before = gu_start;
            while (space_before > address && *(space_before - 1) != ' ') {
                space_before--;
            }
            size_t len = gu_start - space_before + strlen("��");
            strncpy(gu_name, space_before, len);
            gu_name[len] = '\0';
        }
        else {
            strcpy(gu_name, "��Ÿ");
        }

        // Parcel ���� �� Ʈ���� ����
        Parcel* p = create_parcel(name, address, is_wow);
        insert_parcel_to_tree(root, gu_name, p);
    }

    cJSON_Delete(json);
    free(data);
}
