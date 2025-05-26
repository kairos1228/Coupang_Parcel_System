
import requests
import json
import random
import sys
from collections import defaultdict

# 사용자 입력: MMDD (예: "1231") → "20231231"
if len(sys.argv) != 2:
    print("❌ MMDD 형식의 날짜 인자가 필요합니다.")
    sys.exit(1)

mmdd = sys.argv[1]
dlvr_ymd = "2023" + mmdd
api_key = "614661766b31323236324e62704769"
url = f"http://openapi.seoul.go.kr:8088/{api_key}/json/seoulGuGu/1/1000/DLVR_YMD={dlvr_ymd}"

# API 호출
response = requests.get(url)
if response.status_code != 200:
    print("❌ API 요청 실패:", response.status_code)
    sys.exit(1)

try:
    print(response.text)
    rows = response.json()["seoulGuGu"]["row"]
except Exception as e:
    print("❌ 응답 데이터 파싱 오류:", str(e))
    sys.exit(1)

# 구별 배송량 계산
volume_by_gu = defaultdict(float)
for row in rows:
    gu = row["RECV_GU_NM"]
    volume = sum([
        row.get(f"LCLSF_C_0{i}", 0.0) for i in range(1, 10)
    ] + [
        row.get(f"LCLSF_C_{i}", 0.0) for i in range(10, 12)
    ])
    volume_by_gu[gu] += volume

# 비중 계산
total_volume = sum(volume_by_gu.values())
ratio_by_gu = {gu: v / total_volume for gu, v in volume_by_gu.items()}

# 랜덤 이름 생성용
last_names = ["김", "이", "박", "최", "정", "강", "조", "윤", "장", "오"]
first_names = [
    "민수", "지훈", "수빈", "다영", "예린", "현우", "지원", "지우", "예준",
    "지안", "유진", "지현", "시우", "지민", "은우", "연우", "민재", "다은"
]

# 비중 기반 100건 생성
converted = []
id_counter = 1
target_total = 100
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
converted = converted[:100]

# 저장
file_name = f"../data/seoul_parcels_{mmdd}.json"
with open(file_name, "w", encoding="utf-8") as f:
    json.dump(converted, f, ensure_ascii=False, indent=2)

print(f"✅ 정제 완료 → {file_name}")
