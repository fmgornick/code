fn main() {
    let (h, d) = include_str!("../input.txt")
        .lines()
        .map(|l| l.split_once(" ").unwrap())
        .fold((0, 0), |(horizontal, depth), (dir, dist)| {
            match (dir, dist.parse::<u32>().unwrap()) {
                ("forward", x) => (horizontal + x, depth),
                ("up", y) => (horizontal, depth - y),
                ("down", y) => (horizontal, depth + y),
                _ => unreachable!(),
            }
        });

    println!("{}", h * d);
}
