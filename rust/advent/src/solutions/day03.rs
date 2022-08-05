pub fn part_one(input: &str) -> u32 {
    let count: u32 = input.lines().count() as u32;
    input
        .lines()
        .map(|line| u32::from_str_radix(line, 2).unwrap())
        .fold(vec![0; 5], |vec, bits| {
            vec.into_iter()
                .enumerate()
                .map(|(i, val)| val + ((bits & 1 << i) >> 1))
                .collect()
        })
        .into_iter()
        .enumerate()
        .map(|(i, val)| ((val >= count / 2) as u32) << i)
        .sum::<u32>()
}

pub fn part_two(input: &str) -> u32 {
    2
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn part_one_test() {
        let input = crate::read_file("src/examples", 3);
        assert_eq!(part_one(&input), 22)
    }
}
