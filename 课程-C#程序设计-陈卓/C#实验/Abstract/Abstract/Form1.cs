namespace Abstract
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }



        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            label3.Text = "";
        }


        public abstract class Shape
        {
            protected double radius;
            public Shape(double radius)
            {
                this.radius = radius;
            }
            public abstract double Cubage();
        }
        public class Globe : Shape
        {
            public Globe(double radius) : base(radius) { }

            public override double Cubage()
            {
                return 3.14 * radius * radius * radius * 4.0 / 3.0;
            }
        }

        public class Cone : Shape
        {
            double h;
            public Cone(double radius, double h) : base(radius)
            {
                this.h = h;
            }

            public override double Cubage()
            {
                return 3.14 * radius * radius * h / 3.0;
            }
        }
        public class Cylinder : Shape
        {
            private double h;
            public Cylinder(double radius, double h) : base(radius)
            {
                this.h = h;
            }

            public override double Cubage()
            {
                return 3.14 * radius * radius * h;
            }
        }

        private void display(Shape shape)
        {
            label3.Text = "Ìå»ýÎª: " + shape.Cubage().ToString();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            double r = double.Parse(textBox1.Text);
            Globe g = new Globe(r);
            display(g);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            double r = double.Parse(textBox1.Text);
            double h = double.Parse(textBox2.Text);
            Cone cone = new Cone(r, h);
            display(cone);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            double r = double.Parse(textBox1.Text);
            double h = double.Parse(textBox2.Text);
            Cylinder cylinder = new Cylinder(r, h);
            display(cylinder);
        }
    }
}