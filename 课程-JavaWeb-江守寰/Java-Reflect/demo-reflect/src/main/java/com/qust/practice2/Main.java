package com.qust.practice2;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.Properties;

public class Main {
    public static void main(String[] args) throws IOException, ClassNotFoundException, NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException {
        // 读取配置文件信息
        Properties prop = new Properties();
        prop.load(new FileInputStream("C:\\Users\\95432\\Desktop\\Java-Reflect\\demo-reflect\\src\\main\\resources\\test .properties"));
        System.out.println(prop);

        // 获取全类名和方法名
        String className = (String) prop.get("classname");
        String methodName = (String) prop.get("method");

        System.out.println(className);
        System.out.println(methodName);

        // 利用反射创建对象，并运行方法
        Class clazz = Class.forName(className);
        // 获取构造方法
        Constructor con = clazz.getDeclaredConstructor();
        Object o = con.newInstance();
        System.out.println(o);

//        clazz.newInstance(); @deprecated

        clazz.getDeclaredMethod(methodName).invoke(o);
    }
}
