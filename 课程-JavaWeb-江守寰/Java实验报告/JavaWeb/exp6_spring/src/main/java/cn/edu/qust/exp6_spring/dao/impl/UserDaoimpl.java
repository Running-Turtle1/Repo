package cn.edu.qust.exp6_spring.dao.impl;

import cn.edu.qust.exp6_spring.dao.UserDao;

public class UserDaoimpl implements UserDao {
    @Override
    public void save(){
        System.out.println("dao save...");
    }
}
