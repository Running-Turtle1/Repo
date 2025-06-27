package cn.edu.qust.ll1;

public class anlysis {
	
	//������
	private String tab[][] = { { "$", "+", "-", "*", "/", "(",  ")", "i", "#" },
							   { "E", "$", "$", "$", "$", "TG", "$", "TG", "$" },
		                       { "G", "+TG", "-TG", "$", "$", "$", "��", "$", "��" },
		                       { "T", "$", "$", "$", "$", "FS", "$", "FS", "$" },
	                       	   { "S", "��", "��", "*FS", "/FS", "$", "��", "$", "��" },
		                       { "F", "$", "$", "$", "$", "(E)", "$", "i", "$" } };

private String input;  //input�д������ı��ʽ

private StringBuffer tempBuffer;    //���Ҫ������ַ���

private int ptr, row, col, step; //ָ�룬Ԥ����е��У��У���ǰ����

private boolean symbol;

private stack stack;

public anlysis(){
	stack =new stack();
	tempBuffer = new StringBuffer();
	symbol=true;
	input="";
	row=1;
	ptr=0;
	step=1;
}


//////////////////////////////////methods./////////////////////////////////
public int column(char c) {  //�ж�Ԥ����е���
	switch (c) {
	case '+':
		return 1;
	case '-':
		return 2;
	case '*':
		return 3;
	case '/':
		return 4;
	case '(':
		return 5;
	case ')':
		return 6;
	case 'i':
		return 7;
	case '#':
		return 8;
	default:
		return -1;
	}
}

public int line(char c) { //�ж�Ԥ����е���
	switch (c) {
	case 'E':
		return 1;
	case 'G':
		return 2;
	case 'T':
		return 3;
	case 'S':
		return 4;
	case 'F':
		return 5;
	default:
		return -1;
	}
}

public void pri(String str) {
	
		tempBuffer.append(String.format("%-8d%-20s%-20s%-20s\r\n", step, stack
				.toString(), input.substring(ptr), str));
	     step++;
}

public void analyse() {
	stack.push(tab[row][0]);   //Ԥ����еĵ�һ��Ԫ�ء�E��
	pri("��ʼ��");
	String tmp;
	char ctmp;   //ջ��Ԫ��
	while (!(input.charAt(ptr) == '#' && stack.getTop() == '#')) {
		ctmp = stack.getTop();
		if (input.charAt(ptr) == ctmp) { //��ջ��Ԫ�رȽ�
			stack.pop();
			ptr++;
			pri("" + ctmp + "ƥ��");
			continue;
		}
		col = column(input.charAt(ptr));
		if (col == -1) {
			symbol = false;
			pri("δ������ַ�");
			ptr++;
			continue;
		}
		row = line(ctmp);
		if (row == -1) {
			symbol = false;
			pri("����");
			stack.pop();
			if (input.charAt(ptr) != '#') {
				ptr++;
			}
			continue;
		}
		tmp = tab[row][col];
		if (tmp.charAt(0) == '$') {
			symbol = false;
			pri("����");
			stack.pop();
			if (input.charAt(ptr) != '#') {
				ptr++;
			}
		} else if (tmp.charAt(0) == '��') {
			stack.pop();
			pri("" + ctmp + "->" + '��');
		} else {
			stack.pop();
			stack.push(tmp);
			pri("" + ctmp + "->" + tmp);
		}
	}
}

public String work(String ts) {
			input = ts;  
			input = input.trim()+ '#';
			symbol = true;
			stack.clear();
			tempBuffer.append("\r\n���� ��  ����ջ           ʣ������ջ       ���ò���ʽ\r\n");
			analyse();
			if (symbol) {
				tempBuffer.append("\r����ȷ�ķ��Ŵ�\r");
				return tempBuffer.toString();
			} else {
				tempBuffer.append("\r������ȷ�ķ��Ŵ�\r");
				return tempBuffer.toString();
			}
		
}

////////////////////////////////////gets and sets////////////////////////////////
public StringBuffer getTempBuffer() {
	return tempBuffer;
}

public void setTempBuffer(StringBuffer tempBuffer) {
	this.tempBuffer = tempBuffer;
}

public stack getStack() {
	return stack;
}

public void setStack(stack stack) {
	this.stack = stack;
}

public String[][] getTab() {
	return tab;
}

public void setTab(String[][] tab) {
	this.tab = tab;
}

public String getInput() {
	return input;
}

public void setInput(String ns) {
	this.input = ns;
}

public int getPtr() {
	return ptr;
}

public void setPtr(int ptr) {
	this.ptr = ptr;
}

public int getRow() {
	return row;
}

public void setRow(int row) {
	this.row = row;
}

public int getCol() {
	return col;
}

public void setCol(int col) {
	this.col = col;
}

public int getStep() {
	return step;
}

public void setStep(int step) {
	this.step = step;
}

public boolean isBoo() {
	return symbol;
}

public void setBoo(boolean boo) {
	this.symbol = boo;
}

}
