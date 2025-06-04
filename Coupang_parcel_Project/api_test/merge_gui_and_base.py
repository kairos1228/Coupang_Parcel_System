import json
import os
import boto3

# 파일 경로
base_path = "./data/seoul_parcels.json"
gui_path = "./data/seoul_parcels_gui.json"
merged_path = "./data/merged_parcels.json"

# AWS 설정
BUCKET_NAME = "seoul-parcel-data"
S3_FILE_NAME = "merged_parcels.json"

def upload_to_s3(local_file, bucket_name, s3_file):
    s3 = boto3.client('s3')
    try:
        s3.upload_file(local_file, bucket_name, s3_file)
        print(f"✅ S3 업로드 완료: {s3_file}")
    except Exception as e:
        print(f"❌ 업로드 실패: {e}")

# 병합 리스트 초기화
merged = []

# 기존 merged 파일 불러오기 (덮어쓰기 방지용)
if os.path.exists(merged_path):
    with open(merged_path, "r", encoding="utf-8") as f:
        merged = json.load(f)

# base 데이터 추가
if os.path.exists(base_path):
    with open(base_path, "r", encoding="utf-8") as f:
        base_data = json.load(f)
        # 중복 방지: base_data만 따로 ID 체크
        existing_ids = {p["id"] for p in merged}
        for parcel in base_data:
            if parcel["id"] not in existing_ids:
                merged.append(parcel)

# gui 데이터 추가
if os.path.exists(gui_path):
    with open(gui_path, "r", encoding="utf-8") as f:
        gui_data = json.load(f)
        # ID 새로 부여
        existing_ids = [p["id"] for p in merged]
        next_id = max(existing_ids, default=0) + 1
        for i, parcel in enumerate(gui_data):
            parcel["id"] = next_id + i
            merged.append(parcel)

# 병합된 결과 저장
with open(merged_path, "w", encoding="utf-8") as f:
    json.dump(merged, f, ensure_ascii=False, indent=2)

# AWS 업로드
upload_to_s3(merged_path, BUCKET_NAME, S3_FILE_NAME)

print(f"✅ 병합 완료 → {merged_path}")
