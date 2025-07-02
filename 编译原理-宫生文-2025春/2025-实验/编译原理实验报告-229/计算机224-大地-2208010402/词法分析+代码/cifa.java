// �ʷ�������ʵ��  
package cn.edu.qust.cffx;  
import java.io.*;  
import java.util.StringTokenizer;  

public class Cifafenxi {  
    // �������б�  
    static String reservedWords = "if else int float void main while for return";  
    // ������ͷָ���  
    static char[] operators = {'+', '-', '*', '/', '=', '>', '<', ',', ';', '{', '}', '(', ')'};  
    static int[] operatorTypes = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};  

    public static void main(String[] args) {  
        System.out.println("==== �ʷ������� ====");  
        try {  
            // ��ȡԴ�ļ�������ΪD:/test.c��  
            File file = new File("D:/test.c");  
            FileReader fr = new FileReader(file);  
            BufferedReader br = new BufferedReader(fr);  
            String line;  

            System.out.println("����ʶ������");  
            while ((line = br.readLine()) != null) {  
                analyzeLine(line);  
            }  
            br.close();  
        } catch (FileNotFoundException e) {  
            System.out.println("�ļ�δ�ҵ���");  
            e.printStackTrace();  
        } catch (IOException e) {  
            e.printStackTrace();  
        }  
    }  

    // �������д���  
    public static void analyzeLine(String line) {  
        String numBuffer = "";       // ���ֻ�����  
        String charBuffer = "";      // ��ĸ/��ʶ��������  
        boolean inComment = false;   // ע�ͱ��  

        for (int i = 0; i < line.length(); i++) {  
            char c = line.charAt(i);  

            // ����ע��  
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
                    break;  // ��ע�ͣ�������ǰ�з���  
                }  
            }  

            // ����������ͷָ���  
            boolean isOperator = false;  
            for (int j = 0; j < operators.length; j++) {  
                if (c == operators[j]) {  
                    isOperator = true;  
                    // �����ǰ����������  
                    if (!charBuffer.isEmpty()) {  
                        checkReservedWord(charBuffer);  
                        charBuffer = "";  
                    }  
                    if (!numBuffer.isEmpty()) {  
                        System.out.println("{NUM," + numBuffer + "}");  
                        numBuffer = "";  
                    }  
                    // ��������  
                    System.out.println("{OP," + operators[j] + "}");  
                    break;  
                }  
            }  
            if (isOperator) continue;  

            // ��������  
            if (c >= '0' && c <= '9') {  
                if (!charBuffer.isEmpty()) {  
                    checkReservedWord(charBuffer);  
                    charBuffer = "";  
                }  
                numBuffer += c;  
            }  
            // ������ĸ���»��ߣ���ʶ��/�����֣�  
            else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {  
                if (!numBuffer.isEmpty()) {  
                    System.out.println("{NUM," + numBuffer + "}");  
                    numBuffer = "";  
                }  
                charBuffer += c;  
            }  
            // ����ո���Ʊ�����ָ�����  
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

        // ������ĩʣ�໺����  
        if (!charBuffer.isEmpty()) {  
            checkReservedWord(charBuffer);  
        }  
        if (!numBuffer.isEmpty()) {  
            System.out.println("{NUM," + numBuffer + "}");  
        }  
    }  

    // ����Ƿ�Ϊ������  
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