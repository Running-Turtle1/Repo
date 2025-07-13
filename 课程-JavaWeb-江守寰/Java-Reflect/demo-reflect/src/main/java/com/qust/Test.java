package com.qust;

import com.qust.reflect__.Student;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class Test {
    public void main(String[] args) {
        Class clazz;
        try {
            clazz = Class.forName("com.qust.reflect__.Student");
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }

        // 获取所有的方法对象（包括父类的所有公共方法）
//        Method[] methods = clazz.getMethods();
//        for(Method method : methods) {
//            System.out.println(method.getName());
//        }


        // 获取所有方法（不包括父类）
        Method[] methods = clazz.getDeclaredMethods();
        for(Method method : methods) {
            System.out.println(method.getName());
        }

        // 获取指定的单一方法
        Method m = null;
        try {
            m = clazz.getMethod("eat", String.class);
        } catch (NoSuchMethodException e) {
            throw new RuntimeException(e);
        }
        System.out.println(m);

        // 获取方法的修饰符
        int modifiers = m.getModifiers();
        // 获取方法名字
        String name = m.getName();
        // 方法形参
        m.getParameters();
        m.getParameterCount();
        m.getParameterTypes();

        // 方法抛出异常
        Class[] exps = m.getExceptionTypes();


        /**
         * 运行方法 invoke
         * 参数一 : 方法的调用者
         * 参数二 : 调用方法传递的参数
         */
        try {
            String res = (String) m.invoke(new Student(), "shit");
            System.out.println(res);
        } catch (IllegalAccessException e) {
            throw new RuntimeException(e);
        } catch (InvocationTargetException e) {
            throw new RuntimeException(e);
        }

        // 获取方法返回值
        Class<?> returnType = m.getReturnType();
        System.out.println(returnType);
    }
}
