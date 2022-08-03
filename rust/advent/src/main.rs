use std::env;

use crate::solutions::*;
use advent::read_file;

mod solutions;

macro_rules! solve_day {
    ($day:path, $input:expr) => {{
        use $day::*;
        // print!("part 1: {}\n", print_result(part_one, $input));
        // print!("part 2: {}\n", print_result(part_two, $input));
        print!("penis");
    }};
}

pub fn main() {
    let args: Vec<String> = env::args().collect();
    let day: u8 = args[1].parse().unwrap();
    let input = read_file("inputs", day);

    match day {
        1 => solve_day!(day01, input),
        // 2 => solve_day!(day02, input),
        // 3 => solve_day!(day03, input),
        // 4 => solve_day!(day04, input),
        // 5 => solve_day!(day05, input),
        // 6 => solve_day!(day06, input),
        // 7 => solve_day!(day07, input),
        // 8 => solve_day!(day08, input),
        // 9 => solve_day!(day09, input),
        // 10 => solve_day!(day10, input),
        // 11 => solve_day!(day11, input),
        // 12 => solve_day!(day12, input),
        // 13 => solve_day!(day13, input),
        // 14 => solve_day!(day14, input),
        // 15 => solve_day!(day15, input),
        // 16 => solve_day!(day16, input),
        // 17 => solve_day!(day17, input),
        // 18 => solve_day!(day18, input),
        // 19 => solve_day!(day19, input),
        // 20 => solve_day!(day20, input),
        // 21 => solve_day!(day21, input),
        // 22 => solve_day!(day22, input),
        // 23 => solve_day!(day23, input),
        // 24 => solve_day!(day24, input),
        // 25 => solve_day!(day25, input),
        _ => print!("no solution for this day!!\n"),
    }
}
