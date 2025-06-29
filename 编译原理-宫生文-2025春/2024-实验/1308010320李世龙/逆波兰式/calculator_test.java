package cn.edu.qust.nbls;

import java.util.Queue;
import java.util.Scanner;
import java.util.Stack;
import java.util.concurrent.LinkedBlockingQueue;

public class calculator_test {

	static String operator = "+-*/%^()";

	/**
	 * Ԥ������ʽ����������ǰ��0(���һ���Ӻţ����ţ���������ǰ��������ź��棬��üӺţ����ţ�Ϊ������)  ����  -1-(-1+1) ���ֱ��ʽ �ᴦ��� 0-1-(0-1+1)
	 */
	public static String pretreatment(String str) {
		StringBuffer sb = new StringBuffer(str);
		for (int i = 0; i < sb.length(); i++) {
			char c = sb.charAt(i);
			if (operator.indexOf(c) >= 0) {
				if (i == 0) {
					sb.insert(0, '0');
					i++;
				} else if (sb.charAt(i - 1) == '(') {
					sb.insert(i, '0');
					i++;
				}
			}
		}
		return sb.toString();
	}

	/***
	 * 0 ���ȼ���� �� -1 op1 ���ȼ�����op2�� 1 op2 ���ȼ����� op1
	 */
	public static int opcompare(char op1, char op2) {
		if (op1 == '(') { // �������� ��ֱ����ջ ���� op2 ��
			return 1;
		}
		if ('^' == op1) {
			if (op2 == '^') {
				return 0;
			}
			return -1;
		} else if ("+-".indexOf(op1) >= 0) {
			if ("+-".indexOf(op2) >= 0) {
				return 0;
			}
			return 1;
		} else // if("*/%".indexOf(op1) >=0) û��Ҫ ���ж��Ƿ�Ϊ */% ��
		{
			if ("+-".indexOf(op2) >= 0) {
				return -1;
			} else if ('^' == op2) {
				return 1;
			}
			return 0;
		}
	}
	/**
	 * ���㴫����������ʽ 
	 */
	public static double Calculator2(String s) throws Exception {
		//Ԥ����ʽ��
		String prestr = pretreatment(s);
		//���ڱ���  �沨��ʽ �Ķ��� 
		LinkedBlockingQueue<String> polish = new LinkedBlockingQueue<String>();
		// ƴ�� ���� char ---> numble
		StringBuffer temp = new StringBuffer();
		
		Stack<Character> stack = new Stack<Character>();
		for (int i = 0; i < prestr.length(); i++) {

			char c = prestr.charAt(i);
			//����ҵ� ������
			if (operator.indexOf(c) >= 0) {
				if (temp.length() > 0) {//��� ������ ��ѹջ
					polish.offer(temp.toString());
					temp = new StringBuffer();
				}
				switch (c) {
				case '(':
					stack.push(c);
					break;
				case ')':
					while (stack.size() > 0) {
						char op = stack.pop();
						if (op != '(') {
							polish.offer(String.valueOf(op));
						} else {
							break;
						}
					}
					break;
				default:
					if (stack.size() == 0) {
						stack.push(c);
					} else {
						while (stack.size() > 0) {
							char op1 = stack.lastElement();
							int com = opcompare(op1, c);
							if (com <= 0) {
								polish.offer(String.valueOf(stack.pop()));
							} else {
								stack.push(c);
								break;
							}
						}
						if (stack.size() == 0) {
							stack.push(c);
						}
					}
					break;
				}
			} else {
				temp.append(c);
			}
		}
		if (temp.length() > 0) {
			polish.offer(temp.toString());
		}
		while (stack.size() > 0) {
			polish.offer(String.valueOf(stack.pop()));
		}
		System.out.println("��׺���ʽ" + polish.toString());

		return CalcstraWithQueue(polish);
	}
	/**
	 *  ���� �沨�����ʽ  �ö��б�ʾ
	 * @throws Exception  ���ִ����п���
	 */
	public static double CalcstraWithQueue(Queue<String> que) throws Exception {
		Stack<Double> stack = new Stack<Double>();
		while(true)
		{
		String str = que.poll();
		if(str == null)
		{
			break;
		}
		if (operator.indexOf(str) >= 0) {
			
			double num2 = stack.pop();
			double num1 = stack.pop();
			double tempresult = 0;
			switch (str.charAt(0)) {
			case '+':
				tempresult = num1 + num2;
				break;
			case '-':
				tempresult = num1 - num2;
				break;
			case '*':
				tempresult = num1 * num2;
				break;
			case '/':
				if(num2 == 0)
				{
					throw new Exception("����:����Ϊ 0");
				}
				tempresult = num1 / num2;
				break;
			case '%':
				tempresult = num1 % num2;
				break;
			case '^':
				tempresult = Math.pow(num1, num2);
				break;
			default:
				throw new Exception("�����: " + str + " δʶ��!");
			}
			stack.push(tempresult);
		} else {
			stack.push(Double.valueOf(str));
		}
		}
		return stack.pop();
	}
	public static void main(String[] args) {

		Scanner reader = new Scanner(System.in);
		while(true)
		{
		String s = reader.nextLine();
		double result = 0;
		try {
			result = Calculator2(s);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println(result);
		}
	}
}
