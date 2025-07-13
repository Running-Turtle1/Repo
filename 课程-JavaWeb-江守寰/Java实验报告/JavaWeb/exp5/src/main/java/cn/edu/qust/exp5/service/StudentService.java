package cn.edu.qust.exp5.service;

import java.util.List;
import cn.edu.qust.exp5.entity.*;
import cn.edu.qust.exp5.dao.*;

public class StudentService {
    private StudentDao studentDao = new StudentDao();

    public List<Student> findAll() {
        return studentDao.findAll();
    }

    public boolean insert(Student s) {
        return studentDao.insert(s);
    }

    public boolean update(Student s) {
        return studentDao.update(s);
    }

    public boolean delete(String sno) {
        return studentDao.delete(sno);
    }

    public Student findBySno(String sno) {
        return studentDao.findBySno(sno);
    }
}

