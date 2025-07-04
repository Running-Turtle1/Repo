## PIE Model

- Execution：运行必须通过错误的代码
- Infection：执行错误代码必须触发一个错误的中间状态
- Propagation：错误的状态必须传播到输出产生 Failure

bug 分为 fault,error,failure，整个传播出去是靠 PIE 模型，即执行到 fault，感染产生 error，并且传播出去我们可观测的 failure。

## 黑盒测试和白盒测试

黑盒测试/功能测试/数据驱动测试：边界值分析法、等价类划分法、因果图法和决策表法（判定表法）。

白盒测试/结构测试/逻辑驱动测试

## 为什么需要静态测试测试？静态测试的手段

走读、小组评审、审查。

- 及早发现缺陷，节省成本，越晚发现成本越高 ; 
- 提高代码质量。
- 覆盖范围广,可以对文档进行检查，这是动态测试难以做到的。

## 单元测试、集成测试、系统测试的侧重点

- 单元测试：聚焦单个模块/函数，确保最小单元正确。
- 集成测试：关注模块间接口、交互，确保模块集成无问题。
- 系统测试：从用户视角，验证系统整体功能是否符合需求。

## 如何结合自动化测试与人工测试提高产品质量？

- 自动化测试：覆盖重复、量大的任务，例如回归测试和性能测试。
- 人工测试：处理复杂业务、探索性测试等自动化测试难以覆盖到的问题。
- 即，自动化做基础验证，人工做深度、灵活的测试，互补提升测试覆盖与质量。

## 整体测试用例的质量要求

- 覆盖率
- 易用性
- 易维护性
- 粒度适中

## 测试用例的必要结构

标志符、测试项、测试环境要求、输入标准、输出标准以及测试用例之间的关联。

## 简答题

1. 简述性能测试、负载测试和压力测试的区别与联系？

答：1）性能测试是用来测量系统在各种预期条件下的表现性能；2）负载测试是测试接近或达到预期并发用户数的条件下，测试系统的响应时间和吞吐能力等；3）压力测试是指并发用户数或事务量远高于预期，系统的表现。

共同点：1）都需要借助测试工具模拟虚拟用户和事务；2）都以性能指标为核心；3）测试结果都用于指导系统优化。

## 设计题

### 等价类方法

- 划分等价类
- 设计用例：有效全覆盖 + 无效单覆盖

## 正交表

- 标准正交表

$L9(3^4),L16(4,5)$

https://blog.csdn.net/dpl12/article/details/101944191?ops_request_misc=%257B%2522request%255Fid%2522%253A%252225334d03264fbebb929ba399103ec672%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=25334d03264fbebb929ba399103ec672&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~ElasticSearch~search_v2-2-101944191-null-null.142^v102^pc_search_result_base3&utm_term=%E6%AD%A3%E4%BA%A4%E6%B3%95%E4%BE%8B%E9%A2%98&spm=1018.2226.3001.4187

| 编号 | A-字体   | B-字符样式 | C-颜色 | D-字号 |
| ---- | -------- | ---------- | ------ | ------ |
| 1    | 仿宋     | 粗体       | 红色   | 20号   |
| 2    | 楷体     | 斜体       | 绿色   | 30号   |
| 3    | 华文彩云 | 下划线     | 蓝色   | 40号   |

