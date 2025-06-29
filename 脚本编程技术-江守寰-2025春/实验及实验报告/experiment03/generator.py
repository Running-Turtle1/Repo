# generate_lagou_cookies.py

import time
import json
import os
from selenium import webdriver
from selenium.webdriver.chrome.options import Options

# 输出的 Cookie 文件名
COOKIE_FILE = 'lagou_cookies.json'

def main():
    print("▶️ 1. 即将启动 Chrome，请完成登录操作…")
    opts = Options()
    opts.add_argument('--start-maximized')
    # headless 模式也可以，但需要你自己调整窗口尺寸、滑块位置等
    # opts.add_argument('--headless')
    driver = webdriver.Chrome(options=opts)
    driver.get('https://www.lagou.com')

    input("🔑 登录成功后按回车继续…")

    cookies = driver.get_cookies()
    driver.quit()

    data = {
        'timestamp': time.time(),
        'cookies': cookies
    }

    with open(COOKIE_FILE, 'w', encoding='utf-8') as f:
        json.dump(data, f, ensure_ascii=False, indent=2)

    print(f"✅ 已生成并保存 `{COOKIE_FILE}`，共 {len(cookies)} 条 Cookie。")

if __name__ == '__main__':
    main()
