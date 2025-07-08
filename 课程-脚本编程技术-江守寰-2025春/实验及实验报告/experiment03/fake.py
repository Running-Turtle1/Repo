import os
import random
import pandas as pd
import matplotlib.pyplot as plt

# 中文字体配置（如有需要）
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

# 模拟爬取的数据条数
NUM_SAMPLES = 50
CHART_DIR = 'charts'
os.makedirs(CHART_DIR, exist_ok=True)

# 行业、经验、学历选项
industries = ['互联网', '金融', '教育', '医疗', '游戏', '电商', '人工智能', '大数据', '云计算', '硬件']
experiences = ['不限', '1-3年', '3-5年', '5-10年', '10年以上']
educations = ['大专', '本科', '硕士', '博士']

# 生成模拟数据
jobs = []
for i in range(NUM_SAMPLES):
    lo = random.randint(8, 20)
    hi = lo + random.randint(2, 10)
    salary_str = f"{lo}k-{hi}k"
    salary_val = (lo + hi) * 500  # 按照 (lo+hi)*500 转换为元
    jobs.append({
        '职位':      f'Python开发工程师{i+1}',
        '公司':      f'公司{i+1}',
        '薪资原始':   salary_str,
        '薪资(元)':  salary_val,
        '经验':      random.choice(experiences),
        '学历':      random.choice(educations),
        '行业':      random.choice(industries),
        '发布时间':   f"2025-06-{random.randint(1,28):02d}"
    })

# 转成 DataFrame
df = pd.DataFrame(jobs)

# 打印前 10 条结果
print(f"🔍 模拟抓取到 {len(df)} 条数据，前 10 条如下：")
print(df[['职位','公司','薪资原始','经验','学历','行业','发布时间']].head(10).to_string(index=False))

# —— 绘制图表 —— #

# 薪资分布柱状图
bins = [0, 5000, 10000, 15000, 20000, 30000, 50000]
labels = ['0-5k','5-10k','10-15k','15-20k','20-30k','30-50k']
df['薪资区间'] = pd.cut(df['薪资(元)'], bins=bins, labels=labels, include_lowest=True)
salary_freq = df['薪资区间'].value_counts().sort_index()

plt.figure(figsize=(8,5))
salary_freq.plot.bar()
plt.title('薪资分布')
plt.xlabel('薪资区间（元）')
plt.ylabel('岗位数量')
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig(f"{CHART_DIR}/薪资分布.png")
plt.close()

# 经验分布柱状图
exp_freq = df['经验'].value_counts().loc[experiences]  # 保证顺序
plt.figure(figsize=(8,5))
exp_freq.plot.bar()
plt.title('经验分布')
plt.xlabel('经验要求')
plt.ylabel('岗位数量')
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig(f"{CHART_DIR}/经验分布.png")
plt.close()

# 行业分布饼图（Top5）
industry_freq = df['行业'].value_counts().head(5)
plt.figure(figsize=(6,6))
industry_freq.plot.pie(autopct='%1.1f%%', labels=industry_freq.index)
plt.title('行业分布（Top5）')
plt.ylabel('')
plt.tight_layout()
plt.savefig(f"{CHART_DIR}/行业分布.png")
plt.close()

print(f"\n✅ 已生成图表并保存到 \"{CHART_DIR}\" 目录：")
print("   - 薪资分布.png")
print("   - 经验分布.png")
print("   - 行业分布.png")