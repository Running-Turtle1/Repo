import os
import time
import random
import json
import re
import requests
import pandas as pd
import matplotlib.pyplot as plt

# 中文字体配置
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

COOKIE_FILE = 'lagou_cookies.json'
EXCEL_FILE = '行业信息.xlsx'
CHART_DIR = 'charts'
MAX_PAGES = 3
KEYWORD = 'Python'

def load_cookies():
    if not os.path.exists(COOKIE_FILE):
        print(f"❌ 找不到 {COOKIE_FILE}，请先生成它")
        return None
    data = json.load(open(COOKIE_FILE, encoding='utf-8'))
    raw = data.get('cookies') if isinstance(data, dict) else data
    if isinstance(raw, list):
        return {c['name']: c['value'] for c in raw if 'name' in c and 'value' in c}
    elif isinstance(raw, dict):
        return raw
    print("❌ Cookie 结构不对")
    return None

def fetch_page(session, page):
    # 第一次请求，获取 __csrf__（会自动存在 session.cookies）
    url_list = f'https://www.lagou.com/wn/jobs?kd={KEYWORD}'
    session.get(url_list, timeout=10)
    time.sleep(random.uniform(1,2))

    csrf = session.cookies.get('__csrf__', '')
    ajax_url = 'https://www.lagou.com/jobs/positionAjax.json?needAddtionalResult=true'
    headers = {
        'Referer': url_list,
        'X-Anit-Forge-Token': csrf,
        'X-Anit-Forge-Code': '0',
        'X-Requested-With': 'XMLHttpRequest',
        'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8',
    }
    data = {
        'first': 'true' if page==1 else 'false',
        'pn': page,
        'kd': KEYWORD
    }
    resp = session.post(ajax_url, headers=headers, data=data, timeout=10)
    resp.raise_for_status()
    return resp.json()['content']['positionResult']['result']

def parse_item(item):
    def parse_salary(s):
        m = re.match(r'(\d+)[kK]-(\d+)[kK]', s)
        if m:
            lo, hi = map(int, m.groups())
            return (lo+hi)*500
        m2 = re.match(r'(\d+)[kK]以上', s)
        if m2:
            return int(m2.group(1))*1000
        return None

    return {
        '职位': item.get('positionName'),
        '公司': item.get('companyFullName'),
        '薪资原始': item.get('salary'),
        '薪资(元)': parse_salary(item.get('salary','')),
        '经验': item.get('workYear'),
        '学历': item.get('education'),
        '行业': item.get('industryField'),
        '发布时间': item.get('createTime')
    }

def save_and_plot(jobs):
    df = pd.DataFrame(jobs)
    # 存 Excel
    with pd.ExcelWriter(EXCEL_FILE, engine='openpyxl') as w:
        df.to_excel(w, sheet_name='原始', index=False)
        # 薪资统计
        df_s = df.dropna(subset=['薪资(元)'])
        cuts = pd.cut(df_s['薪资(元)'], bins=[0,5e3,1e4,1.5e4,2e4,3e4,5e4], include_lowest=True)
        freq = cuts.value_counts().sort_index()
        pd.DataFrame({'区间':[f"{int(i.left)}-{int(i.right)}" for i in freq.index],'频数':freq.values})\
          .to_excel(w,'薪资统计',index=False)
        # 经验统计
        f2 = df['经验'].value_counts()
        pd.DataFrame({'经验':f2.index,'频数':f2.values}).to_excel(w,'经验统计',index=False)
        # 行业统计
        f3 = df['行业'].dropna().value_counts()
        pd.DataFrame({'行业':f3.index,'频数':f3.values}).to_excel(w,'行业统计',index=False)
    print(f"✅ 保存 Excel 到 {EXCEL_FILE}")

    # 画图
    os.makedirs(CHART_DIR, exist_ok=True)
    # 薪资柱状
    stat = pd.read_excel(EXCEL_FILE,'薪资统计')
    plt.figure(figsize=(8,5))
    plt.bar(stat['区间'],stat['频数'])
    plt.xticks(rotation=45); plt.tight_layout()
    plt.savefig(f"{CHART_DIR}/薪资分布.png"); plt.close()
    # 经验柱状
    stat2 = pd.read_excel(EXCEL_FILE,'经验统计')
    plt.figure(figsize=(8,5))
    plt.bar(stat2['经验'],stat2['频数'])
    plt.xticks(rotation=45); plt.tight_layout()
    plt.savefig(f"{CHART_DIR}/经验分布.png"); plt.close()
    # 行业饼图
    stat3 = pd.read_excel(EXCEL_FILE,'行业统计').head(10)
    plt.figure(figsize=(6,6))
    plt.pie(stat3['频数'], labels=stat3['行业'], autopct='%1.1f%%')
    plt.tight_layout()
    plt.savefig(f"{CHART_DIR}/行业分布.png"); plt.close()
    print(f"✅ 图表保存在 {CHART_DIR}/")

def main():
    cookies = load_cookies()
    if not cookies:
        return
    sess = requests.Session()
    sess.headers.update({'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64)'})
    sess.cookies.update(cookies)

    all_jobs = []
    for p in range(1, MAX_PAGES+1):
        print(f"🔍 抓取第 {p} 页…")
        try:
            res = fetch_page(sess, p)
            print(f"  ✔️ 拿到 {len(res)} 条")
            all_jobs += [parse_item(it) for it in res]
        except Exception as e:
            print(f"  ❌ 第 {p} 页失败：{e}")

    if all_jobs:
        save_and_plot(all_jobs)
    else:
        print("❌ 未获取任何数据，检查 Cookie 和网络")

if __name__ == '__main__':
    main()
