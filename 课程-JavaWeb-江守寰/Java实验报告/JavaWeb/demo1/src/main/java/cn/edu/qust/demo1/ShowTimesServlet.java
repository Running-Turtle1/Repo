package cn.edu.qust.demo1;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(name = "ShowTimesServlet", value = "/ShowTimesServlet")
public class ShowTimesServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        response.setContentType("text/html;charset=utf-8"); // 设置中文编码, 防止乱码
        PrintWriter out = response.getWriter(); // 得到输出流对象
        ServletContext context = getServletContext();
        Integer times = (Integer) context.getAttribute("times");
        if(times == null){
            times = 1;
        }
        else{
            times = times.intValue() + 1;
        }
        out.println("<html><head><title>");
        out.println("页面访问统计");
        out.println("</title></head><body>");
        out.println("当前页面被访问了");
        out.println("<font color=red size=20>"+times+"</font>次");
        context.setAttribute("times", times);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}

