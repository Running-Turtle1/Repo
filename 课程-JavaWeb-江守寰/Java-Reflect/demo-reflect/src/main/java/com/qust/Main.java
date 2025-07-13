package com.qust;

import com.qust.reflect_.Student;

import java.lang.reflect.Field;

public class Main {
    public void main(String[] args) {
        // 获取字节码文件
        Class clazz;
        try {
            clazz = Class.forName("com.qust.reflect_.Student");
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }

        // 获取所有公共成员变量
        Field[] fields = clazz.getFields();
        System.out.println("All public variable:");
        for(Field f : fields) {
            System.out.println(f.getName());
        }
        System.out.println();

        // 获取所有成员变量
        fields = clazz.getDeclaredFields();
        System.out.println("All variable:");
        for(Field f : fields) {
            System.out.println(f.getName());
        }
        System.out.println();

        // 获取单个成员变量
        Field gender = null;
        try {
            gender = clazz.getField("gender");
        } catch (NoSuchFieldException e) {
            throw new RuntimeException(e);
        }
        System.out.println(gender);
        System.out.println();

        Field name = null;
        try {
            name = clazz.getDeclaredField("name");
        } catch (NoSuchFieldException e) {
            throw new RuntimeException(e);
        }
        System.out.println(name);
        System.out.println();

        // 获取权限修饰符
        System.out.println(name.getModifiers()); // 2 : 私有的
        // 获取成员变量名
        System.out.println(name.getName());
        // 获取数据类型
        System.out.println(name.getType());
        // 获取对象的值
        Student student = new Student(11, "wpc", "male");
        name.setAccessible(true);
        Object value = null;
        try {
            value = name.get(student);
        } catch (IllegalAccessException e) {
            throw new RuntimeException(e);
        }
        System.out.println(value);
        // 修改对象值
        try {
            name.set(student,"wpc_");
        } catch (IllegalAccessException e) {
            throw new RuntimeException(e);
        }
        System.out.println(student);
    }
}

//        // 获取代理对象
//        BigStar bigStar = new BigStar("鸡哥");
//        Star proxy = ProxyUtil.createProxy(bigStar);
//
//        // 调用对应方法
//        String result = proxy.sing("只因你太美");
//        System.out.println(result);
//
//        proxy.dance();

/**
 * 获取 class 对象的三种方式
 */

//Class clazz1 = null;
//        try {
//clazz1 = Class.forName("com.qust.reflect.Student");
//        } catch (ClassNotFoundException e) {
//        throw new RuntimeException(e);
//        }
//
//Class clazz2 = Student.class;
//
//Class clazz3 = (new Student()).getClass();
//
//        System.out.println(clazz1);
//
//        System.out.println(clazz2);
//
//        System.out.println(clazz3);