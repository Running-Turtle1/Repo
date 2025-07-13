package cn.edu.qust.exp5.util;

import java.sql.*;

public class JdbcUtil {
    private static String url = "jdbc:mysql://localhost:3306/students?serverTimezone=GMT%2B8&useSSL=false&characterEncoding=utf8";
    private static String username = "root";
    private static String password = "123";

    static {
        // 注册并加载 JDBC 驱动
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace(); // 可以改用日志工具记录
        }
    }

    /**
     * 获得连接对象
     *
     * @return Connection
     */
    public static Connection getConnection() {
        Connection conn = null;
        try {
            conn = DriverManager.getConnection(url, username, password);
        } catch (SQLException e) {
            e.printStackTrace(); // 可以改用日志工具记录
        }
        return conn;
    }

    /**
     * 释放 Statement 和 Connection
     *
     * @param stmt Statement
     * @param conn Connection
     */
    public static void release(Statement stmt, Connection conn) {
        if (stmt != null) {
            try {
                stmt.close();
            } catch (SQLException e) {
                e.printStackTrace(); // 可以改用日志工具记录
            }
        }

        if (conn != null) {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace(); // 可以改用日志工具记录
            }
        }
    }

    /**
     * 释放 ResultSet、Statement 和 Connection
     *
     * @param rs   ResultSet
     * @param stmt Statement
     * @param conn Connection
     */
    public static void release(ResultSet rs, Statement stmt, Connection conn) {
        if (rs != null) {
            try {
                rs.close();
            } catch (SQLException e) {
                e.printStackTrace(); // 可以改用日志工具记录
            }
        }
        release(stmt, conn);
    }
}