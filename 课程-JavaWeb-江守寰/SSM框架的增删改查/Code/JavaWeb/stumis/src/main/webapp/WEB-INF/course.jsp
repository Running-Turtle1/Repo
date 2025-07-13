<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<html>
<head>
    <title>course</title>
    <link rel="stylesheet" href="/css/bootstrap.min.css"/>
    <script src="js/jquery.min.js"></script>
    <script src="js/bootstrap.min.js"></script>
    <style>
        #container {
            width: 80%; /* 设置容器宽度为页面的 80% */
            margin: 20px auto; /* 上下 20px，左右居中 */
        }

        /* 自定义样式：增加表格的框线 */
        table {
            width: 100%; /* 使表格宽度自适应容器 */
            border-collapse: collapse; /* 合并单元格边框 */
        }

        th, td {
            border: 1px solid #ddd; /* 细边框 */
            padding: 12px; /* 增加单元格内边距 */
            text-align: center;
        }

        th {
            background-color: #f2f2f2; /* 表头背景色 */
            font-weight: bold;
        }

        /* 新增按钮样式 */
        #add {
            margin-top: 20px; /* 按钮与表格之间有一定间隔 */
            width: 100%; /* 让按钮宽度与表格一致 */
        }
    </style>
    <script>
        $().ready(function () {
            $("#add").click(function () {
                window.location.href = "showAdd";  // Redirect when the button is clicked
            });
        });
    </script>
</head>
<body>
<div id="container">
    <table class="table table-bordered">
        <thead>
        <tr>
            <th>编号</th>
            <th>课程号</th>
            <th>课程名</th>
            <th>学分</th>
            <th>备注</th>
            <th>操作</th>
        </tr>
        </thead>
        <tbody>
        <c:forEach var="cs" items="${courses}">
            <tr>
                <td>${cs.id}</td>
                <td>${cs.cno}</td>
                <td>${cs.cname}</td>
                <td>${cs.credit}</td>
                <td>${cs.memo}</td>
                <td><a href="modify?cno=${cs.cno}" class="btn btn-info">修改</a>
                    <a href="delete?cno=${cs.cno}" class="btn btn-danger">删除</a>
                </td>
            </tr>
        </c:forEach>
        </tbody>
    </table>
    <!-- 添加按钮，与表格宽度一致 -->
    <button id="add" type="button" class="btn btn-primary">新增</button>
</div>
</body>
</html>