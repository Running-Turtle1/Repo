package com.qust.practice1;

import java.io.BufferedOutputStream;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.Field;

public class MyReflectDemo {
    public void main(String[] args) throws IOException, IllegalAccessException {
        Student s = new Student("wpc", 21, "male", "learn", 180.5);
        Teacher t = new Teacher("teacher1", -100);
        System.out.println(System.getProperty("user.dir"));
        saveObjects(s);
    }

    // 将对象里面所有的成员变量名和值保存到本地文件中
    public static void saveObjects(Object obj) throws IOException, IllegalAccessException {
        // 1. 获取字节码文件对象
        Class clazz = obj.getClass();

        // 2. 创建 IO 流
        BufferedWriter bw = new BufferedWriter(new FileWriter("C:\\Users\\95432\\Desktop\\Java-Reflect\\demo-reflect\\src\\main\\java\\com\\qust\\practice1\\data.txt"));
//        BufferedWriter bw = new BufferedWriter(new FileWriter("demo-reflect\\src\\main\\java\\com\\qust\\practice1\\data.txt"));

        // 3. 获取所有的成员变量
        Field[] fields = clazz.getDeclaredFields();
        for (Field field : fields) {
            field.setAccessible(true);
            String name = field.getName();
            Object value = field.get(obj);
            System.out.println(name + "=" + value);
            bw.write(name + "=" + value);
            bw.write("\n");
        }
        bw.close();
    }
}
