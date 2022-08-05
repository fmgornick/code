pub fn part_one(input: &str) -> u32 {
    let (depth, horizontal) = input
        .lines()
        .map(|line| line.split_once(' ').unwrap())
        .fold((0, 0), |(depth, horizontal), (direction, val)| {
            let v: u32 = val.parse::<u32>().unwrap();
            match direction {
                "down" => (depth + v, horizontal),
                "up" => (depth - v, horizontal),
                "forward" => (depth, horizontal + v),
                _ => unreachable!(),
            }
        });
    depth * horizontal
}

pub fn part_two(input: &str) -> u32 {
    let (_, depth, horizontal) = input
        .lines()
        .map(|line| line.split_once(' ').unwrap())
        .fold((0, 0, 0), |(a, d, h), (dir, val)| {
            let v: u32 = val.parse::<u32>().unwrap();
            match dir {
                "down" => (a + v, d, h),
                "up" => (a - v, d, h),
                "forward" => (a, d + a * v, h + v),
                _ => unreachable!(),
            }
        });
    depth * horizontal
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn part_one_test() {
        let input = advent::read_file("src/examples", 2);
        assert_eq!(part_one(&input), 150)
    }

    #[test]
    fn part_two_test() {
        let input = advent::read_file("src/examples", 2);
        assert_eq!(part_two(&input), 900)
    }
}
