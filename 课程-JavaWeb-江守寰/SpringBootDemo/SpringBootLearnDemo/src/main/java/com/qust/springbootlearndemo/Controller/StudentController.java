package com.qust.springbootlearndemo.Controller;

import com.qust.springbootlearndemo.dao.Student;
import com.qust.springbootlearndemo.dto.StudentDTO;
import com.qust.springbootlearndemo.response.Response;
import com.qust.springbootlearndemo.service.StudentService;
import jakarta.persistence.MapKey;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
public class StudentController {

    @Autowired
    private StudentService studentService;

    @GetMapping("/student/{id}")
    public Response<StudentDTO> getStudentById(@PathVariable int id) {
        return Response.newSuccess(studentService.getStudentById(id));
    }

    @PostMapping("/student")
    public Response<Integer> addNewStudent(@RequestBody StudentDTO studentDTO) {
        return Response.newSuccess(studentService.addNewStudent(studentDTO));
    }

    @DeleteMapping("/student/{id}")
    public void deleteStudentById(@PathVariable int id) {
        studentService.deleteStudentById(id);
    }

    @PutMapping("/student/{id}")
    public Response<StudentDTO> updateStudent(@PathVariable int id, @RequestParam(required = false) String name, @RequestParam(required = false) String email) {
        return Response.newSuccess(studentService.updateStudentById(id, name, email));
    }
}
