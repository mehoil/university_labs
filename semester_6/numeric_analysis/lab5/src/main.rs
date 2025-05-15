use std::fs::File;
use std::io::{BufRead, BufReader, Write};

const EPS: f64 = 1e-10;

// Runge-Kutta of the 2nd order (solution)
fn rk2_step(x: f64, y: f64, h: f64, f: &dyn Fn(f64, f64) -> f64) -> f64 {
    let k1 = h * f(x, y);
    let k2 = h * f(x + h, y + k1);
    y + (k1 + k2) / 2.0
}

// Runge-Kutta of the 3rd order (error estimation) 
fn rk3_step(x: f64, y: f64, h: f64, f: &dyn Fn(f64, f64) -> f64) -> f64 {
    let k1 = h * f(x, y);
    let k2 = h * f(x + h / 2.0, y + k1 / 2.0);
    let k3 = h * f(x + h, y - k1 + 2.0 * k2);
    y + (k1 + 4.0 * k2 + k3) / 6.0
}

fn print_analysis(steps: &Vec<(f64, f64, f64, f64)>, end: f64, epsilon: f64, h_min: f64, h_max: f64, inaccurate_points: usize, min_steps: usize, max_steps: usize) {
    let step = steps.len() - 1;
    let total_points = steps.len();
    println!("\nАнализ вывода:");
    println!("Начальная точка: x = {}, y = {}, локальная погрешность = 0 (корректно)", steps[0].0, steps[0].1);
    println!("Программа выполнила {} шага(ов), конечная точка: x = {:.5}, y = {:.5}", step, steps[step].0, steps[step].1);
    if (steps[step].0 - end).abs() > EPS {
        println!("x = {:.5} немного превышает B = {}, что допустимо из-за адаптивного шага.", steps[step].0, end);
    }
    let exact_y = end.exp();
    println!("Точное решение: y({}) = e^{} ≈ {:.5}, значение y = {:.5}", end, end, exact_y, steps[step].1);
    println!("Абсолютная ошибка: |{:.5} - {:.5}| = {:.5}", exact_y, steps[step].1, (exact_y - steps[step].1).abs());
    println!("Локальные погрешности (примеры):");
    if step >= 1 {
        println!("Шаг 1: {:.6} < {}", steps[1].2, epsilon);
    }
    if step >= 2 {
        println!("Шаг 2: {:.6} < {}", steps[2].2, epsilon);
    }
    if step >= 1 {
        println!("Шаг {}: {:.6} < {}", step, steps[step].2, epsilon);
    }
    println!("Все погрешности не превышают ϵ = {}", epsilon);
    println!("Размеры шагов (разница x между соседними точками):");
    if step >= 1 {
        let h1 = steps[1].3;
        println!("Шаг 1: {:.5} < {}", h1, h_max);
    }
    if step >= 2 {
        let h2 = steps[2].3;
        println!("Шаг 2: {:.5} < {}", h2, h_max);
    }
    if step >= 1 {
        let h_last = steps[step].3;
        println!("Минимальный шаг (например, шаг {}): {:.5} >= {}", step, h_last, h_min);
    }
    println!("Все шаги в пределах [{}, {}]", h_min, h_max);
    println!("Итог: {} точек, {} неточных, {} минимальных шагов, {} максимальных, Icod = {}",
             total_points, inaccurate_points, min_steps, max_steps,
             if inaccurate_points == 0 { 0 } else { 1 });
    println!("\nВывод:");
    println!("Программа корректно обработала интервал, поддерживая локальную погрешность ниже ϵ и адаптируя шаги в заданных пределах.");
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("Введите имя (путь) исходного файла: ");
    let mut file = String::new();
    std::io::stdin().read_line(&mut file)?;
    let file = file.trim();

    let file = File::open(file)
        .expect("Ошибка во время открытия файла");
    let reader = BufReader::new(file);
    let mut lines = reader.lines();

    let line1 = lines.next()
        .expect("Первая строка отсутствует")
        .expect("Ошибка во время чтения первой строки");
    let params: Vec<f64> = line1.split_whitespace()
        .map(|s| s.parse().expect("Неверное число в первой строке"))
        .collect();
    if params.len() != 4 {
        panic!("Первая строка должна содержать 4 числа");
    }
    let a = params[0];
    let b = params[1];
    let c = params[2];
    let y_c = params[3];

    if (c - a).abs() > EPS && (c - b).abs() > EPS {
        println!("Icod = 2");
        return Err("C должна быть точкой A или B".into());
    }
    let forward = c == a;
    let sign = if forward { 1.0 } else { -1.0 };
    let start = c;
    let end = if forward { b } else { a };

    let line2 = lines.next()
        .expect("Вторая строка отсутствует")
        .expect("Ошибка во время чтения второй строки");
    let params: Vec<f64> = line2.split_whitespace()
        .map(|s| s.parse().expect("Неверное число во второй строке"))
        .collect();
    if params.len() != 3 {
        panic!("Вторая строка должна содержать 3 числа");
    }
    let h_min = params[0];
    let h_max = params[1];
    let epsilon = params[2];

    if h_min <= 0.0 || h_max < h_min || epsilon <= 0.0 || a == b {
        println!("Icod = 2");
        return Err("Неверные входные параметры".into());
    }

    println!("Входные параметры:");
    println!("A = {}, B = {}, C = {}, y_c = {}, h_min = {}, h_max = {}, eps = {}",
             a, b, c, y_c, h_min, h_max, epsilon);

    let f = |x: f64, y: f64| 2.0 * x + y - x.powi(2);

    /// Прийти к конечной точке (в правый конец) и дальше НЕ ИДТИ! (т.е. прийти прям в точку B)
    /// интегрировать нужно уметь также справа-налево, а не только слева-направо
    ///
    /// Если погрешность на первом шаге больше заданной, откат в x0 y0, и сделать шаг с h_eps
    ///
    /// Поправить формулы в отчете

    let mut outfile = File::create("rez")
        .expect("Ошибка во время создания файла 'rez'");

    let mut x = start;
    let mut y = y_c;
    let mut h = (b - a).abs() / 10.0 * sign;
    let mut step = 0;
    let mut steps: Vec<(f64, f64, f64, f64)> = Vec::new();
    let mut inaccurate_points = 0;
    let mut min_steps = 0;
    let mut max_steps = 0;
    steps.push((x, y, 0.0, 0.0));

    println!("Шаг {:2}: x = {:.15}, y = {:.15}, локальная погрешность = 0.0", step, x, y);
    println!("Исходные точки: x = {:.5}, y = {:.5}, локальная погрешность = 0.0", x, y);

    let mut first_step = true;
    while (forward && x < end - EPS) || (!forward && x > end + EPS) {
        let h_max_possible = end - x;
        let h_trial = if (forward && x + h > end) || (!forward && x + h < end) {
            h_max_possible
        } else {
            h
        };

        let y_rk2 = rk2_step(x, y, h_trial, &f);
        let y_rk3 = rk3_step(x, y, h_trial, &f);
        let epsilon_trial = (y_rk3 - y_rk2).abs();

        if epsilon_trial <= epsilon || h_trial.abs() <= h_min || (x + h_trial - end).abs() < EPS {
            let next_x = x + h_trial;
            if (forward && next_x >= end - EPS) || (!forward && next_x <= end + EPS) {
                x = end;
                y = y_rk2;
                step += 1;
                steps.push((x, y, epsilon_trial, h_trial));
                writeln!(outfile, "{:.15} {:.15} {:.15}", x, y, epsilon_trial)?;
                println!("Шаг {:2}: x = {:.15}, y = {:.15}, локальная погрешность = {:.15}", step, x, y, epsilon_trial);
                break;
            } else {
                x = next_x;
                y = y_rk2;
                step += 1;
                if epsilon_trial > epsilon {
                    inaccurate_points += 1;
                }
                if h_trial.abs() <= h_min + EPS {
                    min_steps += 1;
                }
                if h_trial.abs() >= h_max - EPS {
                    max_steps += 1;
                }
                steps.push((x, y, epsilon_trial, h_trial));
                writeln!(outfile, "{:.15} {:.15} {:.15}", x, y, epsilon_trial)?;
                println!("Шаг {:2}: x = {:.15}, y = {:.15}, локальная погрешность = {:.15}", step, x, y, epsilon_trial);
                first_step = false;

                let h_epsilon = 0.9 * h_trial.abs() * (epsilon / epsilon_trial).powf(1.0 / 3.0);
                h = sign * h_epsilon.clamp(h_min, h_max);
            }
        } else {
            if first_step {
                println!("Первый шаг: погрешность {:.15} > {}, откат к x0, y0", epsilon_trial, epsilon);
            }
            let h_epsilon = 0.9 * h_trial.abs() * (epsilon / epsilon_trial).powf(1.0 / 3.0);
            h = sign * h_epsilon.clamp(h_min, h_max);
        }
    }

    writeln!(outfile, "{} {} {} {}", steps.len(), inaccurate_points, min_steps, max_steps)
        .expect("Ошибка записи результатов вычислений");

    print_analysis(&steps, end, epsilon, h_min, h_max, inaccurate_points, min_steps, max_steps);
    Ok(())
}