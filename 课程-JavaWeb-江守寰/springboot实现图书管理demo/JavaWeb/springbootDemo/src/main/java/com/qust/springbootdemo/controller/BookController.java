package com.qust.springbootdemo.controller;

import com.qust.springbootdemo.model.Book;
import com.qust.springbootdemo.mapper.BookMapper;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@Controller
public class BookController {

    @Autowired
    private BookMapper bookMapper;

    @GetMapping("/")
    public String getAllBooks(Model model) {
        List<Book> books = bookMapper.getAllBooks();
        model.addAttribute("books", books);
        return "book-list";
    }

    @GetMapping("/add")
    public String addBookForm() {
        return "add-book";
    }

    @PostMapping("/add")
    public String addBook(Book book) {
        bookMapper.insertBook(book);
        return "redirect:/";
    }

    @GetMapping("/edit/{id}")
    public String editBookForm(@PathVariable int id, Model model) {
        Book book = bookMapper.getBookById(id);
        model.addAttribute("book", book);
        return "edit-book";
    }

    @PostMapping("/edit")
    public String editBook(Book book) {
        bookMapper.updateBook(book);
        return "redirect:/";
    }

    @GetMapping("/delete/{id}")
    public String deleteBook(@PathVariable int id) {
        bookMapper.deleteBook(id);
        return "redirect:/";
    }
}
