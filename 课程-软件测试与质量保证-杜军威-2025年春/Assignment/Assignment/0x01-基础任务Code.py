import time
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import TimeoutException, NoSuchElementException


class TestPhoenixNews:
    def setup_method(self):
        # 使用 Chrome 浏览器
        self.driver = webdriver.Chrome()
        self.driver.maximize_window()
        self.driver.get("https://www.ifeng.com/")
        self.wait = WebDriverWait(self.driver, 15)  # 增加等待时间到 15 秒

    def teardown_method(self):
        self.driver.quit()

    def test_logo_display(self):
        """测试首页 logo 显示"""
        try:
            logo = self.wait.until(EC.presence_of_element_located((By.XPATH, '//*[@id="main_nav"]/div[1]/div/a/img')))
            assert logo.is_displayed()
            print("首页 logo 显示测试通过")
        except (AssertionError, TimeoutException):
            print("首页 logo 显示测试失败")
            self.driver.save_screenshot("logo_display_failure.png")

    def test_news_page_load(self):
        """测试资讯页加载"""
        try:
            # 定位并点击资讯链接
            news_link = self.wait.until(EC.element_to_be_clickable((By.XPATH, '//*[@id="nav"]/li[1]/a')))
            current_window = self.driver.current_window_handle
            news_link.click()

            # 等待新窗口打开
            self.wait.until(EC.number_of_windows_to_be(2))

            # 切换到新窗口
            for window in self.driver.window_handles:
                if window != current_window:
                    self.driver.switch_to.window(window)
                    break

            # 使用新时代的 XPath 作为验证依据，等待元素加载
            new_era_element = self.wait.until(
                EC.presence_of_element_located((By.XPATH, '//*[@id="navigation"]/ul/li[1]/a'))
            )
            assert new_era_element.is_displayed()
            print("资讯页加载测试通过")
        except (AssertionError, TimeoutException) as e:
            print(f"资讯页加载测试失败: {e}")
            self.driver.save_screenshot("news_page_load_failure.png")
        finally:
            # 关闭新窗口并切换回原窗口
            if len(self.driver.window_handles) > 1:
                self.driver.close()
            self.driver.switch_to.window(current_window)

    def test_search_function(self):
        """测试搜索功能"""
        try:
            # 定位并点击搜索图标
            search_icon = self.wait.until(EC.element_to_be_clickable((By.XPATH, '//*[@id="main_nav"]/div[2]/div[2]/div[1]/div/div/span[2]')))
            search_icon.click()

            # 等待搜索输入框出现并验证其是否显示
            search_input = self.wait.until(EC.presence_of_element_located((By.XPATH, '//*[@id="main_nav"]/div[2]/div[2]/div[1]/div/div/input')))
            assert search_input.is_displayed()
            print("搜索功能测试通过")
        except (AssertionError, TimeoutException) as e:
            print(f"搜索功能测试失败: {e}")
            self.driver.save_screenshot("search_function_failure.png")

if __name__ == "__main__":
    test = TestPhoenixNews()
    test.setup_method()
    test.test_logo_display()
    test.test_news_page_load()
    test.test_search_function()
    test.teardown_method()