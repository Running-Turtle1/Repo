// 逆波兰式分析器实现  
package cn.edu.qust.nbls;  
import java.util.*;  

public class calculator_test {  
    static String operator = "+-*/%^()";  // 运算符集合  

    /** 预处理表达式：处理正负号，如-1+(-2)转为0-1+(0-2) */  
    public static String pretreatment(String str) {  
        StringBuffer sb = new StringBuffer(str);  
        for (int i = 0; i < sb.length(); i++) {  
            char c = sb.charAt(i);  
            if (operator.indexOf(c) >= 0) {  
                if (i == 0) {                  // 开头的正负号  
                    sb.insert(0, '0');  
                    i++;  
                } else if (sb.charAt(i - 1) == '(') {  // 括号后的正负号  
                    sb.insert(i, '0');  
                    i++;  
                }  
            }  
        }  
        return sb.toString();  
    }  

    /** 运算符优先级比较：返回-1(op1>op2)、0(相等)、1(op1<op2) */  
    public static int opcompare(char op1, char op2) {  
        if (op1 == '(') return 1;             // 左括号优先级最低，需压栈  
        if (op1 == '^') return (op2 == '^') ? 0 : -1;  
        if ("+-".indexOf(op1) >= 0) {  
            return ("+-".indexOf(op2) >= 0) ? 0 : 1;  
        } else {  
            if ("+-".indexOf(op2) >= 0) return -1;  
            else if (op2 == '^') return 1;  
            else return 0;  
        }  
    }  

    /** 中缀表达式转后缀表达式并计算 */  
    public static double Calculator2(String s) throws Exception {  
        String prestr = pretreatment(s);  
        LinkedBlockingQueue<String> polish = new LinkedBlockingQueue<>();  
        Stack<Character> opStack = new Stack<>();  
        StringBuffer numBuffer = new StringBuffer();  

        // 生成后缀表达式  
        for (int i = 0; i < prestr.length(); i++) {  
            char c = prestr.charAt(i);  

            if (operator.indexOf(c) >= 0) {  // 遇到运算符  
                if (numBuffer.length() > 0) {  
                    polish.offer(numBuffer.toString());  
                    numBuffer = new StringBuffer();  
                }  

                switch (c) {  
                    case '(':  
                        opStack.push(c);  
                        break;  
                    case ')':  
                        while (!opStack.isEmpty() && opStack.peek() != '(') {  
                            polish.offer(String.valueOf(opStack.pop()));  
                        }  
                        if (!opStack.isEmpty() && opStack.peek() == '(') {  
                            opStack.pop();  // 弹出左括号  
                        }  
                        break;  
                    default:  
                        while (!opStack.isEmpty() && opStack.peek() != '(') {  
                            char topOp = opStack.peek();  
                            if (opcompare(topOp, c) <= 0) {  
                                polish.offer(String.valueOf(opStack.pop()));  
                            } else {  
                                break;  
                            }  
                        }  
                        opStack.push(c);  
                        break;  
                }  
            } else {  // 遇到数字  
                numBuffer.append(c);  
            }  
        }  

        // 处理剩余数字和运算符  
        if (numBuffer.length() > 0) {  
            polish.offer(numBuffer.toString());  
        }  
        while (!opStack.isEmpty()) {  
            polish.offer(String.valueOf(opStack.pop()));  
        }  

        System.out.println("后缀表达式：" + polish);  
        return CalcstraWithQueue(polish);  
    }  

    /** 计算后缀表达式的值 */  
    public static double CalcstraWithQueue(Queue<String> que) throws Exception {  
        Stack<Double> numStack = new Stack<>();  
        while (true) {  
            String str = que.poll();  
            if (str == null) break;  

            if (operator.indexOf(str) >= 0) {  // 运算符  
                if (numStack.size() < 2) {  
                    throw new Exception("表达式错误：操作数不足");  
                }  
                double num2 = numStack.pop();  
                double num1 = numStack.pop();  
                double result = 0;  

                switch (str.charAt(0)) {  
                    case '+': result = num1 + num2; break;  
                    case '-': result = num1 - num2; break;  
                    case '*': result = num1 * num2; break;  
                    case '/':  
                        if (num2 == 0) throw new Exception("错误：除数为0");  
                        result = num1 / num2; break;  
                    case '%':  
                        if (num2 == 0) throw new Exception("错误：取模除数为0");  
                        result = num1 % num2; break;  
                    case '^': result = Math.pow(num1, num2); break;  
                    default: throw new Exception("未知运算符：" + str);  
                }  
                numStack.push(result);  
            } else {  // 数字  
                numStack.push(Double.valueOf(str));  
            }  
        }  

        if (numStack.size() != 1) {  
            throw new Exception("表达式错误：计算结果不唯一");  
        }  
        return numStack.pop();  
    }  

    public static void main(String[] args) {  
        System.out.println("==== 逆波兰式计算器 ====");  
        Scanner reader = new Scanner(System.in);  
        System.out.println("请输入表达式（支持+ - * / % ^ ()）：");  
        while (reader.hasNextLine()) {  
            String s = reader.nextLine();  
            if (s.equals("exit")) break;  
            try {  
                double result = Calculator2(s);  
                System.out.println("计算结果：" + result);  
            } catch (Exception e) {  
                System.out.println("错误：" + e.getMessage());  
            }  
            System.out.println("请输入下一个表达式（或输入exit退出）：");  
        }  
        reader.close();  
    }  
}  