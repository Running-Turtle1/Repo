package cn.edu.qust.epx4;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class StudentDao {
    public List<Student> findAll(){
        List<Student> students = null;
        try{
            // 加载 JDBC 驱动
            Class.forName("com.mysql.jdbc.Driver");
            String user = "root";
            String password = "1234";
            String url = "jdbc:mysql://localhost:3306/students";
            Connection conn = DriverManager.getConnection(url, user, password);

            String sql = "select * from students";
            PreparedStatement ps = conn.prepareStatement(sql);
            ResultSet rs = ps.executeQuery();

            students = new ArrayList<>();
            while(rs.next()){
                Student student = new Student();
                student.setSno(rs.getInt("sno"));
                student.setSname(rs.getString("sname"));
                student.setAge(rs.getInt("age"));
                students.add(student);
            }
            rs.close();
            ps.close();
            conn.close();
        }
        catch(Exception e){

        }
        return students;
    }
}
