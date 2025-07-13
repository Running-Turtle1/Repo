package cn.edu.qust.demo1;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.IOException;
import java.net.URLDecoder;
import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.Date;

@WebServlet(name = "LastAccessServlet", value = "/LastAccessServlet")
public class LastAccessServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=utf-8"); // 中文编码
        Cookie[] cookies = request.getCookies(); // 获取所有 cookie
        boolean flag = false; // 用于判断 cookies 是否为空
        if(cookies != null){
            for(Cookie cookie : cookies){
                String name = cookie.getName();
                // 判断名称是否是 lastTime
                if("lastTime".equals(name)){
                    // 表示该 cookie 不是第一次访问
                    flag = true;
                    // 响应数据
                    // 获取 cookie 的 value 时间
                    String value = cookie.getValue();
                    // URL 解码
                    value = URLDecoder.decode(value, "utf-8");
                    response.getWriter().write("欢迎回来, 您上次访问的时间是:"+value);
                    break;
                }
            }
        }

        if(flag == false){
            response.getWriter().write("您好, 这是您首次访问该网站!");
        }

        // 将本次访问时间写回客户端
        // 获取当前时间的字符串, 重新设置 cookie 的值， 重新发送 cookie
        Date date = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy年MM月dd日 HH:mm:ss");
        String str_date = sdf.format(date);
        // URL 编码
        str_date = URLEncoder.encode(str_date, "utf-8");
        // 创建 cookie 对象
        Cookie cookie = new Cookie("lastTime", str_date);
        // 设置 cookie 存活时间
        cookie.setMaxAge(60*60*24*30); // 一个月
        response.addCookie(cookie);

    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}
