package cn.edu.qust.ll1;


public class stack {

	private char s[];

	private int top;

	public stack() {
		s = new char[200];
		s[0] = '#';
		top = 0;
	}

	char getTop() {
		return s[top];
	}

	void push(String str) {
		for (int i = str.length() - 1; i >= 0; i--) {
			s[++top] = str.charAt(i);
		}
	}

	void clear() {
		top = 0;
	}

	char pop() {
		if (top != 0) {
			top--;
		}
		return s[top];
	}

	public String toString() {
		String tmp = "";
		for (int i = 0; i <= top; i++) {
			tmp += s[i];
		}
		return tmp;
	}
}

