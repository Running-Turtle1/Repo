import pytest
import time
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.firefox.options import Options
from selenium.webdriver.firefox.firefox_profile import FirefoxProfile

class TestJDShopping:
    def setup_method(self, method):
        # 初始化Firefox浏览器
        # profile_path = r"C:\Users\95432\AppData\Roaming\Mozilla\Firefox\Profiles\q8uyn2xu.default-release"
        # profile = FirefoxProfile(profile_path)
        # options = Options()
        # self.driver = webdriver.Firefox(firefox_profile=profile, options=options)
        self.driver = webdriver.Firefox()
        self.driver.maximize_window()
        self.wait = WebDriverWait(self.driver, 50)

    def teardown_method(self, method):
        # 测试结束关闭浏览器
        self.driver.quit()

    def open_jd_homepage(self):
        """打开京东首页并断言标题包含‘京东’"""
        self.driver.get("https://www.jd.com/")
        assert "京东" in self.driver.title, "未成功打开京东首页"

    def search_product(self, keyword):
        """搜索商品"""
        search_box = self.wait.until(EC.presence_of_element_located((By.ID, "key")))  # 通过ID定位
        search_box.clear()
        search_box.send_keys(keyword)
        search_button = self.wait.until(EC.element_to_be_clickable((By.CSS_SELECTOR, ".button")))  # 通过CSS定位
        search_button.click()

    def apply_filter(self):
        """筛选商品"""
        filter_element = self.wait.until(EC.element_to_be_clickable(
            (By.XPATH, '//*[@id="J_feature"]/li[1]/i')  # 使用XPath定位
        ))
        filter_element.click()

    def click_product(self):
        """点击第一个搜索到的商品"""
        product_name = self.wait.until(EC.element_to_be_clickable(
            (By.CSS_SELECTOR, "#J_goodsList .gl-item:nth-child(1) .p-name em")
        ))
        assert product_name is not None, "商品元素未找到"
        product_name.click()

    def add_to_cart(self):
        """添加商品到购物车"""
        self.switch_to_new_window()
        add_to_cart_button = self.wait.until(EC.element_to_be_clickable((By.ID, "InitCartUrl")))
        add_to_cart_button.click()
        # 断言购物车按钮存在
        assert self.driver.find_element(By.ID, "InitCartUrl"), "添加到购物车失败"

    def switch_to_new_window(self):
        """切换到新打开的窗口"""
        current_handles = self.driver.window_handles
        time.sleep(2)  # 简单等待新页面打开
        new_handles = self.driver.window_handles
        for handle in new_handles:
            if handle not in current_handles:
                self.driver.switch_to.window(handle)
                break

    @pytest.mark.run(order=1)
    def test_jd_shopping_flow(self):
        """完整测试流程"""
        self.open_jd_homepage()
        self.search_product("Redmi Buds6")
        self.apply_filter()
        self.click_product()
        self.add_to_cart()