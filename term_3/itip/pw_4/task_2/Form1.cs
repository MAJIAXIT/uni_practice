using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace task_2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = this.CreateGraphics();
            DrawCat(g);
        }
        private void DrawCat(Graphics g)
        {
            Pen pen = new Pen(Color.Black, 4);

            // Draw body
            Point[] shape = {
                 // paws
                 new Point(255, 265),
                 new Point(245, 310),
                 new Point(230, 310),
                 new Point(225, 265),
                 new Point(215, 310),
                 new Point(200, 310),
                 // left side 
                 new Point(195, 250),
                 new Point(200, 200),
                 new Point(185, 180),
                 new Point(185, 140),
                 // left ear
                 new Point(175, 100),
                 new Point(205, 115),
                 // head
                 new Point(230, 110),
                 new Point(255, 115),
                 // right ear
                 new Point(280, 100),
                 new Point(270, 140),
                 new Point(270, 180),
                 // Right side
                 new Point(255, 200),
                 new Point(300, 250),
                 new Point(310, 290),
                 // bottom
                 new Point(280, 305),
                 new Point(250, 300),
            };
            g.DrawCurve(pen, shape);

            Point[] tail = {
                new Point(310, 275),
                new Point(330, 270),
                new Point(335, 240),
                new Point(340, 235),
                new Point(350, 240),
                new Point(345, 265),
                new Point(335, 280),
                new Point(310, 285),
            };
            g.DrawCurve(pen, tail);

            // draw hind paw
            g.DrawEllipse(pen, 270, 260, 17, 45);

            // draw eyes
            g.FillEllipse(Brushes.Black, 200, 140, 10, 10);
            g.FillEllipse(Brushes.Black, 240, 140, 10, 10);

            Pen thinnerPen = new Pen(Color.Black, 2);
            // nose
            Point[] nose = {
                new Point(220, 160),
                new Point(225, 165),
                new Point(230, 160),
            };
            g.DrawCurve(thinnerPen, nose);

            // mouth
            Point[] mouthL = {
                new Point(225, 165),
                new Point(220, 170),
                new Point(215, 175),
                new Point(210, 168),
            };
            g.DrawCurve(thinnerPen, mouthL);

            Point[] mouthR = {
                new Point(225, 165),
                new Point(230, 170),
                new Point(235, 175),
                new Point(240, 168),
            };
            g.DrawCurve(thinnerPen, mouthR);

            // whiskers
            g.DrawCurve(thinnerPen, new Point[]{
                new Point(200, 160),
                new Point(180, 155),
            });
            g.DrawCurve(thinnerPen, new Point[]{
                new Point(200, 170),
                new Point(180, 165),
            });

            g.DrawCurve(thinnerPen, new Point[]{
                new Point(250, 160),
                new Point(270, 155),
            });
            g.DrawCurve(thinnerPen, new Point[]{
                new Point(250, 170),
                new Point(270, 165),
            });
        }
    }
}
