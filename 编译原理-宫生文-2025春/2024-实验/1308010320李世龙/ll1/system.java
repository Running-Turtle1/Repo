package cn.edu.qust.ll1;

import java.util.Scanner;

public class system {
		public static void main(String[] args){
			while(true){
			anlysis a = new anlysis();	
			Scanner scanner = new Scanner(System.in);// 创建输入流扫描器
			System.out.println("请输入语句");// 提示用户输入
			String line = scanner.nextLine();// 获取用户输入的一行文本
			//System.out.println(line);
			System.out.println(a.work(line));
			}
			
		}
}
