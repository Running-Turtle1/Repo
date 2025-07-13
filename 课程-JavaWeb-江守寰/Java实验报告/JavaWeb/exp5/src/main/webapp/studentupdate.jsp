<%--
  Created by IntelliJ IDEA.
  User: 95432
  Date: 2024/10/21
  Time: 8:50
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
<form action="studentServlet?action=save" method="post">
    学号 : <input type="text" name="sno" readonly value="${stu.sno}"/>
    <br/>
    姓名 : <input type="text" name="sname" value="${sno.sname}"/>
    <br/>
    <input type="submit" value="保存"/>${msg}
</form>
</body>
</html>
