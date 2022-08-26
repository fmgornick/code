#![feature(drain_filter)]

pub fn part_one(input: &str) -> u32 {
    let width: usize = input.split_once('\n').unwrap().0.len();
    let count: u32 = input.lines().count() as u32;
    input
        .lines()
        .map(|line| u32::from_str_radix(line, 2).unwrap())
        .fold(vec![0; width], |vec, bits| {
            vec.into_iter()
                .enumerate()
                .map(|(i, val)| val + ((bits & 1 << i) >> i))
                .collect()
        })
        .into_iter()
        .enumerate()
        .map(|(i, val)| ((val >= count / 2) as u32) << i)
        .sum::<u32>()
}

pub fn part_two(input: &str) -> u32 {
    let width: usize = input.split_once('\n').unwrap().0.len();
    let nums = input
        .lines()
        .map(|line| u32::from_str_radix(line, 2).unwrap())
        .collect::<Vec<u32>>();

    let vecs = (nums.clone(), nums.clone());

    for i in (0..width).rev() {
        for j in 0..2 {
            let mut common =
                vecs.j.iter().filter(|&num| (num & 1 << i) > 0).count() >= (vecs.j.len() + 1) / 2;
            if j == 1 {
                common = !common;
            }
            k.retain(|&num| (num & 1 << i > 0) == common);
        }
    }
    vecs.first().unwrap().first().unwrap() * vecs.last().unwrap().last().unwrap()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn part_one_test() {
        let input = crate::read_file("src/examples", 3);
        assert_eq!(part_one(&input), 22)
    }

    #[test]
    fn part_two_test() {
        let input = crate::read_file("src/examples", 3);
        assert_eq!(part_two(&input), 230)
    }
}
