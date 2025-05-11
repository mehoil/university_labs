use std::error::Error;
use std::fs::File;
use std::io::{BufRead, BufReader};
use plotters::prelude::*;

struct Smoother {
    x: Vec<f64>,
    y: Vec<f64>,
    yy: Vec<f64>,
    n: usize,
    ier: i32,
}

impl Smoother {
    fn new() -> Self {
        Smoother {
            x: Vec::new(),
            y: Vec::new(),
            yy: Vec::new(),
            n: 0,
            ier: 0,
        }
    }

    fn read_data(&mut self, filename: &str) -> Result<(), Box<dyn Error>> {
        let file = File::open(filename)?;
        let reader = BufReader::new(file);
        let mut lines = reader.lines();
        let n_line = lines.next().ok_or("Missing N")??;
        self.n = n_line.trim().parse::<usize>()?;
        self.x.clear();
        self.y.clear();
        for _ in 0..self.n {
            let line = lines.next().ok_or("Insufficient data lines")??;
            let parts: Vec<&str> = line.trim().split_whitespace().collect();
            if parts.len() != 2 {
                return Err("Invalid data format".into());
            }
            let x = parts[0].parse::<f64>()?;
            let y = parts[1].parse::<f64>()?;
            self.x.push(x);
            self.y.push(y);
        }
        Ok(())
    }

    fn smooth(&mut self) {
        self.ier = 0;
        if self.n < 3 {
            self.yy = self.y.clone();
            return;
        }
        // Check if X is sorted
        for i in 1..self.n {
            if self.x[i] <= self.x[i - 1] {
                self.ier = 2;
                return;
            }
        }
        self.yy = vec![0.0; self.n];
        self.yy[0] = self.y[0];
        self.yy[self.n - 1] = self.y[self.n - 1];
        for i in 1..self.n - 1 {
            let h0 = self.x[i] - self.x[i - 1];
            let h1 = self.x[i + 1] - self.x[i];
            let num = self.y[i - 1] * h1 * (h0 + h1)
                + self.y[i] * (h0 * h0 + h1 * h1)
                + self.y[i + 1] * h0 * (h0 + h1);
            let denom = 2.0 * (h0 * h0 + h0 * h1 + h1 * h1);
            self.yy[i] = num / denom;
        }
        // Check if YY == Y within tolerance
        let tolerance = 1e-12;
        let all_equal = self.yy.iter().zip(self.y.iter()).all(|(&yy, &y)| (yy - y).abs() < tolerance);
        if all_equal {
            self.ier = 1;
        }
    }

    fn print(&self) {
        println!("X = {:?}", self.x);
        println!("Y = {:?}", self.y);
        println!("\nIER = {}", self.ier);
        if self.ier != 2 {
            println!("YY = {:.5?}", self.yy);
        }
    }

    fn get_x(&self) -> &Vec<f64> {
        &self.x
    }

    fn get_y(&self) -> &Vec<f64> {
        &self.y
    }

    fn get_yy(&self) -> &Vec<f64> {
        &self.yy
    }

    fn get_n(&self) -> usize {
        self.n
    }

    fn get_ier(&self) -> i32 {
        self.ier
    }
}

fn plot_data(smoother: &Smoother, output_file: &str) -> Result<(), Box<dyn Error>> {
    if smoother.get_ier() == 2 {
        eprintln!("Cannot plot due to error in data.");
        return Ok(());
    }
    let root = BitMapBackend::new(output_file, (800, 600)).into_drawing_area();
    root.fill(&WHITE)?;

    let y_min = smoother.get_y().iter().chain(smoother.get_yy().iter()).fold(f64::INFINITY, |a, &b| a.min(b)) - 0.01;
    let y_max = smoother.get_y().iter().chain(smoother.get_yy().iter()).fold(f64::NEG_INFINITY, |a, &b| a.max(b)) + 0.01;

    let mut chart = ChartBuilder::on(&root)
        .caption("Результат Сглаживания", ("sans-serif", 50).into_font())
        .margin(5)
        .x_label_area_size(30)
        .y_label_area_size(30)
        .build_cartesian_2d(
            smoother.get_x()[0]..smoother.get_x()[smoother.get_n() - 1],
            y_min..y_max,
        )?;

    chart.configure_mesh().draw()?;

    chart
        .draw_series(smoother.get_x().iter().zip(smoother.get_y().iter()).map(|(&x, &y)| {
            Circle::new((x, y), 2, RED.filled())
        }))?
        .label("Исходные точки")
        .legend(|(x, y)| Circle::new((x + 10, y), 3, RED.filled()));

    chart
        .draw_series(LineSeries::new(
            smoother.get_x().iter().zip(smoother.get_y().iter()).map(|(&x, &y)| (x, y)),
            &RED,
        ))?
        .label("Исходная функция")
        .legend(|(x, y)| PathElement::new(vec![(x, y), (x + 20, y)], &RED));

    chart
        .draw_series(LineSeries::new(
            smoother.get_x().iter().zip(smoother.get_yy().iter()).map(|(&x, &yy)| (x, yy)),
            &BLUE,
        ))?
        .label("Сглаженная функция")
        .legend(|(x, y)| PathElement::new(vec![(x, y), (x + 20, y)], &BLUE));

    chart
        .configure_series_labels()
        .background_style(&WHITE.mix(0.8))
        .border_style(&BLACK)
        .draw()?;

    root.present()?;
    Ok(())
}

fn main() -> Result<(), Box<dyn Error>> {
    println!("Enter the name of the source file: ");
    let mut file = String::new();
    std::io::stdin().read_line(&mut file)?;
    let file = file.trim();
    let mut smoother = Smoother::new();
    smoother.read_data(file)?;
    smoother.smooth();
    smoother.print();

    plot_data(&smoother, "smoothing_results.png")?;
    Ok(())
}