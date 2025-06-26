## 测试报告：京东购物流程自动化测试

### 一、测试内容

1. 打开京东首页
2. 搜索指定商品（Redmi Buds6）
3. 应用商品筛选器（京东物流）
4. 点击商品进入详情页
5. 将商品加入购物车

### 二、测试功能

#### 1. 打开京东首页

**设计思路：**

- 使用 `driver.get()` 打开京东首页。
- 通过断言页面标题中包含 “京东” 来验证页面是否成功加载。
- 这是基础的 smoke test，用于判断京东首页是否正常访问。

**目的：**
 验证网络连接和首页可用性，为后续操作做准备。

**对应代码：**

```python
def open_jd_homepage(self):
    """打开京东首页并断言标题包含‘京东’"""
    self.driver.get("https://www.jd.com/")
    assert "京东" in self.driver.title, "未成功打开京东首页"
```

**测试截图：**

![7bae2d1c09b28e58884aecd4e95b81b](C:\Users\95432\Desktop\课程\软件质量保证与测试\期中\测试截图\7bae2d1c09b28e58884aecd4e95b81b.png)

#### 2. 搜索指定商品

**设计思路：**

- 通过 ID 精确定位搜索框（`#key`），这是京东搜索框的唯一标识。
- 输入商品关键词 `Redmi Buds6`，使用 `clear()` 避免历史输入影响。
- 使用 CSS 选择器 `.button` 定位搜索按钮并点击。

**目的：**
 模拟用户在首页搜索商品的行为，检验搜索功能是否可用。

**对应代码：**

```python
def search_product(self, keyword):
    """搜索商品"""
    search_box = self.wait.until(EC.presence_of_element_located((By.ID, "key")))
    search_box.clear()
    search_box.send_keys(keyword)
    search_button = self.wait.until(EC.element_to_be_clickable((By.CSS_SELECTOR, ".button")))
    search_button.click()
```

**测试截图：** 

![image-20250508204809054](C:\Users\95432\AppData\Roaming\Typora\typora-user-images\image-20250508204809054.png)


#### 3. 应用商品筛选器

**设计思路：**

- 使用 XPath 定位筛选器中“京东物流”选项（第一个特征项）。
- 使用 `element_to_be_clickable` 等待元素加载完成。
- 点击后页面会自动刷新以应用过滤。

**目的：**
 验证筛选器功能是否正常运作，且页面是否能正确响应用户的筛选行为。

**对应代码：**

```python
def apply_filter(self):
    """筛选商品"""
    filter_element = self.wait.until(EC.element_to_be_clickable(
        (By.XPATH, '//*[@id="J_feature"]/li[1]/i')
    ))
    filter_element.click()
```

**测试截图：**
![88114d9de88c9736040f95363a2a0f0](C:\Users\95432\Desktop\课程\软件质量保证与测试\期中\测试截图\88114d9de88c9736040f95363a2a0f0.png)

####  4. 点击商品进入详情页 

**设计思路：**

- 使用 CSS Selector 定位第一个商品的标题文字区域（`#J_goodsList .gl-item:nth-child(1) .p-name em`）。
- 加入显式等待，确保元素可点击。
- 使用 `assert` 判断元素是否存在，提升测试健壮性。
- 点击商品后会打开新页面。

**目的：**
 确保点击商品后能够正确跳转到详情页。

**对应代码：**

```python
def click_product(self):
    """点击第一个搜索到的商品"""
    product_name = self.wait.until(EC.element_to_be_clickable(
        (By.CSS_SELECTOR, "#J_goodsList .gl-item:nth-child(1) .p-name em")
    ))
    assert product_name is not None, "商品元素未找到"
    product_name.click()
```

**测试截图：**

![image-20250508204846536](C:\Users\95432\AppData\Roaming\Typora\typora-user-images\image-20250508204846536.png)

#### 5. 添加商品到购物车 

**设计思路：**

- 首先调用 `switch_to_new_window()` 切换到商品详情页。
- 等待并点击“加入购物车”按钮（通过 ID `InitCartUrl` 定位）。
- 使用断言检查加入购物车按钮存在，作为添加成功的标志。

**目的：**
 模拟购物操作的最后一步，验证加入购物车功能是否正常。

**对应代码：**

```python
def add_to_cart(self):
    """添加商品到购物车"""
    self.switch_to_new_window()
    add_to_cart_button = self.wait.until(EC.element_to_be_clickable((By.ID, "InitCartUrl")))
    add_to_cart_button.click()
    assert self.driver.find_element(By.ID, "InitCartUrl"), "添加到购物车失败"
```

**测试截图：**

![image-20250508204908340](C:\Users\95432\AppData\Roaming\Typora\typora-user-images\image-20250508204908340.png)

### 三、总代码

```python
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
```

