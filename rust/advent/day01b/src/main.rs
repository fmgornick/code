#![feature(array_windows)]

fn main() {
    println!(
        "{}",
        include_str!("../input.txt")
            .lines()
            .map(|n| n.parse().unwrap())
            .collect::<Vec<u32>>()
            .array_windows()
            .filter(|[a, _, _, d]| a < d)
            .count()
    );
}
