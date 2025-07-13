package com.qust.stumis.service.impl;

import com.qust.stumis.dao.CourseDao;
import com.qust.stumis.entity.Course;
import com.qust.stumis.service.CourseService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class CourseServiceImpl implements CourseService {

    @Autowired
    CourseDao courseDao;

    @Override
    public List<Course> search() {
        return courseDao.search();
    }

    @Override
    public boolean add(Course course) {
        int rtn = courseDao.add(course);
        return rtn > 0;
    }

    @Override
    public boolean delete(String cno) {
        int rtn = courseDao.delete(cno);
        return rtn > 0;
    }

    @Override
    public boolean update(Course course){
        int rtn = courseDao.update(course);
        return rtn > 0;
    }

    @Override
    public Course findByCno(String cno) {
        return courseDao.findByCno(cno);
    }
}
