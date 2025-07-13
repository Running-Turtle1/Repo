package com.qust.practice2;

public class Teacher {
    private String name;
    private long salary;


    public Teacher() {
    }

    public Teacher(String name, long salary) {
        this.name = name;
        this.salary = salary;
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
     * @return salary
     */
    public long getSalary() {
        return salary;
    }

    /**
     * 设置
     * @param salary
     */
    public void setSalary(long salary) {
        this.salary = salary;
    }

    public void teach() {
        System.out.println("The Teacher" + name + " is teaching");
    }


    public String toString() {
        return "Teacher{name = " + name + ", salary = " + salary + "}";
    }
}
