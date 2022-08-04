pub fn part_one(input: &str) -> u32 {
    let mut depth: u32 = 0;
    let mut horizontal: u32 = 0;
    for line in input.lines() {
        match line.split_once(' ').map(|(d, x)| (d, x.parse::<u32>())) {
            Some(("forward", Ok(x))) => horizontal += x,
            Some(("down", Ok(x))) => depth += x,
            Some(("up", Ok(x))) => depth -= x,
            _ => print!("error parsing input!!\n"),
        }
    }
    depth * horizontal
}

pub fn part_two(input: &str) -> u32 {
    let mut aim: u32 = 0;
    let mut depth: u32 = 0;
    let mut horizontal: u32 = 0;
    for line in input.lines() {
        match line.split_once(' ').map(|(d, x)| (d, x.parse::<u32>())) {
            Some(("forward", Ok(x))) => {
                horizontal += x;
                depth += aim * x;
            }
            Some(("down", Ok(x))) => aim += x,
            Some(("up", Ok(x))) => aim -= x,
            _ => print!("error parsing input!!\n"),
        }
    }
    depth * horizontal
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn pt_one_test() {
        let input = advent::read_file("src/examples", 2);
        assert_eq!(part_one(&input), 150)
    }

    #[test]
    fn pt_two_test() {
        let input = advent::read_file("src/examples", 2);
        assert_eq!(part_two(&input), 900)
    }
}
