package cn.edu.qust.exp5.dao;

import cn.edu.qust.exp5.entity.Student;
import cn.edu.qust.exp5.util.JdbcUtil;

import java.sql.*;
import java.util.*;

public class StudentDao {
    private Connection conn = null;
    private PreparedStatement stmt = null;
    private ResultSet rs = null;
    private List<Student> students = null;

    public List<Student> findAll() {
        List<Student> students = new ArrayList<>();
        try {
            // 获取连接
            conn = JdbcUtil.getConnection();
            String sql = "select sno, sname, age from student";
            stmt = conn.prepareStatement(sql);
            rs = stmt.executeQuery();
            while (rs.next()) {
                Student student = new Student();
                student.setSno(rs.getString("sno"));
                student.setSname(rs.getString("sname"));
                student.setAge(rs.getInt("age"));
                students.add(student);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            // 释放资源
            JdbcUtil.release(rs, stmt, conn);
        }
        return students;
    }

    public boolean insert(Student s) {
        int row = 0;
        try {
            // 获取连接
            conn = JdbcUtil.getConnection();
            String sql = "insert into student(sno, sname, age) values(?, ?, ?)";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, s.getSno());
            stmt.setString(2, s.getSname());
            stmt.setInt(3, s.getAge());
            row = stmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            // 释放资源
            JdbcUtil.release(rs, stmt, conn);
        }
        if (row > 0)
            return true;
        else
            return false;
    }

    public boolean update(Student s) {
        int row = 0;
        try {
            // 获取连接
            conn = JdbcUtil.getConnection();
            String sql = "update student set sname=?, age=? where sno=?";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, s.getSname());
            stmt.setInt(2, s.getAge());
            stmt.setString(3, s.getSno());
            row = stmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            // 释放资源
            JdbcUtil.release(rs, stmt, conn);
        }
        if (row > 0)
            return true;
        else
            return false;
    }

    public boolean delete(String sno) {
        int row = 0;
        try {
            // 获取连接
            conn = JdbcUtil.getConnection();
            String sql = "delete from student where sno=?";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, sno);
            row = stmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            // 释放资源
            JdbcUtil.release(rs, stmt, conn);
        }
        if (row > 0)
            return true;
        else
            return false;
    }

    public Student findBySno(String sno) {
        Student student = null;
        try {
            // 获取连接
            conn = JdbcUtil.getConnection();
            String sql = "select sno, sname, age from student where sno=?";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, sno);
            rs = stmt.executeQuery();
            if (rs.next()) {
                student = new Student();
                student.setSno(rs.getString("sno"));
                student.setSname(rs.getString("sname"));
                student.setAge(rs.getInt("age"));
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            // 释放资源
            JdbcUtil.release(rs, stmt, conn);
        }
        return student;
    }
}

