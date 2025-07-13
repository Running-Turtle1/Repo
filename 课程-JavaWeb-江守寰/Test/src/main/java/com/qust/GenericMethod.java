package com.qust;

public class GenericMethod {
    public static <T> void printArray(T[] array) {
        for(T element : array) {
            System.out.println(element);
        }
        System.out.println();
    }
    public static void main(String[] args) {
        Integer[] intArray = {1, 2, 3};
        String[] strArray = {"A", "B", "C"};

        printArray(intArray);
        printArray(strArray);
    }
}
