fn main() {
    let gamma = include_str!("../input.txt")
        .lines()
        .map(|l| u32::from_str_radix(l, 2).expect("not binary"))
        .fold(vec![(0,0); 5], |(count0, count1), num| {})
    println!("Hello, world!");
}
