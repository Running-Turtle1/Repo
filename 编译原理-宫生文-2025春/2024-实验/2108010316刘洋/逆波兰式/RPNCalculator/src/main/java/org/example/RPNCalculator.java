package org.example;

import java.util.Stack;

public class RPNCalculator {

    public static String infixToRPN(String expression) {
        StringBuilder rpn = new StringBuilder();
        Stack<Character> stack = new Stack<>();

        for (char c : expression.toCharArray()) {
            if (Character.isDigit(c)) {
                rpn.append(c);
            } else if (c == '(') {
                stack.push(c);
            } else if (c == ')') {
                while (!stack.isEmpty() && stack.peek() != '(') {
                    rpn.append(stack.pop());
                }
                stack.pop(); // Discard '('
            } else {
                while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(c)) {
                    rpn.append(stack.pop());
                }
                stack.push(c);
            }
        }

        while (!stack.isEmpty()) {
            rpn.append(stack.pop());
        }

        return rpn.toString();
    }

    public static double evaluateRPN(String rpnExpression) {
        Stack<Double> stack = new Stack<>();

        for (char c : rpnExpression.toCharArray()) {
            if (Character.isDigit(c)) {
                stack.push((double)(c - '0'));
            } else {
                double b = stack.pop();
                double a = stack.pop();
                switch (c) {
                    case '+':
                        stack.push(a + b);
                        break;
                    case '-':
                        stack.push(a - b);
                        break;
                    case '*':
                        stack.push(a * b);
                        break;
                    case '/':
                    if (b == 0) {
                        throw new ArithmeticException("Division by zero");
                    }
                    stack.push(a / b);
                    break;
                    case '^':
                        stack.push(Math.pow(a, b));
                        break;
                }
            }
        }

        return stack.pop();
    }

    private static int precedence(char operator) {
        if (operator == '+' || operator == '-') {
            return 1;
        } else if (operator == '*' || operator == '/') {
            return 2;
        } else if (operator == '^') {
            return 3;
        }
        return 0;
    }

    public static void main(String[] args) {
        String infixExpr = "3+4*2/(1-5)^2";
        String rpnExpr = infixToRPN(infixExpr);
        System.out.println("中缀表达式: " + infixExpr);
        System.out.println("逆波兰式: " + rpnExpr);
        System.out.println("计算结果: " + evaluateRPN(rpnExpr));
    }
}
