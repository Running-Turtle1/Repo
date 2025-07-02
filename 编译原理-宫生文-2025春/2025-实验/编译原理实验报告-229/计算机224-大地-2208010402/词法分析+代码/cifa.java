// 词法分析器实现  
package cn.edu.qust.cffx;  
import java.io.*;  
import java.util.StringTokenizer;  

public class Cifafenxi {  
    // 保留字列表  
    static String reservedWords = "if else int float void main while for return";  
    // 运算符和分隔符  
    static char[] operators = {'+', '-', '*', '/', '=', '>', '<', ',', ';', '{', '}', '(', ')'};  
    static int[] operatorTypes = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};  

    public static void main(String[] args) {  
        System.out.println("==== 词法分析器 ====");  
        try {  
            // 读取源文件（假设为D:/test.c）  
            File file = new File("D:/test.c");  
            FileReader fr = new FileReader(file);  
            BufferedReader br = new BufferedReader(fr);  
            String line;  

            System.out.println("单词识别结果：");  
            while ((line = br.readLine()) != null) {  
                analyzeLine(line);  
            }  
            br.close();  
        } catch (FileNotFoundException e) {  
            System.out.println("文件未找到！");  
            e.printStackTrace();  
        } catch (IOException e) {  
            e.printStackTrace();  
        }  
    }  

    // 分析单行代码  
    public static void analyzeLine(String line) {  
        String numBuffer = "";       // 数字缓冲区  
        String charBuffer = "";      // 字母/标识符缓冲区  
        boolean inComment = false;   // 注释标记  

        for (int i = 0; i < line.length(); i++) {  
            char c = line.charAt(i);  

            // 跳过注释  
            if (inComment) {  
                if (c == '*' && i < line.length() - 1 && line.charAt(i+1) == '/') {  
                    inComment = false;  
                    i++;  
                }  
                continue;  
            }  
            if (c == '/' && i < line.length() - 1) {  
                if (line.charAt(i+1) == '*') {  
                    inComment = true;  
                    i++;  
                } else if (line.charAt(i+1) == '/') {  
                    break;  // 行注释，结束当前行分析  
                }  
            }  

            // 处理运算符和分隔符  
            boolean isOperator = false;  
            for (int j = 0; j < operators.length; j++) {  
                if (c == operators[j]) {  
                    isOperator = true;  
                    // 输出当前缓冲区内容  
                    if (!charBuffer.isEmpty()) {  
                        checkReservedWord(charBuffer);  
                        charBuffer = "";  
                    }  
                    if (!numBuffer.isEmpty()) {  
                        System.out.println("{NUM," + numBuffer + "}");  
                        numBuffer = "";  
                    }  
                    // 输出运算符  
                    System.out.println("{OP," + operators[j] + "}");  
                    break;  
                }  
            }  
            if (isOperator) continue;  

            // 处理数字  
            if (c >= '0' && c <= '9') {  
                if (!charBuffer.isEmpty()) {  
                    checkReservedWord(charBuffer);  
                    charBuffer = "";  
                }  
                numBuffer += c;  
            }  
            // 处理字母和下划线（标识符/保留字）  
            else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {  
                if (!numBuffer.isEmpty()) {  
                    System.out.println("{NUM," + numBuffer + "}");  
                    numBuffer = "";  
                }  
                charBuffer += c;  
            }  
            // 处理空格和制表符（分隔符）  
            else if (c == ' ' || c == '\t') {  
                if (!charBuffer.isEmpty()) {  
                    checkReservedWord(charBuffer);  
                    charBuffer = "";  
                }  
                if (!numBuffer.isEmpty()) {  
                    System.out.println("{NUM," + numBuffer + "}");  
                    numBuffer = "";  
                }  
            }  
        }  

        // 处理行末剩余缓冲区  
        if (!charBuffer.isEmpty()) {  
            checkReservedWord(charBuffer);  
        }  
        if (!numBuffer.isEmpty()) {  
            System.out.println("{NUM," + numBuffer + "}");  
        }  
    }  

    // 检查是否为保留字  
    private static void checkReservedWord(String word) {  
        StringTokenizer tokenizer = new StringTokenizer(reservedWords);  
        boolean isReserved = false;  
        while (tokenizer.hasMoreTokens()) {  
            if (word.equalsIgnoreCase(tokenizer.nextToken())) {  
                System.out.println("{RESERVED," + word + "}");  
                isReserved = true;  
                break;  
            }  
        }  
        if (!isReserved) {  
            System.out.println("{ID," + word + "}");  
        }  
    }  
}  