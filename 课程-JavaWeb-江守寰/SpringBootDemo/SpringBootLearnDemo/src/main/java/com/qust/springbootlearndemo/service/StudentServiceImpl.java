package com.qust.springbootlearndemo.service;

import com.qust.springbootlearndemo.converter.StudentConverter;
import com.qust.springbootlearndemo.dao.Student;
import com.qust.springbootlearndemo.dao.StudentRepository;
import com.qust.springbootlearndemo.dto.StudentDTO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.CollectionUtils;

import java.util.Collection;
import java.util.List;

@Service
public class StudentServiceImpl implements StudentService{
    @Autowired
    private StudentRepository studentRepository;

    @Override
    public StudentDTO getStudentById(int id) {
        Student student = studentRepository.findById(id);
        return StudentConverter.studentToStudentDTO(student);
    }

    @Override
    public int addNewStudent(StudentDTO studentDTO) {
        List<Student> studentList = studentRepository.findByEmail(studentDTO.getEmail());
        if (!CollectionUtils.isEmpty(studentList)) {
            throw new IllegalStateException("email" + studentDTO.getEmail() + "has been taken");
        }
        return studentRepository.save(StudentConverter.studentDTOToStudent(studentDTO)).getId();
    }

    @Override
    public void deleteStudentById(int id) {
        if(studentRepository.existsById(id)) {
            studentRepository.deleteById(id);
        }
        else {
            throw new IllegalStateException("studentId" + id + "has not been taken");
        }
    }

    @Override
    @Transactional
    public StudentDTO updateStudentById(int id, String name, String email) {
        if(studentRepository.existsById(id)) {
            Student student = studentRepository.findById(id);
            student.setName(name);
            student.setEmail(email);
            return StudentConverter.studentToStudentDTO(studentRepository.save(student));
        }
        else{
            throw new IllegalStateException("studentId" + id + "has not been taken");
        }
    }
}
