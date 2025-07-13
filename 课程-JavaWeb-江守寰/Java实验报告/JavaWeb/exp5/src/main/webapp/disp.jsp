<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
<head>
    <title>学生管理系统</title>
    <style>
        .pure-table {
            border-collapse: collapse;
            width: 100%;
            margin-top: 20px;
        }

        .pure-table th, .pure-table td {
            border: 1px solid #cbcbcb;
            padding: 8px;
            text-align: center;
        }

        .pure-table th {
            background-color: #f2f2f2;
        }

        .link {
            color: #007BFF;
            text-decoration: none;
        }

        .link:hover {
            text-decoration: underline;
        }
    </style>
</head>
<body>
<a href="studentServlet?action=insert">新增</a><br/>
<h1>学生管理系统</h1>
<table class="pure-table">
    <thead>
    <tr>
        <th>学号</th>
        <th>姓名</th>
        <th>年龄</th>
        <th>操作</th>
        <th>操作</th>
    </tr>
    <tr>
        <th>2208010423</th>
        <th>魏鹏超</th>
        <th>21</th>
        <th><a href="studentServlet?action=insert">修改</a><br/></th>
        <th><a href="studentServlet?action=insert">删除</a><br/></th>
    </tr>
    </thead>
    <tbody>
    <c:forEach var="stu" items="${students}">
        <tr>
            <td>${stu.sno}</td>
            <td>${stu.sname}</td>
            <td>${stu.age}</td>
            <td><a href="studentServlet?action=update&sno=${stu.sno}" class="link">修改</a></td>
            <td><a href="studentServlet?action=del&sno=${stu.sno}" class="link">删除</a></td>
        </tr>
    </c:forEach>
    </tbody>
</table>
<br/>
<br/>
</body>
</html>



<%--&ndash;%&gt;--%>
<%--<%@ page contentType="text/html;charset=UTF-8" language="java" %>--%>
<%--<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>--%>
<%--<html>--%>
<%--<head>--%>
<%--    <title>Title</title>--%>
<%--    <style>--%>
<%--        .pure-table{--%>
<%--            border-collapse: collapse;--%>
<%--            border-spacing: 0;--%>
<%--            empty-cells: show;--%>
<%--            border: 1px solid #cbcbcb;--%>
<%--        }--%>

<%--        .pure-table td,.pure-table th{--%>
<%--            border: 1px solid #cbcbcb;--%>
<%--            border-width: 1px;--%>
<%--            margin: 0;--%>
<%--            overflow: visible;--%>
<%--            padding: .5em 1em;--%>
<%--        }--%>
<%--    </style>--%>
<%--</head>--%>
<%--<body>--%>
<%--    <a href="studentServlet?action=insert">新增</a><br/>--%>
<%--    <table class="pure-table">--%>
<%--        <thead>--%>
<%--        <tr>--%>
<%--            <th>学号</th>--%>
<%--            <th>姓名</th>--%>
<%--            <th>年龄</th>--%>
<%--            <th>操作</th>--%>
<%--            <th>操作</th>--%>
<%--        </tr>--%>
<%--        </thead>--%>
<%--        <tbody>--%>
<%--        <c:forEach var="stu" items="${students}">--%>
<%--            <tr>--%>
<%--                <td>${stu.sno}</td>--%>
<%--                <td>${stu.sname}</td>--%>
<%--                <td>${stu.age}</td>--%>
<%--                <td>--%>
<%--                    <a href="studentServlet?action=update&sno=${stu.sno}">修改</a>--%>
<%--                    <a href="studentServlet?action=del&sno=${stu.sno}">删除</a>--%>
<%--                </td>--%>
<%--            </tr>--%>
<%--        </c:forEach>--%>
<%--        </tbody>--%>
<%--    </table>--%>
<%--</body>--%>
<%--</html>--%>
