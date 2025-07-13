package cn.edu.qust.webdemo;

import java.sql.*;

import com.mysql.cj.PerConnectionLRUFactory;
import com.mysql.cj.jdbc.Driver;

public class JDBCTest2 {
    public static void main(String[] args) throws ClassNotFoundException, SQLException {
        Class.forName("com.mysql.cj.jdbc.Driver");
        String username = "root";
        String password = "1234";
        String url = "jdbc:mysql://localhost:3306/students?ServerTimezone=GMT%2B8&useSSL=false";
        Connection conn = DriverManager.getConnection(url, username, password);

        String sqlInsert = "insert into students values(?,?,?)";
        PreparedStatement stmtInsert = conn.prepareStatement(sqlInsert);
        stmtInsert.setInt(1, 401);
        stmtInsert.setString(2, "P1");
        stmtInsert.setInt(3, 18);

        int cntInsert = 0;
        try{
            cntInsert = stmtInsert.executeUpdate();
        }
        catch (Exception e){
            System.out.println(e.getMessage());
        }

        if(cntInsert > 0){
            System.out.println("Add successfully!\n");
        }
        else{
            System.out.println("Fail at add!\n");
        }

        // 删除
        String sqlDelete = "delete from students where age = ?";
        PreparedStatement stmtDelete = conn.prepareStatement(sqlDelete);
        stmtDelete.setInt(1, 18);
        int cnt = stmtDelete.executeUpdate();
        System.out.println("delete " + cnt + " infos!\n");

        String sqlUpdate = "update students set sno = ? where age = ?";
        PreparedStatement stmtUpdate = conn.prepareStatement(sqlUpdate);
        stmtUpdate.setInt(1, 666);
        stmtUpdate.setInt(2, 21);
        int updateCnt = 0;
        try{
            updateCnt = stmtUpdate.executeUpdate();
        }
        catch (Exception e){
            System.out.println(e.getMessage());
        }
        if(updateCnt > 0){
            System.out.println("update successfully!\n");
        }
        else{
            System.out.println("Fail at update!\n");
        }

        // release object
        stmtInsert.close();
        stmtDelete.close();
        stmtUpdate.close();
        conn.close();
    }
}
