package com.qust.stumis.service;

import com.qust.stumis.entity.Course;

import java.util.List;

public interface CourseService {
    List<Course> search();

    boolean add(Course course);

    boolean delete(String cno);

    boolean update(Course course);

    Course findByCno(String cno);
}
