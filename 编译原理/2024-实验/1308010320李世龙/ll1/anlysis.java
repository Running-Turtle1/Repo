package cn.edu.qust.ll1;

public class anlysis {
	
	//分析表
	private String tab[][] = { { "$", "+", "-", "*", "/", "(",  ")", "i", "#" },
							   { "E", "$", "$", "$", "$", "TG", "$", "TG", "$" },
		                       { "G", "+TG", "-TG", "$", "$", "$", "ε", "$", "ε" },
		                       { "T", "$", "$", "$", "$", "FS", "$", "FS", "$" },
	                       	   { "S", "ε", "ε", "*FS", "/FS", "$", "ε", "$", "ε" },
		                       { "F", "$", "$", "$", "$", "(E)", "$", "i", "$" } };

private String input;  //input中存放输入的表达式

private StringBuffer tempBuffer;    //存放要输出的字符串

private int ptr, row, col, step; //指针，预测表中的行，列，当前步骤

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
public int column(char c) {  //判断预测表中的列
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

public int line(char c) { //判定预测表中的行
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
	stack.push(tab[row][0]);   //预测表中的第一个元素‘E’
	pri("初始化");
	String tmp;
	char ctmp;   //栈顶元素
	while (!(input.charAt(ptr) == '#' && stack.getTop() == '#')) {
		ctmp = stack.getTop();
		if (input.charAt(ptr) == ctmp) { //与栈顶元素比较
			stack.pop();
			ptr++;
			pri("" + ctmp + "匹配");
			continue;
		}
		col = column(input.charAt(ptr));
		if (col == -1) {
			symbol = false;
			pri("未定义的字符");
			ptr++;
			continue;
		}
		row = line(ctmp);
		if (row == -1) {
			symbol = false;
			pri("出错");
			stack.pop();
			if (input.charAt(ptr) != '#') {
				ptr++;
			}
			continue;
		}
		tmp = tab[row][col];
		if (tmp.charAt(0) == '$') {
			symbol = false;
			pri("出错");
			stack.pop();
			if (input.charAt(ptr) != '#') {
				ptr++;
			}
		} else if (tmp.charAt(0) == 'ε') {
			stack.pop();
			pri("" + ctmp + "->" + 'ε');
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
			tempBuffer.append("\r\n步骤   分析栈           剩余输入栈       所用产生式\r\n");
			analyse();
			if (symbol) {
				tempBuffer.append("\r是正确的符号串\r");
				return tempBuffer.toString();
			} else {
				tempBuffer.append("\r不是正确的符号串\r");
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
