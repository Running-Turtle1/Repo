package com.qust.springbootdemo.mapper;

import com.qust.springbootdemo.model.Book;
import org.apache.ibatis.annotations.*;

import java.util.List;

@Mapper
public interface BookMapper {
    @Insert("INSERT INTO book(bookname, author, price) VALUES(#{bookname}, #{author}, #{price})")
    void insertBook(Book book);

    @Delete("DELETE FROM book WHERE id = #{id}")
    void deleteBook(int id);

    @Update("UPDATE book SET bookname = #{bookname}, author = #{author}, price = #{price} WHERE id = #{id}")
    void updateBook(Book book);

    @Select("SELECT * FROM book WHERE id = #{id}")
    Book getBookById(int id);

    @Select("SELECT * FROM book")
    List<Book> getAllBooks();
}
