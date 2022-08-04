use std::env;
use std::fmt::Display;

use crate::solutions::*;
use advent::read_file;

mod solutions;

fn print_result<T: Display>(func: impl FnOnce(&str) -> T, input: &str) {
    print!("{}\n", func(input));
}
macro_rules! solve {
    ($day:path, $input:expr) => {{
        use $day::*;
        print!("part one: ");
        print_result(part_one, $input);
        print!("part two: ");
        print_result(part_two, $input);
    }};
}

pub fn main() {
    let args: Vec<String> = env::args().collect();
    let day: u8 = args[1].parse().unwrap();
    let input = read_file("inputs", day);

    match day {
        1 => solve!(day01, &input),
        // 2 => solve!(day02, input),
        // 3 => solve!(day03, input),
        // 4 => solve!(day04, input),
        // 5 => solve!(day05, input),
        // 6 => solve!(day06, input),
        // 7 => solve!(day07, input),
        // 8 => solve!(day08, input),
        // 9 => solve!(day09, input),
        // 10 => solve!(day10, input),
        // 11 => solve!(day11, input),
        // 12 => solve!(day12, input),
        // 13 => solve!(day13, input),
        // 14 => solve!(day14, input),
        // 15 => solve!(day15, input),
        // 16 => solve!(day16, input),
        // 17 => solve!(day17, input),
        // 18 => solve!(day18, input),
        // 19 => solve!(day19, input),
        // 20 => solve!(day20, input),
        // 21 => solve!(day21, input),
        // 22 => solve!(day22, input),
        // 23 => solve!(day23, input),
        // 24 => solve!(day24, input),
        // 25 => solve!(day25, input),
        _ => print!("no solution for this day!!\n"),
    }
}
