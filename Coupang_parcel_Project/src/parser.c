// JSON 파싱 로직 
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
        fprintf(stderr, "파일 열기 실패: %s\n", filename);
        return;
    }

    // 파일 크기 구하기
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    // 파일 내용 읽기
    char* data = (char*)malloc(length + 1);
    if (!data) {
        fprintf(stderr, "메모리 할당 실패\n");
        fclose(file);
        return;
    }
    fread(data, 1, length, file);
    data[length] = '\0';  // 문자열 끝 표시
    fclose(file);

    // cJSON 파싱 시작
    cJSON* json = cJSON_Parse(data);
    if (!json) {
        fprintf(stderr, "JSON 파싱 실패\n");
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
            continue; // 형식 오류 시 건너뜀
        }

        const char* name = name_json->valuestring;
        const char* address = address_json->valuestring;
        bool is_wow = cJSON_IsTrue(is_wow_json);

        // 구 이름 추출 (예: "서울특별시 강남구 ..." → "강남구")
        char gu_name[50] = { 0 };
        const char* gu_start = strstr(address, "구");
        if (gu_start != NULL) {
            // "강남구" 찾았을 때, 앞에 있는 "강남" 추출
            const char* space_before = gu_start;
            while (space_before > address && *(space_before - 1) != ' ') {
                space_before--;
            }
            size_t len = gu_start - space_before + strlen("구");
            strncpy(gu_name, space_before, len);
            gu_name[len] = '\0';
        }
        else {
            strcpy(gu_name, "기타");
        }

        // Parcel 생성 및 트리에 삽입
        Parcel* p = create_parcel(name, address, is_wow);
        insert_parcel_to_tree(root, gu_name, p);
    }

    cJSON_Delete(json);
    free(data);
}
