package cn.edu.qust.exp5.servlet;

import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.io.IOException;
import java.util.List;
import cn.edu.qust.exp5.entity.Student;
import cn.edu.qust.exp5.service.*;

@WebServlet(name = "studentServlet", value = "/studentServlet")
public class StudentServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setCharacterEncoding("utf-8");
        response.setContentType("text/html;charset=utf-8");

        String action = request.getParameter("action");
        if (action == null) {
            action = "";
        }

        switch (action) {
            case "delete":
                delete(request, response);
                break;
            case "update":
                update(request, response);
                break;
            case "insert":
                insert(request, response);
                break;
            case "findBySno":
                findBySno(request, response);
                break;
            case "findAll":
                findAll(request, response);
                break;
            default:
                findAll(request, response);
                break;
        }
    }

    private void delete(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String sno = request.getParameter("sno");

        StudentService service = new StudentService();
        boolean flag = service.delete(sno);

        if (flag) {
            request.setAttribute("msg", "删除成功！");
        } else {
            request.setAttribute("msg", "删除失败！");
        }

        request.getRequestDispatcher("/studentServlet?action=findAll").forward(request, response);
    }

//    private void insert(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
//        // 直接转发到 add.jsp 页面，供用户填写信息
//        request.getRequestDispatcher("/studentInsert.jsp").forward(request, response);
//    }

//    private void insert(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
//        String sno = request.getParameter("sno");
//        String sname = request.getParameter("sname");
//        String ageStr = request.getParameter("age");
//
//        // 检查所有字段是否为空
//        if (sno == null || sname == null || ageStr == null || sno.isEmpty() || sname.isEmpty() || ageStr.isEmpty()) {
//            request.setAttribute("msg", "所有字段都是必填的！");
//            request.getRequestDispatcher("/error.jsp").forward(request, response);
//            return; // 直接返回
//        }
//
//        int age;
//        try {
//            age = Integer.parseInt(ageStr);
//        } catch (NumberFormatException e) {
//            request.setAttribute("msg", "年龄必须是一个有效的数字！");
//            request.getRequestDispatcher("/error.jsp").forward(request, response);
//            return; // 直接返回
//        }
//
//        // 创建学生对象
//        Student stu = new Student();
//        stu.setSno(sno);
//        stu.setSname(sname);
//        stu.setAge(age);
//
//        // 调用服务层
//        StudentService service = new StudentService();
//        boolean flag = service.insert(stu);
//
//        // 返回结果
//        if (flag) {
//            request.setAttribute("msg", "添加成功！");
//        } else {
//            request.setAttribute("msg", "添加失败！");
//        }
//
//        request.getRequestDispatcher("/studentServlet?action=findAll").forward(request, response);
//    }


//    private void update(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
//        String sno = request.getParameter("sno");
//        String sname = request.getParameter("sname");
//        String ageStr = request.getParameter("age"); // 这里获取年龄字符串
//
//        // 检查所有字段是否为空
//        if (sno == null || sname == null || ageStr == null || sno.isEmpty() || sname.isEmpty() || ageStr.isEmpty()) {
//            request.setAttribute("msg", "所有字段都是必填的！");
//            request.getRequestDispatcher("/error.jsp").forward(request, response);
//            return; // 直接返回
//        }
//
//        int age;
//        try {
//            age = Integer.parseInt(ageStr); // 尝试转换年龄
//        } catch (NumberFormatException e) {
//            request.setAttribute("msg", "年龄必须是一个有效的数字！");
//            request.getRequestDispatcher("/error.jsp").forward(request, response);
//            return; // 直接返回
//        }
//
//        // 创建学生对象并设置属性
//        Student stu = new Student();
//        stu.setSno(sno);
//        stu.setSname(sname);
//        stu.setAge(age);
//
//        // 调用服务层
//        StudentService service = new StudentService();
//        boolean flag = service.update(stu);
//
//        // 返回结果
//        if (flag) {
//            request.setAttribute("msg", "修改成功！");
//        } else {
//            request.setAttribute("msg", "修改失败！");
//        }
//
//        request.getRequestDispatcher("/studentServlet?action=findAll").forward(request, response);
//    }



    private void update(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String sno = request.getParameter("sno");
        String sname = request.getParameter("sname");
        int age = Integer.parseInt(request.getParameter("age"));

        Student stu = new Student();
        stu.setSno(sno);
        stu.setSname(sname);
        stu.setAge(age);

        StudentService service = new StudentService();
        boolean flag = service.update(stu);

        if (flag) {
            request.setAttribute("msg", "修改成功！");
        } else {
            request.setAttribute("msg", "修改失败！");
        }

        request.getRequestDispatcher("/studentServlet?action=findAll").forward(request, response);
    }

    private void insert(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String sno = request.getParameter("sno");
        String sname = request.getParameter("sname");
        int age = Integer.parseInt(request.getParameter("age"));

        Student stu = new Student();
        stu.setSno(sno);
        stu.setSname(sname);
        stu.setAge(age);

        StudentService service = new StudentService();
        boolean flag = service.insert(stu);

        if (flag) {
            request.setAttribute("msg", "添加成功！");
        } else {
            request.setAttribute("msg", "添加失败！");
        }

        request.getRequestDispatcher("/studentServlet?action=findAll").forward(request, response);
    }

    private void findBySno(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String sno = request.getParameter("sno");

        StudentService service = new StudentService();
        Student student = service.findBySno(sno);

        request.setAttribute("student", student);
        request.getRequestDispatcher("/update.jsp").forward(request, response);
    }

    private void findAll(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StudentService service = new StudentService();
        List<Student> students = service.findAll();

        request.setAttribute("students", students);
        request.getRequestDispatcher("/disp.jsp").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        this.doGet(request, response);
    }
}
