package org.example;

public class DateUtil {
    /**    判断是否为闰年 **/
    public static boolean isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    /*** 判断输入的日期是否合法  */
    public static boolean isValidDate(int year, int month, int day) {
        if (year < 1900 || year > 2050) return false;
        if (month < 1 || month > 12) return false;

        int[] daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (isLeapYear(year)) {
            daysInMonth[1] = 29; // 闰年2月29天
        }

        return day >= 1 && day <= daysInMonth[month - 1];
    }
    /**  计算下一天  返回格式  YYYY年MM月DD日  */
    public static String nextDate(String y, String m, String d) {

        int year ;
        int month ;
        int day ;
        try {   /**  排除一些非数值的输入   例如年份为 "dsda" */
            year = Integer.parseInt(y);
            month = Integer.parseInt(m);
            day = Integer.parseInt(d);

        } catch (NumberFormatException e) {
            return "非法输入";
        }


        if(!isValidDate(year,month,day)){
            return "非法输入";
        }


        int[] daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // 处理闰年2月
        if (isLeapYear(year)) {
            daysInMonth[1] = 29;
        }

        // 增加一天
        day++;

        // 检查是否超过了当前月份的天数
        if (day > daysInMonth[month - 1]) {
            day = 1;
            month++;
            // 检查是否超过了12月
            if (month > 12) {
                month = 1;
                year++;
            }
        }

        return String.format("%d年%d月%d日", year, month, day);
    }

    public static void main(String[] args) {

    }
}
