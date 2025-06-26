import time
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import TimeoutException, NoSuchElementException


class TestPhoenixNews:
    def setup_method(self):
        # 使用 Chrome 浏览器
        self.driver = webdriver.Chrome()
        self.driver.maximize_window()
        self.driver.get("https://www.ifeng.com/")
        self.wait = WebDriverWait(self.driver, 10)

    def teardown_method(self):
        self.driver.quit()

    def test_video_module(self):
        """测试视频模块：导航到视频页面，播放一个视频并验证播放器状态"""
        try:
            video_link = self.wait.until(EC.element_to_be_clickable((By.LINK_TEXT, "视频")))
            video_link.click()
            self.wait.until(EC.title_contains("视频"))
            video = self.wait.until(EC.presence_of_element_located((By.CSS_SELECTOR, "video")))
            self.driver.execute_script("arguments[0].play()", video)
            time.sleep(2)
            paused = self.driver.execute_script("return arguments[0].paused", video)
            assert not paused
            print("视频模块测试通过")
        except (AssertionError, TimeoutException) as e:
            print(f"视频模块测试失败: {e}")
            self.driver.save_screenshot("video_module_failure.png")

    def test_login_function(self):
        """测试登录功能：尝试使用测试账号登录（注意：不要提交真实凭证）"""
        try:
            login_link = self.wait.until(EC.element_to_be_clickable(
                (By.CSS_SELECTOR, ".index_login_in_2x_HyIfj")
            ))
            login_link.click()

            # 等待元素稳定可见
            phone_input = self.wait.until(
                EC.presence_of_element_located(
                    (By.XPATH, ".//div[contains(@class, 'index_Input_c6qmA')]//input[@name='text']"))
            )
            self.wait.until(
                EC.visibility_of(phone_input)  # 确保元素可见
            )
            phone_input.send_keys("13800000000")  # 测试手机号


            # 等待验证码输入框
            code_input = self.wait.until(
                EC.presence_of_element_located((By.CSS_SELECTOR, 'input[placeholder="短信验证码"]'))
            )
            code_input.send_keys("1234")

            time.sleep(2)
            # 验证登录成功，假设登录成功后页面会有特定元素
            logged_in_element = self.wait.until(EC.presence_of_element_located((By.CSS_SELECTOR, ".logged-in")))
            assert logged_in_element.is_displayed()
            print("登录功能测试通过")
        except (AssertionError, TimeoutException, NoSuchElementException) as e:
            print(f"登录功能测试失败: {e}")
            self.driver.save_screenshot("login_function_failure.png")

    def test_comment_section(self):
        """测试评论区：找到一篇文章，展开评论区并验证元素存在"""
        try:
            article = self.wait.until(EC.element_to_be_clickable((By.CSS_SELECTOR, ".article")))
            article.click()
            comment_button = self.wait.until(EC.element_to_be_clickable((By.CSS_SELECTOR, ".comment-button")))
            comment_button.click()
            comment_section = self.wait.until(EC.presence_of_element_located((By.CSS_SELECTOR, ".comment-section")))
            assert comment_section.is_displayed()
            print("评论区测试通过")
        except (AssertionError, TimeoutException) as e:
            print(f"评论区测试失败: {e}")
            self.driver.save_screenshot("comment_section_failure.png")

    def test_responsive_design(self):
        """响应式测试：调整浏览器窗口大小，验证页面布局变化"""
        try:
            original_size = self.driver.get_window_size()
            self.driver.set_window_size(375, 812)  # 模拟手机屏幕
            time.sleep(2)
            # 验证页面上某个元素的布局变化，假设存在一个特定元素
            element = self.wait.until(EC.presence_of_element_located((By.CSS_SELECTOR, ".responsive-element")))
            new_location = element.location
            self.driver.set_window_size(original_size['width'], original_size['height'])
            assert new_location != element.location
            print("响应式测试通过")
        except (AssertionError, TimeoutException) as e:
            print(f"响应式测试失败: {e}")
            self.driver.save_screenshot("responsive_design_failure.png")


if __name__ == "__main__":
    test = TestPhoenixNews()
    test.setup_method()
    test.test_video_module()
    test.test_login_function()
    test.test_comment_section()
    test.test_responsive_design()
    test.teardown_method()
