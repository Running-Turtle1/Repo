## Question One

> Java 实现动作监听，网格布局添加四个按钮，实现四个不同的文本显示

```java
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class myGUI extends JFrame implements ActionListener{
    private Button b1, b2, b3, b4;
    private TextField t;

    myGUI(){
        this.setSize(300, 500);
        this.setLocation(500, 300);
        this.setVisible(true);
        this.setBackground(Color.GRAY);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLayout(new GridLayout(5, 1));

        b1 = new Button("Click Me, I am dog");
        b1.setBackground(Color.MAGENTA);
        b2 = new Button("Click Me, I am cat");
        b2.setBackground(Color.gray);
        b3 = new Button("Click Me, I am pig");
        b3.setBackground(Color.white);
        b4 = new Button("Click Me, I am chicken");
        b4.setBackground(Color.BLUE);
        t = new TextField();
        t.setBackground(Color.GRAY);

        this.add(b1);
        this.add(b2);
        this.add(b3);
        this.add(b4);
        this.add(t);

        b1.addActionListener(this);
        b2.addActionListener(this);
        b3.addActionListener(this);
        b4.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e){
         if(e.getSource() == b1){
             t.setText("Do not touch me");
         }
         else if(e.getSource() == b2){
             t.setText("I am cat");
         }
         else if(e.getSource() == b3){
             t.setText("Do not eat me");
         }
         else{
             t.setText("chicken");
         }
    }
}

public class Main {
    public static void main(String[] args) {
        new myGUI();
    }
}
```

## Question Two

> 实现计算器

```java
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class Calculator {
    public static void main(String[] args) {
        new ShowCalculate();
    }
}

class ShowCalculate extends JFrame implements ActionListener{
    private JPanel jp;
    private TextField jf1;
    private TextField jf2;
    private TextField jf3;
    private JButton btnAdd;
    private JButton btnMins;
    private JButton btnCheng;
    private JButton btnChu;

    ShowCalculate(){
        this.setSize(300,400);
        this.setTitle("计算器");
        this.setLocation(100, 100);
        jp=new JPanel();
        this.setContentPane(jp); // 设置 jp 为窗口的主面板
        jf1=new TextField();
        jf2=new TextField();
        jf3=new TextField();
        btnAdd =new JButton("+");
        btnAdd.addActionListener(this);
        btnMins=new JButton("-");
        btnMins.addActionListener(this);
        btnCheng=new JButton("*");
        btnCheng.addActionListener(this);
        btnChu=new JButton("/");
        btnChu.addActionListener(this);
        jp.setLayout(new GridLayout(4,1));
        jp.add(jf1);
        jp.add(jf2);

        JPanel jp1=new JPanel();
        jp1.setLayout(new GridLayout(1,4));
        jp1.add(btnAdd);
        jp1.add(btnMins);
        jp1.add(btnCheng);
        jp1.add(btnChu);

        jp.add(jp1);
        jp.add(jf3);

        this.setVisible(true);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
    }


    @Override
    public void actionPerformed(ActionEvent e) {
        int a1=0;
        int a2=0;

        a1=Integer.parseInt((String)jf1.getText());
        a2=Integer.parseInt((String)jf2.getText());
        if(e.getSource()==btnAdd){
            int a=a1+a2;
            jf3.setText(""+a);
            jf1.setText("");
            jf2.setText("");
        }
        else if(e.getSource()==btnMins){
            jf3.setText(""+(a1-a2));
            jf1.setText("");
            jf2.setText("");
        }
        else if(e.getSource()==btnCheng){
            jf3.setText(""+(a1*a2));
            jf1.setText("");
            jf2.setText("");
        }
        else if(e.getSource()==btnChu){
            jf3.setText(""+(a1/a2));
            jf1.setText("");
            jf2.setText("");
        }
    }
}
```

## Question Three

> 实现布局管理

```java
import java.awt.*;
import java.awt.Color;
/*
在使用 AWT（Abstract Window Toolkit）创建图形界面时，通常的做法是 :
先创建所有的组件并将它们添加到容器中，然后再设置容器（比如框架）的大小和可见性，
这样可以确保所有组件按照预期的布局显示出来。
 */

public class Main {
    public static void main(String[] args) {
        // 创建一个框架 f
        Frame f = new Frame("Frame with Panel");

        // 创建一个面板p
        Panel p = new Panel();

        // 把面板p添加到框架f中
        f.add(p);

        // 设置面板p的背景颜色为蓝色
        p.setBackground(Color.BLUE);

        // 设置面板p的布局为流式布局
        p.setLayout(new FlowLayout());

        // 在面板p中添加一个标签l
        Label l = new Label("Label in Panel");
        p.add(l);

        // 在面板p中添加六个按钮
        for (int i = 1; i <= 6; i++) {
            Button b = new Button("Button " + i);
            p.add(b);
        }

        // 创建一个文本框c
        TextField c = new TextField("TextField in Panel", 20);

        // 把文本框c添加到面板p中
        p.add(c);

        // 设置框架f的大小和可见性
        f.setSize(400, 300);
        f.setVisible(true);
    }
}
```

但是更推荐 JFrame 和 JPanel，理由如下 : 

使用 `JFrame` 替代 `Frame`，通常可以避免一些 AWT 的布局和可见性设置上的问题。`JFrame` 是 Swing 提供的一个更现代化的窗口组件，它具有更好的布局管理和组件显示控制机制，能够更方便地创建和管理复杂的用户界面。

使用 `JFrame` 的优势包括：

1. **更好的布局管理器支持：** Swing 提供了多种布局管理器（如 `FlowLayout`, `BorderLayout`, `GridLayout` 等），可以更灵活地管理组件布局。
2. **更直观的可见性设置：** `JFrame` 提供了 `setVisible(true)` 方法来显示窗口，并且通常会在所有组件添加完毕后设置可见性，避免布局显示不正确的问题。
3. **更丰富的组件支持：** Swing 提供了丰富的组件库，比如 `JPanel`, `JButton`, `JLabel` 等，它们更易于使用和管理。

## Question Four

> 实现菜单功能

```java
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

class MenuExample {
    public MenuExample() {
        // 创建 JFrame
        JFrame frame = new JFrame("Menu Example");

        // 设置关闭操作和大小
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);

        // 创建菜单条
        JMenuBar menuBar = new JMenuBar();

        // 创建文件菜单及其菜单项
        JMenu fileMenu = new JMenu("File");

        // 创建菜单项并添加事件处理
        JMenuItem openMenuItem = new JMenuItem();
        openMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 打开文件对话框的操作，这里做简单输出
                System.out.println("Open menu item clicked");
            }
        });
        fileMenu.add(openMenuItem);

        JMenuItem saveMenuItem = new JMenuItem("Save");
        saveMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 保存文件的操作，这里做简单输出
                System.out.println("Save menu item clicked");
            }
        });
        fileMenu.add(saveMenuItem);

        JMenuItem exitMenuItem = new JMenuItem("Exit");
        exitMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 退出程序的操作
                System.exit(0);
            }
        });
        fileMenu.add(exitMenuItem);

        // 创建编辑菜单及其菜单项
        JMenu editMenu = new JMenu("Edit");

        JMenuItem cutMenuItem = new JMenuItem("Cut");
        cutMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 执行剪切操作，这里做简单输出
                System.out.println("Cut menu item clicked");
            }
        });
        editMenu.add(cutMenuItem);

        JMenuItem copyMenuItem = new JMenuItem("Copy");
        copyMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 执行复制操作，这里做简单输出
                System.out.println("Copy menu item clicked");
            }
        });
        editMenu.add(copyMenuItem);

        JMenuItem pasteMenuItem = new JMenuItem("Paste");
        pasteMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 执行粘贴操作，这里做简单输出
                System.out.println("Paste menu item clicked");
            }
        });
        editMenu.add(pasteMenuItem);

        // 把菜单添加到菜单条
        menuBar.add(fileMenu);
        menuBar.add(editMenu);

        // 把菜单条添加到 JFrame
        frame.setJMenuBar(menuBar);

        // 设置 JFrame 可见
        frame.setVisible(true);
    }
}

public class Main{
    public static void main(String[] args) {
        new MenuExample();
    }
}
```
