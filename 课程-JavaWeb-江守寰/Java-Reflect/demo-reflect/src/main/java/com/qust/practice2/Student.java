package com.qust.practice2;

public class Student {
    private String name;
    private int age;
    private String gender;
    private String hobby;
    private double height;


    public Student() {
    }

    public Student(String name, int age, String gender, String hobby, double height) {
        this.name = name;
        this.age = age;
        this.gender = gender;
        this.hobby = hobby;
        this.height = height;
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
     * @return gender
     */
    public String getGender() {
        return gender;
    }

    /**
     * 设置
     * @param gender
     */
    public void setGender(String gender) {
        this.gender = gender;
    }

    /**
     * 获取
     * @return hobby
     */
    public String getHobby() {
        return hobby;
    }

    /**
     * 设置
     * @param hobby
     */
    public void setHobby(String hobby) {
        this.hobby = hobby;
    }

    /**
     * 获取
     * @return height
     */
    public double getHeight() {
        return height;
    }

    /**
     * 设置
     * @param height
     */
    public void setHeight(double height) {
        this.height = height;
    }

    public void learn() {
        System.out.println("The student is learning.");
    }

    public String toString() {
        return "Student{name = " + name + ", age = " + age + ", gender = " + gender + ", hobby = " + hobby + ", height = " + height + "}";
    }
}
