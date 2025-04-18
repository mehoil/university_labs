﻿namespace Lab0_5 
{
    /**
     * A square. Inheritor of [Figure]. 
     */
    public class Square : Figure 
    {
        
        private double side;
        public double Side 
        {
            get => side;
            set //todo readonly!
            {
                if (value > 0)
                {
                    side = value;
                }
            }
        }

        public Square(double side) 
        {
            this.side = side;
        }

        public override double CalculateArea() 
        {
            return side * side;
        }

        public override double CalculatePerimeter() 
        {
            return 4 * side;
        }
        
        public override string ToString()
        {
            return $"Square (side = {side})" +
                   $"(P = {CalculatePerimeter()})(S = {CalculateArea()})";
        }
        
    }
}