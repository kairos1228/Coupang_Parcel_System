import json
import random
from collections import defaultdict
import os

# 경로 설정 (현재 파일 기준 상대경로 or 절대경로로 수정 가능)
input_path = "C:/Users/c/Desktop/Data_Structure_class/Coupang_parcel_Project/data/seoul_parcels_raw.json"
output_path = "C:/Users/c/Desktop/Data_Structure_class/Coupang_parcel_Project/data/seoul_parcels.json"

# 이름 리스트
last_names = ["김", "이", "박", "최", "정", "강", "조", "윤", "장", "오"]
first_names = [
    "민수", "지훈", "수빈", "다영", "예린", "현우", "지원", "지우", "예준",
    "지안", "유진", "지현", "시우", "지민", "은우", "연우", "민재", "다은",
    "예은", "서준", "지호", "승현", "예지", "주원", "채원", "가은", "하윤",
    "소율", "유나", "시현", "하린", "민서", "태희", "서하", "도윤", "소연",
    "은서", "수연", "하진"
]

# 데이터 불러오기
with open(input_path, "r", encoding="utf-8") as f:
    raw = json.load(f)

rows = raw["seoulGuGu"]["row"]

# 자치구별 배송량 합계
volume_by_gu = defaultdict(float)
for row in rows:
    gu = row["RECV_GU_NM"]
    volume = sum([
        row.get(f"LCLSF_C_0{i}", 0.0) for i in range(1, 10)
    ] + [
        row.get(f"LCLSF_C_{i}", 0.0) for i in range(10, 12)
    ])
    volume_by_gu[gu] += volume

# 비율 계산
total_volume = sum(volume_by_gu.values())
ratio_by_gu = {gu: v / total_volume for gu, v in volume_by_gu.items()}

# 100개로 비율 기반 생성
target_total = 100
converted = []
id_counter = 1

for gu, ratio in sorted(ratio_by_gu.items(), key=lambda x: -x[1]):
    count = int(round(ratio * target_total))
    for _ in range(count):
        name = random.choice(last_names) + random.choice(first_names)
        is_wow = random.random() < 0.38
        parcel = {
            "id": id_counter,
            "name": name,
            "address": f"서울특별시 {gu}",
            "is_wow": is_wow
        }
        converted.append(parcel)
        id_counter += 1

# 100개로 자르기
converted = converted[:100]

# 저장
os.makedirs(os.path.dirname(output_path), exist_ok=True)
with open(output_path, "w", encoding="utf-8") as f:
    json.dump(converted, f, ensure_ascii=False, indent=2)

print(f"✅ 변환 완료 → {output_path}")
