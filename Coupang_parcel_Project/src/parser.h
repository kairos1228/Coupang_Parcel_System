// JSON 파서 헤더 
#ifndef PARSER_H
#define PARSER_H

#include "tree.h"  // TreeNode 정의 포함됨
#include "list.h"  // Parcel 정의 포함됨

// 내부적으로 cJSON 사용
#include "cJSON.h"  // 실제 cJSON 라이브러리 헤더 포함

// JSON 파일 → 트리 삽입 함수
void load_parcels_from_file(const char* filename, TreeNode** root);

#endif