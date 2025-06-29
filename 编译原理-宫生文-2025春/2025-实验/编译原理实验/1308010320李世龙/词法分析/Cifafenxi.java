package cn.edu.qust.cffx;


import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class Cifafenxi {
	
	static String hongString="ID IF GT INT THEN BEGIN  WHILE DO END static";
	static char []word={'+','-','*','/','>','=',',',';','{','}','(',')','&'};
	static int  []word1={1,2,3,4,5,6,7,8,9,10,11,12,13};
	
	
	public static void main(String[] args) throws FileNotFoundException {
	File file=new File("D:/test.txt");  //输入文件
	FileReader fReader=new FileReader(file);
	BufferedReader bf=new BufferedReader(fReader);
		                   String t1;
						try {
							t1 = bf.readLine();
						
	                    while(t1 != null){  
	                        getChar(t1);
	                        t1=bf.readLine();  
		                    } 
						}
	                    catch (IOException e) {
							// TODO 自动生成 catch 块
							e.printStackTrace();
						}  
	}
	
	
	public static void getChar(String t1){
		String startNum="";
		String startChar="";
		char[]a=t1.toCharArray();
			for(int i=0;i<a.length;i++)
		{
			for(int j=0;j<13;j++)
			{
				if(a[i]==word[j]){
					
					if(startChar!=""){
						if(!suitableChar(startChar))
						{
							 System.out.println("{ID,"+startChar);
						}
						startChar="";
					}
					if(startNum!=""){
						System.out.println("{REAL,"+startNum+"}");
						startNum="";
					}
					System.out.println("{"+word1[j]+"   "+word[j]+" }");
					break;
				}
			
				else if('0'<=a[i]&&a[i]<='9') {
					if(startChar!=""){
						if(suitableChar(startChar))
						{
							 System.out.println("{ID,"+startChar+"}");
						}
						startChar="";
					}
					startNum=startNum+a[i];
					break;
				}
				else if (('A'<=a[i]&&a[i]<='Z')||('a'<=a[i]&&a[i]<='z')) {
	              if(startNum!=""){
	            	  System.out.println("{REAL,"+startNum+"}");
						startNum="";
					}
					startChar=startChar+a[i];
					break;
				}
				else {
					if(startChar!=""){
						if(suitableChar(startChar));
						else
						{
							 System.out.println("{ID,"+startChar+"}");
						}
						startChar="";
					}
					if(startNum!=""){
						System.out.println("{REAL,"+startNum+"}");
						startNum="";
					}
				}
			}
		}
		if(startChar!=""){
			System.out.println("本条语句执行");
			if(suitableChar(startChar));
			else
			{
				 System.out.println("{ID,"+startChar+"}");
			}
			startChar="";
		}
		if(startNum!=""){
			System.out.println("{REAL,"+startNum+"}");
			startNum="";
		}
		
	}
	
	
	private static boolean suitableChar(String startChar) {
		// TODO 自动生成方法存根
		boolean flag=false ;//定义布尔变量 flag
		StringTokenizer tokenizer=new StringTokenizer(hongString);//string tokenizer 类允许应用程序将字符串分解为标记。
		  while (tokenizer.hasMoreTokens()) {             
			if(  startChar.equalsIgnoreCase(tokenizer.nextToken()))
				{
				System.out.println("{"+startChar+","+startChar.toLowerCase()+"}");
				flag=true;
				}   
			  
		  }
		  return flag;
	}
	
}
