import csv
import json

csv_file = 'students.csv'
json_file = 'students.json'

data = []
with open(csv_file, 'r', encoding='utf-8') as f:
    reader = csv.DictReader(f)
    for row in reader:
        print(row)

with open(json_file, 'w', encoding='utf-8') as f:
    json.dump(data, f, ensure_ascii=False, indent=4)

print(f"已成功将 {csv_file} 转换为 {json_file}")
