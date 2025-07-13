import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class Main {
    @BeforeEach
    void setUp() {
        System.out.println("Execute before every Test method");
    }

    @Test
    public void addTest() {
        int A = 3, B = 2;
        int result = A + B;
        assertEquals(5, result, "结果应该是5");
    }

    @Test
    public void subTest() {
        int A = 3, B = 2;
        int result = A - B;
        assertEquals(1, result);
    }

    public static void main(String[] args) {
        // Main method can be used to run other logic if needed, but not for tests
    }

    @AfterEach
    public void tearDown() {
        System.out.println("Execute after every Test method");
    }
}
