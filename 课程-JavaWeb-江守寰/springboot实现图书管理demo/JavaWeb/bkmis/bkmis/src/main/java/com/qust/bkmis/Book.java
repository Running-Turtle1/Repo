import javax.persistence.*;

@Entity
@Table(name = "book")
public class Book {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    @Column(name = "bookname")
    private String bookname;

    @Column(name = "author")
    private String author;

    @Column(name = "price")
    private float price;

    // Getters and Setters
}
