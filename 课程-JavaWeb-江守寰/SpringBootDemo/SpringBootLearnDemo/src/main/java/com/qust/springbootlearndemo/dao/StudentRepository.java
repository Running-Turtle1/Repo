package com.qust.springbootlearndemo.dao;

import com.qust.springbootlearndemo.dto.StudentDTO;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * JpaRepository 会提供很多 Crud 方法, 无需自己实现
 */
@Repository
public interface StudentRepository extends JpaRepository<Student, Integer> {
    Student findById(int id);

    List<Student> findByEmail(String email);
}
