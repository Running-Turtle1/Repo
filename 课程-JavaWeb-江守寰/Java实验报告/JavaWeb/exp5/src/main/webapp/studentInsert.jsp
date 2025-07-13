<%@ page language="java" contentType="text/html; charset=UTF-8"
         pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <title>新增学生</title>
</head>
<body>
<h2>新增学生信息</h2>
<form action="studentServlet?action=insert" method="post">
    <label for="sno">学号：</label>
    <input type="text" id="sno" name="sno" required /><br />
    <label for="sname">姓名：</label>
    <input type="text" id="sname" name="sname" required /><br />
    <label for="age">年龄：</label>
    <input type="number" id="age" name="age" required /><br />
    <input type="submit" value="提交" />
</form>
</body>
</html>
