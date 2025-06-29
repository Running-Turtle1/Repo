# 1、定义一个成绩类Score，包括3个属性，分别表示语文、数学、物理的成绩。
# 重载“+”运算符，用于对两个Score对象对应的成绩求和，重载方法返回一个Score对象。
# 创建3个Score类的对象，相加进行成绩求和。
class Score:
    def __init__(self, chinese, math, physics):
        self.chinese = chinese
        self.math = math
        self.physics = physics

    def __add__(self, other):
        return Score(
            self.chinese + other.chinese,
            self.math + other.math,
            self.physics + other.physics
        )

    def __str__(self):
        return f'语文: {self.chinese}, 数学: {self.math}, 物理: {self.physics}'

# 创建3个Score对象
score1 = Score(85, 90, 88)
score2 = Score(78, 92, 81)
score3 = Score(91, 87, 85)

# 对3个对象求和
total_score = score1 + score2 + score3

# 打印结果
print("总成绩为：", total_score)
