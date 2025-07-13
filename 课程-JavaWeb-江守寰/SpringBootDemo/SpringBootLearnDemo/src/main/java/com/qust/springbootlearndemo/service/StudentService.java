package com.qust.springbootlearndemo.service;

import com.qust.springbootlearndemo.dao.Student;
import com.qust.springbootlearndemo.dto.StudentDTO;
import org.springframework.stereotype.Service;

@Service
public interface StudentService {
    StudentDTO getStudentById(int id);

    int addNewStudent(StudentDTO studentDTO);

    void deleteStudentById(int id);

    StudentDTO updateStudentById(int id, String name, String email);
}
