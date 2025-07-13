package cn.edu.qust.demo1;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.IOException;

@WebServlet(name = "RequestParamsServlet", value = "/RequestParamsServlet")
public class RequestParamsServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setCharacterEncoding("utf-8");
        String name = request.getParameter("username");
        String password = request.getParameter("password");
        System.out.println("用户名:" + name);
        System.out.println("密 码:" + password);
        String[] hobbies = request.getParameterValues("hobby");
        if (hobbies != null) {
            System.out.println("爱好: " + String.join(", ", hobbies));
        } else {
            System.out.println("爱好: 无");
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}
