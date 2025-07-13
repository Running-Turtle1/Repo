package com.qust.reflect__;

public class Student {
    private String name;
    private int age;
    public String email;


    public Student() {
    }

    public Student(String name, int age, String email) {
        this.name = name;
        this.age = age;
        this.email = email;
    }

    /**
     * 获取
     * @return name
     */
    public String getName() {
        return name;
    }

    /**
     * 设置
     * @param name
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * 获取
     * @return age
     */
    public int getAge() {
        return age;
    }

    /**
     * 设置
     * @param age
     */
    public void setAge(int age) {
        this.age = age;
    }

    /**
     * 获取
     * @return email
     */
    public String getEmail() {
        return email;
    }

    /**
     * 设置
     * @param email
     */
    public void setEmail(String email) {
        this.email = email;
    }

    public String toString() {
        return "Student{name = " + name + ", age = " + age + ", email = " + email + "}";
    }

    public String eat(String food) {
        System.out.println("eating " + food);
        return "full";
    }

    public void sleep() {
        System.out.println("sleeping");
    }
}
