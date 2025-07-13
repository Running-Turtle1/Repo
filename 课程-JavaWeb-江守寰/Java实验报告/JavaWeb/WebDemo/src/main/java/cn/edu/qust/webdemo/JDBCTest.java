
package cn.edu.qust.webdemo;
import java.sql.*;
import com.mysql.cj.jdbc.Driver;

public class JDBCTest {
    public static void main(String[] args) throws ClassNotFoundException, SQLException {
        // 注册JDBC驱动
        Class.forName("com.mysql.cj.jdbc.Driver");

        // 数据库连接信息
        String username = "root"; // 用户名
        String password = "1234"; // 密码
        String url = "jdbc:mysql://localhost:3306/students"; // 数据库URL

        // 创建连接
        Connection conn = DriverManager.getConnection(url, username, password);

        // SQL查询语句
        String sql = "SELECT sno, sname, age FROM students";
        PreparedStatement stmt = conn.prepareStatement(sql);
        ResultSet rs = stmt.executeQuery();

        // 处理结果集
        while (rs.next()) {
            System.out.print(rs.getString("sno") + "\t"); // 获取学号
            System.out.print(rs.getString("sname") + "\t"); // 获取姓名
            System.out.println(rs.getInt("age")); // 获取年龄
        }

        // 关闭资源
        rs.close();
        stmt.close();
        conn.close();
    }
}
