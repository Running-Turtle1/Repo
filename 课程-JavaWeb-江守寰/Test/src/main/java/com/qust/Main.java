package com.qust;


import java.io.FileWriter;
import java.io.IOException;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) throws IOException {
        FileWriter fw = new FileWriter("src\\main\\java\\com\\qust\\data.txt", true);
        fw.append("Hello World\n");
        fw.close();
    }
}
