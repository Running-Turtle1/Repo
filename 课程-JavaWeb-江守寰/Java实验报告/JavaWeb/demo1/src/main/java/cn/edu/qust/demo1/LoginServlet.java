package cn.edu.qust.demo1;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(name = "LoginServlet", value = "/LoginServlet")
public class LoginServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=utf-8");
        PrintWriter out = response.getWriter();

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if(username == null || password == null || !(username.equals("admin") && password.equals("123"))){
            out.println("密码错误, 3秒返回到登录界面!!!");
            response.setHeader("Refresh", "3;url=login.html");
        }
        else{
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("hello-servlet"); // 重定向地址
        }
    }
}
