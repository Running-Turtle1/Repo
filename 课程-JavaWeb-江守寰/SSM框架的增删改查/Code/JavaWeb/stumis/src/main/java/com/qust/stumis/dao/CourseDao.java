package com.qust.stumis.dao;

import org.springframework.stereotype.Repository;
import com.qust.stumis.entity.Course;

import java.util.List;

@Repository
public interface CourseDao {
    List<Course> search();

    int add(Course course);

    int delete(String cno);

    int update(Course course);

    Course findByCno(String cno);
}
