package com.qust.springbootlearndemo.dto;

import com.qust.springbootlearndemo.service.StudentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RestController;


/**
 * 直接返回给前端数据库对象是不合理的
 * 可能有一些加密字段不适合展示
 * 所以一般来说要把数据库对象转换为类对象
 */
@RestController
public class StudentDTO {
    private int id;

    private String name;

    private String email;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }
}
