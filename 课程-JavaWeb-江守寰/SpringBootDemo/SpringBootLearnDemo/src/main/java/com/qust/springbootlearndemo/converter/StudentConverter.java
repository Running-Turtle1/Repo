package com.qust.springbootlearndemo.converter;

import com.qust.springbootlearndemo.dao.Student;
import com.qust.springbootlearndemo.dto.StudentDTO;

public class StudentConverter {
    public static StudentDTO studentToStudentDTO(Student student) {
        StudentDTO studentDTO = new StudentDTO();
        studentDTO.setId(student.getId());
        studentDTO.setName(student.getName());
        studentDTO.setEmail(student.getEmail());
        return studentDTO;
    }

    public static Student studentDTOToStudent(StudentDTO studentDTO) {
        Student student = new Student();
        student.setId(studentDTO.getId());
        student.setName(studentDTO.getName());
        student.setEmail(studentDTO.getEmail());
        return student;
    }
}
