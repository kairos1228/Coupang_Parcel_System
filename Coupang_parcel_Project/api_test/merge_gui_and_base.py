
import json
import os

base_path = "./data/seoul_parcels.json"
gui_path = "./data/seoul_parcels_gui.json"
merged_path = "./data/merged_parcels.json"

merged = []

# AWS 기반 원본 데이터 불러오기
if os.path.exists(base_path):
    with open(base_path, "r", encoding="utf-8") as f:
        base_data = json.load(f)
        merged.extend(base_data)

# GUI에서 입력한 데이터가 있다면 병합
if os.path.exists(gui_path):
    with open(gui_path, "r", encoding="utf-8") as f:
        gui_data = json.load(f)
        # ID 중복 방지: base 이후로 이어붙이기
        next_id = max([p["id"] for p in merged], default=0) + 1
        for i, parcel in enumerate(gui_data):
            parcel["id"] = next_id + i
            merged.append(parcel)

# 병합 결과 저장
with open(merged_path, "w", encoding="utf-8") as f:
    json.dump(merged, f, ensure_ascii=False, indent=2)

print(f"✅ 병합 완료 → {merged_path}")
