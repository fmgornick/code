fn main() {
    let count: usize = include_str!("../input.txt").lines().count();
    let width: usize = include_str!("../input.txt").lines().next().unwrap().len();

    let gamma: u32 = include_str!("../input.txt")
        .lines()
        .map(|l| usize::from_str_radix(l, 2).unwrap())
        .fold(vec![0; width], |cnt, bits| {
            cnt.into_iter()
                .enumerate()
                .map(|(i, n)| n + ((bits & 1 << i) >> i))
                .collect()
        })
        .into_iter()
        .enumerate()
        .map(|(i, b)| if b >= count / 2 { 1 << i } else { 0 })
        .sum();

    println!("{}", gamma * (!gamma & (1 << width) - 1));
}
