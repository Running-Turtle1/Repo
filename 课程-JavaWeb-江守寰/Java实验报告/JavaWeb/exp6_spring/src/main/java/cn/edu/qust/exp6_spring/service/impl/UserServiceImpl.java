package cn.edu.qust.exp6_spring.service.impl;

import cn.edu.qust.exp6_spring.dao.UserDao;
import cn.edu.qust.exp6_spring.service.UserService;

public class UserServiceImpl implements UserService{
    private UserDao userDao;

    public void setUserDao(UserDao userDao) {
        this.userDao = userDao;
    }

    @Override
    public void save() {
        System.out.println("service save");
        userDao.save();
    }

}
