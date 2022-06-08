fn main() {
    let (h, d, _) = include_str!("../input.txt")
        .lines()
        .map(|l| l.split_once(" ").unwrap())
        .fold((0, 0, 0), |(horizontal, depth, aim), (dir, dist)| {
            match (dir, dist.parse::<u32>().unwrap()) {
                ("forward", x) => (horizontal + x, depth + aim * x, aim),
                ("up", y) => (horizontal, depth, aim - y),
                ("down", y) => (horizontal, depth, aim + y),
                _ => unreachable!(),
            }
        });

    println!("{}", h * d);
}
