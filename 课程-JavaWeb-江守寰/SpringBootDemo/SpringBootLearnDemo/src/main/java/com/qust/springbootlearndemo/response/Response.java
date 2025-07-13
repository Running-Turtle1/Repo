package com.qust.springbootlearndemo.response;

/**
 * 泛型 <T> 代表该类的字段 data 可以存储任意类型的数据
 * 成功响应
 * Response<String> response = Response.newSuccess("操作成功");
 * 失败响应
 * Response<Void> response = Response.newFail("发生了错误");
 * 可以使用类型参数（如 T 或 k）来表示可以替代的类型。
 * <T> 和 <k> 都是泛型类型参数，它们的作用是相同的——它们都是用来表示一种可以灵活变化的类型，
 * 可以在方法调用时由编译器推断。不同的只是你在定义时使用的名字而已。
 * @param <T>
 */
public class Response <T>{
    private T data;
    private boolean success;
    private String errorMessage;

    public static <T>Response<T> newSuccess (T data) {
        Response<T> response = new Response<>();
        response.setData(data);
        response.setSuccess(true);
        return response;
    }

    public static Response<Void> newFail (String errorMessage) {
        Response<Void> response = new Response<>();
        response.setErrorMessage(errorMessage);
        response.setSuccess(false);
        return response;
    }

    public T getData() {
        return data;
    }

    public void setData(T data) {
        this.data = data;
    }

    public boolean isSuccess() {
        return success;
    }

    public void setSuccess(boolean success) {
        this.success = success;
    }

    public String getErrorMessage() {
        return errorMessage;
    }

    public void setErrorMessage(String errorMessage) {
        this.errorMessage = errorMessage;
    }
}
