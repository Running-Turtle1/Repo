package cn.edu.qust.ll1;

import java.util.Scanner;

public class system {
		public static void main(String[] args){
			while(true){
			anlysis a = new anlysis();	
			Scanner scanner = new Scanner(System.in);// ����������ɨ����
			System.out.println("���������");// ��ʾ�û�����
			String line = scanner.nextLine();// ��ȡ�û������һ���ı�
			//System.out.println(line);
			System.out.println(a.work(line));
			}
			
		}
}
