package cn.edu.qust.demo1;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.*;

@WebServlet(name = "OutputWordServlet", value = "/OutputWordServlet")
public class OutputWordServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        ServletContext context = getServletContext();
        response.setContentType("application/msword");
//        response.setHeader("Content-Disposition", "attachment; filename=test.doc");
        response.setHeader("Content-disposition", "attachment; filename=test.doc");

        String fileName = context.getRealPath("/WEB-INF/test.doc");
        File file = new File(fileName);
        BufferedInputStream bis = new BufferedInputStream(new FileInputStream(file));
        BufferedOutputStream bos = new BufferedOutputStream(response.getOutputStream());
        byte[] buffer = new byte[1024];
        while (bis.read(buffer) != -1) {
            bos.write(buffer);
        }
        bos.close();
        bis.close();
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}
