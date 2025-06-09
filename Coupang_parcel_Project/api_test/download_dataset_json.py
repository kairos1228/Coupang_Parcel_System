import boto3
import botocore

def download_json():
    s3 = boto3.client('s3')
    bucket_name = 'seoul-parcel-data'
    merged_key = 'merged_parcels.json'
    base_key = 'seoul_parcels.json'

    try:
        s3.download_file(
            Bucket=bucket_name,
            Key=merged_key,
            Filename='./data/merged_parcels.json'
        )
        print("✅ 최신 merged_parcels.json 다운로드 완료")

    except botocore.exceptions.ClientError as e:
        error_code = e.response['Error']['Code']
        if error_code == '404' or 'NoSuchKey' in str(e):
            print("⚠️ merged_parcels.json이 존재하지 않습니다. 기본 seoul_parcels.json 다운로드를 시도합니다...")
            try:
                s3.download_file(
                    Bucket=bucket_name,
                    Key=base_key,
                    Filename='./data/seoul_parcels.json'
                )
                print("✅ 기본 seoul_parcels.json 다운로드 완료")
            except Exception as e2:
                print(f"❌ seoul_parcels.json 다운로드도 실패: {e2}")
        else:
            print(f"❌ 다운로드 실패: {e}")

if __name__ == "__main__":
    download_json()

